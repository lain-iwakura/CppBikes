#ifndef _BIKES_OBJECTSTREAMMACROS_H_
#define _BIKES_OBJECTSTREAMMACROS_H_
#include <Bikes/MacrosBikes.h>


//=========================================================================

#define BIKES_OBJECTSTREAMER_DECL(ObjectStreamerName, ObjClass)				\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>	\
{																			\
private:																	\
struct AuxReader															\
{																			\
	template<class T>void add(T &var){bs->read(var);}						\
	void read(ObjClass *p);													\
	Bikes::ByteStream *bs;													\
};																			\
struct AuxWriter															\
{																			\
	template<class T>void add(const T &var){bs->write(var);}				\
	void write(const ObjClass *p);											\
	Bikes::ByteStream *bs;													\
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

//-------------------------------------------------------------------------

#define BIKES_OBJECTSTREAMER_DECLDEF_EXTENDED(ObjectStreamerName, ObjClass, ValAccessList, PostReadAction)\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>	\
{																			\
private:																	\
struct AuxReader															\
{																			\
	template<class T>void add(T &var){bs->read(var);}						\
	void read(ObjClass *p){ValAccessList;}									\
	Bikes::ByteStream *bs;													\
};																			\
struct AuxWriter															\
{																			\
	template<class T>void add(const T &var){bs->write(var);}				\
	void write(const ObjClass *p){ValAccessList;}							\
	Bikes::ByteStream *bs;													\
};																			\
public:																		\
	ObjectStreamerName(ObjClass *obj=0){setObject(obj);}					\
	ObjectStreamerName(const ObjClass *obj){setObject(obj);}				\
	void read(Bikes::ByteStream &bstr) const{read(bstr,obj_r);}				\
	void write(Bikes::ByteStream &bstr) const{write(bstr,obj_w);}			\
	static void read(Bikes::ByteStream &bstr, ObjClass* p)					\
	{																		\
		AuxReader r;r.bs=&bstr;												\
		r.read(p);															\
		PostReadAction;														\
	}																		\
	static void write(Bikes::ByteStream &bstr, const ObjClass* p)			\
	{																		\
		AuxWriter w; w.bs=&bstr;											\
		w.write(p);															\
	}																		\
};

//-------------------------------------------------------------------------

#define BIKES_OBJECTSTREAMER_DECLDEF(ObjectStreamerName, ObjClass, ValAccessList)\
class ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>	\
{																			\
private:																	\
struct AuxReader															\
{																			\
	template<class T>void add(T &var){bs->read(var);}						\
	void read(ObjClass *p){ValAccessList;}									\
	Bikes::ByteStream *bs;													\
};																			\
struct AuxWriter															\
{																			\
	template<class T>void add(const T &var){bs->write(var);}				\
	void write(const ObjClass *p){ValAccessList;}							\
	Bikes::ByteStream *bs;													\
};																			\
public:																		\
	ObjectStreamerName(ObjClass *obj=0){setObject(obj);}					\
	ObjectStreamerName(const ObjClass *obj){setObject(obj);}				\
	void read(Bikes::ByteStream &bstr) const{read(bstr,obj_r);}				\
	void write(Bikes::ByteStream &bstr) const{write(bstr,obj_w);}			\
	static void read(Bikes::ByteStream &bstr, ObjClass* p)					\
	{																		\
		AuxReader r;r.bs=&bstr;												\
		r.read(p);															\
	}																		\
	static void write(Bikes::ByteStream &bstr, const ObjClass* p)			\
	{																		\
		AuxWriter w; w.bs=&bstr;											\
		w.write(p);															\
	}																		\
};

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
	static bool inited=false;												\
	if(!inited)																\
	{																		\
		inited=true;														\
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


#define BIKES_MULTITYPESTREAMER_DECLDEF(MultiTypeStreamerName, addObjectStreamer_list)\
class MultiTypeStreamerName: public MultiTypeStreamer<TypeCollector<MultiTypeStreamerName> >\
{																			\
public:																		\
	MultiTypeStreamerName()													\
	{																		\
		Init();																\
	}																		\
	template<class T>														\
	MultiTypeStreamerName(T* obj)											\
	{																		\
		Init();																\
		setObject(obj);														\
	}																		\
	template<class T>														\
	MultiTypeStreamerName(const T* obj)										\
	{																		\
		Init();																\
		setObject(obj);														\
	}																		\
private:																	\
	static void Init()														\
	{																		\
		static bool inited=false;											\
		if(!inited)															\
		{																	\
			inited=true;													\
			addObjectStreamer_list;											\
		}																	\
	}																		\
};


#define BIKES_MULTITYPESTREAMER_ADDVALUESTREAMER							\
	add<ValueStreamer<bool> >();											\
	add<ValueStreamer<char> >();											\
	add<ValueStreamer<short> >();											\
	add<ValueStreamer<unsigned short> >();									\
	add<ValueStreamer<int> >();												\
	add<ValueStreamer<unsigned int> >();									\
	add<ValueStreamer<long> >();											\
	add<ValueStreamer<unsigned long> >();									\
	add<ValueStreamer<unsigned long long> >();								\
	add<ValueStreamer<float> >();											\
	add<ValueStreamer<double> >();



#endif