#ifndef CALCVAL_H
#define CALCVAL_H

#define TMIN_DEF 0
#define TMAX_DEF 0

#include "BasicMath.h"
#include "PhantomObject.h"
#include "List.h"
#include "Bikes.h"

namespace CppBikes
{


	template<typename T>
	class CalcVal
	{
	public:
		CalcVal():val_(0),calc_(false){}
		CalcVal(T v):val_(v),calc_(true){}

		T val() const {return val_;}
		T& rval(){calc_=true; return val_;} // (!)
		bool isCalc() const {return calc_;}
		void clear(){calc_=false;}
		
		operator T() const { return val_;}
		operator T&() {calc_=true; return val_;}
		operator const T&() const {return val_;}		
		operator bool(){return calc_;}
		bool operator !(){return !calc_;}

		T& operator = (T v) {calc_=true; val_=v; return val_;}
		T& operator += (T v) {val_+=v; return val_;}
		T& operator -= (T v) {val_-=v; return val_;}
		T& operator *= (T v) {val_*=v; return val_;}
		T& operator /= (T v) {val_/=v; return val_;}
		T& operator ++ () {val_++; return val_;}
		T& operator -- () {val_--; return val_;}
		bool operator == (T v) const {return val_==v;}
		bool operator >= (T v) const {return val_>=v;}
		bool operator <= (T v) const {return val_<=v;}
		bool operator > (T v) const {return val_>v;}
		bool operator < (T v) const {return val_<v;}

		CalcVal<T>& operator = (const CalcVal<T> &cv) {val_=cv.val_; calc_=cv.calc_; return *this;}
		

	private:
		T val_;
		bool calc_;
	};

	typedef CalcVal<RNUM> CRNUM;
/*
template<class T>
class CalcVal
{
public:

	CalcVal():binfo(0),val(0){}
	
	static const unsigned char DEFINED=iBit8(0);
	static const unsigned char VALUE_DEFINITION=iBit8(1);
	static const unsigned char SIGN_DEFINITION=iBit8(2);
	static const unsigned char INFINITY=iBit8(3);
	static const unsigned char AMBIGUITY=iBit8(4)
	static const unsigned char COMPLEX=iBit8(6);//?
	static const unsigned char NEGATIVE=iBit8(7);


	bool isDifined(){ return binfo&DEFINED;}
	T sign(){return (binfo&NEGATIVE)?(-1):(1);}
	void Clear(){binfo=0; val=0;}


	template<class T2>
	CalcVal & operator = (const T2 &v) 
	{
		val=T(v);		
		binfo=DEFINED|VALUE_DEFINITION|SIGN_DEFINITION;
		if(val<0) binfo|=NEGATIVE;
		return *this;
	}

	CalcVal & operator = (const CalcVal &v)
	{
		val=v.val;
		binfo=v.binfo;
		return *this;
	}

	T val;
	unsigned char binfo;
};

*/

/*
template<class T, int TDEF=0, int TMIN=TMIN_DEF, int TMAX=TMAX_DEF, int TORDER=0>
class CalcVal: public PhantomVal<T>
{
public:

	

	T val() const { return PhantomVal<T>::Val(val_def);}
	T Val() const {return val();}

	operator T() const {return val();}
	T& operator =(const T& v) {return Obj()=v;}

	bool inRange() const
	{
		T v=val();
		if(v<val_min) return false;
		if(v>val_max) return false;
		return true;
	}

	void moveToRange()
	{
		T v=val();
		if(v<val_min)
		{
			Obj()=val_min;			
		}else if(v>val_max)
		{
			Obj()=val_max;
		}
	}

	void setDef(){Obj()=val_def;}

	
	static const T val_min;
	static const T val_max;
	static const T val_def;

private:	
};


template<class T, int TDEF, int TMIN, int TMAX, int TORDER>
const T CalcVal<T,TDEF,TMIN,TMAX, TORDER>::val_min=(T)(MIN(TMIN,TMAX)*pow(double(10),TORDER));

template<class T, int TDEF, int TMIN, int TMAX, int TORDER>
const T CalcVal<T,TDEF,TMIN,TMAX,TORDER>::val_max=(T)(MAX(TMAX,TMIN)*pow(double(10),TORDER));

template<class T, int TDEF, int TMIN, int TMAX, int TORDER>
const T  CalcVal<T,TDEF,TMIN,TMAX,TORDER>::val_def=(T)(TDEF*pow(double(10),TORDER));




template<class T, int TDEF, int TMIN, int TMAX>
class CalcVal<T,TDEF,TMIN,TMAX,0>: public PhantomVal<T>
{
public:



	T val() const { return PhantomVal<T>::Val(val_def);}
	T Val() const {return val();}

	operator T() const {return val();}
	T& operator =(const T& v) {return Obj()=v;}

	bool inRange() const
	{
		T v=val();
		if(v<val_min) return false;
		if(v>val_max) return false;
		return true;
	}

	void moveToRange()
	{
		T v=val();
		if(v<val_min)
		{
			Obj()=val_min;			
		}else if(v>val_max)
		{
			Obj()=val_max;
		}
	}

	void setDef(){Obj()=val_def;}


	static const T val_min;
	static const T val_max;
	static const T val_def;

private:	
};


template<class T, int TDEF, int TMIN, int TMAX>
const T CalcVal<T,TDEF,TMIN,TMAX,0>::val_min=(T)(MIN(TMIN,TMAX));

template<class T, int TDEF, int TMIN, int TMAX>
const T CalcVal<T,TDEF,TMIN,TMAX,0>::val_max=(T)(MAX(TMAX,TMIN));

template<class T, int TDEF, int TMIN, int TMAX>
const T  CalcVal<T,TDEF,TMIN,TMAX,0>::val_def=(T)(TDEF);



// template <class T, int N>
// class RandVal
// {
// 	RandVal();
// 
// private:
// 	T x[N];
// 	int i_cur;
// };

*/

}
#endif