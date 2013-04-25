#ifndef _BIKES_OBJECTSTREAMMACROS_H_
#define _BIKES_OBJECTSTREAMMACROS_H_
#include <Bikes/MacrosBikes.h>


//=========================================================================

#define BIKES_OBJECTSTREAMER_DECL(ObjectStreamerName, ObjClass)				\
																			\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>	\
{																			\
private:																	\
struct AuxReader															\
{																			\
	template<class T>void add(T &var){bs->read(var);}						\
	void read(ObjClass *p);													\
	ByteStream *bs;															\
};																			\
struct AuxWriter															\
{																			\
template<class T>void add(const T &var){bs->write(var);}					\
void write(const ObjClass *p);												\
ByteStream *bs;																\
};																			\
public:																		\
	ObjectStreamerName(ObjClass *obj=0);									\
	ObjectStreamerName(const ObjClass *obj);								\
	void read(Bikes::ByteStream &bstr) const;								\
	static void read(Bikes::ByteStream &bstr, ObjClass* p);					\
	void write(Bikes::ByteStream &bstr) const;								\
	static void write(Bikes::ByteStream &bstr, const ObjClass* p);			\
};

//-------------------------------------------------------------------------

#define BIKES_OBJECTSTREAMER_DEF_EXTENDED(ObjectStreamerName, ValAccessList, PostReadAction)\
	ObjectStreamerName::ObjectStreamerName(StreamerType *obj):Bikes::AbstractObjectStreamer<StreamerType>(obj){}\
	ObjectStreamerName::ObjectStreamerName(const StreamerType *obj):Bikes::AbstractObjectStreamer<StreamerType>(obj){}\
	void ObjectStreamerName::read(Bikes::ByteStream &bstr) const			\
	{																		\
		read(bstr,obj_r);													\
	}																		\
	void ObjectStreamerName::read(Bikes::ByteStream &bstr, StreamerType* p)	\
	{																		\
		AuxReader r;r.bs=&bstr;												\
		r.read(p);															\
		PostReadAction;														\
	}																		\
	void ObjectStreamerName::write(Bikes::ByteStream &bstr) const			\
	{																		\
		write(bstr,obj_w);													\
	}																		\
	void ObjectStreamerName::write(Bikes::ByteStream &bstr, const StreamerType* p)\
	{																		\
		AuxWriter w; w.bs=&bstr;											\
		w.write(p);															\
	}																		\
	void ObjectStreamerName::AuxReader::read(StreamerType* p)				\
	{																		\
		ValAccessList;														\
	}																		\
	void ObjectStreamerName::AuxWriter::write(const StreamerType* p)		\
	{																		\
		ValAccessList;														\
	}

//-------------------------------------------------------------------------

#define BIKES_OBJECTSTREAMER_DEF(ObjectStreamerName, ValAccessList)			\
	BIKES_OBJECTSTREAMER_DEF_EXTENDED(ObjectStreamerName, ValAccessList, )


//=========================================================================


#define BIKES_ABSTRACTTYPESTREAMER_DECL(AbstractTypeStreamerName, AbstractRegistrableTypeClass, AbstractRegistrableTypePtrClass)\
class AbstractTypeStreamerName: public AbstractTypeStreamer<AbstractRegistrableTypeClass,AbstractRegistrableTypePtrClass,AbstractTypeStreamerName>\
{																			\
public:																		\
AbstractTypeStreamerName(AbstractRegistrableTypePtrClass* ptr);				\
AbstractTypeStreamerName(const AbstractRegistrableTypePtrClass* ptr);		\
private:																	\
typedef AbstractRegistrableTypePtrClass ART_PtrClass;						\
static void Init();															\
};

//-------------------------------------------------------------------------

#define BIKES_ABSTRACTTYPESTREAMER_DEF(AbstractTypeStreamerName, addObjectStreamer_list )\
void AbstractTypeStreamerName::Init()										\
{																			\
	if(streamersCount()==0)													\
	{																		\
		addObjectStreamer_list;												\
	}																		\
}																			\
AbstractTypeStreamerName::AbstractTypeStreamerName(ART_PtrClass* ptr)		\
{																			\
	Init();																	\
	setObject(ptr);															\
}																			\
AbstractTypeStreamerName::AbstractTypeStreamerName(const ART_PtrClass* ptr)	\
{																			\
	Init();																	\
	setObject(ptr);															\
}	

//=========================================================================



#endif