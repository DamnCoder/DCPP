//
//	md5loader
//	DCPP
//
//	Created by Jorge López González on 23/06/2017 10:43:01.
//

#include "md5loader.h"

#include <dirent.h>

#include "component/gameobject.h"
#include "component/modelcomponent.h"
#include "component/renderercomponent.h"

#include "persist/texture/textureloader.h"

#include "help/utils.h"
#include "renderer/vertexproperty.h"

#include <vector>

namespace dc
{
	const std::string FindFile(const Pathie::Path& path, const std::string& extension)
	{
		// Open directory
		DIR* dd = opendir (path.c_str());
		assert(dd && "[FindFile] The path doesn't exist");
		
		// Read the directory to find the file with the proper extension
		dirent* dit;
		
		while ((dit = readdir (dd)) != NULL)
		{
			const std::string filename (dit->d_name);
			
			if (filename.length () - extension.length () == filename.find (extension))
			{
				closedir(dd);
				
				return filename;
			}
		}
		
		closedir(dd);
		
		return "";
	}
	
	const CTokenHandler Tokenize(char* line, const char* tokens)
	{
		std::queue<string> tokenQueue;
		char* tokLine = strtok(line, tokens);
		while(tokLine)
		{
			tokenQueue.push(tokLine);
			tokLine = strtok(0, tokens);
		}
		
		return CTokenHandler(tokenQueue);
	}
	
	CGameObject* CMD5Loader::Load(const Pathie::Path& pathToModel)
	{
		if(pathToModel.size() == 0)
		{
			printf("[CMD5Loader::Load] File not found: %s!\n", pathToModel.c_str());
			return 0;
		}
		
		// We need the path to all the files, not the file
		if(pathToModel.is_file())
		{
			printf("[CMD5Loader::Load] To load MD3 it is needed only the folder with all the files\n");
			return 0;
		}
		
		const std::string fileName = FindFile(pathToModel, MD5MESH_EXT);
		printf("[CMD5Loader::Load] The file name is %s\n", fileName.c_str());
		
		CGameObject* modelGO = ReadMD5(pathToModel, fileName);
		return modelGO;
	}
	
	CGameObject* CMD5Loader::ReadMD5(const Pathie::Path& pathToModel, const std::string& filename)
	{
		const std::string modelName = pathToModel.basename().strRef();
		printf("[CMD5Loader::ReadMD5Mesh] The model name is %s\n", modelName.c_str());
		
		Pathie::Path modelPath = pathToModel.join(filename);
		
		FILE* fp = fopen(modelPath.c_str(), "r");
		
		if(!fp)
		{
			printf("[CMD5Loader::ReadMD5Mesh] File not found: %s!\n", modelPath.c_str());
			return 0;
		}
		
		TMD5JointList	jointList;
		TMD5MeshList	meshList;
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		while ((read = getline(&line, &len, fp)) != -1)
		{
			//printf("%s\n", line);
			
			if(IsTag(line, VERSION_KEY))
			{
				if(!IsValidVersion(line))
				{
					printf("[CMD5Loader::ReadMD5Mesh] Error MD5 version file not recognized!\n");
					return 0;
				}
			}
			else if(IsTag(line, NUMJOINTS_KEY))
			{
				char tag[255];
				unsigned int numJoints = 0;
				sscanf(line, "%s %d", tag, &numJoints);
				jointList.reserve(numJoints);
				printf("[CMD5Loader::ReadMD5Mesh] Num joints %d\n", numJoints);
			}
			else if(IsTag(line, NUMMESHES_KEY))
			{
				char tag[255];
				unsigned int numMeshes = 0;
				sscanf(line, "%s %d", tag, &numMeshes);
				meshList.reserve(numMeshes);
				printf("[CMD5Loader::ReadMD5Mesh] Num meshes %d\n", numMeshes);
			}
			else if(IsTag(line, JOINTS_KEY))
			{
				ReadMD5Joints(fp, jointList);
			}
			else if(IsTag(line, MESH_KEY))
			{
				TMD5Mesh mesh;
				ReadMD5Mesh(fp, modelPath, mesh);
				meshList.push_back(mesh);
			}
		}
		
		CGameObject* rootGO = new CGameObject(modelName);
		CGameObject* finalGO = CreateGO(jointList, meshList);
		
		rootGO->Transform()->Add(finalGO->Transform());
		return rootGO;
	}
	
