#ifndef INCLUDEBIKES_TOOLS_H
#define INCLUDEBIKES_TOOLS_H

#include <Bikes/Math/Constants.h>


namespace Bikes
{

rnum acosh(rnum a);

rnum asinh(rnum a);

radian normAngle(radian a);

void setNormAngle(radian& a);

radian normAzimuthAngle(radian a);

void setNormAzimuthAngle(radian& a);

rnum signum(rnum n);

radian arccos(cosnum n);

radian arcsin(sinnum n);

inline radian DEG_to_RAD(degree ang) {return ang*RAD_PER_DEG;}

inline degree RAD_to_DEG(radian ang) {return ang*DEG_PER_RAD;}

bool isEqual(rnum n1, rnum n2, rnum O = EQUAL_O);

bool isEqualAngle(radian a1, radian a2, radian O = ANGLE_O);

rnum not0 (rnum n, rnum O = RNUM_O);

void setNot0(rnum& n, rnum O = RNUM_O);

rnum notSmall(rnum n, rnum O = RNUM_O);

void setNotSmall(rnum& n, rnum O = RNUM_O);

rnum normalDistribution(rnum x);


template<class T>
ValSign getSign(T val)
{
	if(val > 0)
		return positiveSign;
	if(val < 0)
		return negativeSign;
	return undefinedSign;
}

template<class T>
T inRange(T val, T val_min, T val_max)
{
	if(val<val_min) 
		return val_min;
	if(val>val_max) 
		return val_max;
	return val;
}

template<class T>
void setInRange(T& val, T val_min, T val_max)
{
	if(val<val_min) 
		val = val_min;
	else if(val>val_max) 
		val = val_max;	
}

template<class T>
T (MAX)(T x, T y)
{
  if(x>y) 
	  return x;
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
  if(val<0) 
	  return -val;
  return val;
}


template<class T>
T intPart(T val)
{
  return T( static_cast<long long>(val) );
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
