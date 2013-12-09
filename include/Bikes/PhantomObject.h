#ifndef PREBIKES_PHANTOMOBJECT_H
#define PREBIKES_PHANTOMOBJECT_H

#include <Bikes/List.h>
#include <Bikes/AdjacentObject.h>
#define TEMPLT_CONSTRUCTOR_DEFALL(C_this,C_that,T) C_this(){}; C_this(const C_this<T> &xo):C_that<T>(xo){} C_this(const T& o):C_that<T>(o){}
#define TEMPLT_ASSIGMENTOPERATORS(C_this,C_that,T) void operator =(const T&  obj_){C_that<T>::operator=(obj_);} void operator=(C_this<T> & cobj){C_that<T>::operator=(cobj);}
#define TEMPLT_DEFALL(C_this,C_that,T) TEMPLT_CONSTRUCTOR_DEFALL(C_this,C_that,T) TEMPLT_ASSIGMENTOPERATORS(C_this,C_that,T)

#define PHANTOMOBJECT_CONSTRUCTOR_DEFALL(C_this,C_that,T) TEMPLT_CONSTRUCTOR_DEFALL(C_this,C_that,T) C_this(T *obj_):C_that<T>(obj_){}
#define PHANTOMOBJECT_ASSIGMENTOPERATORS(C_this,C_that,T) TEMPLT_ASSIGMENTOPERATORS(C_this,C_that,T) void operator=(T* obj_){C_that<T>::operator=(obj_);}
#define PHANTOMOBJECT_DEFALL(C_this,C_that,T) \
    PHANTOMOBJECT_CONSTRUCTOR_DEFALL(C_this,C_that,T)\
    PHANTOMOBJECT_ASSIGMENTOPERATORS(C_this,C_that,T)
//     protected: using C_that<T>::OBJ;\
//     public: using C_that<T>::destroy;\
//     using C_that<T>::exist;


namespace Bikes
{

template<class T> class PhantomObject
{
public:
	PhantomObject(T *obj_=0):OBJ(obj_){}
	PhantomObject(const T &obj_):OBJ(new T(obj_)){created();}
    PhantomObject(const PhantomObject<T> &phantom)
	{
		OBJ=0;
		if(phantom.OBJ) create(*phantom.OBJ);
	//	phantom.transObject(*this);
	}		
	virtual ~PhantomObject(){destroy();}

	void create()
	{
		destroy(); 
		OBJ=new T();
		created();
	}

    void create(const T &obj_)
	{
		destroy();
		OBJ=new T(obj_);
		created();
	}

	void take(T* pOBJ) 
	{
		destroy(); 
		OBJ=pOBJ;
		if(pOBJ) taked();
	}

	T* passObj() 
	{		
		T* rOBJ=OBJ;
		OBJ=0;
		if(rOBJ) passed(); 
		return rOBJ;
	}	

	void takeAway(PhantomObject<T> &phantom)
	{
		destroy();
		OBJ=phantom.OBJ;
		phantom.OBJ=0;
		if(OBJ){phantom.Passed(); taked();}
	}
	
	void destroy()
	{	
		if(OBJ)	
		{
			delete OBJ;
			OBJ=0; 
			destroyed();
		}
	}
	
    bool exist() const
    {
        return OBJ!=0;
    }
		
	T  val() const {if(OBJ) return *OBJ; return T();}
	T  val(const T& defval) const {if(OBJ) return *OBJ; return defval;}
	T& obj(){if(!OBJ) {OBJ=new T();created();}  return *OBJ;  } 
	T& obj(const T &DefObj){if(!OBJ){ OBJ=new T(DefObj);created();}  return *OBJ;  } 
	T* pObj(){return OBJ;} 

	operator T() const { if(OBJ) return *OBJ;  return T();}	
 	operator T*() { return OBJ;}
// 	operator const T*() const { return OBJ;}
// 	operator T const *() const { return OBJ;}
	T& operator =(const T &obj_){create(); *OBJ=obj_; return *OBJ;}
	T* operator =(T *pobj) {take(pobj);	return OBJ;}
	//PhantomObject<T>& operator =(const PhantomObject<T> &phantom){phantom.transObject(*this); return *this;}

	T* operator -> () {return OBJ;}
	const T* operator -> () const {return OBJ;}
	T& operator *(){if(!OBJ) {OBJ=new T();created();}  return *OBJ; }

protected:
	T *OBJ;	

	virtual void destructor(){destroy();}
// 	virtual void transObject(PhantomObject<T> &phobj) const
// 	{			
// 		if(OBJ) {phobj.create(); *phobj.OBJ=*OBJ;}
// 		else phobj.destroy();	
// 	}
	virtual void created(){}
	virtual void destroyed(){}
	virtual void passed(){destroyed();} //?
	virtual void taked(){created();} //?
};




#define TransObject TransPhantomObject
template<class T>class TransPhantomObject: public PhantomObject<T>
{	
protected:
    using PhantomObject<T>::OBJ;
 public:
	TransPhantomObject(T *pobj=0):PhantomObject<T>(pobj),MustDestroy(new bool(true)){}
	TransPhantomObject(const T &obj_):PhantomObject<T>(obj_),MustDestroy(new bool(true)){}
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
		phobj.destroy();
		phobj=OBJ; 
		*MustDestroy=false; 
	}
};
 
