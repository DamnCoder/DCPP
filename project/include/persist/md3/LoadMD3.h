/*
 * LoadMD3.h
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#ifndef LOADMD3_H_
#define LOADMD3_H_

#include "MD3structs.h"
#include "Model.h"

namespace dc
{

	class CLoadMD3
	{

	public:

		CLoadMD3();

		bool ImportMD3(tModel *pModel, const char *strFileName, const float scale);
		bool LoadSkin(tModel *pModel, tSkin* skin, const std::string& path, const std::string& name);

	private:

		void ReadMD3Data(tModel *pModel, const float scale);
		void Adapt(tModel *pModel, const tMd3MeshHeader& meshHeader, const float scale);
		void CleanUp();

		FILE*			m_FilePointer;

		tMd3Header		m_Header;			// The header data
		tMd3Shader*		m_pSkins;			// The skin name data (not used)
		tMd3TexCoord*	m_pTexCoords;		// The texture coordinates
		tMd3Face*		m_pTriangles;		// Face/Triangle data
		tMd3Vertex*		m_pVertices;		// Vertex/UV indices
		tMd3Frame*		m_pFrames;			// This stores the bone data (not used)
	};

}

#endif /* LOADMD3_H_ */
