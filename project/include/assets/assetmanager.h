//
//	assetmanager
//	DCPP
//
//	Created by Jorge López González on 25/05/2017 14:13:35.
//

#ifndef CASSETMANAGER_H
#define CASSETMANAGER_H

#include <unordered_map>

#include "material/shadermanager.h"
#include "material/texturemanager.h"
#include "mesh/meshmanager.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
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
	TMeshManager&			MeshManager()		{ return m_meshManager; }
	TTextureManager&		TextureManager()	{ return m_textureManager; }
	TShaderManager&			ShaderManager()		{ return m_shaderManager; }
	TShaderProgramManager&	ShaderProgManager()	{ return m_shaderProgManager; }

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
	TMeshManager			m_meshManager;
	TTextureManager			m_textureManager;
	TShaderManager			m_shaderManager;
	TShaderProgramManager	m_shaderProgManager;
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* CASSETMANAGER_H */