	void CMD5Loader::ReadMD5Joints(FILE* fp, TMD5JointList& joints)
	{
		if(!fp)
		{
			printf("[CMD5Loader::ReadMD5Joints] File pointer is NULL!\n");
			return;
		}
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		while ((read = getline(&line, &len, fp)) != -1)
		{
			if(IsTag(line, END_BRACE))
			{
				return;
			}
			
			CTokenHandler tokenHandler = Tokenize(line, MD5TOKEN_PARAMS);
			
			while(tokenHandler.HasTokens())
			{
				TMD5Joint joint;
				
				std::string tag = tokenHandler.Consume();
				if(tag == COMMENT)
					break;
				
				joint.boneName = tag;
				joint.parentIndex = tokenHandler.ConsumeInt();
				joint.position = tokenHandler.ConsumeVector3f();
				joint.orientation = tokenHandler.ConsumeQuaternionf();
				
				joints.push_back(joint);
				
				printf("[CMD5Loader::ReadMD5Joints] %s %d ", joint.boneName.c_str(), joint.parentIndex);
				printf("(%f %f %f)", joint.position.x, joint.position.y, joint.position.z);
				printf("(%f %f %f)\n", joint.orientation.x, joint.orientation.y, joint.orientation.z);
				
				// We clear it to avoid comments
				tokenHandler.Clear();
			}
		}
	}
	
	void CMD5Loader::ReadMD5Mesh(FILE* fp, const Pathie::Path modelPath, TMD5Mesh& mesh)
	{
		if(!fp)
		{
			printf("[CMD5Loader::ReadMD5Mesh] File pointer is NULL!\n");
			return;
		}
		
		char * line = NULL;
		size_t len = 0;
		ssize_t read;
		
		while ((read = getline(&line, &len, fp)) != -1)
		{
			// End of the mesh
			if(IsTag(line, END_BRACE))
			{
				return;
			}
			else if(!IsTag(line, COMMENT))
			{
				CTokenHandler tokenHandler = Tokenize(line, MD5TOKEN_PARAMS);
				
				while(tokenHandler.HasTokens())
				{
					const std::string tag = tokenHandler.Consume();
					
					if(tag == COMMENT)
						break;
					
					//printf("[CMD5Loader::ReadMD5Mesh] Tag: %s\n", tag.c_str());
					if(tag == SHADER)
					{
						// Trying to load the typical Doom 3 textures:
						// nnn_local.tga  - normal map
						// nnn_h.tga      - height map
						// nnn_s.tga      - specular map
						// nnn_d.tga      - diffuse map
						const Pathie::Path shaderPath = tokenHandler.ConsumePath();
						
						const Pathie::Path texturePath = modelPath.merge(shaderPath);
						printf("[CMD5Loader::ReadMD5Mesh] Model path: %s\n", modelPath.c_str());
						printf("[CMD5Loader::ReadMD5Mesh] Shader path: %s\n", shaderPath.c_str());
						printf("[CMD5Loader::ReadMD5Mesh] Texture path: %s\n", texturePath.c_str());
						
						const std::string baseName = shaderPath.basename().str();
						mesh.name = baseName;
						
						ProcessTexture(texturePath.str() + ".tga");
						ProcessTexture(texturePath.str() + "_local.tga");
						ProcessTexture(texturePath.str() + "_h.tga");
						ProcessTexture(texturePath.str() + "_s.tga");
					}
					else if(tag == NUMVERTS)
					{
						unsigned int num = tokenHandler.ConsumeUInt();
						mesh.vertices.reserve(num);
						//printf("[CMD5Loader::ReadMD5Mesh] Num vertices %d\n", num);
					}
					else if(tag == NUMFACES)
					{
						unsigned int num = tokenHandler.ConsumeUInt();
						mesh.faces.reserve(num);
						//printf("[CMD5Loader::ReadMD5Mesh] Num faces %d\n", num);
					}
					else if(tag == NUMWEIGHTS)
					{
						unsigned int num = tokenHandler.ConsumeUInt();
						mesh.weights.reserve(num);
						//printf("[CMD5Loader::ReadMD5Mesh] Num weights %d\n", num);
					}
					else if(tag == VERT)
					{
						TMD5Vertex vertex;
						
						tokenHandler.Consume(); // We get rid of the index (they are ordered)
						
						vertex.uv = tokenHandler.ConsumeVector2f();
						vertex.firstWeight = tokenHandler.ConsumeUInt();
						vertex.numWeights = tokenHandler.ConsumeUInt();
						
						mesh.vertices.push_back(vertex);
						
						//printf("[CMD5Loader::ReadMD5Mesh] (%f %f) %d %d\n", vertex.uv.x, vertex.uv.y, vertex.firstWeight, vertex.numWeights);
					}
					else if(tag == FACE)
					{
						TMD5Face face;
						
						tokenHandler.Consume(); // We get rid of the index (they are ordered)
						
						face.vertexIndex[0] = tokenHandler.ConsumeUInt();
						face.vertexIndex[1] = tokenHandler.ConsumeUInt();
						face.vertexIndex[2] = tokenHandler.ConsumeUInt();
						
						mesh.faces.push_back(face);

						//printf("[CMD5Loader::ReadMD5Mesh] (%d %d %d)\n", face.vertexIndex[0], face.vertexIndex[1], face.vertexIndex[2]);
					}
					else if(tag == WEIGHT)
					{
						TMD5Weight weight;
						
						tokenHandler.Consume(); // We get rid of the index (they are ordered)
						
						weight.joint = tokenHandler.ConsumeUInt();
						weight.bias = tokenHandler.ConsumeFloat();
						weight.position = tokenHandler.ConsumeVector3f();
						
						mesh.weights.push_back(weight);
						
						//printf("[CMD5Loader::ReadMD5Mesh] %d %f (%f %f %f)\n", weight.joint, weight.bias, weight.position.x, weight.position.y, weight.position.z);
					}
				}
			}
		}
	}
	
