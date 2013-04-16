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

}
#endif