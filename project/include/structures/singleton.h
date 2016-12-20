/*
 * Singleton.h
 *
 *  Created on: 06/04/2010
 *      Author: jorge
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_


/**
 * Template para crear singletons genericos
 */

template <typename T>
class CSingleton
{
public:
	static T& Instance()
    {
		if(!instance)
        {
            instance = new T();
        }

		return *instance;
	}

	static T* Pointer()
    {
		return &Instance();
	}

	static void Destroy()
    {
		if(instance)
        {
			delete instance;
			instance = 0;
		}
	}

protected:
	virtual ~CSingleton(){};
	CSingleton(){};

private:
    /// Copy constructor and assignation operator are private to avoid any copy
	CSingleton(const CSingleton&) = delete;
	CSingleton& operator=(const CSingleton&) = delete;
    
    static T* instance;
};

template <typename T> T* CSingleton<T>::instance = 0;

#endif /* SINGLETON_H_ */
