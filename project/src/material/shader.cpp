//
//  shader.cpp
//  BitThemAll
//
//  Created by Jorge López González on 27/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "shader.h"

#include "renderer/glwraps.h"
#include "renderer/renderer.h"

#include <assert.h>

namespace dc
{
	//------------------------------------------------------------//
	// CShader
	//------------------------------------------------------------//
	
	//------------------------------------------------------------//
	
	const bool CShader::Compiled() const
	{
		int isCompiled;
		glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &isCompiled);
		return isCompiled == GL_TRUE;
	}

    //------------------------------------------------------------//
	
	void CShader::Create(char* src, const int size)
	{
		m_shaderID = glCreateShader(m_shaderType);
		
		// - shader id
		// - number of elements in shader src array
		// - array of shader src
		// - lengths of each of the shader src
		glShaderSource(m_shaderID, 1, &src, &size);
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
		assert(Compiled() && "Shader compilation error");
	}
	
    //------------------------------------------------------------//
    bool CShader::PrintCompileInfoLog(const unsigned int shaderID)
    {
        int infologLength = 0;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infologLength);
        
        if (infologLength > 0)
        {
			int charsWritten = 0;
			char infoLog[infologLength];
            glGetShaderInfoLog(shaderID, infologLength, &charsWritten, infoLog);
			printf("%s\n", infoLog);
            //general::CLog::getInstance()->log(HE_LogLevel::INFO,"Shader log:\n\n"+log);
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
		m_shaderList.push_back(shader);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Remove(CShader& shader)
	{
		TShaderList::iterator it = std::find(m_shaderList.begin(), m_shaderList.end(), shader);
		
		assert(it != m_shaderList.end() && "[CShaderProgram::Remove] The shader you try to remove doesn't exist!");
		
		m_shaderList.erase(it);
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
	
	void CShaderProgram::BindAttributeLocation(int index, const char* attribute)
	{
		// Bind attribute to an specified index 
		// Attribute locations must be setup before calling glLinkProgram
		glBindAttribLocation(m_programID, index, attribute);
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::Link()
	{
		// Bind attribute locations first
		const TVertexPropertyMap& vertexPropertyMap = CRenderer::Instance().VertexProperties();
		
		for(auto& entry : vertexPropertyMap)
		{
			const CVertexProperty& vertexProperty = entry.second;
			BindAttributeLocation(vertexProperty.Id(), vertexProperty.Name());
		}
		
		// Linking
		glLinkProgram(m_programID);
		PrintLinkInfoLog(m_programID);
		
		int isLinked;
		glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
		
		if (isLinked)
		{
			printf("Shader linked!\n");
		}
	}
	
	const int CShaderProgram::GetUniformHandle(const char* name)
	{
		GLint handle = glGetUniformLocation(m_programID, name);
		if(handle != -1)
		{
			m_uniformMap[name] = handle;
			return handle;
		}
		return -1;
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassFloat(const char* name, float value)
	{
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform1f(uniformLocation, value);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassInteger(const char* name, int value)
	{
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform1i(uniformLocation, value);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector3f(const char* name, const math::Vector3f& vector)
	{
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation !=-1)
		{
			glUniform3fv(uniformLocation, 1, vector);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector4f(const char* name, const math::Vector4f& vector)
	{
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform4fv(uniformLocation, 1, vector);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassQuaternion(const char* name, const math::Quaternionf& quaternion)
	{
		GLint uniformLocation = glGetUniformLocation(m_programID, name);
		if (uniformLocation != -1)
		{
			glUniform4fv(uniformLocation, 1, quaternion);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassMatrix4x4f(const char* name, const math::Matrix4x4f& matrix)
	{
		TUniformMap::iterator it = m_uniformMap.find(name);
		if (it != m_uniformMap.end())
		{
			GLint uniformHandle = it->second;
			const float* data = &matrix[0];
			glUniformMatrix4fv(uniformHandle, 1, GL_FALSE, data);
		}
	}
	
	//------------------------------------------------------------//
	
	void CShaderProgram::PassVector3fArray(const char* name, const math::Vector3f valor[], int size)
	{
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
	
	void CShaderProgram::PrintLinkInfoLog(const unsigned int programID)
	{
		int infologLength = 0;
		int charsWritten  = 0;
		
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH,&infologLength);
		
		if (infologLength > 0)
		{
			char infoLog[infologLength];
			glGetShaderInfoLog(programID, infologLength, &charsWritten, infoLog);
			std::string log = infoLog;
			//general::CLog::getInstance()->log(HE_LogLevel::INFO,"Program log:\n\n"+log);
		}
	}
}
