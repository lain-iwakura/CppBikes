#ifndef INCLUDE_BIKES_STREAM_OBJECTSTREAMERMACROS_H
#define INCLUDE_BIKES_STREAM_OBJECTSTREAMERMACROS_H


//==============================================================================
#define INNERBIKES_OBJ_ACCES_ALIASES(ObjectType)                               \
    ObjectType* p = &obj;
//==============================================================================
#define BIKES_OBJECTSTREAMER_DECL_EXP(EXP, StreamerName, ObjClass)             \
class EXP StreamerName:                                                        \
    public Bikes::AbstractObjectStreamer<ObjClass>                             \
{                                                                              \
public:                                                                        \
    typedef ObjClass ObjectType;                                               \
    typedef Bikes::AbstractObjectStreamer<ObjClass> Base;                      \
                                                                               \
    StreamerName();                                                            \
    StreamerName(ObjectType &obj);                                             \
    StreamerName(const ObjectType& obj);                                       \
                                                                               \
    void read(Bikes::ByteStream &bstr) const;                                  \
    void write(Bikes::ByteStream &bstr) const;                                 \
                                                                               \
    static void read(Bikes::ByteStream &bstr, ObjectType& obj);                \
    static void write(Bikes::ByteStream &bstr, const ObjectType& obj);         \
                                                                               \
    const ByteArray& getObjectTypeSignature() const;                           \
    {                                                                          \
        static const ByteArray s(#ObjClass);                                   \
        return s;                                                              \
    }                                                                          \
private:                                                                       \
    struct _AuxReader;                                                         \
    struct _AuxWriter;                                                         \
};
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECL(StreamerName, ObjClass)				       \
    BIKES_OBJECTSTREAMER_DECL_EXP(, StreamerName, ObjClass)
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DEF_EXTENDED(StreamerName, ValAccessList, PostReadAction)\
    struct StreamerName::_AuxReader                                            \
    {                                                                          \
        _AuxReader(Bikes::ByteStream *_bs) :bs(_bs){}                          \
        template<class T> void add(T &var) const{ bs->read(var); }             \
        void add(const Bikes::StreamerInterface& str) const { bs->read(str); } \
        void read(StreamerName::ObjectType& obj)                               \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(StreamerName::ObjectType)             \
            ValAccessList;                                                     \
            PostReadAction;                                                    \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
    struct StreamerName::_AuxWriter                                            \
    {                                                                          \
        _AuxWriter(Bikes::ByteStream *_bs) :bs(_bs){}                          \
        template<class T>void add(const T &var){ bs->write(var); }             \
        void write(const StreamerName::ObjectType& obj)                        \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(const StreamerName::ObjectType)       \
            ValAccessList;                                                     \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
                                                                               \
    StreamerName::StreamerName()                                               \
    {                                                                          \
    }                                                                          \
    StreamerName::StreamerName(ObjectType& obj):                               \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
    StreamerName::StreamerName(const ObjectType& obj):                         \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
    void StreamerName::read(Bikes::ByteStream &bstr) const                     \
    {                                                                          \
        read(bstr,*obj_r);                                                     \
    }                                                                          \
    void StreamerName::read(Bikes::ByteStream &bstr, ObjectType& obj)          \
    {                                                                          \
        _AuxReader r(&bstr);                                                   \
        r.read(obj);                                                           \
    }                                                                          \
    void StreamerName::write(Bikes::ByteStream &bstr) const                    \
    {                                                                          \
        write(bstr,*obj_w);                                                    \
    }                                                                          \
    void StreamerName::write(Bikes::ByteStream &bstr, const ObjectType& obj)   \
    {                                                                          \
        _AuxWriter w(&bstr);                                                   \
        w.write(obj);                                                          \
    }                                                                          

//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DEF(StreamerName, ValAccessList)			       \
	BIKES_OBJECTSTREAMER_DEF_EXTENDED(StreamerName, ValAccessList, )
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECLDEF_EXTENDED(StreamerName, ObjClass)          \
class StreamerName:                                                            \
    public Bikes::AbstractObjectStreamer<ObjClass>                             \
{                                                                              \
public:                                                                        \
    typedef ObjClass ObjectType;                                               \
    typedef Bikes::AbstractObjectStreamer<ObjClass> Base;                      \
                                                                               \
    StreamerName()                                                             \
    {                                                                          \
    }                                                                          \
    StreamerName(ObjectType &obj) :                                            \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
    StreamerName(const ObjectType& obj) :                                      \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
                                                                               \
    void read(Bikes::ByteStream &bstr) const                                   \
    {                                                                          \
        read(bstr, *obj_r);                                                    \
    }                                                                          \
    void write(Bikes::ByteStream &bstr) const                                  \
    {                                                                          \
        write(bstr, *obj_w);                                                   \
    }                                                                          \
                                                                               \
    static void read(Bikes::ByteStream &bstr, ObjectType& obj)                 \
    {                                                                          \
        _AuxReader r(&bstr);                                                   \
        r.read(obj);                                                           \
    }                                                                          \
    static void write(Bikes::ByteStream &bstr, const ObjectType& obj)          \
    {                                                                          \
        _AuxWriter w(&bstr);                                                   \
        w.write(obj);                                                          \
    }                                                                          \
                                                                               \
    const ByteArray& getObjectTypeSignature() const;                           \
    {                                                                          \
        static const ByteArray s(#ObjClass);                                   \
        return s;                                                              \
    }                                                                          \
private:                                                                       \
    struct _AuxReader                                                          \
    {                                                                          \
        _AuxReader(Bikes::ByteStream *_bs):bs(_bs)                             \
        {                                                                      \
        }                                                                      \
        template<class T> void add(T &var) const                               \
        {                                                                      \
            bs->read(var);                                                     \
        }                                                                      \
        void add(const Bikes::StreamerInterface& str) const                    \
        {                                                                      \
            bs->read(str);                                                     \
        }                                                                      \
        void read(StreamerName::ObjectType& obj)                               \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(StreamerName::ObjectType)             \
            ValAccessList;                                                     \
            PostReadAction;                                                    \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
    struct _AuxWriter                                                          \
    {                                                                          \
        _AuxWriter(Bikes::ByteStream *_bs) :bs(_bs)                            \
        {                                                                      \
        }                                                                      \
        template<class T>void add(const T &var)                                \
        {                                                                      \
            bs->write(var);                                                    \
        }                                                                      \
        void write(const StreamerName::ObjectType& obj)                        \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(const StreamerName::ObjectType)       \
            ValAccessList;                                                     \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
};
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECLDEF(StreamerName, ObjClass, ValAccessList)    \
    BIKES_OBJECTSTREAMER_DECLDEF_EXTENDED(StreamerName, ObjClass, ValAccessList, )
//------------------------------------------------------------------------------
/*
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


#define BIKES_TYPESTREAMER_DECL(AbstractTypeStreamerName, TypeStreamerName, TypeClass)\
	BIKES_OBJECTSTREAMER_DECL(TypeStreamerName,TypeClass)					\
	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DECL(AbstractTypeStreamerName,TypeStreamerName)\
	namespace Aux															\
	{																		\
		typedef AbstractTypeStreamerName TypeStreamerName_##StreamerInterface;\
	}


#define BIKES_TYPESTREAMER_DEF_EXTENDED(TypeStreamerName, TypeClass, ValAccessList, PostReadAction)\
	BIKES_OBJECTSTREAMER_DEF_EXTENDED(TypeStreamerName,TypeClass,ValAccessList,PostReadAction)\
	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DEF(Aux::TypeStreamerName_##StreamerInterface,TypeStreamerName)

#define BIKES_TYPESTREAMER_DEF(TypeStreamerName, TypeClass, ValAccessList)\
	BIKES_OBJECTSTREAMER_DEF(TypeStreamerName,TypeClass)\
	BIKES_ABSTRACTTYPESTREAMER_ADDSTREAMER_DEF(Aux::TypeStreamerName_##StreamerInterface,TypeStreamerName)
	
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

//*/

#endif // <- INCLUDE_BIKES_STREAM_OBJECTSTREAMERMACROS_H
