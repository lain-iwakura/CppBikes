#include <Bikes/TestBikes.h>
#include <Bikes/ByteStream.h>
#include <Bikes/RawArray.h>
#include <Bikes/BikesStream.h>
#include <Bikes/BasicGeometry.h>
#include <Bikes/TypeRegister.h>
//#include "InterpolationFunc.h"
//#include "QuickArray.h"

namespace Bikes
{

namespace Test
{
	struct TestStruct
	{
		~TestStruct()
		{
			int abc=1;
		}
		double func()
		{
			return a+b;
		}
		int a;
		double b;
		ByteStream *bs;
		float c;
	};
	bool Test::test_ByteStream()
	{
	/*	std::vector<char> ba;
		ByteStream bs;
		bs.setByteArray(&ba);

		

		int v1=10;
		float v2=20.20;
		double v3=50.50;
		bs <<v1 <<v2 <<v3;

		{
			TestStruct str;
			str.a=111;
			str.b=222.222;
			str.c=333.333;
			str.bs=&bs;
			bs <<str;
			str.a=0;
			str.b=0;
		}


		int v1_=0;
		float v2_=0;
		double v3_=0;
		TestStruct str_;
		bs.setByteArray(&ba);
		bs>>v1_;
		bs>>v2_;		
		bs>>v3_;
		bs>>str_;

		double d=str_.func();


		int stop_=0;
		return v1_==v1&&v2==v2_&&v3==v3_;
		//*/
		return true;
	}


	bool test_RawArray()
	{
// 		{		
// 			RawArray<TestStruct> rar;
// 			rar.resize(3);
// 			rar[0].a=1;
// 			rar[1].a=2;
// 			rar[2].a=3;
// 			rar.resize(5);
// 			rar[3].a=4;
// 			rar[4].a=5;			
// 		}
		return true;
	}

	bool test_BikesStream()
	{
/*		
		RawArray<char> bs;		
		BikesStream bstr;
		bstr.setByteArray(&bs);
		Point p1(1,11,111);
		Point p2(2,22,222);
		int np=2;
		bstr << np;
		bstr << p1;
		bstr << p2;

		Point p1_;
		Point p2_;
		int np_=0;
		bstr >> np_;
		bstr >> p1_;
		bstr >> p2_;

		int stp=1;
		//*/
		return true;

	}

int func(int x, int y, int z)
{
	return x+y+z;
}




//=====================================================================
//=====================================================================
//=====================================================================
//*
template<class T> class TypeWrapper;

class BaseTypeWrapper
{
public:
	virtual ~BaseTypeWrapper(){}

	virtual void* pObj(){return 0;}

	template<class T>
	T* cast_d()
	{
		if(TypeWrapper<T>* tw=dynamic_cast<TypeWrapper<T>*>(this))
			return tw->obj;
		return 0;
		//---
		//castobj->fcast()
	}

	template<class T>
	T* cast_s()
	{
		return (static_cast<TypeWrapper<T>*>(this))->obj;
	}

};

template<class T> 
class TypeWrapper: public BaseTypeWrapper
{
public:
	void* pObj(){return obj;}
	T *obj;

};


	bool test_main()
	{




//		AbstractPolynomial *apln=new StaticPolynomial<1>(quick_array<rnum>(2,3));


//		rnum y=(*apln)(2);

//		delete apln;
		return true;
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


}
}