#ifndef INCLUDE_BIKES_CREATION_CREATOR_H
#define INCLUDE_BIKES_CREATION_CREATOR_H
#include <Bikes/Types.h>

namespace Bikes
{

template<class T> 
class SimpleCreator
{	
public:
	typedef T value_type;

	static T* create()
	{
		return new T;
	}

	static T* createArray(sznum sz)
	{
		return new T[sz];
	}
};

}

#endif // <- INCLUDE_BIKES_CREATION_CREATOR_H
