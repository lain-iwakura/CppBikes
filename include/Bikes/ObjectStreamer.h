#ifndef _BIKES_OBJECTSTREAMER_H_
#define _BIKES_OBJECTSTREAMER_H_

#include <Bikes/ByteStream.h>
#include <Bikes/ObjectStreamerMacros.h>
#include <Bikes/TypeCollector.h>
#include <vector>
#include <memory>

namespace Bikes
{

class AbstractStreamer
{
public:
	virtual ~AbstractStreamer(){}
	virtual void read(ByteStream& bs) const = 0;
	virtual void write(ByteStream& bs) const = 0;
};
//=========================================================================
template<class T>
class AbstractObjectStreamer: public AbstractStreamer
{
public:
	typedef T StreamerType;

	AbstractObjectStreamer(T *obj=0):obj_r(obj),obj_w(obj){}
	AbstractObjectStreamer(const T *obj):obj_r(0),obj_w(obj){}

	virtual ~AbstractObjectStreamer(){}

	void setObject(T *obj)
	{
		obj_r=obj;
		obj_w=obj;
	}

	void setObject(const T *obj)
	{
		obj_w=obj;
	}	

	T* rObject() const {return obj_r;}
	const T* wObject() const {return obj_w;}

	virtual void read(ByteStream& bs) const = 0;
	virtual void write(ByteStream& bs) const = 0;	

	void read(ByteStream& bs, T *obj) {obj_r=obj; read(bs);}
	void write(ByteStream& bs, const T *obj) {obj_w=obj; write(bs);}

protected:
	const T *obj_w;
	T* obj_r;
};
//=========================================================================
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

// template<class ValueType>
// class ValueStreamer: AbstractObjectStreamer<ValueType>
// {
// public:
// 	ValueStreamer(const ValueType * val):AbstractObjectStreamer<ValueType>(val){}
// 	ValueStreamer(ValueType * val):AbstractObjectStreamer<ValueType>(val){}
// 
// 	void read(ByteStream& bs) const
// 	{
// 	}
// 	void write(ByteStream& bs) const
// 	{
// 	}
// 
// 	static void read(ByteStream& bs, ValueType *val)
// 	{
// 	}
// 
// 	static void write(ByteStream& bs, )
// }
//-------------------------------------------------------------------------
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
//=========================================================================

//=========================================================================
template<class AbstractType>
class TypeAbstractStreamer
{
public:
	virtual~TypeAbstractStreamer(){}
	virtual void read(ByteStream &bs, AbstractType* aobj) const = 0;
	virtual void write(ByteStream &bs,const AbstractType* aobj) const = 0;
	virtual AbstractType* newObject() const = 0;
};

template<class AbstractType, class ChildTypeStreamer>
class TypeStreamer: public TypeAbstractStreamer<AbstractType>
{
public:
	void read(ByteStream &bs, AbstractType* aobj) const
	{
		if(ChildTypeStreamer::StreamerType *obj=dynamic_cast<ChildTypeStreamer::StreamerType *>(aobj))
		{
			ChildTypeStreamer::read(bs,obj);
		}else
		{
			//TODO: exaption
		}
	}
	void write(ByteStream &bs,const AbstractType* aobj) const
	{
		if(const ChildTypeStreamer::StreamerType *obj=dynamic_cast<const ChildTypeStreamer::StreamerType *>(aobj))
		{
			ChildTypeStreamer::write(bs,obj);
		}else
		{
			//TODO: exaption
		}
	}
	AbstractType* newObject() const
	{
		return new ChildTypeStreamer::StreamerType();
	}
};
//=========================================================================
template<class AbstractRegitrableType, class AbstractRegitrableTypePtr = AbstractRegitrableType*, class Collector=AbstractRegitrableType >
class AbstractTypeStreamer: public AbstractObjectStreamer<AbstractRegitrableTypePtr>
{
public:

	virtual ~AbstractTypeStreamer(){}

	void read(ByteStream& bs) const{read(bs,obj_r);}
	void write(ByteStream& bs) const{write(bs,obj_w);}

	template<class ObjectStreamer>
	static void add()
	{
		int ti=ObjectStreamer::StreamerType::typeId();
		if(streamers.size()<=ti) streamers.resize(ti+1);
		streamers[ti].reset(new TypeStreamer<AbstractRegitrableType,ObjectStreamer>());
	}

	static void read(ByteStream& bs, AbstractRegitrableTypePtr * ppAObj)
	{		
		int ti=0;
		bs >> ti;
		if( (ti>=0) && (ti<streamers.size()) && (streamers[ti].get()) )
		{		
			(*ppAObj)=AbstractRegitrableTypePtr(streamers[ti]->newObject());
			streamers[ti]->read(bs,getP(ppAObj));
			//// Проверка совместимости(?):  должно быть сравнение имен типов(?)
		}else
		{
			//TODO: exaption
		}		
	}

	static void write(ByteStream& bs, const AbstractRegitrableTypePtr* ppAObj)
	{
		if(ppAObj&&(getP(ppAObj)))
		{		
			int ti=(*ppAObj)->getTypeId();		

			if( (ti>=0) && (ti<streamers.size()) && (streamers[ti].get()) )
			{
				bs << ti;
				streamers[ti]->write(bs,getP(ppAObj));
			}else
			{
				//TODO: exaption
			}
		}
	}

	static int streamersCount(){return streamers.size();}

private:
	typedef AbstractRegitrableType* AbstractRegitrableTypeP;

	template<class TPtr>
	static AbstractRegitrableType * getP(const TPtr* ptr){return ptr->get();}	
	
	template<>
	static AbstractRegitrableType * getP(const AbstractRegitrableTypeP* ptr){return *ptr;}

	static std::vector<std::tr1::shared_ptr<TypeAbstractStreamer<AbstractRegitrableType> > > streamers; 
};

template<class AbstractRegitrableType, class AbstractRegitrableTypePtr, class Collector> 
std::vector<std::tr1::shared_ptr<TypeAbstractStreamer<AbstractRegitrableType> > > AbstractTypeStreamer<AbstractRegitrableType,AbstractRegitrableTypePtr,Collector>::streamers(AbstractRegitrableType::typesCount());

//=========================================================================


class MultiTypeStreamer: public AbstractStreamer
{
public:
	MultiTypeStreamer(){}

	void read(ByteStream &bs) const
	{
		if(curStr) curStr->read(bs);
	}

	void write(ByteStream &bs) const
	{
		if(curStr) curStr->write(bs);
	}

private:
	AbstractStreamer *curStr;
};


// AbstractTypeStreamer<AbstractRegitrableType>



} // Bikes

#endif