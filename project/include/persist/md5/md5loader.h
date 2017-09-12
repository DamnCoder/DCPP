//
//	md5loader
//	DCPP
//
//	Created by Jorge López González on 23/06/2017 10:43:01.
//

#ifndef CMD5LOADER_H
#define CMD5LOADER_H

#include <pathie.hpp>

#include <map>
#include <queue>

#include <math/vector2.h>
#include <math/vector3.h>
#include <math/quaternion.h>

#include "assets/assetmanager.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	class CGameObject;
	class CMesh;
	
	class CTokenHandler
	{
	public:
		const bool HasTokens() const
		{
			return !m_tokenQueue.empty();
		}
		
	public:
		CTokenHandler(const std::queue<std::string>& tokenQueue): m_tokenQueue(tokenQueue)
		{}
		
	public:
		void Clear()
		{
			std::queue<std::string> empty;
			std::swap(m_tokenQueue, empty);
		}
		
		const std::string Consume()
		{
			const std::string token = m_tokenQueue.front();
			m_tokenQueue.pop();
			return token;
		}
		
		const unsigned int ConsumeInt()
		{
			return std::stoi(Consume());
		}
		
		const unsigned int ConsumeUInt()
		{
			return std::stoul(Consume());
		}
		
		const float ConsumeFloat()
		{
			return std::stof(Consume());
		}
		
		const math::Vector2f ConsumeVector2f()
		{
			return math::Vector2f(ConsumeFloat(), ConsumeFloat());
		}
		
		const math::Vector3f ConsumeVector3f()
		{
			return math::Vector3f(ConsumeFloat(), ConsumeFloat(), ConsumeFloat());
		}
		
		const math::Quaternionf ConsumeQuaternionf()
		{
			return math::Quaternionf(ConsumeFloat(), ConsumeFloat(), ConsumeFloat());
		}
		
		const Pathie::Path ConsumePath()
		{
			Pathie::Path path;
			while(HasTokens())
			{
				const std::string token = m_tokenQueue.front();
				m_tokenQueue.pop();
				path.append(token);
			}
			
			return path;
		}
		
	private:
		std::queue<std::string> m_tokenQueue;
	};
	
	/**
	 * \class CMD5Loader
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CMD5Loader
{
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
private:
	struct TMD5Joint
	{
		// The name of this bone.
		std::string			boneName;
		
		// The index of this bone’s parent (-1 if root).
		int					parentIndex;
		
		math::Vector3f		position;
		
		math::Quaternionf	orientation;
	};
	
	struct TMD5Vertex
	{
		math::Vector2f	uv;
		
		// The index into the weight array where this vertex’s first weight is located.
		unsigned int	firstWeight;
		
		// The number of elements in the weight array that apply to this vertex.
		unsigned int	numWeights;
		
	};
	
	struct TMD5Face
	{
		unsigned int vertexIndex[3];
	};
	
	struct TMD5Weight
	{
		// The index of the joint to which this weight applies
		unsigned int	joint;
		
		float			bias;
		
		math::Vector3f	position;
	};
	
	struct TMD5Mesh
	{
		std::string				name;
		std::vector<TMD5Vertex> vertices;
		std::vector<TMD5Face>	faces;
		std::vector<TMD5Weight>	weights;
	};
	
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
private:
	
	using TMD5JointList	= std::vector<TMD5Joint>;
	using TMD5MeshList	= std::vector<TMD5Mesh>;
	
	const std::string	MD5MESH_EXT		= ".md5mesh";
	const std::string	MD5ANIM_EXT		= ".md5anim";
	
	const char*			MD5TOKEN_PARAMS	= " \n(){}\t\"";
	
	const std::string	VERSION_KEY		= "MD5Version";
	const std::string	NUMJOINTS_KEY	= "numJoints";
	const std::string	NUMMESHES_KEY	= "numMeshes";
	const std::string	JOINTS_KEY		= "joints";
	const std::string	MESH_KEY		= "mesh";
	
	const std::string	SHADER			= "shader";
	const std::string	NUMVERTS		= "numverts";
	const std::string	NUMFACES		= "numtris";
	const std::string	NUMWEIGHTS		= "numweights";
	const std::string	VERT			= "vert";
	const std::string	FACE			= "tri";
	const std::string	WEIGHT			= "weight";

	const std::string	END_BRACE		= "}";
	const std::string	COMMENT			= "//";
	
	const unsigned int	MD5_VERSION		= 10;
	
	// ===========================================================
	// Static fields / methods
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================
public:
	void ScaleFactor(const float scaleFactor)
	{
		m_scaleFactor = scaleFactor;
	}

	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CMD5Loader(CAssetManager& assetManager): m_assetManager(assetManager), m_scaleFactor(1.f / 16.f)
	{}

	~CMD5Loader()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================
public:
	CGameObject*	Load(const Pathie::Path& pathToModel);
	
private:
	CGameObject*	ReadMD5(const Pathie::Path& pathToModel, const std::string& filename);
	
	void			ReadMD5Joints(FILE* fp, std::vector<TMD5Joint>& joints);
	void			ReadMD5Mesh(FILE* fp, const Pathie::Path modelPath, TMD5Mesh& mesh);

	void			ProcessTexture(const std::string& texturePath);
	
	CGameObject*	CreateGO(const TMD5JointList& md5JointList, const TMD5MeshList& md5MeshList);
	
	const bool		IsValidVersion(const char* line);
	const bool		IsTag(const char* line, const std::string& tag);

	// ===========================================================
	// Fields
	// ===========================================================
private:
	CAssetManager	m_assetManager;
	float			m_scaleFactor;
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CMD5LOADER_H */