	void CMD5Loader::ProcessTexture(const std::string& texturePath)
	{
		Pathie::Path path (texturePath);
		TTextureManager& textureManager = m_assetManager.TextureManager();
		CTextureLoader textureLoader;
		const std::string filename = path.basename().str();
		if(!textureManager.Exists(filename))
		{
			CTexture* texture = textureLoader.Load(path.c_str());
			if(texture == 0)
			{
				printf("[CMD5Loader::ProcessTexture] No texture in path %s\n", filename.c_str());
				return;
			}
			
			textureManager.Add(filename, texture);
		}
	}
	
	CGameObject* CMD5Loader::CreateGO(const TMD5JointList& md5JointList, const TMD5MeshList& md5MeshList)
	{
		CGameObject* go = new CGameObject("md5");
		go->Transform()->Rotation(math::Vector3f(-90.f, 0.f, 0.f));
		go->AddComponent<CRendererComponent>();
		CModelComponent* modelComponent = go->AddComponent<CModelComponent>();
		CModel* model = new CModel();
		modelComponent->Model(model);
		
		for(const auto& md5Mesh : md5MeshList)
		{
			const unsigned int vertexNum = md5Mesh.vertices.size();
			
			std::vector<math::Vector3f> vertexList(md5Mesh.vertices.size());
			std::vector<math::Vector3f> normalList(md5Mesh.vertices.size());
			std::vector<math::Vector2f> uvList(md5Mesh.vertices.size());
			std::vector<math::Vector3f> tangentList(md5Mesh.vertices.size());
			std::vector<math::Vector3f> bitangentList(md5Mesh.vertices.size());
			
			printf("[CMD5Loader::CreateGO] Calculating attributes for %s\n", md5Mesh.name.c_str());
			
			TFloatArray vertexArray(vertexNum * CVertexProperty::VERTEX_SIZE);
			TFloatArray normalArray(vertexNum * CVertexProperty::NORMAL_SIZE);
			TFloatArray uvCoordArray(vertexNum * CVertexProperty::UV_SIZE);
			TFloatArray colorArray(vertexNum * CVertexProperty::COLOR_SIZE);
			
			TUIntArray	indexArray(vertexNum * CVertexProperty::INDEX_SIZE);
			
			// Calculating final vertices
			for(int vi=0; vi < md5Mesh.vertices.size(); ++vi)
			{
				const TMD5Vertex& md5Vertex = md5Mesh.vertices[vi];
				
				const math::Vector2f& md5UV = md5Vertex.uv;
				
				// UV coordinates need to invert V component from D3D to OpenGL
				const math::Vector2f uv(md5UV.u, 1.f - md5UV.v);
				uvList[vi] = uv;
				
				uvCoordArray.Append(uv, CVertexProperty::UV_SIZE);
				
				// Calculation of mesh attributes from weights and joint
				math::Vector3f finalVertex;
				
				for(int wi=0; wi < md5Vertex.numWeights; ++wi)
				{
					const TMD5Weight& md5Weight = md5Mesh.weights[md5Vertex.firstWeight + wi];
					const TMD5Joint& md5Joint = md5JointList[md5Weight.joint];
					
					// Calculate transformed vertex for this weight
					math::Vector3f weightPos = md5Weight.position;
					md5Joint.orientation.Rotate(weightPos);
					
					finalVertex += (md5Joint.position + weightPos) * md5Weight.bias;
				}
				
				finalVertex *= m_scaleFactor;
				//PrintVector(finalVertex);
				
				vertexArray.Append(finalVertex, CVertexProperty::VERTEX_SIZE);
				colorArray.Append(math::Vector3f::White(), CVertexProperty::VERTEX_SIZE);
				
				vertexList[vi] = finalVertex;
			}
			
			// Calculating final normals, tangents and bitangents
			for(const auto& face : md5Mesh.faces)
			{
				indexArray.Append(face.vertexIndex, CVertexProperty::INDEX_SIZE);
				
				const math::Vector3f v1 = vertexList[face.vertexIndex[0]];
				const math::Vector3f v2 = vertexList[face.vertexIndex[1]];
				const math::Vector3f v3 = vertexList[face.vertexIndex[2]];
				
				math::Vector3f normal = math::Vector3f::ComputeNormal(v1, v2, v3);
				
				const math::Vector2f& uv1 = uvList[face.vertexIndex[0]];
				const math::Vector2f& uv2 = uvList[face.vertexIndex[1]];
				const math::Vector2f& uv3 = uvList[face.vertexIndex[2]];
				
				math::Vector3f dv1 = v2 - v1;
				math::Vector3f dv2 = v3 - v1;
				
				math::Vector2f dtc1 = uv2 - uv1;
				math::Vector2f dtc2 = uv3 - uv1;
				
				float r = dtc1.u * dtc2.v - dtc2.u * dtc1.v;
				
				// Prevent division by 0
				if(!r)
				{
					r = 1.f;
				}
				
				const float oneOverR = 1.f / r;
				
				math::Vector3f tangent = ((dv1 * dtc2.v) + (dv2 * -dtc1.v)) * oneOverR;
				math::Vector3f bitangent = math::Vector3f::CrossProduct(tangent, normal);
				
				normalList[face.vertexIndex[0]] = normal;
				normalList[face.vertexIndex[1]] = normal;
				normalList[face.vertexIndex[2]] = normal;
				
				tangentList[face.vertexIndex[0]] = tangent;
				tangentList[face.vertexIndex[1]] = tangent;
				tangentList[face.vertexIndex[2]] = tangent;
				
				bitangentList[face.vertexIndex[0]] = bitangent;
				bitangentList[face.vertexIndex[1]] = bitangent;
				bitangentList[face.vertexIndex[2]] = bitangent;
			}
			
			for(const auto& normal : normalList)
			{
				normalArray.Append(normal, CVertexProperty::NORMAL_SIZE);
			}

			CMesh* mesh = new CMesh(md5Mesh.name);
			
			mesh->FloatDataArray(CVertexProperty::IN_VERTEX, vertexArray);
			mesh->FloatDataArray(CVertexProperty::IN_NORMAL, normalArray);
			mesh->FloatDataArray(CVertexProperty::IN_COLOR, colorArray);
			mesh->FloatDataArray(CVertexProperty::IN_UV0, uvCoordArray);
			mesh->IndexArray(indexArray);
			
			CShader* vertexShader = m_assetManager.ShaderManager().Get("mvp_tex.vert");
			CShader* fragmentShader = m_assetManager.ShaderManager().Get("textured.frag");
			
			CShaderProgram* shaderProg = CShaderProgram::Create(vertexShader, fragmentShader);
			
			CTexture* texture = m_assetManager.TextureManager().Get(mesh->Name() + ".tga");
			
			CMaterial* material = new CMaterial(mesh->Name()+"_Material");
			material->AddProperty<CShaderProgram>("ShaderProgram", shaderProg);
			material->AddProperty<CTexture>("Texture", texture);
			material->AddProperty("Blending", EBlendMode::NORMAL);
			
			m_assetManager.MaterialManager().Add(material->Name(), material);
			
			model->Add(material, mesh);

		}
		
		return go;
	}
	
	const bool CMD5Loader::IsValidVersion(const char* line)
	{
		char tag[255];
		unsigned int version = 0;
		sscanf(line, "%s %d", tag, &version);
		return version == MD5_VERSION;
	}
	
	const bool CMD5Loader::IsTag(const char* line, const std::string& tag)
	{
		return strncmp(line, tag.c_str(), tag.length()) == 0;
	}
}
