#ifndef _BIKES_SIGNALS_H_
#define _BIKES_SIGNALS_H_

#include <Bikes/MacrosBikes.h>
#include <vector>
#include <map>


//==============================================================================================

#define BIKES_CONNECTINTERFACE(signal)								signal##_connectInterface()

#define BIKES_CONNECTINTERFACE_DECL(signal)							Bikes::SignalConnectInterface*  BIKES_CONNECTINTERFACE(signal);
#define BIKES_CONNECTINTERFACE_DEF(ClassName,signal)				Bikes::SignalConnectInterface*  ClassName::BIKES_CONNECTINTERFACE(signal){signal.setEmitter(this); return &signal;}
#define BIKES_CONNECTINTERFACE_DECLDEF(signal)						Bikes::SignalConnectInterface*  BIKES_CONNECTINTERFACE(signal){signal.setEmitter(this); return &signal;}

#define BIKES_EMITTER_CONNECTINTERFACE_DECL(EmitterType,signal)				Bikes::SignalConnectInterface*  BIKES_CONNECTINTERFACE(signal);
#define BIKES_EMITTER_CONNECTINTERFACE_DEF(ClassName,EmitterType,signal)	Bikes::SignalConnectInterface*  ClassName::BIKES_CONNECTINTERFACE(signal){signal.setEmitter(static_cast<EmitterType*>(this)); return &signal;}
#define BIKES_EMITTER_CONNECTINTERFACE_DECLDEF(EmitterType,signal)			Bikes::SignalConnectInterface*  BIKES_CONNECTINTERFACE(signal){signal.setEmitter(static_cast<EmitterType*>(this)); return &signal;}

#define BIKES_CONNECT(emitter,signal,receiver,slot_func)			(emitter)->BIKES_CONNECTINTERFACE(signal)->connect(receiver,&slot_func)
#define BIKES_CONNECT_UNSAFE(emitter,signal,receiver,slot_func)		(emitter)->BIKES_CONNECTINTERFACE(signal)->connect_unsafe(receiver,&slot_func)

#define BIKES_DISCONNECT(emitter,signal,receiver,slot_func)			(emitter)->BIKES_CONNECTINTERFACE(signal)->disconnect(receiver,&slot_func)


#define BIKES_CONNECTABLE_OBJECT																\
	public:																						\
	Bikes::ConnectableObject connectable_object;												\
	private:																					\
	void* emitter()																				\
	{																							\
		if(connectable_object.emitter())														\
			return connectable_object.emitter()->pObj();										\
		return 0;																				\
	}																							\
	template<class EmitterClass>																\
	EmitterClass* emitter_cast()																\
	{																							\
		if(connectable_object.emitter())														\
			return connectable_object.emitter()->cast<EmitterClass>();							\
		return 0;																				\
	}

//==============================================================================================


namespace Bikes
{

class BaseSignal;
class ConnectableObject;
class SignalConnectInterface;
class BaseEmitter;
//==============================================================================================
class SignalNullType
{
};
//==============================================================================================
template <typename> class Emitter;

class BaseEmitter
{
public:
	virtual ~ BaseEmitter(){}
	virtual void* pObj() = 0;

	template<class EmitterClass>
	EmitterClass* cast()
	{
		if(Emitter<EmitterClass>*em=dynamic_cast<Emitter<EmitterClass>* >(this))
		{
			return em->obj;
		}
		return 0;
	}
};

template<class EmitterClass>
class Emitter:public BaseEmitter
{
public:
	Emitter(EmitterClass *o): obj(o){}
	void * pObj(){return obj;}
private:
	EmitterClass *obj;
	friend class BaseEmitter;
};
// =============================================================================================
class BaseSignal
{
public:
	BaseSignal();
	virtual ~BaseSignal();
	virtual void disconnectAll(void *pObj) = 0;	
	virtual void disconnectAll() = 0;
	BaseEmitter* emitter() const;

