#ifndef _BIKES_OBJECTSTREAM_H_
#define _BIKES_OBJECTSTREAM_H_

#include <Bikes/ByteStream.h>
#include <Bikes/ObjectStreamMacros.h>

namespace Bikes
{

class AbstractStreamer
{
public:
	virtual ~AbstractStreamer(){}
	virtual void read(ByteStream& bs) const = 0;
	virtual void write(ByteStream& bs) const = 0;
};

template<class T>
class AbstractObjectStreamer: public AbstractStreamer
{
public:
	AbstractObjectStreamer(T *obj):obj_r(obj),obj_w(obj){}
	AbstractObjectStreamer(const T *obj):obj_r(0),obj_w(obj){}

	virtual ~AbstractObjectStreamer(){}

	void setObject(T *obj){obj_r=obj; obj_w=obj;}
	void setObject(const T *obj){obj_r=obj;}		

	virtual void read(ByteStream& bs) const = 0;
	virtual void write(ByteStream& bs) const = 0;	

	void read(ByteStream& bs, T *obj) {obj_r=obj; read(bs);}
	void write(ByteStream& bs, const T *obj) {obj_w=obj; write(bs);}

protected:
	const T *obj_w;
	T* obj_r;
};

} // Bikes

#endif