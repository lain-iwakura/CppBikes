#ifndef PHANTOMOBJECT_H
#define PHANTOMOBJECT_H


#include "List.h"
#include "AdjacentObject.h"
#define TEMPLT_CONSTRUCTOR_DEFALL(C_this,C_that,T) C_this(){}; C_this(const C_this<T> &xo):C_that<T>(xo){} C_this(const T& o):C_that<T>(o){}
#define TEMPLT_ASSIGMENTOPERATORS(C_this,C_that,T) void operator =(const T&  obj){C_that<T>::operator=(obj);} void operator=(C_this<T> & cobj){C_that<T>::operator=(cobj);}
#define TEMPLT_DEFALL(C_this,C_that,T) TEMPLT_CONSTRUCTOR_DEFALL(C_this,C_that,T) TEMPLT_ASSIGMENTOPERATORS(C_this,C_that,T)

#define PHANTOMOBJECT_CONSTRUCTOR_DEFALL(C_this,C_that,T) TEMPLT_CONSTRUCTOR_DEFALL(C_this,C_that,T) C_this(T *obj):C_that<T>(obj){}
#define PHANTOMOBJECT_ASSIGMENTOPERATORS(C_this,C_that,T) TEMPLT_ASSIGMENTOPERATORS(C_this,C_that,T) void operator=(T* obj){C_that<T>::operator=(obj);}
#define PHANTOMOBJECT_DEFALL(C_this,C_that,T) \
    PHANTOMOBJECT_CONSTRUCTOR_DEFALL(C_this,C_that,T)\
    PHANTOMOBJECT_ASSIGMENTOPERATORS(C_this,C_that,T)
//     protected: using C_that<T>::OBJ;\
//     public: using C_that<T>::Destroy;\
//     using C_that<T>::Exist;


