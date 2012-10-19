#ifndef BASICMATH_H
#define BASICMATH_H
#include <math.h>
#include "ContainerInterface.h"

#define CONST_PI  3.1415926535897932384626433832795  // (double) 3.1415926535897932
#define CONST_E   2.7182818284590452353602874713527  // (double) 2.7182818284590452


typedef double TRNUM;

const TRNUM PI=CONST_PI;
const TRNUM E=CONST_E;
const TRNUM TRNUM_O=1E-30; //-35
const TRNUM TRNUM_INFINITY=1/TRNUM_O; 
const TRNUM EQUAL_O=1E-12;
const TRNUM ANGLE_O=1E-10;
const TRNUM TRNUM_0=0;
const TRNUM RAD_IN_DEG=TRNUM(180)/PI;
const TRNUM DEG_IN_RAD=PI/TRNUM(180);

const TRNUM SQRT2=sqrt(TRNUM(2));
const TRNUM SQRT3=sqrt(TRNUM(3));
const TRNUM PIdiv2=PI/2;
const TRNUM PIdiv3=PI/3;
const TRNUM PIdiv4=PI/4;
const TRNUM PIdiv6=PI/6;
const TRNUM PImult2=PI*2;
const TRNUM PI3div2=PIdiv2*3;


TRNUM acosh(TRNUM a);
TRNUM asinh(TRNUM a);
TRNUM NormAngle(TRNUM a);
TRNUM NormAngle_0_2PI(TRNUM a);
TRNUM signum(TRNUM n);
TRNUM arccos(TRNUM n);
TRNUM arcsin(TRNUM n);
inline TRNUM DEG_to_RAD(TRNUM deg){return deg*DEG_IN_RAD;}
inline TRNUM RAD_to_DEG(TRNUM rad){return rad*RAD_IN_DEG;}
bool isEqual(TRNUM n1, TRNUM n2, TRNUM O=EQUAL_O);
bool isEqualAngle(TRNUM a1, TRNUM a2);
TRNUM not0(TRNUM n, TRNUM o=TRNUM_O);
void not0set(TRNUM &n, TRNUM o=TRNUM_O);

TRNUM NormalDistribution(TRNUM x);

//#define MAX(X,Y) (((X)>(Y))?(X):(Y))
//#define MIN(X,Y) (((X)>(Y))?(Y):(X))

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

enum MathFunctionResultType
{
	MATHFUNC_NORMAL_RESULT,
	MATHFUNC_NO_RESULT,
	MATHFUNC_INFINITY_RESULT
};


struct MathFunctionResult
{
	MathFunctionResult(TRNUM r_=0, MathFunctionResultType mfrt_=MATHFUNC_NO_RESULT):r(r_),mfrt(mfrt_){}
	TRNUM r;
	MathFunctionResultType mfrt;
};

class MathFunction
{
public:

	virtual MathFunctionResult f(TRNUM x) const =0;

	MathFunctionResult Diff(TRNUM x, TRNUM dx=EQUAL_O) const;
	TRNUM FindNewtonRoot(TRNUM x_min, TRNUM x_max, bool *suc=0, TRNUM Eps=EQUAL_O, int MaxIter=10000, TRNUM dx=EQUAL_O*10 ) const;
};






//template<class T> T max(const T& X, const T& Y){return (X>Y)?(X):(Y);}

//template<class T> T min(const T& X, const T& Y){return (X<Y)?(X):(Y);}

#endif