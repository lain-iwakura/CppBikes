#ifndef _BIKES_TESTBIKES_H_
#define _BIKES_TESTBIKES_H_
#include <Bikes/BikeStreamer.h>
#include <Bikes/SmartPtr.h>
#include <Bikes/AbstractRegistrableType.h>

namespace Bikes
{
	
	template<class T>
	bool isPointer(const T&){return false;}

	template<class T>
	bool isPointer(const T*){return true;}

namespace Test
{
	//TODO: добавить тесты


	class AClass: public AbstractRegistrableType<AClass>
	{
	public:
		virtual~AClass(){}
		BIKES_REGISTRABLETYPE_DECL(AClass)
			virtual int vfunc(){return 42;}
	};

	BIKES_ABSTRACTTYPESTREAMER_DECL(AClassStreamer,	AClass, Ptr<AClass>::Shared)

	class XClass;
	class YClass;
	BIKES_OBJECTSTREAMER_DECL(XClassStreamer,XClass)
	BIKES_OBJECTSTREAMER_DECL(YClassStreamer,YClass)

	
	

//	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER(AClassStreamer,XClassStreamer)
//	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER(AClassStreamer,YClassStreamer)

	template<class T>
	class test_GlobalObjectClass
	{
	public:
		test_GlobalObjectClass()
		{
			int a=0;
			a++;
		}
	};

	void test_globalFunc();
	bool test_ByteStream();
	bool test_RawArray();
	bool test_BikesStream();
	bool test_main();

	const test_GlobalObjectClass<int> test_globalObject;
	
}	
}

#endif