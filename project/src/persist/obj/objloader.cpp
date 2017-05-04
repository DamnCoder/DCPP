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

#include <math/vector2.h>
#include <math/vector3.h>

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

		// Arrays for mesh
		TFloatArray vertexArray(indexMap.size() * 3);
		TFloatArray uvArray(indexMap.size() * 2);
		TFloatArray normalArray(indexMap.size() * 3);
		
		TUIntArray	indexArray(indexMap.size());
		
		printf("Num of indices %lu\n", indexMap.size());
		for(const auto& entry : indexMap)
		{
			const TPackedIndex& packedIndex = entry.first;
			const unsigned int index = entry.second;
			const math::Vector3f& v = tempVertexArray[packedIndex.iv];
			const math::Vector2f& vt = tempUVArray[packedIndex.ivt];
			const math::Vector3f& vn = tempNormalArray[packedIndex.ivn];
			
			vertexArray.Append(v, 3);
			uvArray.Append(vt, 2);
			normalArray.Append(vn, 3);
			indexArray.Append(index);
			
			printf("V %d %f %f %f\n", index, v[0], v[1], v[2]);
		}
		
		CMesh* mesh = new CMesh(nameBuffer);
		mesh->FloatDataArray(CVertexProperty::IN_VERTEX, vertexArray);
		mesh->FloatDataArray(CVertexProperty::IN_NORMAL, normalArray);
		mesh->FloatDataArray(CVertexProperty::IN_UV0, uvArray);
		mesh->IndexArray(indexArray);
		
		CArray<CMesh*> meshArray(1);
		meshArray.Append(mesh);
		return meshArray;
	}
}

