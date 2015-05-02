#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/IStreamer.h>
#include <Bikes/Creation/CreationManager.h>
#include <Bikes/TypeTools/Info.h>
#include <Bikes/Stream/StreamException.h>
#include <Bikes/Stream/StreamPositionSaver.h>

namespace Bikes
{
//==============================================================================
#define BIKES_OBJECTSTREAMER_CONSTRUCTORS_DECLDEF(ThisObjectStreamer,BaseStreamer)\
    explicit ThisObjectStreamer(StreamType& obj) :                             \
        BaseStreamer(obj)                                                      \
    {}                                                                         \
    explicit ThisObjectStreamer(const StreamType& obj) :                       \
        BaseStreamer(obj)                                                      \
    {}
//------------------------------------------------------------------------------
template<
    class StreamTypeT,
    class CrMngPolicyT = CreationManagment::Simple<StreamTypeT>
>
class ObjectStreamer : 
    public IStreamer,
    public ICreationManager<StreamTypeT>
{
public:

    typedef StreamTypeT StreamType;
    typedef ObjectStreamer<StreamTypeT, CrMngPolicyT> ThisType;
    typedef CrMngPolicyT CreationManagmentPolicy;

    ObjectStreamer():
        obj_w(0), 
        obj_r(0)
    {
    }

    explicit ObjectStreamer(StreamType& obj) :
        obj_w(&obj),
        obj_r(&obj)
    {
    }

    explicit ObjectStreamer(const StreamType& obj) :
		obj_w(&obj),
		obj_r(0)
	{
	}

    virtual ~ObjectStreamer()
    {
    }

    void setObject(StreamType& obj)
	{
		obj_r = &obj;
		obj_w = &obj;
	}

    void setObject(const StreamType& obj)
	{
		obj_w = &obj;
		obj_r = 0;
	}

    StreamType* rObject() const
    {
        return obj_r; 
    }

    const StreamType* wObject() const
    { 
        return obj_w; 
    }

    void read(ByteStream& bs) const
    {
        BIKES_CHECK_INSTANCE(obj_r);
        read(bs, *obj_r);
    }
     
    void write(ByteStream& bs) const
    {
        BIKES_CHECK_INSTANCE(obj_w);
        write(bs, *obj_w);
    }

    StreamType* create() const
    {
        return CreationManagmentPolicy::new_object();
    }

    void destroy(StreamType* obj) const
    {
        CreationManagmentPolicy::delete_object(obj);
    }

    StreamType* copy(const StreamType* obj) const
    {
        return CreationManagmentPolicy::new_object(obj);
    }

    virtual const ByteArray& signature() const
    {
        static const ByteArray sig(TT::Info<StreamType>::name);
        return sig;
    }

    virtual StreamType* readAndCreate(ByteStream& bs) const //?
    {
        StreamType* obj = create();
        if (obj)
        {
            try
            {
                read(bs, *obj);
            }
            catch (std::exception&)
            {
                destroy(obj);
                throw;
            }
        }
        return obj;
    }

    void writeWhithSign(ByteStream& bs) const
    {
        BIKES_CHECK_INSTANCE(obj_w);
        writeWhithSign(bs, *obj_w);
    }
        
    virtual ThisType* clone() const //?
    {
        return new ThisType(*this); 
    }

//protected:

    virtual void read(ByteStream& bs, StreamType& obj) const = 0;

    virtual void write(ByteStream& bs, const StreamType& obj) const = 0;

    virtual void writeWithSign(ByteStream& bs, const StreamType& obj) const
    {        
        bs.writeRecurrentData(signature());
        write(bs, obj);
    }

private:
    const StreamType *obj_w;
    StreamType* obj_r;
};
//==============================================================================
template<
    class BaseObjectStreamerT,
    class AdaptebleObjectStreamerT,
    class CrMngPolicyT = typename AdaptebleObjectStreamerT::CrMngPolicy
    >
class ObjectStreamerAdapter:
    public BaseObjectStreamerT
{
public:

    typedef BaseObjectStreamerT BaseObjectStreamer;
    typedef typename BaseObjectStreamerT::StreamType StreamType;
    typedef AdaptebleObjectStreamerT AdaptebleObjectStreamer;
    typedef typename AdaptebleObjectStreamerT::StreamType AdaptebleStreamType;
    typedef CrMngPolicyT CrMngPolicy;

    BIKES_OBJECTSTREAMER_CONSTRUCTORS_DECLDEF(ObjectStreamerAdapter,BaseObjectStreamerT)

    StreamType* create() const 
    {
        return CrMngPolicy::new_object();
    }

    void destroy(StreamType* obj) const 
    {
        CrMngPolicy::delete_object(obj);
    }

    virtual StreamType* copy(const StreamType* obj) const
    {
        return CrMngPolicy::new_object(obj);
    }

    const ByteArray& signature() const 
    {
        return _objStr.signature();
    }

    void read(ByteStream&bs, StreamType& obj) const 
    {
        if (AdaptebleStreamType* adObj = optimum_cast<AdaptebleStreamType*>(&obj))
            _objStr.read(bs, *adObj);
        else
            unexpectedType(obj);
    }

    void write(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = optimum_cast<const AdaptebleStreamType*>(&obj))
            _objStr.write(bs, *adObj);
        else
            unexpectedType(obj);
    }

    void writeWhithSign(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = optimum_cast<const AdaptebleStreamType*>(&obj))
            _objStr.writeWhithSign(bs, *adObj);   
        else
            unexpectedType(obj);
    }

protected:

    virtual void unexpectedType(const StreamType& obj) const
    {
        Inner::throwUnexpectedStreamType(obj, *this, true);
    }

private:
    const AdaptebleObjectStreamer _objStr;
};

}

#endif // <- INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
