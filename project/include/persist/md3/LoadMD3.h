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

namespace dc
{
	class CMesh;
	
	template<typename T>
	class CArray;
	
	using TFloatArray = CArray<float>;
	
	class CLoadMD3
	{

	public:

		CLoadMD3();
		
		CArray<CMesh*> Load(const char* modelPath);

		bool ImportMD3(tModel *pModel, const char *strFileName, const float scale);
		bool LoadSkin(tModel *pModel, tSkin* skin, const std::string& path, const std::string& name);

	private:

		void ReadMD3Data(tModel *pModel, const float scale);
		void Adapt(tModel *pModel, const tMd3MeshHeader& meshHeader, const float scale);
		CMesh* Adapt(const tMd3MeshHeader& meshHeader, const float scale);
		void CleanUp();
		
		CArray<CMesh*> ReadModel(FILE* filePtr, const tMd3Header& header);
		void AdaptVertices(tMd3Vertex* md3VertexArray, TFloatArray* vertexArray, TFloatArray* normalArray, const unsigned int numElements);

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
