/*
 * LoadMD3.h
 *
 *  Created on: 24/04/2010
 *      Author: jorge
 */

#ifndef LOADMD3_H_
#define LOADMD3_H_

#include <pathie.hpp>

#include "assets/assetmanager.h"

#include "md3structs.h"
#include "md3skinloader.h"

#include "containers/array.h"

#include "component/transform.h"

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

	private:
		const bool ValidateHeader(const tMd3Header& header) const;
		const bool CheckMagicToken(const char* token) const;
		
	public:
		CMD3Loader(CAssetManager& assetManager): m_assetManager(assetManager) {}
		
	public:
		CGameObject*	Load(const Pathie::Path& pathToModel);
		
	private:
		CGameObject*	ReadMD3(const Pathie::Path& modelPath, const char* filename);
		
		CGameObject*	CreateMD3GO(FILE* filePtr, const tMd3Header& header, const TSkinMap& skinMap, const char* name);
		CMesh*			CreateMesh(FILE* filePtr, const tMd3MeshHeader& meshHeader, const int meshOffset);
		void			AdaptVertices(tMd3Vertex* md3VertexArray, TFloatArray* vertexArray, TFloatArray* normalArray, const unsigned int numElements);
		TTransformList	FindTags(const CTransform* md3Transform);
		void			Link(CGameObject* lower, CGameObject* upper);
		
	private:
		CAssetManager m_assetManager;
	};

}

#endif /* LOADMD3_H_ */
