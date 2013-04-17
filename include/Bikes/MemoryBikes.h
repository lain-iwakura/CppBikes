#ifndef _BIKES_MEMORYBIKES_H_
#define _BIKES_MEMORYBIKES_H_



namespace Bikes
{

template<class T> 
void swap(T& obj1, T& obj2)
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


void swap_void(void* a, void* b, unsigned int size);

bool isEqual_void(void *a, void *b, unsigned int n);

void copy_void(void *a, void *b, unsigned int n);


}

#endif



