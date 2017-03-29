//
//  renderlayer.cpp
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#include "renderlayer.h"

#include <algorithm>
#include "help/deletehelp.h"
#include "help/utils.h"

namespace dc
{
    CGraphicNode* CRenderLayer::GetNode(const std::string& identifier)
    {
        TNodesList::iterator requestedNodeIt = FindNodeIterator(identifier);

        if (requestedNodeIt == ml_layerNodes.end()) return 0;
        
        return (*requestedNodeIt);
    }
    
    bool CRenderLayer::AddNode(CGraphicNode* newNode)
    {
        if(IdExists(newNode->identifier())) return false;
        
        ml_layerNodes.push_back(newNode);
        mn_count = ml_layerNodes.size();
        return true;
    }
    
    bool CRenderLayer::AddNodeAndChildren(CGraphicNode* parentNode)
    {
        TNodesList::iterator it(parentNode->childs().begin()),
                             end(parentNode->childs().end());
        for (; it != end; ++it)
        {
            AddNodeAndChildren((*it));
        }
        AddNode(parentNode);
        return true;
    }
    
    bool CRenderLayer::RemoveNode(CGraphicNode* oldNode)
    {
        ml_layerNodes.remove(oldNode);
        mn_count = ml_layerNodes.size();
        return true;
    }
    
    bool CRenderLayer::RemoveNode(const std::string& identifier)
    {
        TNodesList::iterator requestedNodeIt = FindNodeIterator(identifier);
        if(requestedNodeIt != ml_layerNodes.end())
        {
            ml_layerNodes.erase(requestedNodeIt);
            mn_count = ml_layerNodes.size();
            return true;
        }
        return false;
    }
    
    void CRenderLayer::Clear()
    {
        DeleteWithFunctors(ml_layerNodes);
        mn_count = 0;
    }
    
    bool CRenderLayer::IdExists(const std::string &name)
    {
        return FindNodeIterator(name) != ml_layerNodes.end();
    }
    
    bool CRenderLayer::NodeExists(const CGraphicNode* node)
    {
        return FindNodeIterator(node) != ml_layerNodes.end();
    }
    
    TNodesList::iterator CRenderLayer::FindNodeIterator(const std::string& name)
    {
        return std::find_if(ml_layerNodes.begin(), ml_layerNodes.end(), NodeIdEquals(name));
    }
    
    TNodesList::iterator CRenderLayer::FindNodeIterator(const CGraphicNode* node)
    {
        return std::find_if(ml_layerNodes.begin(), ml_layerNodes.end(), ComparisonFunctor<CGraphicNode>(node));
    }
}