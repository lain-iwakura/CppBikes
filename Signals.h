#ifndef CPPBIKES_SIGNALS_H
#define CPPBIKES_SIGNALS_H

#include <CppBikes/List.h>


namespace CppBikes
{

class BaseSignal;
class BaseConnectableObject;
class SignalConnectInterface;
//=====================================================================
class SignalNullType
{
};
//=====================================================================
class BaseSlot
{
public:
	virtual ~BaseSlot(){}
	virtual void* pObj() =0;
};
//=====================================================================
class BaseConnectableObject
{
public:
	virtual ~BaseConnectableObject(){}
protected:
	void *parent_;
	friend class BaseSignal;
};
//=====================================================================
class BaseSignal
{
public:
	virtual ~BaseSignal(){}
	virtual void disconnectAll(void *pObj) = 0;
private:
	void setParentForConnectableObject(BaseConnectableObject* bco, void *parent)
	{
		bco->parent_=parent;
	}
	friend class SignalConnectInterface;
};
//=====================================================================
#define CPPBIKES_TYPES_FOR_SIGNAL_TEMPLATECLASS_DECL class T1=SignalNullType,class T2=SignalNullType, class T3=SignalNullType, class T4=SignalNullType, class T5=SignalNullType, class T6=SignalNullType, class T7=SignalNullType , class T8=SignalNullType, class T9=SignalNullType , class T10=SignalNullType
//=====================================================================
template<CPPBIKES_TYPES_FOR_SIGNAL_TEMPLATECLASS_DECL> class AbstractSlot;
//=====================================================================
template<class ObjectClass, class RT, CPPBIKES_TYPES_FOR_SIGNAL_TEMPLATECLASS_DECL> class SlotObject;
//=====================================================================
template<CPPBIKES_TYPES_FOR_SIGNAL_TEMPLATECLASS_DECL> class Signal;
//=====================================================================
#define CPPBIKES_SIGNAL_CONNECTINTERFACE(signal) signal##_connectInterface()
#define CPPBIKES_SIGNAL_CONNECTINTERFACE_DECL(signal) CppBikes::SignalConnectInterface&  CPPBIKES_SIGNAL_CONNECTINTERFACE(signal){return signal;}
#define CPPBIKES_CONNECT(emitter,signal,receiver,slot_func) emitter.CPPBIKES_SIGNAL_CONNECTINTERFACE(signal).connect(&receiver,&slot_func)
#define CPPBIKES_CONNECT_UNSAFE(emitter,signal,receiver,slot_func) emitter.CPPBIKES_SIGNAL_CONNECTINTERFACE(signal).connect_unsafe(&receiver,&slot_func)
#define CPPBIKES_DISCONNECT(emitter,signal,receiver,slot_func) emitter.CPPBIKES_SIGNAL_CONNECTINTERFACE(signal).disconnect(&receiver,&slot_func)
#define CPPBIKES_SIGNALS private
//=====================================================================
#define CPPBIKES_COMMA ,
#define CPPBIKES_NOTHING 
#define CPPBIKES_CT1 class T1
#define CPPBIKES_CT2 class T1, class T2
#define CPPBIKES_CT3 class T1, class T2, class T3
#define CPPBIKES_CT4 class T1, class T2, class T3, class T4
#define CPPBIKES_CT5 class T1, class T2, class T3, class T4, class T5
#define CPPBIKES_CT6 class T1, class T2, class T3, class T4, class T5, class T6
#define CPPBIKES_CT7 class T1, class T2, class T3, class T4, class T5, class T6, class T7
#define CPPBIKES_CT8 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8
#define CPPBIKES_CT9 class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9
#define CPPBIKES_TT1 T1
#define CPPBIKES_TT2 T1,T2
#define CPPBIKES_TT3 T1,T2,T3
#define CPPBIKES_TT4 T1,T2,T3,T4
#define CPPBIKES_TT5 T1,T2,T3,T4,T5
#define CPPBIKES_TT6 T1,T2,T3,T4,T5,T6
#define CPPBIKES_TT7 T1,T2,T3,T4,T5,T6,T7
#define CPPBIKES_TT8 T1,T2,T3,T4,T5,T6,T7,T8
#define CPPBIKES_TT9 T1,T2,T3,T4,T5,T6,T7,T8,T9
#define CPPBIKES_TP1 T1 par1
#define CPPBIKES_TP2 T1 par1, T2 par2
#define CPPBIKES_TP3 T1 par1, T2 par2, T3 par3
#define CPPBIKES_TP4 T1 par1, T2 par2, T3 par3, T4 par4
#define CPPBIKES_TP5 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5
#define CPPBIKES_TP6 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6
#define CPPBIKES_TP7 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7
#define CPPBIKES_TP8 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7, T8 par8
#define CPPBIKES_TP9 T1 par1, T2 par2, T3 par3, T4 par4, T5 par5, T6 par6, T7 par7, T8 par8, T9 par9
#define CPPBIKES_PP1 par1
#define CPPBIKES_PP2 par1,par2
#define CPPBIKES_PP3 par1,par2,par3
#define CPPBIKES_PP4 par1,par2,par3,par4
#define CPPBIKES_PP5 par1,par2,par3,par4,par5
#define CPPBIKES_PP6 par1,par2,par3,par4,par5,par6
#define CPPBIKES_PP7 par1,par2,par3,par4,par5,par6,par7,
#define CPPBIKES_PP8 par1,par2,par3,par4,par5,par6,par7,par8
#define CPPBIKES_PP9 par1,par2,par3,par4,par5,par6,par7,par8,par9

//=====================================================================
#define CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CT,TT,COMMA)\
template<class ObjectClass, class RT COMMA CT>\
void connect(ObjectClass *obj, RT(ObjectClass::*f)(TT))\
{\
	if(Signal<TT>* s=dynamic_cast<Signal<TT>*>(this))\
	{\
		s->connect(obj,f);	\
		s->setParentForConnectableObject(&obj->connectable_object,obj);\
		obj->CPPBIKES_SIGNAL_CONNECTINTERFACE(signal_deleted).connect_unsafe(s,&Signal<TT>::disconnectAll);\
	}		\
}\
template<class ObjectClass, class RT COMMA CT>	\
void connect_unsafe(ObjectClass *obj, RT(ObjectClass::*f)(TT))\
{\
	if(Signal<TT>* s=dynamic_cast<Signal<TT>*>(this))\
	{\
		s->connect(obj,f);\
	}\
}\
template<class ObjectClass, class RT COMMA CT>\
void disconnect(ObjectClass *obj, RT(ObjectClass::*f)(TT))\
{\
	if(Signal<TT>* s=dynamic_cast<Signal<TT>*>(this))\
	{\
		s->disconnect(obj,f);\
	}\
}
//=====================================================================

class SignalConnectInterface
{
public:
	virtual ~SignalConnectInterface(){}

CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_NOTHING,CPPBIKES_NOTHING,CPPBIKES_NOTHING)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT1,CPPBIKES_TT1,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT2,CPPBIKES_TT2,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT3,CPPBIKES_TT3,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT4,CPPBIKES_TT4,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT5,CPPBIKES_TT5,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT6,CPPBIKES_TT6,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT7,CPPBIKES_TT7,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT8,CPPBIKES_TT8,CPPBIKES_COMMA)
CPPBIKES_SIGNALCONNECTINTERFACE_CONNECT_DECL(CPPBIKES_CT9,CPPBIKES_TT9,CPPBIKES_COMMA)

};



