#ifndef INCLUDE_BIKES_ABSTRACT_CLONER_H
#define INCLUDE_BIKES_ABSTRACT_CLONER_H


namespace Bikes
{


template<class T>
class SimpleCopier
{
public:

	static T* createCopy(T const* obj)
	{
		return new T(*obj);
	}
};


template<class T >
class SimpleCloner
{
public:
		
	static T* createCopy(T const* obj)
	{
		return obj->clone();
	}
};


}


#endif // <- INCLUDE_BIKES_ABSTRACT_CLONER_H
