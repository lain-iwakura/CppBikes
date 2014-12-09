#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/StreamerInterface.h>

namespace Bikes
{

template<class T>
class AbstractObjectStreamer : public StreamerInterface
{
public:
    typedef T ObjectType;
    typedef AbstractObjectStreamer<T> ThisType;

    AbstractObjectStreamer():
        obj_w(0), 
        obj_r(0)
    {
    }

    explicit AbstractObjectStreamer(T &obj) :
        obj_w(&obj),
        obj_r(&obj)
    {
    }

    explicit AbstractObjectStreamer(const T &obj) :
		obj_w(&obj),
		obj_r(0)
	{
	}

    virtual ~AbstractObjectStreamer()
    {
    }

	void setObject(T &obj)
	{
		obj_r = &obj;
		obj_w = &obj;
	}

	void setObject(const T &obj)
	{
		obj_w = &obj;
		obj_r = 0;
	}

    T* rObject() const 
    {
        return obj_r; 
    }

    const T* wObject() const 
    { 
        return obj_w; 
    }

    virtual void read(ByteStream& bs) const = 0;

    virtual void write(ByteStream& bs) const = 0;

    virtual const ByteArray& getObjectTypeSignature() const = 0;

protected:
    const T *obj_w;
    T* obj_r;
};

}

#endif // <- INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
