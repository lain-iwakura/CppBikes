#ifndef INCLUDE_BIKES_ABSTRACT_CREATOR_H
#define INCLUDE_BIKES_ABSTRACT_CREATOR_H

namespace Bikes
{

template<class T> 
class SimpleCreator
{
public:
	static T* create()
	{
		return new T();
	}
};

}

#endif // <- INCLUDE_BIKES_ABSTRACT_CREATOR_H
