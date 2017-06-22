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

#include "component/gameobject.h"
#include "component/modelcomponent.h"
#include "component/renderercomponent.h"

#include "help/utils.h"
#include "renderer/vertexproperty.h"

namespace dc
{
	const bool CMD3Loader::ValidateHeader(const tMd3Header& header) const
	{
		if(CheckMagicToken(header.ident))
		{
			printf("[CMD3Loader::Load] Invalid MD3 file: No magic token found in file\n");
			return false;
		}
		
		if(header.version != 15)
		{
			printf("[CMD3Loader::Load] Invalid MD3 file: Version not recognized\n");
			return false;
		}
		
		if(!header.numMeshes)
		{
			printf("[CMD3Loader::Load] Invalid MD3 file: Num meshes is 0\n");
			return false;
		}
		
		return true;
	}
	
	const bool CMD3Loader::CheckMagicToken(const char* token) const
	{
		return strcmp(token, "IDP3") == 0;
	}
	
	CGameObject* CMD3Loader::Load(const Pathie::Path& pathToModel)
	{
		if(pathToModel.size() == 0)
		{
			printf("[CMD3Loader::Load] File not found: %s!\n", pathToModel.c_str());
			return 0;
		}
		
		// We need the path to all the files, not the file
		if(pathToModel.is_file())
		{
			printf("[CMD3Loader::Load] To load MD3 it is needed only the folder with all the files\n");
			return 0;
		}
		
		const char* modelName = pathToModel.basename().c_str();
		printf("The model name is %s\n", modelName);
		
		CGameObject* md3MultipartModel = new CGameObject(modelName);
		CTransform* rootTransform = md3MultipartModel->Transform();
		
		CGameObject* lower = ReadMD3(pathToModel, "lower.md3");
		CGameObject* upper = ReadMD3(pathToModel, "upper.md3");
		CGameObject* head = ReadMD3(pathToModel, "head.md3");
		
		lower->Transform()->Rotation(math::Vector3f(-90.f, 0.f, 0.f));
		
		rootTransform->Add(lower->Transform());
		Link(lower, upper);
		Link(upper, head);
		
		return md3MultipartModel;
	}
	
	CGameObject* CMD3Loader::ReadMD3(const Pathie::Path& modelPath, const char* filename)
	{
		Pathie::Path filePath = modelPath.join(filename);
		
		const char* md3FilePath = filePath.c_str();
		
		// read binary file (rb)
		FILE* filePtr = fopen(md3FilePath, "rb");
		
		if(!filePtr)
		{
			printf("[CMD3Loader::Load] File not found: %s!\n", md3FilePath);
			return 0;
		}
		
		tMd3Header header;
		fread(&header, 1, sizeof(tMd3Header), filePtr);
		
		if(!ValidateHeader(header))
		{
			printf("[CMD3Loader::Load] Invalid MD3 file %s\n", md3FilePath);
			return 0;
		}
		
		char* filenameNoExt = GetFileExtension(filename);
		printf("[CMD3Loader::ReadMD3] Start reading %s\n", md3FilePath);
		
		CSkinLoader skinLoader(m_assetManager);
		TSkinMap skinMap = skinLoader.Load(modelPath, filenameNoExt);
		
		CGameObject* md3GO = CreateMD3GO(filePtr, header, skinMap, filenameNoExt);
		printf("[CMD3Loader::ReadMD3] GO name %s\n", md3GO->Name().c_str());
		
		free(filenameNoExt);
		fclose(filePtr);
		filePtr = 0;
		
		return md3GO;
	}
	
