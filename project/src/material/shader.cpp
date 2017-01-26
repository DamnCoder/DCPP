//
//  shader.cpp
//  BitThemAll
//
//  Created by Jorge López González on 27/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "shader.h"

#include <OpenGL/gl.h>

#include <assert.h>

namespace dc
{
	//------------------------------------------------------------//
	// CShader
	//------------------------------------------------------------//
	
	//------------------------------------------------------------//
	
	const bool CShader::CompilationSuccesful() const
	{
		int isCompiled;
		glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &isCompiled);
		return isCompiled == GL_TRUE;
	}

    //------------------------------------------------------------//
	
	void CShader::Create(const char* shaderSrc)
	{
		m_shaderID = glCreateShader(m_shaderType);
		
		// - shader id
		// - number of elements in shader src array
		// - array of shader src
		// - lengths of each of the shader src
		glShaderSource(m_shaderID, 1, &shaderSrc, NULL);
	}
	
	//------------------------------------------------------------//
	
	void CShader::Destroy()
	{
		glDeleteShader(m_shaderID);
	}
	
	//------------------------------------------------------------//
	
	void CShader::Compile()
	{
		glCompileShader(m_shaderID);
		PrintCompileInfoLog(m_shaderID);
		assert(CompilationSuccesful() && "Shader compilation error");
	}
	
    //------------------------------------------------------------//
    bool CShader::PrintCompileInfoLog(GLuint shaderID)
    {
        int infologLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infologLength);
        
        if (infologLength > 0)
        {
			int charsWritten = 0;
            char *infoLog = (char *)malloc(infologLength);
            glGetShaderInfoLog(shaderID, infologLength, &charsWritten, infoLog);
            //general::CLog::getInstance()->log(HE_LogLevel::INFO,"Shader log:\n\n"+log);
            free(infoLog);
            return false;
        }
        
        return true;
    }
	
	//------------------------------------------------------------//
	// CShaderProgram
	//------------------------------------------------------------//
	
	const bool CShaderProgram::CorrectlyLinked() const
	{
		int linked;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &linked);
		return (linked == GL_TRUE);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Create()
	{
		m_programID = glCreateProgram();
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Destroy()
	{
		DetachAll();
		
		for(CShader& shader : m_shaderList)
		{
			shader.Destroy();
		}
		
		m_shaderList.clear();
		
		glDeleteProgram(m_programID);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Add(const CShader& shader)
	{
		m_shaderList.push_front(shader);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Remove(CShader& shader)
	{
		m_shaderList.remove(shader);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Compile()
	{
		for(CShader& shader : m_shaderList)
		{
			shader.Compile();
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::AttachAll()
	{
		for(CShader& shader : m_shaderList)
		{
			glAttachShader(m_programID, shader.Identifier());
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::DetachAll()
	{
		for(CShader& shader : m_shaderList)
		{
			glDetachShader(m_programID, shader.Identifier());
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Activate() const
	{
		glUseProgram(m_programID);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Deactivate() const
	{
		glUseProgram(0);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Link()
	{
		glLinkProgram(m_programID);
		PrintLinkInfoLog(m_programID);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassFloat(const char* name, float value)
	{
		Activate();
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform1f(uniformLocation, value);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassInteger(const char* name, int value)
	{
		Activate();
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform1i(uniformLocation, value);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector3f(const char* name, const math::Vector3f& vector)
	{
		Activate();
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation !=-1)
		{
			glUniform3fv(uniformLocation, 1, vector);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector4f(const char* name, const math::Vector4f& vector)
	{
		Activate();
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform4fv(uniformLocation, 1, vector);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassQuaternion(const char* name, const math::Quaternionf& quaternion)
	{
		Activate();
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			
			glUniform4fv(uniformLocation, 1, quaternion);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassMatrix4x4f(const char* name, const math::Matrix4x4f& matrix)
	{
		Activate();
		GLint v = glGetUniformLocation(m_programID, name);
		if (v != -1)
		{
			glUniformMatrix4fv(v, 1, GL_FALSE, matrix.m);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector3fArray(const char* name, const math::Vector3f valor[], int size)
	{
		Activate();
		GLint v = glGetUniformLocation(m_programID, name);
		if (size>0 && v!=-1)
		{
			float lp[size*3];
			int pos = 0;
			for (int i = 0; i< size; ++i)
			{
				lp[pos++] = valor[i].x;
				lp[pos++] = valor[i].y;
				lp[pos++] = valor[i].z;
			}
			glUniform3fv(v, size, lp);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector4fArray(const char* name, const math::Vector4f valor[], int size)
	{
		Activate();
		GLint v = glGetUniformLocation(m_programID, name);
		if (size>0 && v!=-1)
		{
			float lp[size * 4];
			int pos = 0;
			for (int i = 0; i< size; ++i)
			{
				lp[pos++] = valor[i].x;
				lp[pos++] = valor[i].y;
				lp[pos++] = valor[i].z;
				lp[pos++] = valor[i].w;
			}
			glUniform4fv(v, size, lp);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassMat4x4fArray(const char* name, const math::Matrix4x4f valor[], int size)
	{
		Activate();
		GLint v = glGetUniformLocation(m_programID, name);
		if (size>0 && v!=-1)
		{
			float lp[size * 16];
			int pos = 0;
			for (int i = 0; i< size; ++i)
			{
				for (int j = 0; j< 16; ++j)
				{
					lp[pos++] = valor[i].m[j];
				}
			}
			glUniformMatrix4fv(v, size, GL_FALSE, lp);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassQuaternionArray(const char* name, const math::Quaternionf valor[], int size)
	{
		Activate();
		GLint v = glGetUniformLocation(m_programID, name);
		if (size>0 && v!=-1)
		{
			float lp[size * 4];
			int pos = 0;
			for (int i = 0; i< size; ++i)
			{
				lp[pos++] = valor[i].x;
				lp[pos++] = valor[i].y;
				lp[pos++] = valor[i].z;
				lp[pos++] = valor[i].w;
			}
			glUniform4fv(v, size, lp);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PrintLinkInfoLog(const GLuint programID)
	{
		int infologLength = 0;
		int charsWritten  = 0;
		
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH,&infologLength);
		
		if (infologLength > 0)
		{
			char *infoLog = (char *)malloc(infologLength);
			glGetShaderInfoLog(programID, infologLength, &charsWritten, infoLog);
			std::string log = infoLog;
			//general::CLog::getInstance()->log(HE_LogLevel::INFO,"Program log:\n\n"+log);
			free(infoLog);
		}
	}
}