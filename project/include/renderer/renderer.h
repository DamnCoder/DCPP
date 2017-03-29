//
//  renderer.h
//  BitThemAll
//
//  Created by Jorge López González on 07/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__renderer__
#define __BitThemAll__renderer__

#include "structures/singleton.h"

#include "glwraps.h"
#include "Array.h"

#include <map>
#include <string>

namespace dc
{
    class CVertexProperty
    {
	public:
		const bool IsValid() const { return -1 < identifier; }
    public:
		CVertexProperty():
            name(""),
            size(1),
            identifier(-1)
        {};
		
        CVertexProperty(const std::string& name, int size, int identifier):
            name(name),
            size(size),
            identifier(identifier)
        {};
        
		std::string		name;
		unsigned int	size;
		int				identifier;
    };
    
    typedef std::map<std::string, CVertexProperty> TVertexPropertyMap;
    
    class CRenderer : public CSingleton<CRenderer>
    {
    friend class CSingleton<CRenderer>;
    public:
        CRenderer()
        {}
        
        ~CRenderer()
        {}
        
    public:
        void Init();
        void End();
        
    public:
        //VERTEX PROPERTIES+++++++++++++++++++++++++++++++++++++++
		void AddVertexProperty(const std::string& name, int size);
		const TVertexPropertyMap VertexProperties();
		
		//DATA ARRAYS++++++++++++++++++
		void CreateDataArray(TFloatArray& array);
        
		void ActivateDataArray(const TFloatArray& data, const std::string& name);
		void ActivateDataArray(const TUIntArray& array, const std::string& name);
        
		void SubmitDataArray(const TFloatArray& data);
        
		void DeleteDataArray(const TFloatArray& data);
		
		//INDEX ARRAYS+++++++++++++++++
		void CreateIndexArray(TUIntArray& array);
		void ActivateIndexArray(const TUIntArray& array);
		void SubmitIndexArray(const TUIntArray& array);
        
        // DRAW FUNCTIONS+++++++
        void DrawMesh(const CMesh* mesh, void (*DrawFunc)(const CMesh*));
    private:
        
        TVertexPropertyMap  mm_vertexProperties;
    };
}
#endif /* defined(__BitThemAll__renderer__) */