//=====================================================================
#define CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CT,TT,TP,PP,COMMA)\
template<CT>\
class AbstractSlot<TT>: public BaseSlot\
{\
public:\
	virtual ~AbstractSlot(){}\
	virtual void call(TP) = 0;\
	template<class ObjectClass,class RT>\
	bool isSlotObject(ObjectClass *pObg,RT(ObjectClass::*slot_func)(TT))\
	{\
		if(SlotObject<ObjectClass,RT COMMA TT> *s=dynamic_cast<SlotObject<ObjectClass,RT COMMA TT>*>(this))\
			return (s->pObj_==pObg)&&(s->f==slot_func);	\
		return false;\
	}\
};\
template<class ObjectClass, class RT COMMA CT>\
class SlotObject<ObjectClass,RT COMMA TT>: public AbstractSlot<TT>\
{\
public:	\
	typedef RT (ObjectClass::*ObjFuncType)(TT);\
	SlotObject(ObjectClass *obj,ObjFuncType fu): pObj_(obj),f(fu){}\
	void call(TP){(pObj_->*f)(PP);}\
	void* pObj(){return pObj_;}\
	ObjectClass *pObj_;\
	ObjFuncType f;\
};\
\
template<CT>\
class Signal<TT>: public SignalConnectInterface, public BaseSignal\
{\
public:	\
	void operator ()(TP){for(int i=0; i<slots_.count(); i++)slots_[i].call(PP);} \
	template<class ObjectClass, class RT>\
	void connect(ObjectClass *obj,RT(ObjectClass::*slot_func)(TT))\
	{\
		for(int i=0; i<slots_.size(); i++)if(slots_[i].isSlotObject(obj,slot_func)) return;\
		slots_.Take(new SlotObject<ObjectClass,RT COMMA TT>(obj,slot_func));\
	}\
	template<class ObjectClass, class RT>\
	void disconnect(ObjectClass *obj, RT(ObjectClass::*slot_func)(TT))\
	{\
		for(int i=0; i<slots_.size(); i++)\
			if(slots_[i].isSlotObject(obj,slot_func)){slots_.removeAt(i);return;}\
	}\
	void disconnectAll(void *pObj)\
	{\
		for(int i=0; i<slots_.size(); i++)\
			if(slots_[i].pObj()==pObj){slots_.removeAt(i);i--;}\
	}\
private:\
	List<AbstractSlot<TT> > slots_;\
};
//=====================================================================

//CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_NOTHING,CPPBIKES_NOTHING,CPPBIKES_NOTHING,CPPBIKES_NOTHING,CPPBIKES_NOTHING)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT1,CPPBIKES_TT1,CPPBIKES_TP1,CPPBIKES_PP1,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT2,CPPBIKES_TT2,CPPBIKES_TP2,CPPBIKES_PP2,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT3,CPPBIKES_TT3,CPPBIKES_TP3,CPPBIKES_PP3,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT4,CPPBIKES_TT4,CPPBIKES_TP4,CPPBIKES_PP4,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT5,CPPBIKES_TT5,CPPBIKES_TP5,CPPBIKES_PP5,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT6,CPPBIKES_TT6,CPPBIKES_TP6,CPPBIKES_PP6,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT7,CPPBIKES_TT7,CPPBIKES_TP7,CPPBIKES_PP7,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT8,CPPBIKES_TT8,CPPBIKES_TP8,CPPBIKES_PP8,CPPBIKES_COMMA)
CPPBIKES_SIGNAL_TEMPLATECLASS_DECL(CPPBIKES_CT9,CPPBIKES_TT9,CPPBIKES_TP2,CPPBIKES_PP9,CPPBIKES_COMMA)


//=====================================================================
class ConnectableObject: public BaseConnectableObject
{	
public:
	ConnectableObject(){parent_=0;}
	~ConnectableObject()
	{
		signal_deleted(parent_);
	}
	CPPBIKES_SIGNAL_CONNECTINTERFACE_DECL(signal_deleted)
private:
	Signal<void*> signal_deleted;
};
//=====================================================================
#define CPPBIKES_CONNECTABLEOBJECT \
public:\
CppBikes::ConnectableObject connectable_object;\
CppBikes::SignalConnectInterface& CPPBIKES_SIGNAL_CONNECTINTERFACE(signal_deleted){return connectable_object.CPPBIKES_SIGNAL_CONNECTINTERFACE(signal_deleted);}


}// CppBikes

#endif // CPPBIKES_SIGNALS_H
