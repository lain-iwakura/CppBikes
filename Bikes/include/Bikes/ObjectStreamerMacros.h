#ifndef _BIKES_OBJECTSTREAMMACROS_H_
#define _BIKES_OBJECTSTREAMMACROS_H_
#include <Bikes/MacrosBikes.h>


//=========================================================================

#define BIKES_OBJECTSTREAMER_DECL_EXP(EXP,ObjectStreamerName, ObjClass)		\
class EXP ObjectStreamerName: public Bikes::AbstractObjectStreamer<ObjClass>\
{																			\
	typedef ObjClass ObjType;												\
private:																	\
struct AuxReader															\
{																			\
    template<class T>void add(T &var){bs->read(var);}						\
    void add(const AbstractStreamer& str){bs->read(str);}                   \
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

#define BIKES_OBJECTSTREAMER_DECL(ObjectStreamerName, ObjClass)				\
	BIKES_OBJECTSTREAMER_DECL_EXP(,ObjectStreamerName, ObjClass)		
//-------------------------------------------------------------------------

#define BIKES_OBJECTSTREAMER_DEF_EXTENDED(ObjectStreamerName, ValAccessList, PostReadAction)\
	ObjectStreamerName::ObjectStreamerName(ObjType *obj):Bikes::AbstractObjectStreamer<ObjType>(obj){}\
	ObjectStreamerName::ObjectStreamerName(const ObjType *obj):Bikes::AbstractObjectStreamer<ObjType>(obj){}\
	void ObjectStreamerName::read(Bikes::ByteStream &bstr) const			\
	{																		\
		read(bstr,obj_r);													\
	}																		\
	void ObjectStreamerName::read(Bikes::ByteStream &bstr, ObjType* p)	\
	{																		\
		AuxReader r;r.bs=&bstr;												\
		r.read(p);															\
	}																		\
	void ObjectStreamerName::write(Bikes::ByteStream &bstr) const			\
	{																		\
		write(bstr,obj_w);													\
	}																		\
	void ObjectStreamerName::write(Bikes::ByteStream &bstr, const ObjType* p)\
	{																		\
		AuxWriter w; w.bs=&bstr;											\
		w.write(p);															\
	}																		\
	void ObjectStreamerName::AuxReader::read(ObjType* p)				\
	{																		\
		ValAccessList;														\
		PostReadAction;														\
	}																		\
	void ObjectStreamerName::AuxWriter::write(const ObjType* p)		\
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
    void add(const AbstractStreamer &s){bs->read(s);}						\
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



#define BIKES_ABSTRACTTYPESTREAMER_DECL_EXP(EXP,AbstractTypeStreamerName, AbstractRegistrableTypeClass, AbstractRegistrableTypePtrClass)\
class EXP AbstractTypeStreamerName: public Bikes::AbstractTypeStreamer<AbstractRegistrableTypeClass,AbstractRegistrableTypePtrClass,AbstractTypeStreamerName>\
{																			\
public:																		\
typedef AbstractRegistrableTypePtrClass ART_PtrClass;						\
AbstractTypeStreamerName();													\
AbstractTypeStreamerName(ART_PtrClass* ptr);								\
AbstractTypeStreamerName(const ART_PtrClass* ptr);							\
private:																	\
static void Init();															\
};

#define BIKES_ABSTRACTTYPESTREAMER_DECL(AbstractTypeStreamerName, AbstractRegistrableTypeClass, AbstractRegistrableTypePtrClass)\
	BIKES_ABSTRACTTYPESTREAMER_DECL_EXP(,AbstractTypeStreamerName, AbstractRegistrableTypeClass, AbstractRegistrableTypePtrClass)

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
AbstractTypeStreamerName::AbstractTypeStreamerName()						\
{																			\
	Init();																	\
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

#define BIKES_ABSTRACTTYPESTREAMER_DECLDEF(AbstractTypeStreamerName, AbstractRegistrableTypeClass, AbstractRegistrableTypePtrClass, addObjectStreamer_list )\
class AbstractTypeStreamerName: public Bikes::AbstractTypeStreamer<AbstractRegistrableTypeClass,AbstractRegistrableTypePtrClass,AbstractTypeStreamerName>\
{																			\
public:																		\
	AbstractTypeStreamerName()												\
	{																		\
		Init();																\
	}																		\
	AbstractTypeStreamerName(AbstractRegistrableTypePtrClass* ptr)			\
	{																		\
		Init();																\
		setObject(ptr);														\
	}																		\
	AbstractTypeStreamerName(const AbstractRegistrableTypePtrClass* ptr)	\
	{																		\
		Init();																\
		setObject(ptr);														\
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

//-------------------------------------------------------------------------

//#define BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DECL(AbstractTypeStreamerName, AddStreamerName)\
namespace Aux																\
{																			\
	/*const Bikes::Aux::AbstractTypeStreamerInitor<AbstractTypeStreamerName,AddStreamerName> initor_##AbstractTypeStreamerName##_add_##AddStreamerName;*/\
	class AbstractTypeStreamerNameInitor_add_##AddStreamerName\
	{\
	public:\
		AbstractTypeStreamerNameInitor_add_##AddStreamerName();\
	};\
	const AbstractTypeStreamerNameInitor_add_##AddStreamerName initor_##AbstractTypeStreamerName##_add_##AddStreamerName;\
}	


//#define BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DEF(AbstractTypeStreamerName, AddStreamerName)\
namespace Aux\
{\
	AbstractTypeStreamerNameInitor_add_##AddStreamerName::AbstractTypeStreamerNameInitor_add_##AddStreamerName()\
	{\
		static bool i=false;\
		if(!i)\
		{\
			i=true;\
			AbstractTypeStreamerName ats;\
			ats.add<AddStreamerName>();\
		}\
	}\
}
	

#define BIKES_TYPESTREAMER_DECL(AbstractTypeStreamerName, TypeStreamerName, TypeClass)\
	BIKES_OBJECTSTREAMER_DECL(TypeStreamerName,TypeClass)					\
	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DECL(AbstractTypeStreamerName,TypeStreamerName)\
	namespace Aux															\
	{																		\
		typedef AbstractTypeStreamerName TypeStreamerName_##AbstractStreamer;\
	}


// #define BIKES_TYPESTREAMER_DECLDEF(AbstractTypeStreamerName, TypeStreamerName, TypeClass, ValAccessList)\
// 	BIKES_OBJECTSTREAMER_DECLDEF(TypeStreamerName,TypeClass,ValAccessList)\
// 	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DECL(AbstractTypeStreamerName,TypeStreamerName)

// #define BIKES_TYPESTREAMER_DECLDEF_EXTENDED(AbstractTypeStreamerName, TypeStreamerName, TypeClass, ValAccessList, PostReadAction)\
// 	BIKES_OBJECTSTREAMER_DECLDEF_EXTENDED(TypeStreamerName,TypeClass,ValAccessList,PostReadAction)\
// 	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER(AbstractTypeStreamerName,TypeStreamerName)

#define BIKES_TYPESTREAMER_DEF_EXTENDED(TypeStreamerName, TypeClass, ValAccessList, PostReadAction)\
	BIKES_OBJECTSTREAMER_DEF_EXTENDED(TypeStreamerName,TypeClass,ValAccessList,PostReadAction)\
	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DEF(Aux::TypeStreamerName_##AbstractStreamer,TypeStreamerName)

#define BIKES_TYPESTREAMER_DEF(TypeStreamerName, TypeClass, ValAccessList)\
	BIKES_OBJECTSTREAMER_DEF(TypeStreamerName,TypeClass)\
	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DEF(Aux::TypeStreamerName_##AbstractStreamer,TypeStreamerName)
	
//=========================================================================


#define BIKES_MULTITYPESTREAMER_DECLDEF(MultiTypeStreamerName, addObjectStreamer_list)\
class MultiTypeStreamerName: public Bikes::MultiTypeStreamer<Bikes::TypeCollector<MultiTypeStreamerName> >\
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
	add<Bikes::ValueStreamer<bool> >();										\
	add<Bikes::ValueStreamer<char> >();										\
	add<Bikes::ValueStreamer<short> >();									\
	add<Bikes::ValueStreamer<unsigned short> >();							\
	add<Bikes::ValueStreamer<int> >();										\
	add<Bikes::ValueStreamer<unsigned int> >();								\
	add<Bikes::ValueStreamer<long> >();										\
	add<Bikes::ValueStreamer<unsigned long> >();							\
	add<Bikes::ValueStreamer<unsigned long long> >();						\
	add<Bikes::ValueStreamer<float> >();									\
	add<Bikes::ValueStreamer<double> >();



#endif
