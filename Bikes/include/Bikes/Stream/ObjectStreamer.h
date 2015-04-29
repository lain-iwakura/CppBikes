#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/StreamerInterface.h>
#include <Bikes/Creation/CreationManager.h>
#include <Bikes/TypeTools/Info.h>
#include <Bikes/Stream/StreamException.h>
#include <Bikes/Stream/StreamPositionSaver.h>

namespace Bikes
{

template<class StreamTypeT>
class ObjectStreamerInterface: public StreamerInterface
{
public:

    typedef StreamTypeT StreamType;
    typedef ObjectStreamerInterface<StreamTypeT> ThisType;

    virtual ~ObjectStreamerInterface()
    {
    }

    virtual  void setObject(StreamType& obj) = 0;

    virtual void setObject(const StreamType& obj) = 0;

    virtual StreamType* rObject() const = 0;

    virtual const StreamType* wObject() const = 0;

    virtual void read(ByteStream& bs) const = 0;

    virtual StreamType* readAndCreate(ByteStream& bs) const = 0;

    virtual void write(ByteStream& bs) const = 0;

    virtual void writeWhithSign(ByteStream& bs) const = 0;    

    virtual StreamType* create() const = 0;

    virtual void destroy(StreamType* obj) const = 0;
    
    virtual StreamType* copy(const StreamType* obj) const = 0;    

    virtual const ByteArray& typeSignature() const = 0;    

    virtual ThisType* clone() const = 0;

//protected:

    virtual void read(ByteStream& bs, StreamType& obj) const = 0;    

    virtual void write(ByteStream& bs, const StreamType& obj) const = 0;

    virtual void writeWithSign(ByteStream& bs, const StreamType& obj) const = 0;

};
//==============================================================================
template<
    class StreamTypeT,
    class CrMngPolicyT = CreationManagment::Simple<StreamTypeT>
>
class ObjectStreamer : public ObjectStreamerInterface<StreamTypeT>
{
public:

    typedef StreamTypeT StreamType;
    typedef ObjectStreamer<StreamTypeT, CrMngPolicyT> ThisType;
    typedef CrMngPolicyT CrMngPolicy;

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

    virtual StreamType* readAndCreate(ByteStream& bs) const //?
    {
        StreamType* obj = create();
        if (obj)
        {
            try
            {
                read(bs, *obj);
            }
            catch(...)
            {
                destroy(obj);
                throw;
            }
        }
        return obj;
    }
    
    void write(ByteStream& bs) const
    {
        BIKES_CHECK_INSTANCE(obj_w);
        write(bs, *obj_w);

    }

    void writeWhithSign(ByteStream& bs) const
    {
        BIKES_CHECK_INSTANCE(obj_w);
        writeWhithSign(bs, *obj_w);
    }

    virtual StreamType* create() const
    {
        return CrMngPolicy::new_object();
    }

    virtual void destroy(StreamType* obj) const
    {
        CrMngPolicy::delete_object(obj);
    }

    virtual StreamType* copy(const StreamType* obj) const
    {
        return MultiCreationManager::new_object(obj);
    }

    virtual const ByteArray& typeSignature() const
    {
        static const ByteArray sig(TT::Info<StreamType>::name);
        return sig;
    }
        
    virtual ThisType* clone() const //?
    {
        return new ThisType(*this); 
    }

//protected:

    virtual void read(ByteStream& bs, StreamType& obj) const
    {
        bs >> obj;
    }

    virtual void write(ByteStream& bs, const StreamType& obj) const
    {
        bs << obj;
    }

    virtual void writeWithSign(ByteStream& bs, const StreamType& obj) const
    {        
        bs.writeRecurrentData(typeSignature());
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

    const ByteArray& typeSignature() const 
    {
        return _objStr.typeSignature();
    }

    void read(ByteStream&bs, StreamType& obj) const 
    {
        if (AdaptebleStreamType* adObj = dynamic_cast<AdaptebleStreamType*>(&obj))
            _objStr.read(bs, *adObj);
        else
            unexpectedType(obj);
    }

    void write(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = dynamic_cast<const AdaptebleStreamType*>(&obj))
            _objStr.write(bs, *adObj);
        else
            unexpectedType(obj);
    }

    void writeWhithSign(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = dynamic_cast<const AdaptebleStreamType*>(&obj))
        {
            StreamPositionSaver sp(&bs);            
            try{
                bs.writeRecurrentData(typeSignature());
                _objStr.write(bs, *adObj);
            }
            catch(Exception::StreamException& e){
                sp.tryRestore(e);
                throw;
            }
        }
        else
            unexpectedType(obj);
    }

protected:

    virtual void unexpectedType(const StreamType& obj) const
    {
        Inner::throwUnexpectedStreamType(obj, *this, true);
    }

private:
    static const AdaptebleObjectStreamer _objStr;
};

template< class B, class A, class C >
const A ObjectStreamerAdapter<B, A, C >::_objStr;

}

#endif // <- INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
