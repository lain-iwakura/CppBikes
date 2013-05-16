#ifndef _BIKES_OBJECTSTREAMER_H_
#define _BIKES_OBJECTSTREAMER_H_

#include <Bikes/ByteStream.h>
#include <Bikes/ObjectStreamerMacros.h>
#include <Bikes/TypeCollector.h>
#include <Bikes/SmartPtr.h>
#include <vector>
#include <map>


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

	void read(ByteStream& bs, T *obj) {obj_r=obj; obj_w=obj; read(bs);}
	void write(ByteStream& bs, const T *obj) {obj_w=obj; write(bs);}

protected:
	const T *obj_w;
	T* obj_r;
};
//=========================================================================
template<class ElementStreamer,class ArrayClass>
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
		ElementStreamer::StreamerType el;
		ElementStreamer es(&el);
		for(int i=0; i<sz; i++)
		{			
			bs >> es;
			obj->push_back(el);
		}
	}

	static void write(ByteStream& bs, const StreamerType *obj)
	{
		bs.prepareForWrite(obj->size()+sizeof(int));
		bs << int(obj->size());
		for(int i=0; i<obj->size(); i++)
			bs << ElementStreamer(&((*obj)[i]));		
	}
	
};
//-------------------------------------------------------------------------
template<class ElementStreamer, class ArrayClass>
ArrayStreamer<ElementStreamer,ArrayClass> arrayStreamer(ArrayClass *arr)
{
	return ArrayStreamer<ElementStreamer,ArrayClass>(arr);
}

template<class ElementStreamer, class ArrayClass>
ArrayStreamer<ElementStreamer,ArrayClass> arrayStreamer(const ArrayClass *arr)
{
	return ArrayStreamer<ElementStreamer,ArrayClass>(arr);
}
//=========================================================================
template<class ValueType>
class ValueStreamer: public AbstractObjectStreamer<ValueType>
{
public:
	ValueStreamer(const ValueType * val):AbstractObjectStreamer<ValueType>(val){}
	ValueStreamer(ValueType * val):AbstractObjectStreamer<ValueType>(val){}

	void read(ByteStream& bs) const{read(bs,obj_r);}
	void write(ByteStream& bs) const{write(bs,obj_w);}
	static void read(ByteStream& bs, ValueType *val){bs.readValue(*val);}
	static void write(ByteStream& bs, const ValueType *val){bs.writeValue(*val);}
};
//-------------------------------------------------------------------------
template<class ValueType>
ValueStreamer<ValueType> valueStreamer(ValueType *val)
{
	return ValueStreamer<ValueType>(val);
}