	CGameObject* CMD3Loader::CreateMD3GO(FILE* filePtr, const tMd3Header& header, const TSkinMap& skinMap, const char* name)
	{
		CGameObject* md3GO = new CGameObject(name);
		CModelComponent* modelComponent = md3GO->AddComponent<CModelComponent>();
		md3GO->AddComponent<CRendererComponent>();
		
		CTransform* md3Transform = md3GO->Transform();
		
		tMd3Frame* frames = new tMd3Frame [header.numFrames];
		fread(frames, sizeof(tMd3Frame), header.numFrames, filePtr);
		
		for(int i=0; i< header.numFrames; ++i)
		{
			//CBoundingBox bb = CBoundingBox(mp_Frames[i].minBounds, mp_Frames[i].maxBounds);
			//CBoundingSphere bs = CBoundingSphere(mp_Frames[i].localOrigin, mp_Frames[i].radius);
		}

		// Tags processing
		tMd3Tag tagArray[header.numTags];
		fread(&tagArray, sizeof(tMd3Tag), header.numTags, filePtr);

		// We create a game object for every tag, then whe will add it as child of the model game object
		for (int i = 0; i <header.numTags; ++i)
		{
			tMd3Tag& tag = tagArray[i];
			CGameObject* tagGO = new CGameObject(tag.name);
			CTransform* tagTrans = tagGO->Transform();
			
			math::Matrix4x4f m;
			m.Identify();
			m.m11 = tag.axis[0][0]; m.m12 = tag.axis[0][1]; m.m13 = tag.axis[0][2];
			m.m21 = tag.axis[1][0]; m.m22 = tag.axis[1][1]; m.m23 = tag.axis[1][2];
			m.m31 = tag.axis[2][0]; m.m32 = tag.axis[2][1]; m.m33 = tag.axis[2][2];
			
			m.Translate(tag.origin);
			
			tagTrans->LocalMatrix(m);
			
			md3Transform->Add(tagTrans);
		}
		
		//printf("Number of frames for animation: %d\n", header.numFrames);
		//printf("Number of link points for the model: %d\n", header.numTags);
		//printf("Number of meshes: %d\n", header.numMeshes);

		CModel* md3Model = new CModel();
		
		CArray<CMesh*> meshesArray(header.numMeshes);

		tMd3MeshHeader meshHeader;
		
		int accumMeshOffset = header.ofsMesh;
		for (int i = 0; i < header.numMeshes; ++i)
		{
			// Read the mesh header
			fseek(filePtr, accumMeshOffset, SEEK_SET);
			fread(&meshHeader, sizeof(tMd3MeshHeader), 1, filePtr);
			
			CMesh* mesh = CreateMesh(filePtr, meshHeader, accumMeshOffset);
			
			CShader* vertexShader = m_assetManager.ShaderManager().Get("mvp_tex.vert");
			CShader* fragmentShader = m_assetManager.ShaderManager().Get("textured.frag");
			
			CShaderProgram* shaderProg = CShaderProgram::Create(vertexShader, fragmentShader);
			
			CTexture* texture = 0;
			TSkinMap::const_iterator it = skinMap.find(mesh->Name());
			if(it != skinMap.end())
			{
				const std::string& textureName = it->second;
				texture = m_assetManager.TextureManager().Get(textureName);
			}
			
			CMaterial* material = new CMaterial(mesh->Name()+"_Material");
			material->AddProperty<CShaderProgram>("ShaderProgram", shaderProg);
			material->AddProperty<CTexture>("Texture", texture);
			material->AddProperty("Blending", EBlendMode::NORMAL);
			
			m_assetManager.MaterialManager().Add(material->Name(), material);

			md3Model->Add(material, mesh);
			
			
			// Set the offset to read the next mesh if there is any
			accumMeshOffset += meshHeader.ofsEnd;
		}
		
		modelComponent->Model(md3Model);
		
		return md3GO;
	}
	
