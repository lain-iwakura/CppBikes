#ifndef _BIKES_OBJECTSTREAMMACROS_H_
#define _BIKES_OBJECTSTREAMMACROS_H_
#include <Bikes/MacrosBikes.h>


#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_0(handlerFunc,parPrefix) 
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_1(handlerFunc,parPrefix) handlerFunc(parPrefix##1);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_2(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_3(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_4(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3); handlerFunc(parPrefix##4);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_5(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3); handlerFunc(parPrefix##4); handlerFunc(parPrefix##5);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_6(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3); handlerFunc(parPrefix##4); handlerFunc(parPrefix##5); handlerFunc(parPrefix##6);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_7(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3); handlerFunc(parPrefix##4); handlerFunc(parPrefix##5); handlerFunc(parPrefix##6); handlerFunc(parPrefix##7);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_8(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3); handlerFunc(parPrefix##4); handlerFunc(parPrefix##5); handlerFunc(parPrefix##6); handlerFunc(parPrefix##7); handlerFunc(parPrefix##8);
#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_9(handlerFunc,parPrefix) handlerFunc(parPrefix##1); handlerFunc(parPrefix##2); handlerFunc(parPrefix##3); handlerFunc(parPrefix##4); handlerFunc(parPrefix##5); handlerFunc(parPrefix##6); handlerFunc(parPrefix##7); handlerFunc(parPrefix##8); handlerFunc(parPrefix##9);




#define MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,N)\
	template<MACROSBIKES_CT##N>                                            \
	void exec(MACROSBIKES_##TPREFIX##N)                                    \
	{                                                                      \
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_##N(hObj->handlerFunc,par)   \
	}
	

#define MACROSBIKES_HANDLER_MANYPARFUNC_TO_ONEPARFUNC_DECL(HandlerName,HandlerClass,handlerFunc,TPREFIX)\
	class HandlerName                                                      \
	{                                                                      \
	public:                                                                \
		HandlerName(HandlerClass * obj): hObj(obj){}                       \
		void exec(){}                                                      \
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,1)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,2)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,3)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,4)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,5)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,6)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,7)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,8)\
		MACROSBIKES_MANYPARFUNC_TO_ONEPARFUNC_DECL_N(handlerFunc,TPREFIX,9)\
		HandlerClass *hObj;                                                \
	};


namespace Bikes
{
namespace Aux
{
	MACROSBIKES_HANDLER_MANYPARFUNC_TO_ONEPARFUNC_DECL(byteStream_readManyHandler,ByteStream,read,TTRP)
	MACROSBIKES_HANDLER_MANYPARFUNC_TO_ONEPARFUNC_DECL(byteStream_readManyStreamersHandler,ByteStream,read,TTCRP)
	MACROSBIKES_HANDLER_MANYPARFUNC_TO_ONEPARFUNC_DECL(byteStream_writeManyHandler,ByteStream,write,TTCRP)	
}
}	


#define BIKES_OBJECTSTREAMER_DECL(ObjectStreamerName, ObjClass)\
class ObjClass;\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>   \
{                                                                          \
public:                                                                    \
	ObjectStreamerName(ObjClass *obj);\
	ObjectStreamerName(const ObjClass *obj);\
	void read(Bikes::ByteStream &bstr) const;                                      \
	static void read(Bikes::ByteStream &bstr, ObjClass* p);                        \
	void write(Bikes::ByteStream &bstr) const;                                     \
	static void write(Bikes::ByteStream &bstr, const ObjClass* p);                 \
};


#define BIKES_OBJECTSTREAMER_DEF_EXTENDED(ObjectStreamerName, ValAccessList, StreamersAccessList, PostReadAction)\
	ObjectStreamerName::ObjectStreamerName(StreamerType *obj):Bikes::AbstractObjectStreamer<StreamerType>(obj){}\
	ObjectStreamerName::ObjectStreamerName(const StreamerType *obj):Bikes::AbstractObjectStreamer<StreamerType>(obj){}\
	void ObjectStreamerName::read(Bikes::ByteStream &bstr) const			\
	{																		\
		read(bstr,obj_r);													\
	}																		\
																			\
	void ObjectStreamerName::read(Bikes::ByteStream &bstr, StreamerType* p)		\
	{																		\
		Bikes::Aux::byteStream_readManyHandler h(&bstr);					\
		Bikes::Aux::byteStream_readManyStreamersHandler hs(&bstr);			\
		h.exec ValAccessList ;												\
		hs.exec StreamersAccessList ;										\
	}																		\
	void ObjectStreamerName::write(Bikes::ByteStream &bstr) const			\
	{																		\
		write(bstr,obj_w);													\
	}																		\
	void ObjectStreamerName::write(Bikes::ByteStream &bstr, const StreamerType* p)\
	{																		\
		Bikes::Aux::byteStream_writeManyHandler h(&bstr);					\
		h.exec ValAccessList ;												\
		h.exec StreamersAccessList ;										\
	}																		


