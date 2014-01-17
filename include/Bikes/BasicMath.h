#ifndef PREBIKES_BASICMATH_H
#define PREBIKES_BASICMATH_H
#include <math.h>
#include <Bikes/Types.h>

#define BIKES_CONST_PI  3.1415926535897932384626433832795  // (double) 3.1415926535897932
#define BIKES_CONST_E   2.7182818284590452353602874713527  // (double) 2.7182818284590452

namespace Bikes
{

const rnum PI=BIKES_CONST_PI;

const rnum E=BIKES_CONST_E;

const rnum RNUM_O=1E-30; //-35
const rnum RNUM_INFINITY=rnum(1)/RNUM_O;
const rnum EQUAL_O=1E-12;
const rnum ANGLE_O=1E-10;

const rnum DEG_PER_RAD=rnum(180)/PI;
const rnum RAD_PER_DEG=PI/rnum(180);

const rnum SQRT2=sqrt(rnum(2));
const rnum SQRT3=sqrt(rnum(3));

const rnum PId2=PI/rnum(2);
const rnum PId3=PI/rnum(3);
const rnum PId4=PI/rnum(4);
const rnum PId6=PI/rnum(6);
const rnum PIm2=PI*rnum(2);
const rnum PI3d2=PId2*rnum(3);

const rnum ANG_1DEG=RAD_PER_DEG;
const rnum ANG_1MIN=ANG_1DEG/60.0;
const rnum ANG_1SEC=ANG_1MIN/60.0;


rnum acosh(rnum a);

rnum asinh(rnum a);

rnum normAngle(rnum a);

rnum normAzimuthAngle(rnum a);

rnum signum(rnum n);

rnum arccos(rnum n);

rnum arcsin(rnum n);

inline rnum DEG_to_RAD(rnum deg){return deg*RAD_PER_DEG;}

inline rnum RAD_to_DEG(rnum rad){return rad*DEG_PER_RAD;}

bool isEqual(rnum n1, rnum n2, rnum O=EQUAL_O);

bool isEqualAngle(rnum a1, rnum a2);

rnum not0(rnum n, rnum o=RNUM_O);

void not0set(rnum &n, rnum o=RNUM_O);

rnum normalDistribution(rnum x);


template<class T>
T (MAX)(T x, T y)
{
  if(x>y) return x;
  return y;
}

template<class T>
T (MAX)(T x1, T x2, T x3)
{
    return MAX(MAX(x1,x2),x3);
}

template<class T>
T (MAX)(T x1, T x2, T x3, T x4)
{
    return MAX(MAX(x1,x2),MAX(x3,x4));
}

template<class T>
T (MIN)(T x, T y)
{
  if(x<y) return x;
  return y;
}

template<class T>
T (MIN)(T x1, T x2, T x3)
{
    return MIN(MIN(x1,x2),x3);
}

template<class T>
T (MIN)(T x1, T x2, T x3, T x4)
{
    return MIN(MIN(x1,x2),MIN(x3,x4));
}

template<class T>
T (AVG)(T x1, T x2)
{
    return (x1+x2)/2.0;
}

template<class T>
T (AVG)(T x1, T x2, T x3)
{
    return (x1+x2+x3)/3.0;
}

template<class T>
T (AVG)(T x1, T x2, T x3, T x4)
{
    return (x1+x2+x3+x4)/4.0;
}


template<class T>
T (ABS)(T val)
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
  return static_cast<long long>(val);
}


// DEV ->

#ifdef PREBIKES_DEV_MATHFUNCTION

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

  MathFunctionResult diff(rnum x, rnum dx=EQUAL_O) const;
  rnum findNewtonRoot(rnum x_min, rnum x_max, bool *suc=0, rnum Eps=EQUAL_O, int MaxIter=10000, rnum dx=EQUAL_O*10 ) const;

};
#endif // BIKES_DEV_MATHFUNCTION
// <- DEV 
}
#endif