	template<class EmitterClass>
	void setEmitter(EmitterClass* emtr)
	{
		if(emitter_) 
		{		
			if(emitter_->cast<EmitterClass>()!=emtr)
			{	
				delete emitter_;
				emitter_=new Emitter<EmitterClass>(emtr);
			}
		}else
		{
			emitter_=new Emitter<EmitterClass>(emtr);			
		}
	}
protected:
	BaseEmitter *emitter_;
	virtual void disconnectAll_(void *pObj) = 0;
	friend class ConnectableObject;
};
//==============================================================================================
class BaseSlot
{
public:
	BaseSlot();
	virtual ~BaseSlot();
	virtual void* pObj() = 0;
	virtual void connect(BaseSignal *sig){}
	virtual void disconnect(BaseSignal *sig){}
	

protected:

	std::vector<BaseEmitter*> *emitters;

	template<class ObjectClass>
	void begin_emission(ObjectClass *obj, const BaseSignal* sig) const
	{
		emitters->push_back(obj->connectable_object.cur_emitter_);
		obj->connectable_object.cur_emitter_=sig->emitter();
	}

	template<class ObjectClass>
	void end_emission(ObjectClass *obj) const
	{
		if(emitters->size())
		{
			obj->connectable_object.cur_emitter_=emitters->back();
			emitters->pop_back();
		}else
		{
			obj->connectable_object.cur_emitter_=0;
		}
	}


	template<class ObjectClass>
	void connectConnectableObject(ObjectClass* obj, BaseSignal *sig)
	{
		obj->connectable_object.parent_=obj;
		if(obj->connectable_object.signals_counter.count(sig))
		{
			obj->connectable_object.signals_counter[sig]++;
		}else
		{
			obj->connectable_object.signals_counter[sig]=1;
		}

	}

	template<class ObjectClass>
	void disconnectConnectableObject(ObjectClass* obj, BaseSignal *sig)
	{		
		if(obj->connectable_object.signals_counter.count(sig))
		{
			int& i=obj->connectable_object.signals_counter[sig];
			i--;
			if(i<=0) obj->connectable_object.signals_counter.erase(sig);
		}
	}
};
//==============================================================================================
class ConnectableObject
{
public:
	ConnectableObject();
	~ConnectableObject();
	BaseEmitter* emitter();
protected:
	void *parent_;	
	BaseEmitter *cur_emitter_;
	std::map<BaseSignal*,int> signals_counter;
	friend class BaseSlot;
};

//==============================================================================================

template<MACROSBIKES_CT10_DEFTYPE(SignalNullType)> class AbstractSlot;

template<class ObjectClass, class RT, MACROSBIKES_CT10_DEFTYPE(SignalNullType)> class SlotObject;

template<class ObjectClass, class RT, MACROSBIKES_CT10_DEFTYPE(SignalNullType)> class SlotConnectableObject;

template<MACROSBIKES_CT10_DEFTYPE(SignalNullType)> class Signal;
//==============================================================================================

//==============================================================================================



//==============================================================================================
#define MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CT,TT,COMMA)							\
template<class ObjectClass, class RT COMMA CT>													\
void connect(ObjectClass *obj, RT(ObjectClass::*f)(TT));										\
                                                                                                \
template<class ObjectClass, class RT COMMA CT>													\
void connect_unsafe(ObjectClass *obj, RT(ObjectClass::*f)(TT));									\
                                                                                                \
template<class ObjectClass, class RT COMMA CT>													\
void disconnect(ObjectClass *obj, RT(ObjectClass::*f)(TT));
//-----------------------------------------------------------------------------------------------
class SignalConnectInterface
{
public:
    virtual ~SignalConnectInterface(){}

MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL( , , )
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT1,MACROSBIKES_TT1,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT2,MACROSBIKES_TT2,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT3,MACROSBIKES_TT3,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT4,MACROSBIKES_TT4,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT5,MACROSBIKES_TT5,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT6,MACROSBIKES_TT6,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT7,MACROSBIKES_TT7,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT8,MACROSBIKES_TT8,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT9,MACROSBIKES_TT9,MACROSBIKES_COMMA)

};
//==============================================================================================
#define MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(CT,TT,TP,PP,COMMA)								\
template<CT>																					\
class AbstractSlot<TT>: public BaseSlot															\
{																								\
public:																							\
	virtual ~AbstractSlot(){}																	\
	virtual void call(TP COMMA const BaseSignal *sig) const = 0;								\
	template<class ObjectClass,class RT>														\
	bool isSlotObject(ObjectClass *pObg,RT(ObjectClass::*slot_func)(TT))						\
	{																							\
		if(SlotObject<ObjectClass,RT COMMA TT> *s=dynamic_cast<SlotObject<ObjectClass,RT COMMA TT>*>(this))\
		{																						\
			return (s->pObj_==pObg)&&(s->f==slot_func);											\
		}																						\
		return false;																			\
	}																							\
};																								\
template<class ObjectClass, class RT COMMA CT>													\
class SlotObject<ObjectClass,RT COMMA TT>: public AbstractSlot<TT>								\
{																								\
public:																							\
	virtual ~SlotObject(){}																		\
	typedef RT (ObjectClass::*ObjFuncType)(TT);													\
	SlotObject(ObjectClass *obj,ObjFuncType fu): pObj_(obj),f(fu){}								\
    virtual void call(TP COMMA const BaseSignal *sig) const {(pObj_->*f)(PP);}                  \
	void* pObj(){return pObj_;}																	\
	ObjectClass *pObj_;																			\
	ObjFuncType f;																				\
};																								\
																								\
