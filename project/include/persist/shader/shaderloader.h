//
//  shaderloader.h
//  DCPP
//
//  Created by Jorge López on 4/5/17.
//
//

#ifndef shaderloader_h
#define shaderloader_h

#include "material/shader.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
	class CShaderLoader
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
		
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CShaderLoader()
		{}
		
		~CShaderLoader()
		{}
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		CShader* Load(const char* filePath, const int type);
		
		// ===========================================================
		// Methods
		// ===========================================================
		
		// ===========================================================
		// Fields
		// ===========================================================
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}


#endif /* shaderloader_hpp */
