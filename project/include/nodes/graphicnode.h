//
//  node.h
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__node__
#define __BitThemAll__node__

#include <string>
#include <list>

namespace dc
{
    
    class CGraphicNode;
    
    // Redefinition of types for clarification purposes
    typedef std::list<CGraphicNode*> TNodesList;
    
    class CGraphicNode
    {
    public:
        CGraphicNode(const std::string& name):
            ms_name(name)
        {}
        
        ~CGraphicNode()
        {}
        
    // Accesors
    public:
        const std::string&  identifier() const { return ms_name; }
        TNodesList          childs() const { return ml_childs; }

    
    // Child management
    public:
        void GetChild(const std::string& nodeName);
        
        void AddChild(const CGraphicNode* child);
        
        void RemoveChild(const CGraphicNode* child);
        
        bool IdExists(const std::string &name);
        bool NodeExists(const CGraphicNode* node);
        
    // Hidden member functions
    private:
        TNodesList::iterator FindNodeIterator(const std::string& name);
        TNodesList::iterator FindNodeIterator(const CGraphicNode* node);
    
    // Atributes
    private:
        std::string ms_name;
        
        TNodesList  ml_childs;
    };
    
    //-----------------------------------------------------------------------
    // COMMON FUNCTORS
    //-----------------------------------------------------------------------

    struct NodeIdEquals
    {
    public:
        NodeIdEquals(const std::string& nodeName):
            ms_nodeName(nodeName)
        {}
        
        const bool operator()(const CGraphicNode* node) const
        {
            return ms_nodeName == node->identifier();
        }
        
    private:
        const std::string ms_nodeName;
    };
    
    struct AddNodeToParent
    {
    public:
        AddNodeToParent(CGraphicNode* parent):
            mp_parentNode(parent)
        {}
        
        void operator()(const CGraphicNode* node)
        {
            mp_parentNode->AddChild(node);
        }
        
    private:
        CGraphicNode* mp_parentNode;
    };
    
}

#endif /* defined(__BitThemAll__node__) */
