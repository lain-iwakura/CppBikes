#ifndef INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H
#define INCLUDE_BIKES_STREAM_ABSTRACTOBJECTSTREAMER_H

#include <Bikes/Stream/StreamerInterface.h>

namespace Bikes
{

template<class T>
class AbstractObjectStreamer : public StreamerInterface
{
public:
    typedef T StreamerType;

    AbstractObjectStreamer(T *obj = 0):
        obj_w(obj), 
        obj_r(obj)
    {
    }

	AbstractObjectStreamer(T &obj) :
		obj_w(&obj),
		obj_r(&obj)
	{
	}

    AbstractObjectStreamer(const T *obj):
        obj_w(obj), 
        obj_r(0)
    {
    }


	AbstractObjectStreamer(const T &obj) :
		obj_w(&obj),
		obj_r(0)
	{
	}

    virtual ~AbstractObjectStreamer()
    {
    }

    void setObject(T *obj)
    {
        obj_r = obj;
        obj_w = obj;
    }

	void setObject(T &obj)
	{
		obj_r = &obj;
		obj_w = &obj;
	}

    void setObject(const T *obj)
    {
        obj_w = obj;
		obj_r = 0;
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

    void read(ByteStream& bs, T *obj) 
    {
        obj_r = obj; 
        obj_w = obj; 
        read(bs); 
    }

    void write(ByteStream& bs, const T *obj) 
    {
        obj_w = obj; 
        write(bs); 
    }

protected:
    const T *obj_w;
    T* obj_r;
};

}

#endif