//
//	objloader.h
//	DCPP
//
//	Created by Jorge López on 26/4/17
//

#include "objloader.h"

#include <cmath>
#include <dirent.h>

#include "renderer/vertexproperty.h"
#include "mesh/mesh.h"

#include <math/vector.h>

namespace dc
{
	CArray<CMesh*> CObjLoader::Load(const char* modelPath)
	{
		FILE* fp = fopen(modelPath, "r");
		
		if(!fp)
		{
			printf("File not found: %s!\n", modelPath);
			return 0;
		}
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		char header[2];
		char nameBuffer[255] = { "Mesh" };
		
		// Obj indices
		unsigned int vertexIndex[3];
		unsigned int normalIndex[3];
		unsigned int uvIndex[3];
		
		// To store and merge Obj indices
		TFaceList faceList;
		TIndexMap indexMap;
		TIndexMap::iterator it;
		unsigned int combinedIndex = 0;
		unsigned int nextIndex = 0;
		
		CArray<math::Vector3f> tempVertexArray;
		CArray<math::Vector3f> tempNormalArray;
		math::Vector3f vertex;
		
		CArray<math::Vector2f> tempUVArray;
		math::Vector2f uv;
		
		
		while ((read = getline(&line, &len, fp)) != -1)
		{
			sscanf(line, "%s", header);
			if(strcmp(header, "o") == 0)
			{
				sscanf(line, "%*s %s", nameBuffer);
				printf("Name: %s \n", nameBuffer);
			}
			else if(strcmp(header, "v") == 0)
			{
				sscanf(line, "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				
				tempVertexArray.Append(vertex);
				
				//printf("V %f %f %f\n", vertex[0], vertex[1], vertex[2]);
			}
			else if(strcmp(header, "vt") == 0)
			{
				sscanf(line, "%*s %f %f", &uv.x, &uv.y);
				
				tempUVArray.Append(uv);
				
				//printf("VT %f %f\n", uv[0], uv[1]);
			}
			else if(strcmp(header, "vn") == 0)
			{
				sscanf(line, "%*s %f %f %f", &vertex.x, &vertex.y, &vertex.z);
				
				tempNormalArray.Append(vertex);
				
				//printf("VN %f %f %f\n", vertex[0], vertex[1], vertex[2]);
			}
			else if(strcmp(header, "f") == 0)
			{
				sscanf(line, "%*s %d%*c%d%*c%d %d%*c%d%*c%d %d%*c%d%*c%d",
					   &vertexIndex[0], &uvIndex[0], &normalIndex[0],
					   &vertexIndex[1], &uvIndex[1], &normalIndex[1],
					   &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				
				// Find common vertices and merge them
				for(unsigned int i=0; i<3; ++i)
				{
					TPackedIndex packedIndex(vertexIndex[i]-1, uvIndex[i]-1, normalIndex[i]-1);
					
					faceList.push_back(packedIndex);
					
					it = indexMap.find(packedIndex);
					
					if(it != indexMap.end())
					{
						combinedIndex = it->second;
					}
					else
					{
						indexMap[packedIndex] = nextIndex;
						//printf("%d %d %d -> %d\n", packedIndex.iv, packedIndex.ivt, packedIndex.ivn, nextIndex);
						++nextIndex;
					}
				}

			}
			//printf("Retrieved line of length %zu :\n", read);
			//printf("%s", line);
		}
		
		fclose(fp);
		if (line)
			free(line);
		
		unsigned int size = tempVertexArray.Size();
		unsigned int type = 0;
		
		if(size < tempUVArray.Size())
		{
			size = tempUVArray.Size();
			type = 1;
		}
		
		if(size < tempNormalArray.Size())
		{
			size = tempNormalArray.Size();
			type = 2;
		}

		// Arrays for mesh
		TFloatArray vertexArray(size * 3);
		TFloatArray uvArray(size * 2);
		TFloatArray normalArray(size * 3);
		TFloatArray colorArray(size * 4);
		
		TUIntArray	indexArray(size);
		
		printf("Size of lists %u\n", size);
		for(const TPackedIndex face : faceList)
		{
			unsigned int index = 0;
			
			// If the bigger list are vertices
			if(type == 0)
			{
				index = face.iv;
			}
			// If the bigger list are texture coordinates
			else if (type == 1)
			{
				index = face.ivt;
			}
			// If the bigger list are normals
			else if (type == 3)
			{
				index = face.ivn;
			}
			
			printf("%d %d %d\n", face.iv, face.ivt, face.ivn);
			
			indexArray.Append(index);
			
			const math::Vector3f& v = tempVertexArray[face.iv];
			vertexArray.Set(index*3, v, 3);
			//const float* vArray = vertexArray.At(index, 3);
			//printf("V %f %f %f\n", vArray[0], vArray[1], vArray[2]);
			
			const math::Vector2f& vt = tempUVArray[face.ivt];
			uvArray.Set(index*2, vt, 2);
			
			const math::Vector3f& vn = tempNormalArray[face.ivn];
			normalArray.Set(index*3, vn, 3);
			
			colorArray.Set(index*4, math::ColorRGBAf::White(), 4);
			//printf("VT %d %f %f\n", index, vt[0], vt[1]);
		}
		/*
		for(int i=0; i<vertexArray.Size(); i+=3)
		{
			const float* vArray = vertexArray.At(i, 3);
			printf("V %f %f %f\n", vArray[0], vArray[1], vArray[2]);
			delete[] vArray;
		}
		
		for(int i=0; i<uvArray.Size(); i+=2)
		{
			const float* vArray = uvArray.At(i, 2);
			printf("VT %f %f\n", vArray[0], vArray[1]);
			delete[] vArray;
		}

		for(int i=0; i<normalArray.Size(); i+=3)
		{
			const float* vArray = normalArray.At(i, 3);
			printf("VN %f %f %f\n", vArray[0], vArray[1], vArray[2]);
			delete[] vArray;
		}
		
		for(int i=0; i<colorArray.Size(); i+=4)
		{
			const float* vArray = colorArray.At(i, 4);
			printf("VC %f %f %f %f\n", vArray[0], vArray[1], vArray[2], vArray[3]);
			delete[] vArray;
		}
		*/
		printf("Buffers size %u\n", vertexArray.Size()/3);
		printf("Num indices %u\n", indexArray.Size());

		CMesh* mesh = new CMesh(nameBuffer);
		mesh->VertexCount(size);
		mesh->FloatDataArray(CVertexProperty::IN_VERTEX, vertexArray);
		mesh->FloatDataArray(CVertexProperty::IN_NORMAL, normalArray);
		mesh->FloatDataArray(CVertexProperty::IN_COLOR, colorArray);
		mesh->FloatDataArray(CVertexProperty::IN_UV0, uvArray);
		mesh->IndexArray(indexArray);
		
		CArray<CMesh*> meshArray(1);
		meshArray.Append(mesh);
		return meshArray;
	}
}