template<class ObjectClass, class RT COMMA CT>													\
class SlotConnectableObject<ObjectClass,RT COMMA TT>: public SlotObject<ObjectClass,RT COMMA TT>\
{																								\
    typedef SlotObject<ObjectClass,RT COMMA TT> Base;                                           \
    typedef typename Base::ObjFuncType ObjFuncType;                                             \
public:																							\
    SlotConnectableObject(ObjectClass *obj,ObjFuncType fu): Base(obj,fu){}                      \
																								\
	void call(TP COMMA const BaseSignal *sig)	const											\
	{																							\
        this->begin_emission(this->pObj_,sig);														\
        ((this->pObj_)->*(this->f))(PP);														\
        this->end_emission(this->pObj_);																\
	}																							\
																								\
	void connect(BaseSignal *sig)																\
	{																							\
        this->connectConnectableObject(this->pObj_,sig);												\
	}																							\
																								\
	void disconnect(BaseSignal *sig)															\
	{																							\
        this->disconnectConnectableObject(this->pObj_,sig);											\
	}																							\
																								\
};																								\
                                                                                                \
template<CT>																					\
class Signal<TT>: public SignalConnectInterface, public BaseSignal								\
{																								\
public:																							\
    Signal(){}																					\
    Signal(const Signal<TT>& sig){}																\
    ~Signal()																					\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
        {																						\
            slots_[i]->disconnect(this);														\
            delete slots_[i];																	\
        }																						\
    }																							\
    void operator ()(TP) const																	\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            slots_[i]->call(PP COMMA this);														\
    }																							\
    void call(TP) const																			\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            slots_[i]->call(PP COMMA this);														\
    }																							\
    template<class ObjectClass, class RT>														\
    void connect_unsafe(ObjectClass *obj, RT(ObjectClass::*slot_func)(TT))						\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            if(slots_[i]->isSlotObject(obj,slot_func)) return;									\
        slots_.push_back(new SlotObject<ObjectClass,RT COMMA TT>(obj,slot_func));				\
    }																							\
                                                                                                \
    template<class ObjectClass, class RT>														\
    void connect(ObjectClass *obj,RT(ObjectClass::*slot_func)(TT))								\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            if(slots_[i]->isSlotObject(obj,slot_func))											\
            {																					\
                if(SlotConnectableObject<ObjectClass,RT COMMA TT>* s=dynamic_cast<SlotConnectableObject<ObjectClass,RT COMMA TT>* >(slots_[i]) )\
                {																				\
                    return;																		\
                }else																			\
                {																				\
                    slots_[i]->disconnect(this);												\
                    delete slots_[i];															\
                    slots_[i]=new SlotConnectableObject<ObjectClass,RT COMMA TT>(obj,slot_func);\
                    slots_[i]->connect(this);													\
                    return;																		\
                }																				\
            }																					\
        SlotConnectableObject<ObjectClass,RT COMMA TT> *s=new SlotConnectableObject<ObjectClass,RT COMMA TT>(obj,slot_func);\
        s->connect(this);																		\
        slots_.push_back(s);																	\
    }																							\
                                                                                                \
    template<class ObjectClass, class RT>														\
    void disconnect(ObjectClass *obj, RT(ObjectClass::*slot_func)(TT))							\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            if(slots_[i]->isSlotObject(obj,slot_func))											\
            {																					\
                slots_[i]->disconnect(this);													\
                delete slots_[i];																\
                slots_.erase(slots_.begin()+i);													\
                return;																			\
            }																					\
    }																							\
    void disconnectAll(void *pObj)																\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            if(slots_[i]->pObj()==pObj)															\
            {																					\
                slots_[i]->disconnect(this);													\
                delete slots_[i];																\
                slots_.erase(slots_.begin()+i);													\
                i--;																			\
            }																					\
    }																							\
    void disconnectAll()																		\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
        {																						\
            slots_[i]->disconnect(this);														\
            delete slots_[i];																	\
        }																						\
        slots_.clear();																			\
    }																							\
