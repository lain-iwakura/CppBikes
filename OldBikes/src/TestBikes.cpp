#include <Bikes/TestBikes.h>
//#include <Bikes/ByteStream.h>
#include <Bikes/RawArray.h>
#include <Bikes/BikeStreamer.h>
#include <Bikes/BasicGeometry.h>
#include <Bikes/List.h>
//#include "InterpolationFunc.h"
#include "QuickArray.h"
#include "ObjectStreamer.h"
#include "BikeStreamer.h"
#include "TypeCollector.h"
#include <vector>
#include "AbstractRegistrableType.h"



namespace Bikes
{

#ifdef PREBIKES_DEV_TESTBIKES

namespace Test
{
// 
// 	test_GlobalObjectClass::test_GlobalObjectClass()
// 	{
// 		int a=0;
// 		a++;
// 	}

    bool test_ByteStream()
	{

		int i=11;
		float f=22.22;
		double d=33.33;
		//const std::vector<StreamVal>& svs=quick_vector_val<StreamConstVal>(i,f,d);

		Point p(1,22,333);		
		Vector ve(0.1,0.2,0.3,p);
		Basis b; b.setOrtoBasis_InXY_ByI(ve); b.setO(p);

		ByteArray ba;
		ByteStream bs(&ba);

		List<Point> ps;
		ps+=Point(1,11,111);
		ps+=Point(2,22,222);
		ps+=Point(3,33,333);
		bs << i << f <<d;
		bs << MultiBikeStreamer(&p);
		bs << MultiBikeStreamer(&ve);
		bs << MultiBikeStreamer(&b);
		bs << arrayStreamer<PointStreamer>(&ps);
		
		//bs << i << f << d;

		std::vector<char> v; 
		ba.toVector(v);	


		int i_;
		float f_;
		double d_;
		Point p_;
		Vector v_;
		Basis b_;
		List<Point> ps_;
		

		bs >> MultiBikeStreamer(&i_);
		bs >> MultiBikeStreamer(&f_);
		bs >> MultiBikeStreamer(&d_);
		bs >> MultiBikeStreamer(&p_);
		bs >> MultiBikeStreamer(&v_);
		bs >> MultiBikeStreamer(&b_);
		bs >> arrayStreamer<PointStreamer>(&ps_);

		
		return (i==i_)&&
			(f==f_)&&
			(d==d_)&&
			(p==p_)&&
			(v_==ve)&&
			(v_.anchor==ve.anchor)&&
			(b.i==b_.i)&&
			(b.j==b_.j)&&
			(b.k==b_.k)&&
			(b.O==b.O);
	}


	bool test_RawArray()
	{
		return true;
	}	


class XClass: public AClass
{
public:
	BIKES_REGISTRABLETYPE_DECL(XClass)
	XClass():a(2),b(3){}
	int vfunc(){ return a+b;}
	int a;
	int b;
};

class YClass: public AClass
{
public:
	BIKES_REGISTRABLETYPE_DECL(YClass)
	YClass():c(10){}
	int vfunc(){return c;}
	int c;
	static const XClass xc;
};

const XClass YClass::xc;



BIKES_OBJECTSTREAMER_DEF(XClassStreamer,add(p->a);add(p->b))
BIKES_OBJECTSTREAMER_DEF(YClassStreamer,add(p->c))





BIKES_ABSTRACTTYPESTREAMER_DEF(AClassStreamer,
							add<XClassStreamer>();
							add<YClassStreamer>()
								)



	bool test_AbstractTypeStreamer()
	{
		ByteArray ba;
		ByteStream bs(&ba);

		Ptr<AClass>::Shared xc(new XClass());
		Ptr<AClass>::Shared yc(new YClass());
		int xc_a=((YClass*)yc.get())->xc.a;

		std::vector<Ptr<AClass>::Shared > aarr;
		aarr.push_back(xc);
		aarr.push_back(yc);

	
// 		AbstractTypeStreamer<AClass, Ptr<AClass>::Shared > ats;
// 		ats.add<XClassStreamer>();
// 		ats.add<YClassStreamer>();

		AClassStreamer ats(&xc);

		
	//	AClassStreamer ats2;

		int i1=111;
		int i2=222;
		bs << i1;
		//ats.setObject(&xc);
		bs << arrayStreamer<AClassStreamer>(&aarr);
		//ats.setObject(&yc);
		//bs << AClassStreamer(&yc);
		bs << i2;


		Ptr<AClass>::Shared ac1;
		Ptr<AClass>::Shared ac2;

		std::vector<Ptr<AClass>::Shared > aarr_;
		int i1_;
		int i2_;

		bs >> i1_;
		bs >> arrayStreamer<AClassStreamer>(&aarr_);
		//ats.setObject(&ac1);
		//bs >> AClassStreamer(&ac1);
		//ats.setObject(&ac2);
		//bs >> AClassStreamer(&ac2);
		bs >> i2_;
		
		return true;
	}


	bool test_TypeCollector()
	{
		//int gid1=TypeGlobalRegister<int>::typeId;
		//int gid2=TypeGlobalRegister<float>::typeId;

		int ic1=TypeCollector<int>::typeCount();
		int id11=TypeCollector<int>::typeId<int>();
		int id12=TypeCollector<int>::typeId<float>();
		int id13=TypeCollector<int>::typeId<double>();

		int ic2=TypeCollector<char>::typeCount();
		int id21=TypeCollector<char>::typeId<float>();
		int id22=TypeCollector<char>::typeId<int>();
		int id23=TypeCollector<char>::typeId<double>();

// 		int id12_=TypeCollector<int>::typeGlobalId<float>();
// 		int id21_=TypeCollector<char>::typeGlobalId<float>();
// 		int id11_=TypeCollector<int>::typeGlobalId<int>();
// 		int id22_=TypeCollector<char>::typeGlobalId<int>();


		return true;
	}

#define MMM(X) X;

	bool test_main()
	{		
		int v1=3;
		int v2=2;
		int v3=0;
		MMM(v3=v1+v2;v1++)

		test_TypeCollector();
		test_AbstractTypeStreamer();
		test_ByteStream();
		return true;
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


}//Test

#endif
}// Bikes
