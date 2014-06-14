#ifndef INCLUDE_BIKES_CREATION_CREATOR_H
#define INCLUDE_BIKES_CREATION_CREATOR_H

namespace Bikes
{

template<class T> 
class SimpleCreator
{	
public:
	typedef T value_type;

	static T* create()
	{
		return new T();
	}
};

}

#endif // <- INCLUDE_BIKES_CREATION_CREATOR_H