namespace CppBikes
{

template<class T> class PhantomObject
{
public:
	PhantomObject(T *obj=0):OBJ(obj){}
	PhantomObject(const T &obj):OBJ(new T(obj)){Created();}
    PhantomObject(const PhantomObject<T> &phantom)
	{
		OBJ=0;
		if(phantom.OBJ) Create(*phantom.OBJ);
	//	phantom.transObject(*this);
	}		
	virtual ~PhantomObject(){Destroy();}

	void Create()
	{
		Destroy(); 
		OBJ=new T();
		Created();
	}

    void Create(const T &obj)
	{
		Destroy();
		OBJ=new T(obj);
		Created();
	}

	void Take(T* pOBJ) 
	{
		Destroy(); 
		OBJ=pOBJ;
		if(pOBJ) Taked();
	}

	T* PassObj() 
	{		
		T* rOBJ=OBJ;
		OBJ=0;
		if(rOBJ) Passed(); 
		return rOBJ;
	}	

	void TakeAway(PhantomObject<T> &phantom)
	{
		Destroy();
		OBJ=phantom.OBJ;
		phantom.OBJ=0;
		if(OBJ){phantom.Passed(); Taked();}
	}
	
	void Destroy()
	{	
		if(OBJ)	
		{
			delete OBJ;
			OBJ=0; 
			Destroyed();
		}
	}
	
    bool Exist() const
    {
        return OBJ!=0;
    }
		
	T  Val() const {if(OBJ) return *OBJ; return T();}
	T  Val(const T& defval) const {if(OBJ) return *OBJ; return defval;}
	T& Obj(){if(!OBJ) {OBJ=new T();Created();}  return *OBJ;  } 
	T& Obj(const T &DefObj){if(!OBJ){ OBJ=new T(DefObj);Created();}  return *OBJ;  } 
	T* pObj(){return OBJ;} 

	operator T() const { if(OBJ) return *OBJ;  return T();}	
 	operator T*() { return OBJ;}
// 	operator const T*() const { return OBJ;}
// 	operator T const *() const { return OBJ;}
	T& operator =(const T &obj){Create(); *OBJ=obj; return *OBJ;}
	T* operator =(T *pobj) {Take(pobj);	return OBJ;}
	//PhantomObject<T>& operator =(const PhantomObject<T> &phantom){phantom.transObject(*this); return *this;}

	T* operator -> () {return OBJ;}
	const T* operator -> () const {return OBJ;}
	T& operator *(){if(!OBJ) {OBJ=new T();Created();}  return *OBJ; }

protected:
	T *OBJ;	

	virtual void destructor(){Destroy();}
// 	virtual void transObject(PhantomObject<T> &phobj) const
// 	{			
// 		if(OBJ) {phobj.Create(); *phobj.OBJ=*OBJ;}
// 		else phobj.Destroy();	
// 	}
	virtual void Created(){}
	virtual void Destroyed(){}
	virtual void Passed(){Destroyed();} //?
	virtual void Taked(){Created();} //?
};




#define TransObject TransPhantomObject
template<class T>class TransPhantomObject: public PhantomObject<T>
{	
protected:
    using PhantomObject<T>::OBJ;
 public:
	TransPhantomObject(T *pobj=0):PhantomObject<T>(pobj),MustDestroy(new bool(true)){}
	TransPhantomObject(const T &obj):PhantomObject<T>(obj),MustDestroy(new bool(true)){}
	TransPhantomObject(const TransPhantomObject<T> &tobj):PhantomObject<T>(tobj),MustDestroy(new bool(true)){}	
	PHANTOMOBJECT_ASSIGMENTOPERATORS(TransPhantomObject,PhantomObject,T)
	~TransPhantomObject()
	{
		if(!(*MustDestroy)) OBJ=0;
		delete MustDestroy;
	}
	
	//PHANTOMOBJECT_DEFALL(TransPhantomObject,PhantomObject,T)	
 	
private:
	bool *MustDestroy;
	void transObject(PhantomObject<T> &phobj) const
	{		
		phobj.Destroy();
		phobj=OBJ; 
		*MustDestroy=false; 
	}
};
 
#define JointObject JointPhantomObject
template<class T>class JointPhantomObject: public PhantomObject<T>, public AdjacentObject
{
protected:
    using PhantomObject<T>::OBJ;
	using PhantomObject<T>::Taked;
	using PhantomObject<T>::Passed;
public:
	using PhantomObject<T>::Destroy;
	

    JointPhantomObject(T *pobj=0):PhantomObject<T>(pobj){}
	JointPhantomObject(JointPhantomObject &jobg)
	{
		jobg.insertAsNext(*this);
		OBJ=jobg.OBJ;
	}
    JointPhantomObject(const T & obj):PhantomObject<T>(obj){}
	
	~JointPhantomObject()
	{
		if(next()||previous()){detachJ(); OBJ=0; }
		else Destroy();
	}
	
	ADJACENTOBJECT_DEFFUNC(JointPhantomObject<T>)

	void operator = (const T &obj){PhantomObject<T>::operator =(obj);}

	void operator = (JointPhantomObject<T> &jobj)
	{
		Release();
		jobj.insertAsNext(*this);			
		OBJ=jobj.OBJ;
	}

	void Join(JointPhantomObject<T> &jobj, bool AllObj=false)
	{
		if(!AllObj)
		{		
			jobj.Release();
			insertAsNext(jobj);
			jobj.OBJ=OBJ;
		}else
		{
			//jobj.Destroy();
			jobj.Take(OBJ);
			JointPhantomObject<T> *ti=this;
			JointPhantomObject<T> *ta=&jobj;
			while(ti->next())ti=ti->next();
			while(ta->previous()) ta=ta->previous();
			ti->setNext(ta);
		}
	}

	void Release(bool SaveObj=false)
	{
		if(next()||previous())
		{
			detachJ();
			if(OBJ)
			{
				if(SaveObj) OBJ=new T(*OBJ);
				else OBJ=0;
			}
		}else if(!SaveObj) Destroy(); 
	}

	void TakeAway(PhantomObject<T> &phantom)  
	{
		if(OBJ==phantom.pObj()) return;
		if(OBJ) delete OBJ;
		OBJ=phantom.OBJ;
		phantom.OBJ=0;
		if(OBJ) phantom.Passed(); 
		Taked();
	}

	void Take(T* pOBJ)
	{
		if(OBJ) delete OBJ;		
        OBJ=pOBJ;
        Taked();
	}

protected:	

	void Created()
	{		
		JointPhantomObject *n=this;
		JointPhantomObject *p=this;
		while(n=n->next()) n->OBJ=OBJ;
		while(p=p->previous()) p->OBJ=OBJ;
	}

	void Destroyed()
	{
		JointPhantomObject *n=this;
		JointPhantomObject *p=this;
		while(n=n->next()) n->OBJ=0;
		while(p=p->previous()) p->OBJ=0;	
	}
};

template<class T>class JointPhantomValue: public JointPhantomObject<T>
{
protected:
      using JointPhantomObject<T>::OBJ;
public:

     using JointPhantomObject<T>::Exist;


	PHANTOMOBJECT_DEFALL(JointPhantomValue,JointPhantomObject,T)
	ADJACENTOBJECT_DEFFUNC(JointPhantomValue<T>)

	operator T() const {if(OBJ) return *OBJ; return T(0);}
	void operator +=(const T &val){if(OBJ) *OBJ+=val; else OBJ=new T(val);}
	void operator -=(const T &val){if(OBJ) *OBJ-=val; else OBJ=new T(-val);}
	void operator *=(const T &val){if(OBJ) *OBJ*=val;}
	void operator /=(const T &val){if(OBJ) *OBJ/=val;}
	void operator +=(const JointPhantomValue<T> &jval){if(jval.OBJ){ if(OBJ)*OBJ+=*jval.OBJ; else *OBJ=new T(*jval.OBJ);}}
	void operator -=(const JointPhantomValue<T> &jval){if(jval.OBJ){ if(OBJ)*OBJ-=*jval.OBJ; else *OBJ=new T(-(*jval.OBJ));}}
	void operator /=(const JointPhantomValue<T> &jval){if(OBJ){ if(jval.OBJ) *OBJ/=*jval.OBJ;}}
	void operator *=(const JointPhantomValue<T> &jval){if(OBJ){ if(jval.OBJ) *OBJ*=*jval.OBJ;}}
	T operator -(){if(OBJ) return -*OBJ; return -T(0);}
	T operator +(){if(OBJ) return +*OBJ; return +T(0);}
    bool operator ==(const JointPhantomValue<T> &jval) const{if(Exist()&&jval.Exist()) return *OBJ==*jval.OBJ; return false;}
};



#define VALOPERATORS_DEFALL(T,B) \
	void operator +=(const T &v){ B::operator +=(v);}\
	void operator -=(const T &v){ B::operator -=(v);}\
	void operator /=(const T &v){ B::operator /=(v);}\
	void operator *=(const T &v){ B::operator *=(v);}\
	


template<class T> class PhantomVal: public PhantomObject<T>   
{
protected:
    using  PhantomObject<T>::OBJ;
public:
	using  PhantomObject<T>::Destroy;
    using  PhantomObject<T>::Exist;
	TEMPLT_DEFALL(PhantomVal,PhantomObject,T)

	void Clear(){Destroy();}

	operator T() const {if(OBJ) return *OBJ; return T(0);}
	//T val() const {return PhantomObject<T>::Val()}

	void operator +=(const T &val){if(OBJ) *OBJ+=val; else OBJ=new T(val);}
	void operator -=(const T &val){if(OBJ) *OBJ-=val; else OBJ=new T(-val);}
	void operator *=(const T &val){if(OBJ) *OBJ*=val;}
	void operator /=(const T &val){if(OBJ) *OBJ/=val;}

	void operator +=(const PhantomVal<T> &cval){if(cval.OBJ){ if(OBJ)*OBJ+=*cval.OBJ; else *OBJ=new T(*cval.OBJ);}}
	void operator -=(const PhantomVal<T> &cval){if(cval.OBJ){ if(OBJ)*OBJ-=*cval.OBJ; else *OBJ=new T(-(*cval.OBJ));}}
	void operator /=(const PhantomVal<T> &cval){if(OBJ){ if(cval.OBJ) *OBJ/=*cval.OBJ;}}
	void operator *=(const PhantomVal<T> &cval){if(OBJ){ if(cval.OBJ) *OBJ*=*cval.OBJ;}}

	T operator -() const {if(OBJ) return -*OBJ; return -T(0);}
	T operator +() const {if(OBJ) return +*OBJ; return +T(0);}

	bool operator ==(const PhantomVal<T> &cval) const{if(Exist()&&cval.Exist()) return *OBJ==*cval.OBJ; return false;}	
};



// class Deleter // ?
// {
// public:
// 	Deleter(void *delObj=0){*this+=delObj;}
// 	~Deleter()
// 	{
// 		for(int i=0; i<delObjects.count(); i++) delete delObjects[i];
// 	}
// 	void operator +=(void *delObj){if(delObj) delObjects+=delObj;}
// 	List<void*> delObjects;
// };
}
#endif

