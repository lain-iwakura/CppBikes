#ifndef BASICMATH_H
#define BASICMATH_H
#include <math.h>
//#include "List.h"
#include <CppBikes/List.h>
#include <CppBikes/Types.h>

#define CPPBIKES_CONST_PI  3.1415926535897932384626433832795  // (double) 3.1415926535897932
#define CPPBIKES_CONST_E   2.7182818284590452353602874713527  // (double) 2.7182818284590452

namespace CppBikes
{

//typedef double RNUM;

const RNUM PI=CPPBIKES_CONST_PI;
const RNUM E=CPPBIKES_CONST_E;
const RNUM RNUM_O=1E-30; //-35
const RNUM RNUM_INFINITY=RNUM(1)/RNUM_O; 
const RNUM EQUAL_O=1E-12;
const RNUM ANGLE_O=1E-10;
const RNUM RAD_IN_DEG=RNUM(180)/PI;
const RNUM DEG_IN_RAD=PI/RNUM(180);

const RNUM SQRT2=sqrt(RNUM(2));
const RNUM SQRT3=sqrt(RNUM(3));
const RNUM PIdiv2=PI/RNUM(2);
const RNUM PIdiv3=PI/RNUM(3);
const RNUM PIdiv4=PI/RNUM(4);
const RNUM PIdiv6=PI/RNUM(6);
const RNUM PImult2=PI*RNUM(2);
const RNUM PI3div2=PIdiv2*RNUM(3);


RNUM acosh(RNUM a);
RNUM asinh(RNUM a);
RNUM NormAngle(RNUM a);
RNUM NormAngle_0_2PI(RNUM a);
RNUM signum(RNUM n);
RNUM arccos(RNUM n);
RNUM arcsin(RNUM n);
inline RNUM DEG_to_RAD(RNUM deg){return deg*DEG_IN_RAD;}
inline RNUM RAD_to_DEG(RNUM rad){return rad*RAD_IN_DEG;}
bool isEqual(RNUM n1, RNUM n2, RNUM O=EQUAL_O);
bool isEqualAngle(RNUM a1, RNUM a2);
RNUM not0(RNUM n, RNUM o=RNUM_O);
void not0set(RNUM &n, RNUM o=RNUM_O);


RNUM NormalDistribution(RNUM x);


template<class T> 
T MAX(T x, T y) 
{
	if(x>y) return x;
	return y;
}

template<class T> 
T MIN(T x, T y) 
{
	if(x<y) return x;
	return y;
}

template<class T>
T ABS(T val)
{
    if(val<0) return -val;
    return val;
}

template<class T>
T inRange(T val, T val_min, T val_max)
{
	if(val<val_min) val=val_min;
	else if(val>val_max) val=val_max;
	return val;
}





//=============================================

// WTF?

enum MathFunctionResultType
{
	MATHFUNC_NORMAL_RESULT,
	MATHFUNC_NO_RESULT,
	MATHFUNC_INFINITY_RESULT
};


struct MathFunctionResult
{
	MathFunctionResult(RNUM r_=0, MathFunctionResultType mfrt_=MATHFUNC_NO_RESULT):r(r_),mfrt(mfrt_){}
	RNUM r;
	MathFunctionResultType mfrt;
};

class MathFunction
{
public:

	virtual MathFunctionResult f(RNUM x) const =0;

	MathFunctionResult Diff(RNUM x, RNUM dx=EQUAL_O) const;
	RNUM FindNewtonRoot(RNUM x_min, RNUM x_max, bool *suc=0, RNUM Eps=EQUAL_O, int MaxIter=10000, RNUM dx=EQUAL_O*10 ) const;
};

}
#endif
