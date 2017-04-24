//
//  layermanager.h
//  DCPP
//
//  Created by Jorge López on 1/4/17.
//
//

#ifndef layermanager_h
#define layermanager_h

#include <vector>
#include <map>

#include "renderlayer.h"
#include "structures/singleton.h"

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	using TLayerList		= std::vector<const char*>;
	using TRenderLayerMap	= std::map<const char*, CRenderLayer*>;
	using TRenderLayerList	= std::vector<CRenderLayer*>;
	
	class CRenderLayerManager : public CSingleton<CRenderLayerManager>
	{
		// ===========================================================
		// Constant / Enums / Typedefs internal usage
		// ===========================================================
		friend class CSingleton<CRenderLayerManager>;
		
	public:
		
		static const char* DEFAULT_LAYER;
		
		// ===========================================================
		// Static fields / methods
		// ===========================================================
		
		// ===========================================================
		// Inner and Anonymous Classes
		// ===========================================================
		
		// ===========================================================
		// Getter & Setter
		// ===========================================================
	public:
		const char*				DefaultLayerName() const;
		const unsigned int		DefaultLayerIndex() const;
		
		const char*				LayerName(const unsigned int index) const;
		const unsigned int		LayerIndex(const char* name) const;
		
		CRenderLayer*			Layer(const char* name);
		
		const unsigned int		Count() const;
		
		const TRenderLayerList&	RenderLayerList() const { return m_renderLayerList; }
		
		// ===========================================================
		// Constructors
		// ===========================================================
	private:
		CRenderLayerManager();
		
		~CRenderLayerManager();
		
		CRenderLayerManager(const CRenderLayerManager& copy) = delete;
		
		// ===========================================================
		// Methods for/from SuperClass/Interfaces
		// ===========================================================
	public:
		void operator= (const CRenderLayerManager& copy) = delete;
		
		// ===========================================================
		// Methods
		// ===========================================================
	public:
		void Add(const char* name);
		void Add(const char* name, CRenderLayer* renderLayer);
		
		void Remove(const char* name);
		
		const bool Exists(const char* name) const;
		
		// ===========================================================
		// Fields
		// ===========================================================
	private:
		TLayerList			m_layerList;
		TRenderLayerMap		m_renderLayerMap;
		TRenderLayerList	m_renderLayerList;
	};
	
	// ===========================================================
	// Class typedefs
	// ===========================================================
}


#endif /* layermanager_hpp */
