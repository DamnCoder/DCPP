//
//	objloader.h
//	DCPP
//
//	Created by Jorge López on 26/4/17
//

#ifndef objloader_h
#define objloader_h

#include <map>
#include <string.h>

namespace dc
{
	// ===========================================================
	// External Enums / Typedefs for global usage
	// ===========================================================
	
	class CMesh;
	
	template<typename T>
	class CArray;
	
	/**
	 * \class
	 * \brief
	 * \author Jorge Lopez Gonzalez
	 *
	 * Description.
	 */
class CObjLoader
{
	// ===========================================================
	// Constant / Enums / Typedefs internal usage
	// ===========================================================
private:
	struct TPackedIndex;
	using TIndexMap = std::map<TPackedIndex, unsigned int>;
	using TFaceList = std::vector<TPackedIndex>;
	// ===========================================================
	// Static fields / methods
	// ===========================================================

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
private:
	struct TPackedIndex
	{
		unsigned int iv;
		unsigned int ivt;
		unsigned int ivn;
		
		TPackedIndex(const unsigned int iv, const unsigned int ivt, const unsigned int ivn):
			iv(iv),
			ivt(ivt),
			ivn(ivn)
		{}
		
		const bool operator==(const TPackedIndex& packedIndex)
		{
			return iv == packedIndex.iv && ivt == packedIndex.ivt && ivn == packedIndex.ivn;
		};
		
		bool operator<(const TPackedIndex& that) const{
			return memcmp((void*)this, (void*)&that, sizeof(TPackedIndex))>0;
		};
	};

	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Constructors
	// ===========================================================
public:
	CObjLoader()
	{}

	~CObjLoader()
	{}
	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
public:
	CArray<CMesh*> Load(const char* modelPath);
	
	void MergeVertices();

	// ===========================================================
	// Methods
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================
};

	// ===========================================================
	// Class typedefs
	// ===========================================================
	
	// ===========================================================
	// Template/Inline implementation
	// ===========================================================
}

#endif /* #CLASS_NAME */
