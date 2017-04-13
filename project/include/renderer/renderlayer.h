//
//  renderlayer.h
//  BitThemAll
//
//  Created by Jorge López González on 02/11/12.
//  Copyright (c) 2012 Jorge López González. All rights reserved.
//

#ifndef __BitThemAll__renderlayer__
#define __BitThemAll__renderlayer__

#include "nodes/graphicnode.h"

namespace dc
{
    /**
     * \class RenderLayer
     * \brief This class groups a subset of the graphic nodes for rendering
     * \author Jorge Lopez Gonzalez
     *
     * Holds a list of Nodes that should be rendered together. The graphics engine
     * will render a RenderLayer given to it, sorting the Nodes by distance to the camera node.
     */
    class CRenderLayer
    {
    // Constructors / Destructors
    public:
        CRenderLayer():
            mn_count(0)
        {}
        
        ~CRenderLayer()
        {};
        
    // Accesors
    public:
        const unsigned int  Count() const { return mn_count; }
        const TNodesList    LayerNodes() const { return ml_layerNodes; }
        
        CGraphicNode*       GetNode(const std::string& identifier);
        
    // Public interface
    public:
		void Render();
		
        /**
         * Adds a node to this render group. Note that only the node is added, children and parent nodes
         * are not affected.
         * \param a the node.
         * \return true if there was no existing node with the same name. false otherwise.
         */
        bool AddNode(CGraphicNode* newNode);
        
        /**
         * Adds a node to this render group. This also adds all its children recursively down to the
         * leafs of the node tree.
         * \param a the node.
         * \return true if there was no existing nodes with the same names. false otherwise.
         */
        bool AddNodeAndChildren(CGraphicNode* parentNode);
        
        /**
         * Removes a node from this render group. Note that only this node is removed, children and parent nodes
         * are not affected.
         * \param a the node.
         * \return true if there was no existing node with the same name. false otherwise.
         */
        bool RemoveNode(CGraphicNode* oldNode);
        bool RemoveNode(const std::string& identifier);
        
        void Clear();
        
        bool IdExists(const std::string &name);
        bool NodeExists(const CGraphicNode* node);
        
    // Hidden member functions
    private:
        TNodesList::iterator FindNodeIterator(const std::string& name);
        TNodesList::iterator FindNodeIterator(const CGraphicNode* node);
        
    // Atributes
    private:
        TNodesList              ml_layerNodes;
        unsigned int            mn_count;
    };
}

#endif /* defined(__BitThemAll__renderlayer__) */
