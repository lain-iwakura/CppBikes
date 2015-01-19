#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/StreamerInterface.h>
#include <Bikes/Creation/CreationManager.h>
#include <Bikes/TypeTools/Info.h>
#include <Bikes/Exception.h>

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

    virtual StreamType* createObject() const = 0;

    virtual void destroyObject(StreamType* obj) const = 0;
    
    virtual StreamType* copyObject(StreamType* obj) const = 0;    

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
    class CreationManagerT = SimpleCopyingManager<StreamTypeT>
>
class ObjectStreamer : public ObjectStreamerInterface<StreamTypeT>
{
public:

    typedef StreamTypeT StreamType;
    typedef ObjectStreamer<StreamTypeT, CreationManagerT> ThisType;
    typedef CreationManagerT CreationManager;

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
        StreamType* obj = createObject();
        if (obj)
        {
            try
            {
                read(bs, *obj);
            }
            catch(...)
            {
                destroyObject(obj);
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

    virtual StreamType* createObject() const
    {
        return CreationManager::create();
    }

    virtual void destroyObject(StreamType* obj) const
    {
        CreationManager::destroy(obj);
    }

    virtual StreamType* copyObject(StreamType* obj) const
    {
        return CreationManager::createCopy(obj);
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
    class CreationManagerT = typename AdaptebleObjectStreamerT::CreationManager
    >
class ObjectStreamerAdapter:
    public BaseObjectStreamerT
{
public:

    typedef BaseObjectStreamerT BaseObjectStreamer;
    typedef typename BaseObjectStreamerT::StreamType StreamType;
    typedef AdaptebleObjectStreamerT AdaptebleObjectStreamer;
    typedef typename AdaptebleObjectStreamerT::StreamType AdaptebleStreamType;
    typedef CreationManagerT CreationManager;

    StreamType* createObject() const 
    {
        return CreationManager::create();
    }

    void destroyObject(StreamType* obj) const 
    {
        CreationManager::destroy(obj);
    }

    virtual StreamType* copyObject(StreamType* obj) const
    {
        return CreationManager::createCopy(obj);
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
            unexpectedRead(bs, obj);
    }

    void write(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = dynamic_cast<const AdaptebleStreamType*>(&obj))
            _objStr.write(bs, *adObj);
        else
            unexpectedWrite(bs, obj);
    }

    void writeWhithSign(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = dynamic_cast<const AdaptebleStreamType*>(&obj))
        {
            bs.writeRecurrentData(typeSignature());
            _objStr.tryWrite(bs, *adObj);
        }
        else
            unexpectedWriteWithSign(bs, obj);
    }

protected:

    virtual void unexpectedRead(ByteStream&bs, StreamType& obj) const
    {
        unexpectedType(obj);
    }

    virtual void unexpectedWrite(ByteStream&bs, const StreamType& obj) const
    {
        unexpectedType(obj);
    }

    virtual void unexpectedWriteWithSign(ByteStream&bs, const StreamType& obj) const
    {
        unexpectedType(obj);
    }

    virtual void unexpectedType(const StreamType& obj) const
    {
        Inner::throwUnexpectedStreamType(obj, *this);
    }

private:
    static const AdaptebleObjectStreamer _objStr;
};

template< class B, class A, class C >
const A ObjectStreamerAdapter<B, A, C >::_objStr;

}

#endif // <- INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
