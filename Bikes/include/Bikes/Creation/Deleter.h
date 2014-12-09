#ifndef INCLUDE_BIKES_CREATION_DELETER_H
#define INCLUDE_BIKES_CREATION_DELETER_H

namespace Bikes
{
	
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

}



#endif // <- INCLUDE_BIKES_CREATION_DELETER_H