template<class ValueType>
ValueStreamer<ValueType> valueStreamer(const ValueType *val)
{
	return ValueStreamer<ValueType>(val);
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

template<class AbstractRegistrableType, class AbstractRegistrableTypePtr = AbstractRegistrableType*, class Collector=AbstractRegistrableType >
class AbstractTypeStreamer: public AbstractObjectStreamer<AbstractRegistrableTypePtr>
{
public:

	virtual ~AbstractTypeStreamer(){}

	void read(ByteStream& bs) const{read(bs,obj_r);}
	void write(ByteStream& bs) const{write(bs,obj_w);}

	template<class ObjectStreamer>
	static void add()
	{
		//int ti=ObjectStreamer::StreamerType::typeId();
		//if(streamers.size()<=ti) streamers.resize(ti+1);
		//streamers[ti].reset(new TypeStreamer<AbstractRegistrableType,ObjectStreamer>());
		streamers[ObjectStreamer::StreamerType::typeName()].reset(new TypeStreamer<AbstractRegistrableType,ObjectStreamer>());
	}

	static void read(ByteStream& bs, AbstractRegistrableTypePtr * ppAObj)
	{
		/*
		int ti=0;
		bs >> ti;
		if( (ti>=0) && (ti<streamers.size()) && (streamers[ti].get()) )
		{		
			(*ppAObj)=AbstractRegistrableTypePtr(streamers[ti]->newObject());
			streamers[ti]->read(bs,getP(ppAObj));
			//// Проверка совместимости(?):  должно быть сравнение имен типов(?)
		}else
		{
			//TODO: exaption
		}
		*/
		ByteArray bastr(50,10);
		ByteStream bstr(&bastr);
		char ch;
		while(!bs.getIO()->atEnd())
		{	
			bs >> ch;
			bstr << ch;
			if(ch=='\0') break;
		}
		if(ch=='\0')
		{
			const char *str=bastr.data();
			std::map<const char*,typename Ptr<TypeAbstractStreamer<AbstractRegistrableType> >::Shared >::iterator pItr;
			typename Ptr<TypeAbstractStreamer<AbstractRegistrableType> >::Shared stre;

			for(pItr=streamers.begin(); pItr!=streamers.end(); pItr++)
				if(bastr==pItr->first)
				{
					stre=pItr->second;
					break;
				}

			if(stre.get())
			{					
				(*ppAObj)=AbstractRegistrableTypePtr(stre->newObject());
				stre->read(bs,getP(ppAObj));
			}else
			{
				// TODO: exaption
			}
		}else
		{
			// TODO: exaption
		}
	}

	static void write(ByteStream& bs, const AbstractRegistrableTypePtr* ppAObj)
	{
		/*
		if(ppAObj&&(getP(ppAObj)))
		{		
			int ti=(*ppAObj)->getTypeId();		

			if( (ti>=0) && (ti<streamers.size()) && (streamers[ti].get()) )
			{
				bs << ti;
				

			}else
			{
				//TODO: exaption
			}
		}
		*/

		if(ppAObj&&(getP(ppAObj)))
		{
			ByteArray bastr((*ppAObj)->getTypeName());
			
			std::map<const char*,typename Ptr<TypeAbstractStreamer<AbstractRegistrableType> >::Shared >::iterator pItr;
			typename Ptr<TypeAbstractStreamer<AbstractRegistrableType> >::Shared stre;

			for(pItr=streamers.begin(); pItr!=streamers.end(); pItr++)
				if(bastr==pItr->first)
				{
					stre=pItr->second;
					break;
				}

			if(stre.get())
			{
				bs.writeBytes(bastr.data(),bastr.size());
				stre->write(bs,getP(ppAObj));
			}else
			{
				//TODO: exaption
			}
		}else
		{
			//TODO: exaption
		}
	}

	static int streamersCount(){return streamers.size();}

private:
	typedef AbstractRegistrableType* AbstractRegitrableTypeP;

	template<class TPtr>
	static AbstractRegistrableType * getP(const TPtr* ptr){return ptr->get();}	
	
	template<>
	static AbstractRegistrableType * getP(const AbstractRegitrableTypeP* ptr){return *ptr;}

	static std::map<const char*,typename Ptr<TypeAbstractStreamer<AbstractRegistrableType> >::Shared > streamers; 
};

template<class AbstractRegistrableType, class AbstractRegistrableTypePtr, class Collector> 
std::map<const char*, typename Ptr<TypeAbstractStreamer<AbstractRegistrableType> >::Shared > AbstractTypeStreamer<AbstractRegistrableType,AbstractRegistrableTypePtr,Collector>::streamers;

//-------------------------------------------------------------------------

namespace Aux
{
	template<class AbstractTypeStreamerClass, class AddStreamerClass>
	class AbstractTypeStreamerInitor
	{
	public:
		AbstractTypeStreamerInitor()
		{
			static bool i=false;
			if(!i)
			{
				i=true;
				AbstractTypeStreamerClass::add<AddStreamerClass>();
			}
		}
	};
}

//=========================================================================

template<class T> class OneTypeStreamerCreator;

class AbstractOneTypeStreamerCreator
{
public:
	virtual~AbstractOneTypeStreamerCreator(){}

	template<class T>
	AbstractObjectStreamer<T>* newObjectStreamer(T *obj)
	{	
		OneTypeStreamerCreator<T>* ots=dynamic_cast<OneTypeStreamerCreator<T>*>(this);
		if(ots==0){	/*TODO: exaption*/	}
		return ots->newObjectStreamer(obj);
	}

	template<class T>
	AbstractObjectStreamer<T>* newObjectStreamer(const T *obj)
	{	
		OneTypeStreamerCreator<T>* ots=dynamic_cast<OneTypeStreamerCreator<T>*>(this);
		if(ots==0){	/*TODO: exaption*/ }
		return ots->newObjectStreamer(obj);
	}
};
//-------------------------------------------------------------------------
template<class T>
class OneTypeStreamerCreator: public AbstractOneTypeStreamerCreator
{
public:
	virtual ~OneTypeStreamerCreator(){}
	virtual AbstractObjectStreamer<T>* newObjectStreamer(T *obj) = 0;
	virtual AbstractObjectStreamer<T>* newObjectStreamer(const T *obj) = 0;
};
//-------------------------------------------------------------------------
template<class ObjectStreamer>
class OneTypeObjectStreamerCreator: public OneTypeStreamerCreator<typename ObjectStreamer::StreamerType>
{
public:
	AbstractObjectStreamer<typename ObjectStreamer::StreamerType>* newObjectStreamer(typename ObjectStreamer::StreamerType *obj)
	{
		return new ObjectStreamer(obj);
	}
	AbstractObjectStreamer<typename ObjectStreamer::StreamerType>* newObjectStreamer(const typename ObjectStreamer::StreamerType *obj)
	{
		return new ObjectStreamer(obj);
	}
};
//-------------------------------------------------------------------------
// class BaseMultiTypeStreamer
// {
// public:
// 	virtual~BaseMultiTypeStreamer(){}
// };


template<class TypesCollection>
class MultiTypeStreamer: public AbstractStreamer
{
public:

	MultiTypeStreamer(){}

	template<class T>
	MultiTypeStreamer(T* obj){setObject(obj);}

	template<class T>
	MultiTypeStreamer(const T* obj){setObject(obj);}

	
	template<class ObjectStreamer>
	static void add()
	{
		int it=TypesCollection::typeId<typename ObjectStreamer::StreamerType>();
		if(it>=strCreators.size()) strCreators.resize(it+1);
		strCreators[it].reset(new OneTypeObjectStreamerCreator<ObjectStreamer>());
	}

// 	template<class OtherMultiTypeStreamer>
// 	static void addMulti()
// 	{
// 		const std::vector<std::tr1::shared_ptr<AbstractOneTypeStreamerCreator> >&strCr OtherMultiTypeStreamer::streamerCreators();
// 
// 		for(int i=0; i<strCr.size(); i++)
// 		{	
// 			if(strCr[i])
// 			{		
// 				int it=TypesCollection::typeId<ObjectStreamer::StreamerType>();
// 				if(it>=strCreators.size()) strCreators.resize(it+1);
// 				strCreators[it].reset(new OneTypeObjectStreamerCreator<ObjectStreamer>());
// 			}
// 		}
// 	}

	template<class T>
	void setObject(T *obj)
	{
		int it=TypesCollection::typeId<T>();
		if((it<strCreators.size())&&(strCreators[it].get()))
		{
			curStr.reset(strCreators[it]->newObjectStreamer(obj));
		}else
		{
			//TODO: exaption
		}		
	}

	template<class T>
	void setObject(const T *obj)
	{
		int it=TypesCollection::typeId<T>();
		if((it<strCreators.size())&&(strCreators[it].get()))
		{
			curStr.reset(strCreators[it]->newObjectStreamer(obj));
		}else
		{
			//TODO: exaption
		}
	}

	void read(ByteStream &bs) const
	{
		if(curStr.get())
		{
			curStr->read(bs);
		}else
		{
			//TODO: exaption
		}
	}

	void write(ByteStream &bs) const
	{
		if(curStr.get()) 
		{
			curStr->write(bs);
		}else
		{
			//TODO: exaption
		}
	}

private:
	Ptr<AbstractStreamer>::Auto curStr;
	static std::vector<Ptr<AbstractOneTypeStreamerCreator>::Shared > strCreators;
};


template<class TypesCollection>
std::vector<Ptr<AbstractOneTypeStreamerCreator>::Shared >  MultiTypeStreamer<TypesCollection>::strCreators(TypesCollection::typeCount());


//=========================================================================
 


} // Bikes

#endif