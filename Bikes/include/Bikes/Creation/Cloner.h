#ifndef INCLUDE_BIKES_CREATION_CLONER_H
#define INCLUDE_BIKES_CREATION_CLONER_H


namespace Bikes
{
//------------------------------------------------------------------------------
template<class T>
class SimpleCopier
{
public:
	typedef T value_type;

	static T* createCopy(T const* obj)
	{
		return new T(*obj);
	}
};
//------------------------------------------------------------------------------
template<class T>
class SafetyCopier
{
public:
    typedef T value_type;

    static T* createCopy(T const* obj)
    {
        if (obj)
            return new T(*obj);
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T >
class SimpleCloner
{
public:
	typedef T value_type;
		
	static T* createCopy(T const* obj)
	{
		return obj->clone();
	}
};
//------------------------------------------------------------------------------
template<class T >
class SafetyCloner
{
public:
    typedef T value_type;

    static T* createCopy(T const* obj)
    {
        if (obj)
            return obj->clone();
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T >
class NullCloner
{
public:
    typedef T value_type;

    static T* createCopy(T const* obj)
    {
        return 0;
    }
};
//------------------------------------------------------------------------------
}


#endif // <- INCLUDE_BIKES_CREATION_CLONER_H
