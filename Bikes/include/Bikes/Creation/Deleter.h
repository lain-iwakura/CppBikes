#ifndef INCLUDE_BIKES_CREATION_DELETER_H
#define INCLUDE_BIKES_CREATION_DELETER_H

namespace Bikes
{
//------------------------------------------------------------------------------	
template<class T>
class SimpleDeleter
{
public:
	typedef T value_type;
		
	static void destroy(T *obj)
	{
		delete obj;
	}

	static void destroyArray(T *obj)
	{
		delete[] obj;
	}
};
//------------------------------------------------------------------------------
template<class T>
class SafetyDeleter
{
public:
    typedef T value_type;

    static void destroy(T *obj)
    {
        if (obj)
            delete obj;
    }

    static void destroyArray(T *obj)
    {
        if (obj)
            delete[] obj;
    }
};
//------------------------------------------------------------------------------
template<class T>
class NullDeleter
{
public:
    typedef T value_type;

    static void destroy(T *obj)
    {
    }

    static void destroyArray(T *obj)
    {
    }
};
//------------------------------------------------------------------------------
}



#endif // <- INCLUDE_BIKES_CREATION_DELETER_H
