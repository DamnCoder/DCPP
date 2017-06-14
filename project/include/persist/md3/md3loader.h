/*
 * LoadMD3.h
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#ifndef LOADMD3_H_
#define LOADMD3_H_

#include "md3structs.h"
#include "md3model.h"

#include "containers/array.h"

namespace dc
{
	class CGameObject;
	class CMesh;
	
	class CMD3Loader
	{
	private:
		const size_t UV_SIZE = sizeof(float) * 2;
		const size_t TRIANGLE_SIZE = sizeof(unsigned int) * 3;
		const size_t VERTEX_SIZE = sizeof(tMd3Vertex);

	public:
		CMD3Loader();
		
	public:
		CGameObject* Load(const char* pathToModel);
		
	private:
		const bool ValidateHeader(const tMd3Header& header) const;
		const bool CheckMagicToken(const char* token) const;
		
		CArray<CMesh*> ReadMD3(const char* md3FilePath);
		
		CArray<CMesh*> ReadModel(FILE* filePtr, const tMd3Header& header);
		CMesh* CreateMesh(FILE* filePtr, const tMd3MeshHeader& meshHeader, const int meshOffset);
		void AdaptVertices(tMd3Vertex* md3VertexArray, TFloatArray* vertexArray, TFloatArray* normalArray, const unsigned int numElements);
		
	public:
		bool OldImportMD3(tModel *pModel, const char *strFileName, const float scale);
		bool OldLoadSkin(tModel *pModel, tSkin* skin, const std::string& path, const std::string& name);

	private:
		void OldReadMD3Data(tModel *pModel, const float scale);
		void Adapt(tModel *pModel, const tMd3MeshHeader& meshHeader, const float scale);
		CMesh* Adapt(const tMd3MeshHeader& meshHeader, const float scale);
		void CleanUp();
		
		

		
	private:
		FILE*			m_FilePointer;

		tMd3Header		m_Header;			// The header data
		tMd3Shader*		mp_Skins;			// The skin name data (not used)
		tMd3TexCoord*	mp_TexCoords;		// The texture coordinates
		tMd3Face*		mp_Triangles;		// Face/Triangle data
		tMd3Vertex*		mp_Vertices;		// Vertex/UV indices
		tMd3Frame*		mp_Frames;			// This stores the bone data (not used)
	};

}

#endif /* LOADMD3_H_ */
