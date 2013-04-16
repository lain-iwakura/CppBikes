#ifndef _BIKES_OBJECTSTREAMMACROS_H_
#define _BIKES_OBJECTSTREAMMACROS_H_
#include <Bikes/MacrosBikes.h>

#define BIKES_OBJECTSTREAMER(ObjClass) ObjClass##Streamer
#define BIKES_OBJECTSTREAMER_BASEDECL(ObjClass,ReadActions,WriteActions) \
class BIKES_OBJECTSTREAMER(ObjClass): public AbstractObjectStreamer<ObjClass> \
{\
public:\
	virtual ~ BIKES_OBJECTSTREAMER(ObjClass){}\
	void read(ByteStream &bstr, ObjClass* p){ReadActions;}\
	void write(ByteStream &bstr,const ObjClass* p){WriteActions;}\
};



//												(x,y,z)
#define BIKES_OBJECTSTREAMER_DECL(ObjClass, ValNameList )\
namespace Bikes{
namespace Aux{
	class Aux##ObjClass##Streamer: public ObjClass\
	{\
	public:\
		void aux_read(){ XX(ObjClass).XXX(x,y,z);}\
	};\
	const Aux##ObjClass##Streamer aux##ObjClass##Streamer;\
}
}


#define BIKES_OBJECTSTREAMER_READACTIONS_1(V1) bstr <<p->V1;
#define BIKES_OBJECTSTREAMER_READACTIONS_2(V1,V2) bstr <<p->V1<<p->V2;
#define BIKES_OBJECTSTREAMER_READACTIONS_3(V1,V2,V3) bstr <<p->V1<<p->V2<<p->V3;
#define BIKES_OBJECTSTREAMER_READACTIONS_4(V1,V2,V3,V4) bstr <<p->V1<<p->V2<<p->V3<<p->V4;
#define BIKES_OBJECTSTREAMER_READACTIONS_5(V1,V2,V3,V4,V5) bstr <<p->V1<<p->V2<<p->V3<<p->V4<<p->V5;

#define BIKES_OBJECTSTREAMER_WRITEACTIONS_1(V1) bstr >>p->V1;
#define BIKES_OBJECTSTREAMER_WRITEACTIONS_2(V1,V2) bstr >>p->V1>>p->V2;
#define BIKES_OBJECTSTREAMER_WRITEACTIONS_3(V1,V2,V3) bstr >>p->V1>>p->V2>>p->V3;
#define BIKES_OBJECTSTREAMER_WRITEACTIONS_4(V1,V2,V3,V4) bstr >>p->V1>>p->V2>>p->V3>>p->V4;
#define BIKES_OBJECTSTREAMER_WRITEACTIONS_5(V1,V2,V3,V4,V5) bstr >>p->V1>>p->V2>>p->V3>>vV4>>p->V5;


BIKES_OBJECTSTREAMER_BASEDECL(Point,BIKES_OBJECTSTREAMER_READACTIONS_3(gx,gy,gz),BIKES_OBJECTSTREAMER_READACTIONS_3(gx,gy,gz))

namespace Bikes
{
namespace Aux
{
	class AuxObjectStreamerDefType{};

	template<MACROSBIKES_CT10_DEFTYPE(AuxObjectStreamerDefType)> class AuxObjectStreamer; 

#define AUXBIKES_OBJECTSTREAMER(CT,TT,TP,PP, TCLP, TCLP_DECL)
	template<CT>
	class AuxObjectStreamer<TT>
	{
	public:
		AuxObjectStreamer(TCLP)

	private:
		TCLP_DECL
	};
}
}
#endif