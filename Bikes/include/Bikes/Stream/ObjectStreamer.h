#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/StreamerInterface.h>
#include <Bikes/Creation/CreationManager.h>
#include <Bikes/TypeTools/Info.h>

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

    virtual bool tryRead(ByteStream& bs) const = 0;

    virtual StreamType* tryReadAndCreate(ByteStream& bs) const = 0;    

    virtual bool tryWrite(ByteStream& bs) const = 0;

    bool tryWriteWhithSign(ByteStream& bs) const = 0;

    virtual StreamType* createObject() const = 0;

    virtual void destroyObject(StreamType* obj) const = 0;
    
    virtual StreamType* copyObject(StreamType* obj) const = 0;    

    virtual const ByteArray& typeSignature() const = 0;    

    virtual ThisType* clone() const = 0;

//protected:

    virtual void read(ByteStream& bs, StreamType& obj) const = 0;    

    virtual void write(ByteStream& bs, const StreamType& obj) const = 0;

    virtual void writeWithSign(ByteStream& bs, const StreamType& obj) const = 0;

    virtual bool tryRead(ByteStream& bs, const StreamType& obj) const = 0;

    virtual bool tryWrite(ByteStream& bs, const StreamType& obj) const = 0;
    
    virtual bool tryWriteWithSign(ByteStream& bs, const StreamType& obj) const = 0;
    
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
        if (obj_r)
            read(bs, *obj_r);
    }

    virtual StreamType* readAndCreate(ByteStream& bs) const
    {
        StreamType* obj = createObject();
        if (obj)
            read(bs, *obj);
        return obj;
    }
    
    void write(ByteStream& bs) const
    {
        if (obj_w)
            write(bs, *obj_w);       
    }

    void writeWhithSign(ByteStream& bs) const
    {
        if (obj_w)
            writeWhithSign(bs, *obj_w);
    }

    bool tryRead(ByteStream& bs) const //?
    {
        if (obj_r)
            return tryRead(bs, *obj_r);
        return false;
    }

    virtual StreamType* tryReadAndCreate(ByteStream& bs) const
    {
        StreamType* obj = createObject();
        if (obj)
        {
            if (!tryRead(bs, *obj))
            {
                destroyObject(obj);
                obj = 0;
            }
        }
        return obj;
    }

    bool tryWrite(ByteStream& bs) const
    {
        if (obj_w)
            return tryWrite(bs, obj_w);
        return false;
    }

    bool tryWriteWhithSign(ByteStream& bs) const
    {
        if (obj_w)
            return tryWriteWhithSign(bs, *obj_w);
        return false;
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
        tryRead(bs, obj);
    }

    virtual void write(ByteStream& bs, const StreamType& obj) const
    {
        tryWrite(bs, obj);
    }

    virtual void writeWithSign(ByteStream& bs, const StreamType& obj) const
    {        
        tryWriteWithSign(bs, obj);
    }


    virtual bool tryRead(ByteStream& bs, const StreamType& obj) const
    {
        bs >> obj;
        return true;
    }

    virtual bool tryWrite(ByteStream& bs, const StreamType& obj) const
    {
        bs << obj;
        return true;
    }

    virtual bool tryWriteWithSign(ByteStream& bs, const StreamType& obj) const
    {
        bs.writeRecurrentData(typeSignature());
        write(bs, obj);
        return true;
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

    bool tryRead(ByteStream&bs, StreamType& obj) const 
    {
        if (AdaptebleStreamType* adObj = dynamic_cast<AdaptebleStreamType*>(&obj))
        {
            return _objStr.tryRead(bs, *adObj);
        }
        return false;
    }

    bool tryWrite(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = dynamic_cast<const AdaptebleStreamType*>(&obj))
        {
            return _objStr.tryWrite(bs, *adObj);            
        }
        return false;
    }

    bool tryWriteWhithSign(ByteStream& bs, const StreamType& obj) const 
    {
        if (const AdaptebleStreamType* adObj = dynamic_cast<const AdaptebleStreamType*>(&obj))
        {
            bs.writeRecurrentData(typeSignature());
            return _objStr.tryWrite(bs, *adObj);            
        }
        return false;
    }

private:
    static const AdaptebleObjectStreamer _objStr;
};

template< class B, class A, class C >
const A ObjectStreamerAdapter<B, A, C >::_objStr;

}

#endif // <- INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