	CMesh* CMD3Loader::CreateMesh(FILE* filePtr, const tMd3MeshHeader& meshHeader, const int meshOffset)
	{
		CMesh* mesh = new CMesh(meshHeader.name);
		
		// Initialize structures to hold the information of the mesh
		float uvArray[meshHeader.numVerts * 2];
		unsigned int iArray[meshHeader.numFaces * 3];
		
		TFloatArray vertexArray(meshHeader.numVerts * 3);
		TFloatArray normalArray(meshHeader.numVerts * 3);
		TFloatArray uvCoordArray(meshHeader.numVerts * 2);
		TFloatArray colorArray(meshHeader.numVerts * 4);
		TUIntArray	indexArray(meshHeader.numFaces * 3);
		
		// Materials
		tMd3Shader skinArray[meshHeader.numShaders];
		fread(&skinArray, sizeof(tMd3Shader), meshHeader.numShaders, filePtr);
		for(int i=0; i<meshHeader.numShaders; ++i)
		{
			//const tMd3Shader& shader = skinArray[i];
			//printf("Shader name: %s\n", shader.name);
			//printf("Shader index: %d\n", shader.shaderIndex);
		}
		
		// Indices
		fseek(filePtr, meshOffset + meshHeader.ofsFaces, SEEK_SET);
		fread(iArray, MD3_TRIANGLE_SIZE, meshHeader.numFaces, filePtr);
		indexArray.Append(iArray, meshHeader.numFaces * 3);
		
		// UVs
		fseek(filePtr, meshOffset + meshHeader.ofsUV, SEEK_SET);
		fread(uvArray, MD3_UV_SIZE, meshHeader.numVerts, filePtr);
		uvCoordArray.Append(uvArray, meshHeader.numVerts * 2);
		
		// Vertex, they need an adaptation
		tMd3Vertex md3VertexArray[meshHeader.numVerts];
		
		fseek(filePtr, meshOffset + meshHeader.ofsVert, SEEK_SET);
		fread(md3VertexArray, MD3_VERTEX_STRUCT_SIZE, meshHeader.numVerts, filePtr);
		
		unsigned int currentVertexSize = 0;
		for(unsigned int i = 0; i<meshHeader.numVerts; ++i)
		{
			const tMd3Vertex& md3Vertex = md3VertexArray[i];
			AdaptVertices(md3Vertex, vertexArray, normalArray, currentVertexSize);
			colorArray.Set(i*4, math::ColorRGBAf::White(), 4);
			currentVertexSize = vertexArray.Size();
		}
		
		// Assign the arrays to the mesh
		mesh->FloatDataArray(CVertexProperty::IN_VERTEX, vertexArray);
		mesh->FloatDataArray(CVertexProperty::IN_NORMAL, normalArray);
		mesh->FloatDataArray(CVertexProperty::IN_COLOR, colorArray);
		mesh->FloatDataArray(CVertexProperty::IN_UV0, uvCoordArray);
		mesh->IndexArray(indexArray);
		
		return mesh;
	}
	
	void CMD3Loader::AdaptVertices(const tMd3Vertex& md3Vertex, TFloatArray& vertexArray, TFloatArray& normalArray, const unsigned int currentVertexSize)
	{
		// We need to scale up the vertex coordinates and in the process we transform them into float
		vertexArray.Set(currentVertexSize, md3Vertex.coord[0] * MD3_SCALE_FACTOR);
		vertexArray.Set(currentVertexSize + 1, md3Vertex.coord[1] * MD3_SCALE_FACTOR);
		vertexArray.Set(currentVertexSize + 2, md3Vertex.coord[2] * MD3_SCALE_FACTOR);

		// We need to decode the normal because it comes expressed as polar coordinates
		math::Vector3f normal;
		normal.FromPolarAngles(md3Vertex.normal[0], md3Vertex.normal[1]);
		normalArray.Append(normal, 3);
	}
	
	void CMD3Loader::Link(CGameObject* lower, CGameObject* upper)
	{
		TTransformList lowerTagList = FindTags(lower->Transform());
		TTransformList upperTagList = FindTags(upper->Transform());
		
		for(auto* lowerTag : lowerTagList)
		{
			printf("[CMD3Loader::Link] Looking for tag %s\n", lowerTag->GameObject()->Name().c_str());
			CGameObject* tagGO = upper->FindChild(lowerTag->GameObject()->Name());
			if(tagGO)
			{
				printf("[CMD3Loader::Link] Link %s\n", tagGO->Name().c_str());
				upper->Transform()->Remove(tagGO->Transform());
				
				lowerTag->Add(upper->Transform());
			}
		}
	}
	
	TTransformList CMD3Loader::FindTags(const CTransform* md3Transform)
	{
		TTransformList tagList;
		const TTransformList& childrenList = md3Transform->Children();
		for(auto* child : childrenList)
		{
			if(IsInString(child->GameObject()->Name(), "tag_"))
			{
				tagList.push_back(child);
			}
		}
		return tagList;
	}
}
