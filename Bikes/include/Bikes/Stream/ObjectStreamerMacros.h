#ifndef INCLUDE_BIKES_STREAM_OBJECTSTREAMERMACROS_H
#define INCLUDE_BIKES_STREAM_OBJECTSTREAMERMACROS_H


//==============================================================================
#define INNERBIKES_OBJ_ACCES_ALIASES(StreamType)                               \
    StreamType* p = &obj;
//==============================================================================
#define BIKES_OBJECTSTREAMER_DECL_EXP_CRMNG(EXP, StreamerName, ObjClass, CrMng)\
class EXP StreamerName:                                                        \
    public Bikes::ObjectStreamer<ObjClass, CrMng>                              \
{                                                                              \
public:                                                                        \
    typedef Bikes::ObjectStreamer<ObjClass, CrMng> Base;                       \
    typedef Base::CreationManagmentPolicy CreationManagmentPolicy;             \
    typedef Base::StreamType StreamType;                                       \
                                                                               \
    StreamerName();                                                            \
    explicit StreamerName(StreamType &obj);                                    \
    explicit StreamerName(const StreamType& obj);                              \
                                                                               \
    void read(Bikes::ByteStream &bstr, StreamType& obj) const;                 \
    void write(Bikes::ByteStream &bstr, const StreamType& obj) const;          \
                                                                               \
    const Bikes::ByteArray& signature() const;                                 \
private:                                                                       \
    struct _AuxReader;                                                         \
    struct _AuxWriter;                                                         \
};
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECL_EXP(EXP, StreamerName, ObjClass)             \
    BIKES_OBJECTSTREAMER_DECL_EXP_CRMNG(EXP, StreamerName, ObjClass, Bikes::ObjectStreamer<ObjClass>::CreationManagmentPolicy)
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECL_CRMNG(StreamerName, ObjClass, CrMng)         \
    BIKES_OBJECTSTREAMER_DECL_EXP_CRMNG(,StreamerName, ObjClass, CrMng)
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECL(StreamerName, ObjClass)                      \
    BIKES_OBJECTSTREAMER_DECL_EXP(, StreamerName, ObjClass)
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DEF_EXT(StreamerName, ValAccessList, PostReadAction)\
    struct StreamerName::_AuxReader                                            \
    {                                                                          \
        _AuxReader(Bikes::ByteStream *_bs) :bs(_bs){}                          \
        template<class T> void add(T &var) const{ bs->read(var); }             \
        void add(const Bikes::IStreamer& str) const { bs->read(str); }         \
        void read(StreamerName::StreamType& obj)                               \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(StreamerName::StreamType)             \
            ValAccessList;                                                     \
            PostReadAction;                                                    \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
    struct StreamerName::_AuxWriter                                            \
    {                                                                          \
        _AuxWriter(Bikes::ByteStream *_bs) :bs(_bs){}                          \
        template<class T>void add(const T &var){ bs->write(var); }             \
        void write(const StreamerName::StreamType& obj)                        \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(const StreamerName::StreamType)       \
            ValAccessList;                                                     \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
                                                                               \
    StreamerName::StreamerName()                                               \
    {                                                                          \
    }                                                                          \
    StreamerName::StreamerName(StreamType& obj):                               \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
    StreamerName::StreamerName(const StreamType& obj):                         \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
    void StreamerName::read(Bikes::ByteStream &bstr, StreamType& obj) const    \
    {                                                                          \
        _AuxReader r(&bstr);                                                   \
        r.read(obj);                                                           \
    }                                                                          \
    void StreamerName::write(Bikes::ByteStream &bstr, const StreamType& obj) const   \
    {                                                                          \
        _AuxWriter w(&bstr);                                                   \
        w.write(obj);                                                          \
    }                                                                          \
    const Bikes::ByteArray& StreamerName::signature() const                    \
    {                                                                          \
        static const Bikes::ByteArray s(#StreamerName);                        \
        return s;                                                              \
    }

//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DEF(StreamerName, ValAccessList)			       \
	BIKES_OBJECTSTREAMER_DEF_EXT(StreamerName, ValAccessList, )
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECLDEF_EXT_CRMNG(StreamerName, ObjClass, CrMng, ValAccessList, PostReadAction)\
class StreamerName:                                                            \
    public Bikes::ObjectStreamer<ObjClass, CrMng>                              \
{                                                                              \
public:                                                                        \
    typedef Bikes::ObjectStreamer<ObjClass, CrMng> Base;                       \
    typedef Base::CreationManagmentPolicy CreationManagmentPolicy;             \
    typedef Base::StreamType StreamType;                                       \
                                                                               \
    StreamerName()                                                             \
    {                                                                          \
    }                                                                          \
    explicit StreamerName(StreamType &obj) :                                   \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
    explicit StreamerName(const StreamType& obj) :                             \
        Base(obj)                                                              \
    {                                                                          \
    }                                                                          \
                                                                               \
    void read(Bikes::ByteStream &bstr, StreamType& obj) const                  \
    {                                                                          \
        _AuxReader r(&bstr);                                                   \
        r.read(obj);                                                           \
    }                                                                          \
    void write(Bikes::ByteStream &bstr, const StreamType& obj) const           \
    {                                                                          \
        _AuxWriter w(&bstr);                                                   \
        w.write(obj);                                                          \
    }                                                                          \
                                                                               \
    const ByteArray& signature() const;                                        \
    {                                                                          \
        static const ByteArray s(#StreamerName);                               \
        return s;                                                              \
    }                                                                          \                                                                         \
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
        void add(const Bikes::IStreamer& str) const                            \
        {                                                                      \
            bs->read(str);                                                     \
        }                                                                      \
        void read(StreamerName::StreamType& obj)                               \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(StreamerName::StreamType)             \
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
        void write(const StreamerName::StreamType& obj)                        \
        {                                                                      \
            INNERBIKES_OBJ_ACCES_ALIASES(const StreamerName::StreamType)       \
            ValAccessList;                                                     \
        }                                                                      \
        Bikes::ByteStream *bs;                                                 \
    };                                                                         \
};
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECLDEF_EXT(StreamerName, ObjClass, ValAccessList, PostReadAction)   \
    BIKES_OBJECTSTREAMER_DECLDEF_EXT_CRMNG(StreamerName, ObjClass, Bikes::ObjectStreamer<ObjClass>::CreationManagmentPolicy, ValAccessList, PostReadAction)
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECLDEF_CRMNG(StreamerName, ObjClass, CrMng, ValAccessList)   \
    BIKES_OBJECTSTREAMER_DECLDEF_EXT_CRMNG(StreamerName, ObjClass, CrMng, ValAccessList, )
//------------------------------------------------------------------------------
#define BIKES_OBJECTSTREAMER_DECLDEF(StreamerName, ObjClass, ValAccessList)    \
    BIKES_OBJECTSTREAMER_DECLDEF_EXT(StreamerName, ObjClass, ValAccessList,)
//------------------------------------------------------------------------------


#endif // <- INCLUDE_BIKES_STREAM_OBJECTSTREAMERMACROS_H
