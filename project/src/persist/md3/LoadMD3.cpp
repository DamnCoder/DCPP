/*
 * LoadMD3.cpp
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#include "LoadMD3.h"
//#include "gui/TextureManager.h"
#include <cmath>
#include "help/utils.h"

namespace dc
{

	CLoadMD3::CLoadMD3()
	{
		memset(&m_Header, 0, sizeof(tMd3Header));

		m_pSkins=NULL;
		m_pTexCoords=NULL;
		m_pTriangles=NULL;
		m_pFrames=NULL;
	}

	bool CLoadMD3::ImportMD3(tModel *pModel, const char *strFileName, const float scale)
	{
		m_FilePointer = fopen(strFileName, "rb");

		if(!m_FilePointer)
		{
			printf("Unable to find the file: %s!", strFileName);
			return false;
		}

		fread(&m_Header, 1, sizeof(tMd3Header), m_FilePointer);

		char *ID = m_Header.ident;

		if((ID[0] != 'I' || ID[1] != 'D' || ID[2] != 'P' || ID[3] != '3') || m_Header.version != 15)
		{
			printf("Invalid file format (Version not 15): %s!", strFileName);
			return false;
		}

		ReadMD3Data(pModel, scale);

		CleanUp();

		return true;
	}

	void CLoadMD3::ReadMD3Data(tModel *pModel, const float scale)
	{
		int i = 0;

		m_pFrames = new tMd3Frame [m_Header.numFrames];
		fread(m_pFrames, sizeof(tMd3Frame), m_Header.numFrames, m_FilePointer);
		
		for(int i=0; i< m_Header.numFrames; ++i)
		{
			tBoundingVolumes volume;
			volume.bb = CBoundingBox(m_pFrames[i].minBounds, m_pFrames[i].maxBounds);
			volume.bs = CBoundingSphere(m_pFrames[i].localOrigin, m_pFrames[i].radius);
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

			m_pSkins     = new tMd3Shader [meshHeader.numShaders];
			m_pTexCoords = new tMd3TexCoord [meshHeader.numVerts];
			m_pTriangles = new tMd3Face [meshHeader.numFaces];
			m_pVertices  = new tMd3Vertex [meshHeader.numVerts * meshHeader.numFrames];

			fread(m_pSkins, sizeof(tMd3Shader), meshHeader.numShaders, m_FilePointer);

			fseek(m_FilePointer, meshOffset + meshHeader.ofsFaces, SEEK_SET);
			fread(m_pTriangles, sizeof(tMd3Face), meshHeader.numFaces, m_FilePointer);

			fseek(m_FilePointer, meshOffset + meshHeader.ofsUV, SEEK_SET);
			fread(m_pTexCoords, sizeof(tMd3TexCoord), meshHeader.numVerts, m_FilePointer);

			fseek(m_FilePointer, meshOffset + meshHeader.ofsVert, SEEK_SET);
			fread(m_pVertices, sizeof(tMd3Vertex), meshHeader.numFrames * meshHeader.numVerts, m_FilePointer);

			Adapt(pModel, meshHeader, scale);

			delete [] m_pSkins;
			delete [] m_pTexCoords;
			delete [] m_pTriangles;
			delete [] m_pVertices;

			meshOffset += meshHeader.ofsEnd;
		}

	}

	void CLoadMD3::Adapt(tModel* pModel, const tMd3MeshHeader& meshHeader, const float scale)
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

			currentMesh.pVerts[i].x =  m_pVertices[i].coord[0] * MD3_SCALE_FACTOR;
			currentMesh.pVerts[i].y =  m_pVertices[i].coord[1] * MD3_SCALE_FACTOR;
			currentMesh.pVerts[i].z =  m_pVertices[i].coord[2] * MD3_SCALE_FACTOR;

			// Decodificamos la normal, que vienen expresadas como coordenadas polares
			math::Vector3f normal;
			normal.FromPolarAngles(m_pVertices[i].normal[0], m_pVertices[i].normal[1]);

			currentMesh.pNormals[i].x = normal.x;
			currentMesh.pNormals[i].y = normal.y;
			currentMesh.pNormals[i].z = normal.z;
		}

		for (i=0; i < currentMesh.numTexVerts; i++)
		{
			currentMesh.pTexVerts[i].x =  m_pTexCoords[i].uv[0];
			currentMesh.pTexVerts[i].y = -m_pTexCoords[i].uv[1];
		}

		for(i=0; i < currentMesh.numFaces; i++)
		{
			currentMesh.pFaces[i].indices[0] = m_pTriangles[i].indices[2];
			currentMesh.pFaces[i].indices[1] = m_pTriangles[i].indices[1];
			currentMesh.pFaces[i].indices[2] = m_pTriangles[i].indices[0];
		}

		pModel->meshes.push_back(currentMesh);
	}

	/**
	 * Lee el archivo .skin y carga el skin de un modelo
	 * @param pModel
	 * @param path
	 * @param name
	 * @return
	 */
	bool CLoadMD3::LoadSkin(tModel *pModel, tSkin* skin, const std::string& path, const std::string& type)
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

	void CLoadMD3::CleanUp()
	{
		fclose(m_FilePointer);
	}

}