private:																						\
    void disconnectAll_(void *pObj)																\
    {																							\
        for(unsigned int i=0; i<slots_.size(); i++)												\
            if(slots_[i]->pObj()==pObj)															\
            {																					\
                delete slots_[i];																\
                slots_.erase(slots_.begin()+i);													\
                i--;																			\
            }																					\
    }																							\
    std::vector<AbstractSlot<TT>* > slots_;														\
};
//-----------------------------------------------------------------------------------------------
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL( , , , , )
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT1,MACROSBIKES_TT1,MACROSBIKES_TTP1,MACROSBIKES_PP1,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT2,MACROSBIKES_TT2,MACROSBIKES_TTP2,MACROSBIKES_PP2,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT3,MACROSBIKES_TT3,MACROSBIKES_TTP3,MACROSBIKES_PP3,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT4,MACROSBIKES_TT4,MACROSBIKES_TTP4,MACROSBIKES_PP4,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT5,MACROSBIKES_TT5,MACROSBIKES_TTP5,MACROSBIKES_PP5,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT6,MACROSBIKES_TT6,MACROSBIKES_TTP6,MACROSBIKES_PP6,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT7,MACROSBIKES_TT7,MACROSBIKES_TTP7,MACROSBIKES_PP7,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT8,MACROSBIKES_TT8,MACROSBIKES_TTP8,MACROSBIKES_PP8,MACROSBIKES_COMMA)
MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(MACROSBIKES_CT9,MACROSBIKES_TT9,MACROSBIKES_TTP9,MACROSBIKES_PP9,MACROSBIKES_COMMA)
//==============================================================================================

#define MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(CT,TT,COMMA)                             \
template<class ObjectClass, class RT COMMA CT>													\
void SignalConnectInterface::connect(ObjectClass *obj, RT(ObjectClass::*f)(TT))					\
{																								\
    if(Signal<TT>* s=dynamic_cast<Signal<TT>*>(this))											\
    {																							\
        s->connect(obj,f);																		\
    }																							\
}																								\
template<class ObjectClass, class RT COMMA CT>													\
void SignalConnectInterface::connect_unsafe(ObjectClass *obj, RT(ObjectClass::*f)(TT))			\
{																								\
    if(Signal<TT>* s=dynamic_cast<Signal<TT>*>(this))											\
    {																							\
        s->connect_unsafe(obj,f);																\
    }																							\
}																								\
template<class ObjectClass, class RT COMMA CT>													\
void SignalConnectInterface::disconnect(ObjectClass *obj, RT(ObjectClass::*f)(TT))				\
{																								\
    if(Signal<TT>* s=dynamic_cast<Signal<TT>* >(this))											\
    {																							\
        s->disconnect(obj,f);																	\
    }																							\
}

MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF( , , )
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT1,MACROSBIKES_TT1,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT2,MACROSBIKES_TT2,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT3,MACROSBIKES_TT3,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT4,MACROSBIKES_TT4,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT5,MACROSBIKES_TT5,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT6,MACROSBIKES_TT6,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT7,MACROSBIKES_TT7,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT8,MACROSBIKES_TT8,MACROSBIKES_COMMA)
MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(MACROSBIKES_CT9,MACROSBIKES_TT9,MACROSBIKES_COMMA)

}// Bikes

#endif // BIKES_SIGNALS_H
