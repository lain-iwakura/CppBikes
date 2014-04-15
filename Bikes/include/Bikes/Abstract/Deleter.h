#ifndef INCLUDE_BIKES_ABSTRACT_DELETER_H
#define INCLUDE_BIKES_ABSTRACT_DELETER_H

namespace Bikes
{
	
template<class T>
class SimpleDeleter
{
public:
		
	static void cleanup(T *obj)
	{
		delete obj;
	}
};

template<class T>
class ArrayDeleter
{
public:

	static void cleanup(T *obj)
	{
		delete [] obj;
	}
};

}



#endif // <- INCLUDE_BIKES_ABSTRACT_DELETER_H
