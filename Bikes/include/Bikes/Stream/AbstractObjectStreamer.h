#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/StreamerInterface.h>
#include <Bikes/Creation/CreationManager.h>

namespace Bikes
{

template<
    class StreamTypeT,
    class CreationManagerT = SimpleCopyingManager<StreamTypeT>
>
class AbstractObjectStreamer : public StreamerInterface
{
public:

    typedef StreamTypeT StreamType;
    typedef AbstractObjectStreamer<StreamTypeT, CreationManagerT> ThisType;
    typedef CreationManagerT CreationManager;

    AbstractObjectStreamer():
        obj_w(0), 
        obj_r(0)
    {
    }

    explicit AbstractObjectStreamer(StreamType& obj) :
        obj_w(&obj),
        obj_r(&obj)
    {
    }

    explicit AbstractObjectStreamer(const StreamType& obj) :
		obj_w(&obj),
		obj_r(0)
	{
	}

    virtual ~AbstractObjectStreamer()
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
        {
            read(bs, *obj_r);
        }
        else
        {
            //?
        }
    }

    StreamType* readAndCreate(ByteStream& bs) const
    {
        StreamType* obj = createObject();
        if (obj)
            read(bs, *obj);
        return obj;
    }

    void write(ByteStream& bs) const
    {
        if (obj_w)
        {
            write(bs, *obj_w);
        }
        else
        {
            //?
        }
    }

    virtual StreamType* createObject() const
    {
        return CreationManager::create();
    }

    virtual const ByteArray& typeSignature() const
    {
        static const ByteArray ba; //?
        return ba;
    }

    virtual read(ByteStream& bs, StreamType& obj) const
    {
        bs >> obj;
    }

    virtual write(ByteStream& bs, const StreamType& obj) const
    {
        bs << obj;
    }
    
private:
    const StreamType *obj_w;
    StreamType* obj_r;
};

}

#endif // <- INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
