/*
 * LoadMD3.cpp
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#include "md3loader.h"
//#include "gui/TextureManager.h"
#include <cmath>
#include <dirent.h>
#include "help/utils.h"

#include "renderer/vertexproperty.h"
#include "mesh/mesh.h"

namespace dc
{
	CMD3Loader::CMD3Loader()
	{
		memset(&m_Header, 0, sizeof(tMd3Header));

		m_FilePointer = 0;
		mp_Skins = NULL;
		mp_TexCoords = NULL;
		mp_Triangles = NULL;
		mp_Frames = NULL;
		mp_Vertices = 0;
	}

	CArray<CMesh*> CMD3Loader::Load(const char* modelPath)
	{
		DIR *dp;

		struct dirent *ep;
		dp = opendir ("./");

		if (dp != NULL)
		{
			do
			{
				ep = readdir (dp);
				if(ep)
				{
					puts (ep->d_name);
				}
			}
			while (ep);

			(void) closedir (dp);
		}
		else
			perror ("Couldn't open the directory");

		// read binary file (rb)
		FILE* filePtr = fopen(modelPath, "rb");
		
		if(!filePtr)
		{
			printf("File not found: %s!\n", modelPath);
			return 0;
		}
		
		tMd3Header header;
		fread(&header, 1, sizeof(tMd3Header), filePtr);
		
		const char* meshIdentifier = header.ident;
		
		if((meshIdentifier[0] != 'I' || meshIdentifier[1] != 'D' || meshIdentifier[2] != 'P' || meshIdentifier[3] != '3') || header.version != 15)
		{
			printf("Invalid file format (Version not 15): %s!\n", modelPath);
			return 0;
		}
		
		CArray<CMesh*> meshesArray = ReadModel(filePtr, header);
		
		fclose(filePtr);
		filePtr = 0;
		
		return meshesArray;
	}
	
	CArray<CMesh*> CMD3Loader::ReadModel(FILE* filePtr, const tMd3Header& header)
	{
		int i = 0;
		
		tMd3Frame* frames = new tMd3Frame [header.numFrames];
		tMd3Tag* pTags = new tMd3Tag [header.numFrames * header.numTags];
		
		fread(frames, sizeof(tMd3Frame), header.numFrames, filePtr);
		fread(pTags, sizeof(tMd3Tag), header.numFrames * header.numTags, filePtr);
		
		printf("Number of frames for animation: %d\n", header.numFrames);
		printf("Number of link points for the model: %d\n", header.numTags);
		printf("Number of meshes: %d\n", header.numMeshes);
		
		CArray<CMesh*> meshesArray(header.numMeshes);

		// Faces
		// Shaders
		// UV
		// Vertex

		tMd3MeshHeader meshHeader;
		
		// Information to read the binary data
		auto uvSize = sizeof(float) * 2;
		auto triangleSize = sizeof(unsigned int) * 3;
		auto vertexSize = sizeof(tMd3Vertex);
		
		int meshOffset = header.ofsMesh;
		for (i = 0; i < header.numMeshes; i++)
		{
			// Read the mesh header
			fseek(filePtr, meshOffset, SEEK_SET);
			fread(&meshHeader, sizeof(tMd3MeshHeader), 1, filePtr);
			
			CMesh* mesh = new CMesh(meshHeader.name);
			
			// Initialize structures to hold the information of the mesh
			TFloatArray vertexArray(meshHeader.numVerts * 3);
			TFloatArray normalArray(meshHeader.numVerts * 3);
			TFloatArray uvCoordArray(meshHeader.numVerts * 2);
			TUIntArray	indexArray(meshHeader.numFaces * 3);
			
			// Materials
			mp_Skins     = new tMd3Shader [meshHeader.numShaders];
			fread(mp_Skins, sizeof(tMd3Shader), meshHeader.numShaders, filePtr);
			
			// Indices
			fseek(filePtr, meshOffset + meshHeader.ofsFaces, SEEK_SET);
			fread(indexArray, triangleSize, meshHeader.numFaces, filePtr);
			
			// UVs
			fseek(filePtr, meshOffset + meshHeader.ofsUV, SEEK_SET);
			fread(uvCoordArray, uvSize, meshHeader.numVerts, filePtr);
			
			// Vertex, they need an adaptation
			tMd3Vertex md3VertexArray[meshHeader.numVerts];
			
			fseek(filePtr, meshOffset + meshHeader.ofsVert, SEEK_SET);
			fread(md3VertexArray, vertexSize, meshHeader.numVerts, filePtr);
			
			AdaptVertices(md3VertexArray, &vertexArray, &normalArray, meshHeader.numVerts);
			
			// Assign the arrays to the mesh
			mesh->FloatDataArray(CVertexProperty::IN_VERTEX, vertexArray);
			mesh->FloatDataArray(CVertexProperty::IN_NORMAL, normalArray);
			mesh->FloatDataArray(CVertexProperty::IN_UV0, uvCoordArray);
			mesh->IndexArray(indexArray);
			
			// Set the offset to read the next mesh if there is any
			meshOffset += meshHeader.ofsEnd;
		}
		
		return meshesArray;
	}
	
	void CMD3Loader::AdaptVertices(tMd3Vertex* md3VertexArray, TFloatArray* vertexArray, TFloatArray* normalArray, const unsigned int vertexNum)
	{
		for(unsigned int i = 0; i<vertexNum; ++i)
		{
			const tMd3Vertex& md3Vertex = md3VertexArray[i];

			// We need to scale up the vertex coordinates and in the process we transform them into float
			vertexArray->Set(i, md3Vertex.coord[0] * MD3_SCALE_FACTOR);
			vertexArray->Set(i + 1, md3Vertex.coord[1] * MD3_SCALE_FACTOR);
			vertexArray->Set(i + 2, md3Vertex.coord[2] * MD3_SCALE_FACTOR);
			
			// We need to decode the normal because it comes expressed as polar coordinates
			math::Vector3f normal;
			normal.FromPolarAngles(md3Vertex.normal[0], md3Vertex.normal[1]);
			normalArray->Append(normal, 3);
		}
	}
	
	bool CMD3Loader::ImportMD3(tModel *pModel, const char *strFileName, const float scale)
	{
		m_FilePointer = fopen(strFileName, "rb");

		if(!m_FilePointer)
		{
			printf("Unable to find the file: %s!\n", strFileName);
			return false;
		}

		fread(&m_Header, 1, sizeof(tMd3Header), m_FilePointer);

		char *ID = m_Header.ident;

		if((ID[0] != 'I' || ID[1] != 'D' || ID[2] != 'P' || ID[3] != '3') || m_Header.version != 15)
		{
			printf("Invalid file format (Version not 15): %s!\n", strFileName);
			return false;
		}

		ReadMD3Data(pModel, scale);

		CleanUp();

		return true;
	}
	
	/**
	 * Lee el archivo .skin y carga el skin de un modelo
	 * @param pModel
	 * @param path
	 * @param name
	 * @return
	 */
	bool CMD3Loader::LoadSkin(tModel *pModel, tSkin* skin, const std::string& path, const std::string& type)
	{
		if(!path.c_str())
			return false;
		
		std::ifstream fin(path.c_str());
		
		if(fin.fail())
			return false;
		
		std::string strLine;
		while(getline(fin, strLine))
		{
			for(int i = 0; i < pModel->numMeshes; i++)
			{
				//extern const bool IsInString(const std::string& strString, const std::string& strSubString);
				// Asociamos un material a una malla
				if(IsInString(strLine, pModel->meshes[i].name) )
				{
					std::string texturePath = (std::string)"./" + strLine.substr(strLine.find(",")+1, strLine.size());
					
					tMaterial material;
					strcpy(material.type, type.c_str());
					strcpy(material.filename, texturePath.c_str());
					//material.textureId = (int)CTextureCache::instance().loadTexture(texturePath);
					
					skin->materials[pModel->meshes[i].name] = material;
					
				}
			}
		}
		
		fin.close();
		return true;
	}

	void CMD3Loader::ReadMD3Data(tModel *pModel, const float scale)
	{
		int i = 0;

		mp_Frames = new tMd3Frame [m_Header.numFrames];
		fread(mp_Frames, sizeof(tMd3Frame), m_Header.numFrames, m_FilePointer);
		
		for(int i=0; i< m_Header.numFrames; ++i)
		{
			tBoundingVolumes volume;
			volume.bb = CBoundingBox(mp_Frames[i].minBounds, mp_Frames[i].maxBounds);
			volume.bs = CBoundingSphere(mp_Frames[i].localOrigin, mp_Frames[i].radius);
			pModel->volumes.push_back(volume);
		}

		tMd3Tag* pTags = new tMd3Tag [m_Header.numFrames * m_Header.numTags];
		fread(pTags, sizeof(tMd3Tag), m_Header.numFrames * m_Header.numTags, m_FilePointer);

		// Convertimos los tags del formato MD3 a unos tags propios que usan cuaternios
		for (i = 0; i <(m_Header.numFrames * m_Header.numTags); i++)
			pModel->tags.push_back(new tQuatTag(pTags[i]));

		delete [] pTags;


		pModel->numTags = m_Header.numTags;

		pModel->pLinks = (const tModel**) malloc(sizeof(tModel) * m_Header.numTags);

		for (i = 0; i < m_Header.numTags; i++)
			pModel->pLinks[i] = NULL;

		long meshOffset = ftell(m_FilePointer);

		tMd3MeshHeader meshHeader;

		for (i = 0; i < m_Header.numMeshes; i++)
		{
			fseek(m_FilePointer, meshOffset, SEEK_SET);
			fread(&meshHeader, sizeof(tMd3MeshHeader), 1, m_FilePointer);

			mp_Skins     = new tMd3Shader [meshHeader.numShaders];
			mp_TexCoords = new tMd3TexCoord [meshHeader.numVerts];
			mp_Triangles = new tMd3Face [meshHeader.numFaces];
			mp_Vertices  = new tMd3Vertex [meshHeader.numVerts * meshHeader.numFrames];

			fread(mp_Skins, sizeof(tMd3Shader), meshHeader.numShaders, m_FilePointer);

			fseek(m_FilePointer, meshOffset + meshHeader.ofsFaces, SEEK_SET);

			fread(mp_Triangles, sizeof(tMd3Face), meshHeader.numFaces, m_FilePointer);
			
			for(unsigned int i = 0; i<meshHeader.numFaces; ++i)
			{
				printf("%d ", mp_Triangles[i].indices[0]);
				printf("%d ", mp_Triangles[i].indices[1]);
				printf("%d ", mp_Triangles[i].indices[2]);
				printf("\n");
			}
			printf("\n");

			fseek(m_FilePointer, meshOffset + meshHeader.ofsUV, SEEK_SET);
			fread(mp_TexCoords, sizeof(tMd3TexCoord), meshHeader.numVerts, m_FilePointer);

			fseek(m_FilePointer, meshOffset + meshHeader.ofsVert, SEEK_SET);
			fread(mp_Vertices, sizeof(tMd3Vertex), meshHeader.numFrames * meshHeader.numVerts, m_FilePointer);

			Adapt(pModel, meshHeader, scale);

			delete [] mp_Skins;
			delete [] mp_TexCoords;
			delete [] mp_Triangles;
			delete [] mp_Vertices;
			
			mp_Skins     = 0;
			mp_TexCoords = 0;
			mp_Triangles = 0;
			mp_Vertices  = 0;

			meshOffset += meshHeader.ofsEnd;
		}

	}

	void CMD3Loader::Adapt(tModel* pModel, const tMd3MeshHeader& meshHeader, const float scale)
	{
		int i = 0;

		pModel->numMeshes++;

		tMesh currentMesh;

		strcpy(currentMesh.name, meshHeader.name);

		currentMesh.numVerts   = meshHeader.numVerts;
		currentMesh.numTexVerts = meshHeader.numVerts;
		currentMesh.numFaces   = meshHeader.numFaces;

		currentMesh.pVerts    = new math::Vector3f [currentMesh.numVerts * meshHeader.numFrames];
		currentMesh.pNormals  = new math::Vector3f[currentMesh.numVerts * meshHeader.numFrames];
		currentMesh.pTexVerts = new math::Vector3f [currentMesh.numVerts];
		currentMesh.pFaces    = new tFace [currentMesh.numFaces];

		currentMesh.drawVertArray = new math::Vector3f[currentMesh.numFaces*3];
		currentMesh.drawNormArray = new math::Vector3f[currentMesh.numFaces*3];

		for (i=0; i < currentMesh.numVerts * meshHeader.numFrames; i++)
		{
			currentMesh.pVerts[i].x =  mp_Vertices[i].coord[0] * MD3_SCALE_FACTOR;
			currentMesh.pVerts[i].y =  mp_Vertices[i].coord[1] * MD3_SCALE_FACTOR;
			currentMesh.pVerts[i].z =  mp_Vertices[i].coord[2] * MD3_SCALE_FACTOR;

			// Decodificamos la normal, que vienen expresadas como coordenadas polares
			math::Vector3f normal;
			normal.FromPolarAngles(mp_Vertices[i].normal[0], mp_Vertices[i].normal[1]);

			currentMesh.pNormals[i].x = normal.x;
			currentMesh.pNormals[i].y = normal.y;
			currentMesh.pNormals[i].z = normal.z;
		}

		for (i=0; i < currentMesh.numTexVerts; i++)
		{
			currentMesh.pTexVerts[i].x =  mp_TexCoords[i].uv[0];
			currentMesh.pTexVerts[i].y = -mp_TexCoords[i].uv[1];
		}

		for(i=0; i < currentMesh.numFaces; i++)
		{
			currentMesh.pFaces[i].indices[0] = mp_Triangles[i].indices[2];
			currentMesh.pFaces[i].indices[1] = mp_Triangles[i].indices[1];
			currentMesh.pFaces[i].indices[2] = mp_Triangles[i].indices[0];
		}

		pModel->meshes.push_back(currentMesh);
	}

	CMesh* CMD3Loader::Adapt(const tMd3MeshHeader& meshHeader, const float scale)
	{
		CMesh* mesh = new CMesh("name");
		//mesh->Initialize(meshHeader.numVerts, meshHeader.numFaces);
		
		// VERTEX / NORMAL
		const unsigned int vertexElementsCount = meshHeader.numVerts * 3;
		TFloatArray vertexArray (vertexElementsCount);
		TFloatArray normalArray (vertexElementsCount);
		
		unsigned int i = 0;
		for (i = 0; i < vertexElementsCount; i += 3)
		{
			vertexArray[i] = mp_Vertices[i].coord[0] * MD3_SCALE_FACTOR;
			vertexArray[i+1] = mp_Vertices[i].coord[1] * MD3_SCALE_FACTOR;
			vertexArray[i+2] = mp_Vertices[i].coord[2] * MD3_SCALE_FACTOR;
			
			// We need to decode the normal because it comes expressed as polar coordinates
			math::Vector3f normal;
			normal.FromPolarAngles(mp_Vertices[i].normal[0], mp_Vertices[i].normal[1]);
			
			normalArray[i] = normal.x;
			normalArray[i+1] = normal.y;
			normalArray[i+2] = normal.z;
		}
		
		// UV
		const unsigned int uvElementsCount = meshHeader.numVerts * 2;
		TFloatArray uv0Array (uvElementsCount);
		
		for (i = 0; i < uvElementsCount; i += 2)
		{
			uv0Array[i] =  mp_TexCoords[i].uv[0];
			uv0Array[i+1] = mp_TexCoords[i].uv[1];
		}
		
		// INDICES
		const unsigned int indicesCount = meshHeader.numFaces * 3;
		TUShortArray indices(indicesCount);
		
		for (i = 0; i < indicesCount; i += 3)
		{
			indices[i] = mp_Triangles[i].indices[2];
			indices[i+1] = mp_Triangles[i].indices[1];
			indices[i+2] = mp_Triangles[i].indices[0];
		}
		return mesh;
	}
	
	void CMD3Loader::CleanUp()
	{
		fclose(m_FilePointer);
	}

}
