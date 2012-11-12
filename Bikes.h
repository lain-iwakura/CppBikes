#ifndef BIKES_H
#define BIKES_H

#include "List.h"

namespace CppBikes
{



//#define ISEQUAL(X,Y) VoidIsEqual(&X,&Y,sizeof(X))
//#define COPY(X,Y) VoidCopy(&X,&Y,sizeof(X))

template<class T> void swap(T& obj1, T& obj2)
{
	T b(obj1);
	obj1=obj2;
	obj2=b;
}

void VoidSwap(void* a, void* b, unsigned int size);
bool VoidIsEqual(void *a, void *b, unsigned int n);
void VoidCopy(void *a, void *b, unsigned int n);


///////////////////////////////////////////////////////

class TypeRegister
{		
protected:
	static int cID;	
};
//int TypeRegister::cID=1;

template<class T> class TypeInfo: private TypeRegister
{	
public:
	static const int id;
	static const long long size=sizeof(T);
};
template<class T> const int TypeInfo<T>::id=cID++;

template<class T> int GetTypeID(const T&)
{
	return TypeInfo<T>::id;
}

class NullType
{
public:
	NullType(){}
};

template<int iT> struct iType
{
	typedef NullType t;
	enum{val=iT};
};


}
#endif