#define BIKES_OBJECTSTREAMER_DEF(ObjectStreamerName, ObjClass, ValAccessList, StreamersAccessList)\
	BIKES_OBJECTSTREAMER_DEF_EXTENDED(ObjectStreamerName, ObjClass, ValAccessList, StreamersAccessList,)



#define BIKES_OBJECTSTREAMER_DECLDEF_EXTENDED(ObjectStreamerName, ObjClass, ValAccessList, StreamersAccessList, PostReadAction )\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>   \
{                                                                          \
public:                                                                    \
	ObjectStreamerName(ObjClass *obj):AbstractObjectStreamer<ObjClass>(obj){}\
	ObjectStreamerName(const ObjClass *obj):AbstractObjectStreamer<ObjClass>(obj){}\
	void read(Bikes::ByteStream &bstr) const                               \
	{                                                                      \
		read(bstr,obj_r);                                                  \
	}                                                                      \
	static void read(Bikes::ByteStream &bstr, ObjClass* p)                 \
	{                                                                      \
		Bikes::Aux::byteStream_readManyHandler h(&bstr);                   \
		Bikes::Aux::byteStream_readManyStreamersHandler hs(&bstr);         \
		h.exec ValAccessList ;                                             \
		hs.exec StreamersAccessList ;                                      \
		PostReadAction ;                                                   \
	}                                                                      \
	void write(Bikes::ByteStream &bstr) const                              \
	{                                                                      \
		write(bstr,obj_w);                                                 \
	}                                                                      \
	static void write(Bikes::ByteStream &bstr, const ObjClass* p)          \
	{                                                                      \
		Bikes::Aux::byteStream_writeManyHandler h(&bstr);                  \
		h.exec ValAccessList ;                                             \
		h.exec StreamersAccessList ;                                       \
	}                                                                      \
};


//																(p->x,p->y,p->z)
#define BIKES_OBJECTSTREAMER_DECLDEF(ObjectStreamerName, ObjClass, ValAccessList, StreamersAccessList)\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>	\
{																			\
public:																		\
																			\
	ObjectStreamerName(ObjClass *obj):AbstractObjectStreamer<ObjClass>(obj){}\
	ObjectStreamerName(const ObjClass *obj):AbstractObjectStreamer<ObjClass>(obj){}\
																			\
	void read(Bikes::ByteStream &bstr) const								\
	{																		\
		read(bstr,obj_r);													\
	}																		\
																			\
	static void read(Bikes::ByteStream &bstr, ObjClass* p)					\
	{																		\
		Bikes::Aux::byteStream_readManyHandler h(&bstr);					\
		Bikes::Aux::byteStream_readManyStreamersHandler hs(&bstr);			\
		h.exec ValAccessList ;												\
		hs.exec StreamersAccessList ;										\
	}																		\
																			\
	void write(Bikes::ByteStream &bstr) const								\
	{																		\
		write(bstr,obj_w);													\
	}																		\
																			\
	static void write(Bikes::ByteStream &bstr, const ObjClass* p)			\
{																			\
	Bikes::Aux::byteStream_writeManyHandler h(&bstr);						\
	h.exec ValAccessList ;													\
	h.exec StreamersAccessList ;											\
}																			\
};

//=========================================================================

//#define BIKES_ARRAYSTREAMER_DECL(ArrayStreamerName, ArrayTClass, Obj)\
class ObjClass;\
class ArrayStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>   \
{                                                                          \
public:                                                                    \
	ArrayStreamerName(ObjClass *obj);\
	ArrayStreamerName(const ObjClass *obj);\
	void read(Bikes::ByteStream &bstr) const;                                      \
	static void read(Bikes::ByteStream &bstr, ObjClass* p);                        \
	void write(Bikes::ByteStream &bstr) const;                                     \
	static void write(Bikes::ByteStream &bstr, const ObjClass* p);                 \
};


#endif