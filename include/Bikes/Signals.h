#ifndef PREBIKES_SIGNALS_H_
#define PREBIKES_SIGNALS_H_

#include <Bikes/Types.h>
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
//#define MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(MACROSBIKES_CT##PN,MACROSBIKES_TT##PN,MACROSBIKES_COMMA##PN)							
#define MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(PN)\
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
void connect(ObjectClass *obj, RT(ObjectClass::*f)(MACROSBIKES_TT##PN));										\
                                                                                                \
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
void connect_unsafe(ObjectClass *obj, RT(ObjectClass::*f)(MACROSBIKES_TT##PN));									\
                                                                                                \
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
void disconnect(ObjectClass *obj, RT(ObjectClass::*f)(MACROSBIKES_TT##PN));
//-----------------------------------------------------------------------------------------------
class SignalConnectInterface
{
public:
    virtual ~SignalConnectInterface(){}

    MACROSBIKES_FOREACHPARAMLIST(MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL)
};
//==============================================================================================
//#define MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(CT,TT,TP,PP,COMMA)								
#define MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL(PN)								                \
template<MACROSBIKES_CT##PN>																					\
class AbstractSlot<MACROSBIKES_TT##PN>: public BaseSlot															\
{																								\
public:																							\
	virtual ~AbstractSlot(){}																	\
	virtual void call(MACROSBIKES_TTP##PN MACROSBIKES_COMMA##PN const BaseSignal *sig) const = 0;								\
	template<class ObjectClass,class RT>														\
	bool isSlotObject(ObjectClass *pObg,RT(ObjectClass::*slot_func)(MACROSBIKES_TT##PN))						\
	{																							\
		if(SlotObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN> *s=dynamic_cast<SlotObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>*>(this))\
		{																						\
			return (s->pObj_==pObg)&&(s->f==slot_func);											\
		}																						\
		return false;																			\
	}																							\
};																								\
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
class SlotObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>: public AbstractSlot<MACROSBIKES_TT##PN>								\
{																								\
public:																							\
	virtual ~SlotObject(){}																		\
	typedef RT (ObjectClass::*ObjFuncType)(MACROSBIKES_TT##PN);													\
	SlotObject(ObjectClass *obj,ObjFuncType fu): pObj_(obj),f(fu){}								\
    virtual void call(MACROSBIKES_TTP##PN MACROSBIKES_COMMA##PN const BaseSignal *sig) const {(pObj_->*f)(MACROSBIKES_PP##PN);}                  \
	void* pObj(){return pObj_;}																	\
	ObjectClass *pObj_;																			\
	ObjFuncType f;																				\
};																								\
																								\
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
class SlotConnectableObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>: public SlotObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>\
{																								\
    typedef SlotObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN> Base;                                           \
    typedef typename Base::ObjFuncType ObjFuncType;                                             \
public:																							\
    SlotConnectableObject(ObjectClass *obj,ObjFuncType fu): Base(obj,fu){}                      \
																								\
	void call(MACROSBIKES_TTP##PN MACROSBIKES_COMMA##PN const BaseSignal *sig)	const											\
	{																							\
        this->begin_emission(this->pObj_,sig);														\
        ((this->pObj_)->*(this->f))(MACROSBIKES_PP##PN);														\
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
template<MACROSBIKES_CT##PN>																					\
class Signal<MACROSBIKES_TT##PN>: public SignalConnectInterface, public BaseSignal								\
{																								\
public:																							\
    Signal(){}																					\
    Signal(const Signal<MACROSBIKES_TT##PN>& sig){}																\
    ~Signal()																					\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
        {																						\
            slots_[i]->disconnect(this);														\
            delete slots_[i];																	\
        }																						\
    }																							\
    void operator ()(MACROSBIKES_TTP##PN) const																	\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
            slots_[i]->call(MACROSBIKES_PP##PN MACROSBIKES_COMMA##PN this);														\
    }																							\
    void call(MACROSBIKES_TTP##PN) const																			\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
            slots_[i]->call(MACROSBIKES_PP##PN MACROSBIKES_COMMA##PN this);														\
    }																							\
    template<class ObjectClass, class RT>														\
    void connect_unsafe(ObjectClass *obj, RT(ObjectClass::*slot_func)(MACROSBIKES_TT##PN))						\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
            if(slots_[i]->isSlotObject(obj,slot_func)) return;									\
        slots_.push_back(new SlotObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>(obj,slot_func));				\
    }																							\
                                                                                                \
    template<class ObjectClass, class RT>														\
    void connect(ObjectClass *obj,RT(ObjectClass::*slot_func)(MACROSBIKES_TT##PN))								\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
            if(slots_[i]->isSlotObject(obj,slot_func))											\
            {																					\
                if(SlotConnectableObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>* s=dynamic_cast<SlotConnectableObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>* >(slots_[i]) )\
                {																				\
                    return;																		\
                }else																			\
                {																				\
                    slots_[i]->disconnect(this);												\
                    delete slots_[i];															\
                    slots_[i]=new SlotConnectableObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>(obj,slot_func);\
                    slots_[i]->connect(this);													\
                    return;																		\
                }																				\
            }																					\
        SlotConnectableObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN> *s=new SlotConnectableObject<ObjectClass,RT MACROSBIKES_COMMA##PN MACROSBIKES_TT##PN>(obj,slot_func);\
        s->connect(this);																		\
        slots_.push_back(s);																	\
    }																							\
                                                                                                \
    template<class ObjectClass, class RT>														\
    void disconnect(ObjectClass *obj, RT(ObjectClass::*slot_func)(MACROSBIKES_TT##PN))							\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
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
        for(sznum i=0; i<slots_.size(); i++)												\
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
        for(sznum i=0; i<slots_.size(); i++)												\
        {																						\
            slots_[i]->disconnect(this);														\
            delete slots_[i];																	\
        }																						\
        slots_.clear();																			\
    }																							\
private:																						\
    void disconnectAll_(void *pObj)																\
    {																							\
        for(sznum i=0; i<slots_.size(); i++)												\
            if(slots_[i]->pObj()==pObj)															\
            {																					\
                delete slots_[i];																\
                slots_.erase(slots_.begin()+i);													\
                i--;																			\
            }																					\
    }																							\
    std::vector<AbstractSlot<MACROSBIKES_TT##PN>* > slots_;														\
};
//-----------------------------------------------------------------------------------------------
MACROSBIKES_FOREACHPARAMLIST(MACROSBIKES_SIGNAL_TEMPLATECLASS_DECL)
//==============================================================================================

//#define MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(CT,TT,COMMA)                             
#define MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF(PN)                                      \
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>					\
void SignalConnectInterface::connect(ObjectClass *obj, RT(ObjectClass::*f)(MACROSBIKES_TT##PN))					\
{																								\
    if(Signal<MACROSBIKES_TT##PN>* s=dynamic_cast<Signal<MACROSBIKES_TT##PN>*>(this))											\
    {																							\
        s->connect(obj,f);																		\
    }																							\
}																								\
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
void SignalConnectInterface::connect_unsafe(ObjectClass *obj, RT(ObjectClass::*f)(MACROSBIKES_TT##PN))			\
{																								\
    if(Signal<MACROSBIKES_TT##PN>* s=dynamic_cast<Signal<MACROSBIKES_TT##PN>*>(this))											\
    {																							\
        s->connect_unsafe(obj,f);																\
    }																							\
}																								\
template<class ObjectClass, class RT MACROSBIKES_COMMA##PN MACROSBIKES_CT##PN>													\
void SignalConnectInterface::disconnect(ObjectClass *obj, RT(ObjectClass::*f)(MACROSBIKES_TT##PN))				\
{																								\
    if(Signal<MACROSBIKES_TT##PN>* s=dynamic_cast<Signal<MACROSBIKES_TT##PN>* >(this))											\
    {																							\
        s->disconnect(obj,f);																	\
    }																							\
}
//-----------------------------------------------------------------------------------------------
MACROSBIKES_FOREACHPARAMLIST(MACROSBIKES_SIGNALCONNECTINTERFACE_CONNECT_DEF)
//==============================================================================================

}// Bikes

#endif // BIKES_SIGNALS_H
