//
//  vertexproperty.hpp
//  DCPPTest
//
//  Created by Jorge López on 31/3/17.
//
//

#ifndef vertexproperty_h
#define vertexproperty_h

#include <map>

#include "vbo.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class CVertexProperty
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
	public:
		static const char* IN_VERTEX;
		static const char* IN_NORMAL;
		static const char* IN_UV0;
		static const char* IN_COLOR;
		
		static const unsigned int VERTEX_SIZE;
		static const unsigned int NORMAL_SIZE;
		static const unsigned int UV_SIZE;
		static const unsigned int COLOR_SIZE;
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		static void Activate(const CVertexProperty& vertexProperty)
		{
			const GLuint attributeId = (GLuint)vertexProperty.Id();
			glEnableVertexAttribArray(attributeId);
	
			const GLint typeSize = (GLint)vertexProperty.Size();
			glVertexAttribPointer(
								  attributeId,				// attribute
								  typeSize,					// size
								  GL_FLOAT,					// type
								  GL_FALSE,					// normalized?
								  0,						// stride
								  (void*)0					// array buffer offset
			);
		}
		
		static void Deactivate(const CVertexProperty& vertexProperty)
		{
			glDisableVertexAttribArray(vertexProperty.Id());
		}
		
		static const unsigned int ElementNum(const char* propertyName)
		{
			if(strcmp(propertyName, IN_VERTEX) == 0)
			{
				return VERTEX_SIZE;
			}
			else if(strcmp(propertyName, IN_NORMAL) == 0)
			{
				return NORMAL_SIZE;
			}
			if(strcmp(propertyName, IN_UV0) == 0)
			{
				return UV_SIZE;
			}
			if(strcmp(propertyName, IN_COLOR) == 0)
			{
				return COLOR_SIZE;
			}
			return 0;
		}
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const char*			Name()	const { return mp_name; }
		const unsigned int	Size()	const { return m_size; }
		const unsigned int	Id()	const { return m_identifier; }
		// ===========================================================
		// Constructors
		// ===========================================================
	public:
		CVertexProperty():
			mp_name(""),
			m_size(1),
			m_identifier(-1)
		{};
		
		CVertexProperty(const char* name, const unsigned int size, const unsigned int identifier):
			mp_name(name),
			m_size(size),
			m_identifier(identifier)
		{};
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
		const char*		mp_name;
		unsigned int	m_size;
		unsigned int	m_identifier;

	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
	typedef std::map<const char*, CVertexProperty> TVertexPropertyMap;
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* vertexproperty_hpp */
