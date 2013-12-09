#ifndef PREBIKES_MEMORYBIKES_H
#define PREBIKES_MEMORYBIKES_H

#include <Bikes/Types.h>


namespace Bikes
{

template<class T> 
void swap_(T& obj1, T& obj2)
{
	T b(obj1);
	obj1=obj2;
	obj2=b;
}

template<class T>
void delete_void(void* p)
{
	delete static_cast<T*>(p);
}


void swap_void(void* a, void* b, unum size);

bool isEqual_void(void *a, void *b, unum n);

void copy_void(void *a, void *b, unum n);


}

#endif



