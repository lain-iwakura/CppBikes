#ifndef BASICMATH_H
#define BASICMATH_H
#include <math.h>
//#include "List.h"
#include <Bikes/List.h>
#include <Bikes/Types.h>

#define CPPBIKES_CONST_PI  3.1415926535897932384626433832795  // (double) 3.1415926535897932
#define CPPBIKES_CONST_E   2.7182818284590452353602874713527  // (double) 2.7182818284590452

namespace Bikes
{

//typedef double rnum;

const rnum PI=CPPBIKES_CONST_PI;
const rnum E=CPPBIKES_CONST_E;
const rnum RNUM_O=1E-30; //-35
const rnum RNUM_INFINITY=rnum(1)/RNUM_O; 
const rnum EQUAL_O=1E-12;
const rnum ANGLE_O=1E-10;
const rnum RAD_IN_DEG=rnum(180)/PI;
const rnum DEG_IN_RAD=PI/rnum(180);

const rnum SQRT2=sqrt(rnum(2));
const rnum SQRT3=sqrt(rnum(3));
const rnum PIdiv2=PI/rnum(2);
const rnum PIdiv3=PI/rnum(3);
const rnum PIdiv4=PI/rnum(4);
const rnum PIdiv6=PI/rnum(6);
const rnum PImult2=PI*rnum(2);
const rnum PI3div2=PIdiv2*rnum(3);

const rnum ANG_1DEG=DEG_IN_RAD;
const rnum ANG_1MIN=ANG_1DEG/60.0;
const rnum ANG_1SEC=ANG_1MIN/60.0;


rnum acosh(rnum a);
rnum asinh(rnum a);
rnum NormAngle(rnum a);
rnum NormAngle_0_2PI(rnum a);
rnum signum(rnum n);
rnum arccos(rnum n);
rnum arcsin(rnum n);
inline rnum DEG_to_RAD(rnum deg){return deg*DEG_IN_RAD;}
inline rnum RAD_to_DEG(rnum rad){return rad*RAD_IN_DEG;}
bool isEqual(rnum n1, rnum n2, rnum O=EQUAL_O);
bool isEqualAngle(rnum a1, rnum a2);
rnum not0(rnum n, rnum o=RNUM_O);
void not0set(rnum &n, rnum o=RNUM_O);



rnum NormalDistribution(rnum x);


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

template<class T>
T intPart(T val)
{
	return T(long long(val));
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
	MathFunctionResult(rnum r_=0, MathFunctionResultType mfrt_=MATHFUNC_NO_RESULT):r(r_),mfrt(mfrt_){}
	rnum r;
	MathFunctionResultType mfrt;
};

class MathFunction
{
public:

	virtual MathFunctionResult f(rnum x) const =0;

	MathFunctionResult Diff(rnum x, rnum dx=EQUAL_O) const;
	rnum FindNewtonRoot(rnum x_min, rnum x_max, bool *suc=0, rnum Eps=EQUAL_O, int MaxIter=10000, rnum dx=EQUAL_O*10 ) const;
};

}
#endif
