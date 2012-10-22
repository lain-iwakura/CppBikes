#include "BasicMath.h"

using namespace CppBikes;

RNUM CppBikes::acosh(RNUM a)
{
	if(ABS(a)<1) return 0;
	return log(a+sqrt(a*a-1));
}

RNUM CppBikes::asinh(RNUM a)
{	
	return log(a+sqrt(a*a+1));
}

RNUM CppBikes::not0(RNUM n, RNUM o/* =RNUM_O */)
{
	if(ABS(n)<o) return (n<0)?(-o):(o);
	return n;
}

void CppBikes::not0set(RNUM &n, RNUM o/* =RNUM_O */)
{
	if(ABS(n)<o) n=(n<0)?(-o):(o);
}

RNUM CppBikes::NormAngle(RNUM a)
{
	if(a>PI)  return a-(int(a/PImult2+0.5))*PImult2;
	if(a<-PI) return a-(int(a/PImult2-0.5))*PImult2;
	return a;
}

RNUM CppBikes::NormAngle_0_2PI(RNUM a)
{
	if(ABS(a)>2*PI)	a-=((long)(a/(PImult2)))*PImult2;
	if(a<0) a+=PImult2;
	return a;
}

RNUM CppBikes::signum(RNUM n)
{
	if(n>0) return 1;
	if(n<0) return -1;
	return 0;
}

RNUM CppBikes::arccos(RNUM n)
{
	if(n<=-1) return PI;
	if(n>=1) return 0;
	return acos(n);
}
RNUM CppBikes::arcsin(RNUM n)
{
	if(n<=-1) return -PIdiv2;
	if(n>=1) return PIdiv2;
	return asin(n);
}

//inline RNUM DEG_to_RAD(RNUM deg){return deg*DEG_IN_RAD;}
//inline RNUM RAD_to_DEG(RNUM rad){return rad*RAD_IN_DEG;}

bool CppBikes::isEqual(RNUM n1, RNUM n2, RNUM O)
{
	return ABS(n1-n2)<O;
}

bool CppBikes::isEqualAngle(RNUM a1, RNUM a2)
{
	a1=NormAngle_0_2PI(a1);
	a2=NormAngle_0_2PI(a2);
	return isEqual(a1,a2,ANGLE_O);
}

RNUM CppBikes::NormalDistribution( RNUM x )
{
	static const RNUM m=1/sqrt(2*PI);
	return m*pow(E,-x*x/2);
}




RNUM MathFunction::FindNewtonRoot(RNUM x_min, RNUM x_max, bool *suc/*=0*/, RNUM Eps/*=RNUM_O*/, int MaxIter/*=10000*/, RNUM dx/*=(x_max-x_min)/RNUM(MaxIter) */ ) const
{
	if(suc) *suc=false;
	RNUM roo=x_min;	
	RNUM x=x_min;
	MathFunctionResult fx1;
	MathFunctionResult fx2;
	MathFunctionResult fxr;
	for(int i=0; i<MaxIter; i++)
	{
		fx1=f(x);
		if(fx1.mfrt!=MATHFUNC_NORMAL_RESULT){x+=dx; continue;}
		fx2=f(x+dx);
		if(fx2.mfrt!=MATHFUNC_NORMAL_RESULT){x+=2*dx; continue;}

		RNUM dif=(fx2.r-fx1.r)/dx;
		if(dif==0) {x+=dx; continue;}
		roo=x-fx1.r/dif;
		if((roo>x_min)&&(roo<x_max))
		{
			fxr=f(roo);
			if(ABS(fxr.r)<Eps)
			{
				if(suc) *suc=true;
				return roo;								
			}else
			{
				x=roo;
			}
		}else if(roo<=x_min)
		{	
			x_min=x_min+dx;
			x=x_min;		
		}else
		{
			x_max=x_max-dx;
			x=x_max;			
		}
	}

	return roo;
}



MathFunctionResult MathFunction::Diff( RNUM x, RNUM dx/*=EQUAL_O*/ ) const
{
	MathFunctionResult r;
	MathFunctionResult fx1=f(x);
	if(fx1.mfrt==MATHFUNC_NORMAL_RESULT)
	{
		MathFunctionResult fx2=f(x+dx);
		if(fx2.mfrt==MATHFUNC_NORMAL_RESULT) 
		{
			r.mfrt=MATHFUNC_NORMAL_RESULT;
			r.r=(fx2.r-fx1.r)/dx;
		}else if(fx2.mfrt==MATHFUNC_INFINITY_RESULT)
		{
			r.mfrt=MATHFUNC_INFINITY_RESULT;
			r.r=RNUM_INFINITY;
			if(fx2.r<0) r.r*=-1;
		}else
		{
		}
	}else if(fx1.mfrt==MATHFUNC_INFINITY_RESULT)
	{
		MathFunctionResult fx2=f(x+dx);
		if(fx2.mfrt==MATHFUNC_NORMAL_RESULT) 
		{
			r.mfrt=MATHFUNC_INFINITY_RESULT;
			r.r=RNUM_INFINITY;
			if(fx1.r>0) r.r*=-1;
		}else if(fx2.mfrt==MATHFUNC_INFINITY_RESULT)
		{			
		}else
		{
		}
	}else
	{
	}
	return r;
}



/////////////////////////////////////////////////////