#define JointObject JointPhantomObject
template<class T>class JointPhantomObject: public PhantomObject<T>, public AdjacentObject
{
protected:
    using PhantomObject<T>::OBJ;
	using PhantomObject<T>::taked;
	using PhantomObject<T>::passed;
public:
	using PhantomObject<T>::destroy;
	

    JointPhantomObject(T *pobj=0):PhantomObject<T>(pobj){}
	JointPhantomObject(JointPhantomObject &jobg)
	{
		jobg.insertAsNext(*this);
		OBJ=jobg.OBJ;
	}
    JointPhantomObject(const T & obj_):PhantomObject<T>(obj_){}
	
	~JointPhantomObject()
	{
		if(next()||previous()){detachJ(); OBJ=0; }
		else destroy();
	}
	
	ADJACENTOBJECT_DEFFUNC(JointPhantomObject<T>)

	void operator = (const T &obj_){PhantomObject<T>::operator =(obj_);}

	void operator = (JointPhantomObject<T> &jobj)
	{
		release();
		jobj.insertAsNext(*this);			
		OBJ=jobj.OBJ;
	}

	void join(JointPhantomObject<T> &jobj, bool AllObj=false)
	{
		if(!AllObj)
		{		
			jobj.release();
			insertAsNext(jobj);
			jobj.OBJ=OBJ;
		}else
		{
			//jobj.destroy();
			jobj.take(OBJ);
			JointPhantomObject<T> *ti=this;
			JointPhantomObject<T> *ta=&jobj;
			while(ti->next())ti=ti->next();
			while(ta->previous()) ta=ta->previous();
			ti->setNext(ta);
		}
	}

	void release(bool SaveObj=false)
	{
		if(next()||previous())
		{
			detachJ();
			if(OBJ)
			{
				if(SaveObj) OBJ=new T(*OBJ);
				else OBJ=0;
			}
		}else if(!SaveObj) destroy(); 
	}

	void takeAway(PhantomObject<T> &phantom)  
	{
		if(OBJ==phantom.pObj()) return;
		if(OBJ) delete OBJ;
		OBJ=phantom.OBJ;
		phantom.OBJ=0;
		if(OBJ) phantom.passed(); 
		taked();
	}

	void take(T* pOBJ)
	{
		if(OBJ) delete OBJ;		
        OBJ=pOBJ;
        taked();
	}

protected:	

	void created()
	{		
		JointPhantomObject *n=this;
		JointPhantomObject *p=this;
		while(n=n->next()) n->OBJ=OBJ;
		while(p=p->previous()) p->OBJ=OBJ;
	}

	void destroyed()
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

     using JointPhantomObject<T>::exist;


	PHANTOMOBJECT_DEFALL(JointPhantomValue,JointPhantomObject,T)
	ADJACENTOBJECT_DEFFUNC(JointPhantomValue<T>)

	operator T() const {if(OBJ) return *OBJ; return T(0);}
	void operator +=(const T &v){if(OBJ) *OBJ+=v; else OBJ=new T(v);}
	void operator -=(const T &v){if(OBJ) *OBJ-=v; else OBJ=new T(-v);}
	void operator *=(const T &v){if(OBJ) *OBJ*=v;}
	void operator /=(const T &v){if(OBJ) *OBJ/=v;}
	void operator +=(const JointPhantomValue<T> &jval){if(jval.OBJ){ if(OBJ)*OBJ+=*jval.OBJ; else *OBJ=new T(*jval.OBJ);}}
	void operator -=(const JointPhantomValue<T> &jval){if(jval.OBJ){ if(OBJ)*OBJ-=*jval.OBJ; else *OBJ=new T(-(*jval.OBJ));}}
	void operator /=(const JointPhantomValue<T> &jval){if(OBJ){ if(jval.OBJ) *OBJ/=*jval.OBJ;}}
	void operator *=(const JointPhantomValue<T> &jval){if(OBJ){ if(jval.OBJ) *OBJ*=*jval.OBJ;}}
	T operator -(){if(OBJ) return -*OBJ; return -T(0);}
	T operator +(){if(OBJ) return +*OBJ; return +T(0);}
    bool operator ==(const JointPhantomValue<T> &jval) const{if(exist()&&jval.exist()) return *OBJ==*jval.OBJ; return false;}
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
	using  PhantomObject<T>::destroy;
    using  PhantomObject<T>::exist;
	TEMPLT_DEFALL(PhantomVal,PhantomObject,T)

	void clear(){destroy();}

	operator T() const {if(OBJ) return *OBJ; return T(0);}
	//T val() const {return PhantomObject<T>::Val()}

	void operator +=(const T &v){if(OBJ) *OBJ+=v; else OBJ=new T(v);}
	void operator -=(const T &v){if(OBJ) *OBJ-=v; else OBJ=new T(-v);}
	void operator *=(const T &v){if(OBJ) *OBJ*=v;}
	void operator /=(const T &v){if(OBJ) *OBJ/=v;}

	void operator +=(const PhantomVal<T> &cval){if(cval.OBJ){ if(OBJ)*OBJ+=*cval.OBJ; else *OBJ=new T(*cval.OBJ);}}
	void operator -=(const PhantomVal<T> &cval){if(cval.OBJ){ if(OBJ)*OBJ-=*cval.OBJ; else *OBJ=new T(-(*cval.OBJ));}}
	void operator /=(const PhantomVal<T> &cval){if(OBJ){ if(cval.OBJ) *OBJ/=*cval.OBJ;}}
	void operator *=(const PhantomVal<T> &cval){if(OBJ){ if(cval.OBJ) *OBJ*=*cval.OBJ;}}

	T operator -() const {if(OBJ) return -*OBJ; return -T(0);}
	T operator +() const {if(OBJ) return +*OBJ; return +T(0);}

	bool operator ==(const PhantomVal<T> &cval) const{if(exist()&&cval.exist()) return *OBJ==*cval.OBJ; return false;}	
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

