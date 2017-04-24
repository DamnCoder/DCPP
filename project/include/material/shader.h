//
//  shader.h
//  BitThemAll
//
//  Created by Jorge López González on 27/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__shader__
#define __BitThemAll__shader__

#include <OpenGL/OpenGL.h>

#include "math/quaternion.h"
#include "math/vector.h"
#include "math/matrix.h"

#include <vector>

namespace dc
{
    /**
     * \class CShader
     * \brief shader class.
     * \author Jorge López González
     * \version 1.0
     * \date 2016
     *
     * Holds glsl shader data. Allows for the shader program to be activated/deactivated.
     * It is possible to pass data to the shader, as well.
     */
    class CShader
    {
	public:
		const GLuint Identifier() const { return m_shaderID; }
		const GLenum Type() const { return m_shaderType; }
		
		const bool CompilationSuccesful() const;
		
    public:
		CShader(const GLenum type) : m_shaderType (type) {};
		
		CShader(const CShader& copy) : m_shaderType (copy.Type()), m_shaderID (copy.Identifier()) {};
		
		~CShader(){}
		
	public:
		void operator= (const CShader& copy)
		{
			m_shaderType = copy.Type();
			m_shaderID = copy.Identifier();
		}
		
		const bool operator== (const CShader& shader) const
		{
			return shader.Identifier() == Identifier() && shader.Type() == Type();
		}
		
	public:
		void Create(const char* shaderSrc);
		void Destroy();
		
		void Compile();

    private:
        bool PrintCompileInfoLog(GLuint obj);
        
    private:
		GLenum			m_shaderType;
		GLuint			m_shaderID;
    };
	
	/**
	 * \class CShaderProgram
	 * \brief shader program class.
	 * \author Jorge López González
	 * \version 1.0
	 * \date 20016
	 *
	 * Shader program abstraction.
	 */
	class CShaderProgram
	{
	public:
		using TShaderList = std::vector<CShader>;
		
	public:
		const bool CorrectlyLinked() const;
		
	public:
		CShaderProgram() {}
		~CShaderProgram() {}
		
		CShaderProgram(const CShaderProgram& copy):
			m_programID (copy.m_programID),
			m_shaderList(copy.m_shaderList)
		{}
		
	public:
		void operator= (const CShaderProgram& copy)
		{
			m_programID = copy.m_programID;
			m_shaderList = copy.m_shaderList;
		}
		
	public:
		void Create();
		void Destroy();
		
		void Add(const CShader& shader);
		void Remove(CShader& shader);
		
		void Compile();
		
		void AttachAll();
		void DetachAll();
		
		void Activate() const;
		void Deactivate() const;
		
		void Link();
		
	public:
		void PassFloat	(const char* name, float value);
		void PassInteger(const char* name, int value);
		
		void PassVector3f	(const char* name, const math::Vector3f& vector);
		void PassVector4f	(const char* name, const math::Vector4f& vector);
		void PassQuaternion	(const char* name, const math::Quaternionf& quaternion);
		void PassMatrix4x4f	(const char* name, const math::Matrix4x4f& matrix);
		
		void PassVector3fArray	(const char* name, const math::Vector3f value[], int size);
		void PassVector4fArray	(const char* name, const math::Vector4f value[], int size);
		void PassQuaternionArray(const char* name, const math::Quaternionf value[], int size);
		void PassMat4x4fArray	(const char* name, const math::Matrix4x4f value[], int size);
		
	private:
		void PrintLinkInfoLog(const GLuint obj);
		
	private:
		GLuint		m_programID;
		TShaderList	m_shaderList;
	};
}

#endif /* defined(__BitThemAll__shader__) */
