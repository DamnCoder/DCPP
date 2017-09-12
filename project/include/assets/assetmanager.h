//
//	assetmanager
//	DCPP
//
//	Created by Jorge López González on 25/05/2017 14:13:35.
//

#ifndef CASSETMANAGER_H
#define CASSETMANAGER_H

#include <unordered_map>

#include <pathie.hpp>

#include "material/materialmanager.h"
#include "material/shadermanager.h"
#include "material/texturemanager.h"
#include "mesh/meshmanager.h"

#include "component/gameobject.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TGameObjectManager = CProxy<CGameObject>;
	
	/**
	 * \class CAssetManager
	 * \brief
	 * \author Jorge López González
	 *
	 * Description.
	 */
class CAssetManager
{
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================

	// ===========================================================
	// Static fields / methods
	// ===========================================================

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================

	// ===========================================================
	// Getter & Setter
	// ===========================================================
public:
	const Pathie::Path&		RootPath() const							{ return std::move(Pathie::Path::exe()); }
	const Pathie::Path&		AssetsPath() const							{ return m_assetsPath; }
	void					AssetsPath(const Pathie::Path& assetsPath)	{ m_assetsPath = assetsPath; }
	
	TMeshManager&			MeshManager()		{ return m_meshManager; }
	TTextureManager&		TextureManager()	{ return m_textureManager; }
	TShaderManager&			ShaderManager()		{ return m_shaderManager; }
	TShaderProgramManager&	ShaderProgManager()	{ return m_shaderProgManager; }
	TMaterialManager&		MaterialManager()	{ return m_materialManager; }
	TGameObjectManager&		GameObjectManager()	{ return m_goManager; }

	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CAssetManager()
	{}

	~CAssetManager()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================

	// ===========================================================
	// Methods
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================
private:
	Pathie::Path			m_assetsPath;
	
	TMeshManager			m_meshManager;
	TTextureManager			m_textureManager;
	TShaderManager			m_shaderManager;
	TShaderProgramManager	m_shaderProgManager;
	TMaterialManager		m_materialManager;
	TGameObjectManager		m_goManager;
	
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CASSETMANAGER_H */
