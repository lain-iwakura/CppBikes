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
	typedef T StreamerType;

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

template<class ElementStreamerClass,class ArrayClass>
class ArrayStreamer: public AbstractObjectStreamer<ArrayClass> 
{
public:
	ArrayStreamer(StreamerType *obj): AbstractObjectStreamer<StreamerType>(obj){}
	ArrayStreamer(const StreamerType *obj): AbstractObjectStreamer<StreamerType>(obj){}


	void read(ByteStream& bs) const
	{
		read(bs,obj_r);
	}

	void write(ByteStream& bs) const
	{
		write(bs,obj_w);
	}

	static void read(ByteStream& bs, StreamerType *obj)
	{
		obj->clear();
		int sz;		
		bs >> sz;
		ElementStreamerClass::StreamerType el;
		ElementStreamerClass es(&el);
		for(int i=0; i<sz; i++)
		{			
			bs >> es;
			obj->push_back(el);
		}
	}

	static void write(ByteStream& bs, const StreamerType *obj)
	{
		bs.byteArray()->setCapacity(bs.byteArray()->capacity()+obj->size()+sizeof(int));
		bs << int(obj->size());
		for(int i=0; i<obj->size(); i++)
			bs << ElementStreamerClass(&((*obj)[i]));		
	}
	
};

template<class ElementStreamerClass, class ArrayClass>
ArrayStreamer<ElementStreamerClass,ArrayClass> arrayStreamer(ArrayClass *arr)
{
	return ArrayStreamer<ElementStreamerClass,ArrayClass>(arr);
}

template<class ElementStreamerClass, class ArrayClass>
ArrayStreamer<ElementStreamerClass,ArrayClass> arrayStreamer(const ArrayClass *arr)
{
	return ArrayStreamer<ElementStreamerClass,ArrayClass>(arr);
}


} // Bikes

#endif