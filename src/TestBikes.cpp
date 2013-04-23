#include <Bikes/TestBikes.h>
//#include <Bikes/ByteStream.h>
#include <Bikes/RawArray.h>
#include <Bikes/BikesStream.h>
#include <Bikes/BasicGeometry.h>
#include <Bikes/TypeRegister.h>
//#include "InterpolationFunc.h"
#include "QuickArray.h"
#include "ObjectStream.h"
#include "BikesStream.h"


Bikes::Aux::byteStream_readManyHandler h(0);

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


	template<class T>
	std::vector<T> quick_std_vector_val(T e1, T e2, T e3)
	{
		std::vector<T> v(3);
		v[0]=e1; v[1]=e2; v[2]=e3;
		return v;
	}

	bool Test::test_ByteStream()
	{

		int i=11;
		float f=22.22;
		double d=33.33;
		//const std::vector<StreamVal>& svs=quick_vector_val<StreamConstVal>(i,f,d);

		Point p(1,22,333);		
		Vector ve(0.1,0.2,0.3,p);
		Basis b; b.setOrtoBasis_InXY_ByI(ve); b.setO(p);

		RawArray<char> ra;
		ByteStream bs(&ra);
	//	bs << quick_vector_val<StreamConstVal>(i,f,d);
		bs << i << f <<d;
		bs << PointStreamer(&p);
		bs << VectorStreamer(&ve);
		bs << BasisStreamer(&b);
		
		//bs << i << f << d;

		std::vector<char> v; 
		ra.toVector(v);
		


		int i_;
		float f_;
		double d_;
		Point p_;
		Vector v_;
		Basis b_;
		

		bs >>i_ >>f_ >> d_;
		//bs >> quick_vector_val<StreamVal>(i_,f_,d_);
		bs >> PointStreamer(&p_);
		bs >> VectorStreamer(&v_);
		bs >> BasisStreamer(&b_);

		


	/*	
		std::vector<char> ba;
		ByteStream bs;
		bs.setByteArray(&ba);

		

		int v1=10;
		float v2=20.20;
		double v3=50.50;

		//bs.multiWrite(quick_std_vector<StreamConstVal>(v1,v2,v3));

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

template<class T> 
int tfunc(const T& v)
{
	//v=3;
	int a=1;
	return v+5;
}

	bool test_main()
	{		
//		AClass *ac=new BClass();
//		int i= ac->vfunc();
//		BClass b;
//		TClass t(ac);

		double v=0.1;
		const double &cv=v;
		int i=tfunc(double(5));

		test_ByteStream();
		return true;
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


}
}