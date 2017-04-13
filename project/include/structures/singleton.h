/*
 * Singleton.h
 *
 *  Created on: 06/04/2010
 *      Author: jorge
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <assert.h>
#include <utility>

/**
 * Template for generic singleton creation
 */

template <typename T>
class CSingleton
{
public:
	static T& Instance()
    {
		assert(mp_instance && "You need to create the singleton first!");
        return *mp_instance;
	}

	static T* Pointer()
    {
		assert(mp_instance && "You need to create the singleton first!");
		return mp_instance;
	}
	
	// ST: Specialized Type
	template<typename ST, typename... Args>
	static T* New(Args&&... args)
	{
		if(!mp_instance)
		{
			mp_instance = new ST(std::forward<Args>(args)...);
		}
		return mp_instance;
	}

	static void Destroy()
    {
		if(mp_instance)
        {
			delete mp_instance;
			mp_instance = 0;
		}
	}

protected:
	CSingleton(){};
	virtual ~CSingleton(){};

private:
    /// Copy constructor and assignation operator are private to avoid any copy
	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;
    
    static T* mp_instance;
};

template <typename T> T* CSingleton<T>::mp_instance = 0;

#endif /* SINGLETON_H_ */
