#include <Bikes/TestBikes.h>
//#include <Bikes/ByteStream.h>
#include <Bikes/RawArray.h>
#include <Bikes/BikesStream.h>
#include <Bikes/BasicGeometry.h>
#include <Bikes/TypeRegister.h>
#include <Bikes/List.h>
//#include "InterpolationFunc.h"
#include "QuickArray.h"
#include "ObjectStream.h"
#include "BikesStream.h"
#include "TypeCollector.h"
#include <vector>
#include "AbstractRegistrableType.h"

Bikes::Aux::byteStream_readManyHandler h(0);

namespace Bikes
{



namespace Test
{

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

		List<Point> ps;
		ps+=Point(1,11,111);
		ps+=Point(2,22,222);
		ps+=Point(3,33,333);
		bs << i << f <<d;
		bs << PointStreamer(&p);
		bs << VectorStreamer(&ve);
		bs << BasisStreamer(&b);
		bs << arrayStreamer<PointStreamer>(&ps);
		
		//bs << i << f << d;

		std::vector<char> v; 
		ra.toVector(v);	


		int i_;
		float f_;
		double d_;
		Point p_;
		Vector v_;
		Basis b_;
		List<Point> ps_;
		

		bs >>i_ >>f_ >> d_;
		bs >> PointStreamer(&p_);
		bs >> VectorStreamer(&v_);
		bs >> BasisStreamer(&b_);
		bs >> arrayStreamer<PointStreamer>(&ps_);

		
		return true;
	}


	bool test_RawArray()
	{
		return true;
	}	


class AClass: public AbstractRegistrableType<AClass>
{
public:
	virtual~AClass(){}
	virtual int vfunc(){return 42;}
};

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

BIKES_OBJECTSTREAMER_DECLDEF(XClassStreamer,XClass,(p->a,p->b),())
BIKES_OBJECTSTREAMER_DECLDEF(YClassStreamer,YClass,(p->c),())


BIKES_ABSTRACTTYPESTREAMER_DECL(AClassStreamer,	AClass,std::tr1::shared_ptr<AClass>)

BIKES_ABSTRACTTYPESTREAMER_DEF(AClassStreamer,
							add<XClassStreamer>();
							add<YClassStreamer>()
								)


	bool test_AbstractTypeStreamer()
	{
		ByteArray ba;
		ByteStream bs(&ba);

		std::tr1::shared_ptr<AClass> xc(new XClass());
		std::tr1::shared_ptr<AClass> yc(new YClass());
		int xc_a=((YClass*)yc.get())->xc.a;
	
		AbstractTypeStreamer<AClass, std::tr1::shared_ptr<AClass> > ats;
		ats.add<XClassStreamer>();
		ats.add<YClassStreamer>();
		
	//	AClassStreamer ats2;

		int i1=111;
		int i2=222;
		bs << i1;
		//ats.setObject(&xc);
		bs << AClassStreamer(&xc);
		//ats.setObject(&yc);
		bs << AClassStreamer(&yc);
		bs << i2;


		std::tr1::shared_ptr<AClass> ac1;
		std::tr1::shared_ptr<AClass> ac2;

		int i1_;
		int i2_;

		bs >> i1_;
		//ats.setObject(&ac1);
		bs >> AClassStreamer(&ac1);
		//ats.setObject(&ac2);
		bs >> AClassStreamer(&ac2);
		bs >> i2_;
		


		return true;
	}


#define MMM(X) X;

	bool test_main()
	{		
		int v1=3;
		int v2=2;
		int v3=0;
		MMM(v3=v1+v2;v1++)


		test_AbstractTypeStreamer();
		test_ByteStream();
		return true;
	}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


}//Test
}// Bikes