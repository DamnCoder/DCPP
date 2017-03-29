//
//  renderer.cpp
//  BitThemAll
//
//  Created by Jorge López González on 07/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "renderer.h"

namespace dc
{
    void CRenderer::Init()
    {
        
    }
    void CRenderer::End()
    {
        mm_vertexProperties.clear();
    }
    
    //VERTEX PROPERTIES+++++++++++++++++++++++++++++++++++++++
    void CRenderer::AddVertexProperty(const std::string& name, int size)
    {
        static int identifier = 0;
        mm_vertexProperties[name] = CVertexProperty(name, size, identifier++);
    }
    
    const TVertexPropertyMap CRenderer::VertexProperties()
    {
        return mm_vertexProperties;
    }
    
    //DATA ARRAYS++++++++++++++++++
    void CRenderer::CreateDataArray(TFloatArray& array)
    {
        GLuint identifier;
        glGenBuffers(1, &identifier);
        array.SetId(identifier);
    }
    
    void CRenderer::ActivateDataArray(const TFloatArray& array, const std::string& name)
    {
        CVertexProperty vertexProperty = mm_vertexProperties[name];
		glEnableVertexAttribArray(vertexProperty.identifier);
        glVertexAttribPointer(vertexProperty.identifier, vertexProperty.size, GL_FLOAT, GL_FALSE, 0, 0);
        
        GLuint identifier = array.Id();
        glBindBuffer(GL_ARRAY_BUFFER, identifier);
    }
    
    void CRenderer::ActivateDataArray(const TUIntArray& array, const std::string& name)
    {
        CVertexProperty p = mm_vertexProperties[name];
		glEnableVertexAttribArray(p.identifier);
        glVertexAttribPointer(p.identifier, p.size, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
        
        const GLuint identifier = array.Id();
        glBindBuffer(GL_ARRAY_BUFFER, identifier);
    }
    
    void CRenderer::SubmitDataArray(const TFloatArray& array)
    {
        const GLuint identifier = array.Id();
        glBindBuffer(GL_ARRAY_BUFFER, identifier);
        glBufferData(GL_ARRAY_BUFFER, array.MaxSize()*sizeof(float), array.Data(), GL_STREAM_DRAW);
    }
    
    void CRenderer::DeleteDataArray(const TFloatArray& array)
    {
        const GLuint identifier = array.Id();
        glDeleteBuffers(1, &identifier);
    }
    
    //INDEX ARRAYS+++++++++++++++++
    void CRenderer::CreateIndexArray(TUIntArray& array)
    {
        GLuint identifier;
        glGenBuffers(1, &identifier);
        array.SetId(identifier);
    }
    
    void CRenderer::ActivateIndexArray(const TUIntArray& array)
    {
        const GLuint identifier = array.Id();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identifier);
    }
    
    void CRenderer::SubmitIndexArray(const TUIntArray& array)
    {
        GLuint identifier = array.Id();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, identifier);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, array.MaxSize()*sizeof(unsigned short), array.Data(), GL_STREAM_DRAW);
    }
    
    void CRenderer::DrawMesh(const CMesh* mesh, void (*DrawFunc)(const CMesh*))
    {
        if(!mesh->IsValid()) return;
		
        ActivateIndexArray(mesh->IndexArray());
        /*
		ActivateDataArray(mesh->VertexArray(), "InVertex");
		ActivateDataArray(mesh->NormalArray(), "InNormal");
        ActivateDataArray(mesh->UV0Array(), "InTexCoord0");
        ActivateDataArray(mesh->UV1Array(), "InTexCoord1");
        ActivateDataArray(mesh->ColorArray(), "InColor");
        */
        DrawFunc(mesh);
    }
}
