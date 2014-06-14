#ifndef INCLUDE_BIKES_CREATION_CLONER_H
#define INCLUDE_BIKES_CREATION_CLONER_H


namespace Bikes
{


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


}


#endif // <- INCLUDE_BIKES_CREATION_CLONER_H
