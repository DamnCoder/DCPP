//
//  layermanager.cpp
//  DCPPTest
//
//  Created by Jorge López on 1/4/17.
//
//

#include "renderlayermanager.h"

#include <assert.h>

namespace dc
{
	const char* CRenderLayerManager::DEFAULT_LAYER = "Default";
	
	const char* CRenderLayerManager::DefaultLayerName() const
	{
		return DEFAULT_LAYER;
	}
	
	const unsigned int CRenderLayerManager::DefaultLayerIndex() const
	{
		return 0;
	}
	
	const char* CRenderLayerManager::LayerName(const unsigned int index) const
	{
		TLayerList::const_iterator first = m_layerList.begin();
		TLayerList::const_iterator last = m_layerList.end();
		unsigned int i = 0;
		do
		{
			if(i == index)
				return *first;
			
			++first;
			++i;
		}
		while(first != last);
		
		return "";
	}
	
	const unsigned int CRenderLayerManager::LayerIndex(const char* name) const
	{
		TLayerList::const_iterator first = m_layerList.begin();
		TLayerList::const_iterator last = m_layerList.end();
		unsigned int i = 0;
		do
		{
			if(strcmp(*first, name) == 0)
				return i;
			
			++first;
			++i;
		}
		while(first != last);
		
		return i;
	}
	
	CRenderLayer* CRenderLayerManager::Layer(const char* name)
	{
		assert(Exists(name) && "The render layer does not exist!");
		return m_renderLayerMap[name];
	}
	
	const unsigned int CRenderLayerManager::Count() const
	{
		return m_layerList.size();
	}
	
	CRenderLayerManager::CRenderLayerManager()
	{
		Add(DEFAULT_LAYER);
	}
	
	CRenderLayerManager::~CRenderLayerManager()
	{
		for(const char* layerName : m_layerList)
		{
			Remove(layerName);
		}
		m_layerList.clear();
	}

	void CRenderLayerManager::Add(const char* name)
	{
		Add(name, new CRenderLayer());
	}
	
	void CRenderLayerManager::Add(const char* name, CRenderLayer* renderLayer)
	{
		assert(name && renderLayer && "You are passing NULL pointers");
		
		assert(!Exists(name) && "You can't have duplicate layers");
		
		m_layerList.push_back(name);
		
		m_renderLayerMap[name] = renderLayer;
		m_renderLayerList.push_back(renderLayer);
	}
	
	void CRenderLayerManager::Remove(const char* name)
	{
		assert(name);

		const unsigned int index = LayerIndex(name);
		
		assert(index < Count() && "You are trying to remove a non existent layer");
		
		m_layerList.erase(m_layerList.begin() + index);
		
		TRenderLayerMap::iterator it = m_renderLayerMap.find(name);
		CRenderLayer* renderLayer = it->second;
		m_renderLayerMap.erase(it);
		
		auto listIterator = std::find(m_renderLayerList.begin(), m_renderLayerList.end(), renderLayer);
		m_renderLayerList.erase(listIterator);
		
		assert(renderLayer);
		
		delete renderLayer;
	}
	
	const bool CRenderLayerManager::Exists(const char* name) const
	{
		return LayerIndex(name) < Count();
	}

}
