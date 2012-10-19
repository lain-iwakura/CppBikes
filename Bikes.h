#ifndef BIKES_H
#define BIKES_H

#include "ContainerInterface.h"



 

// long long iBit64(int i);
// int iBit32(int i);
// short iBit16(int i);
unsigned char iBit8(int i);
// 
// 
// 





















#define QIFELSE(EQ,IF_VAL,ELSE_VAL) ((EQ)?(IF_VAL):(ELSE_VAL))

/////////////////////////////////////////////////////

#define INTERCHANGET(T,X,Y) T _BUFX=X; X=Y; Y=_BUFX;
#define INTERCHANGE(X,Y) VoidInterchange(&X,&Y,sizeof(X))
#define ISEQUAL(X,Y) VoidIsEqual(&X,&Y,sizeof(X))
#define COPY(X,Y) VoidCopy(&X,&Y,sizeof(X))











///////////////////////////////////////////////
// 
// #define TYPENUM(NUM) TYPE#NUM
// 
// #define VRT(X) TYPENUM(VarType(X)) 

template<class T> void swap(T& obj1, T& obj2)
{
	T b(obj1);
	obj1=obj2;
	obj2=b;
}

void VoidInterchange(void* a, void* b, unsigned int size);
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

};

template<int iT> struct iType
{
	typedef NullType t;	
	enum{val=iT};
};






#define REGTYPE(X) template<> struct iType<sizeof(new char[TypeInfo<X>::id])>{typedef X t; enum{val=sizeof(new char[TypeInfo<X>::id])};};
#define GETTYPE(X) iType<sizeof(new char[GetTypeID(X)])>::t
#define GETTYPE_I(X) iType<sizeof(new char[GetTypeID(X)])>::val



class AbstractType //?
{
public:
	AbstractType():_typeId(0){}
	int TypeId() const {return _typeId;}
protected:
	template<class T> void RegisterThisType(const T *)
	{
		_typeId=TypeInfo<T>::id;
	}
private:
	int _typeId;
};


#endif



