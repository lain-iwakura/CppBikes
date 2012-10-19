#include "BasicMath.h"



TRNUM acosh(TRNUM a)
{
	if(abs(a)<1) return 0;
	return log(a+sqrt(a*a-1));
}

TRNUM asinh(TRNUM a)
{	
	return log(a+sqrt(a*a+1));
}



TRNUM not0(TRNUM n, TRNUM o/* =TRNUM_O */)
{
	if(abs(n)<o) return o*((n<0)?(-1):(1));
	return n;
}

void not0set(TRNUM &n, TRNUM o/* =TRNUM_O */)
{
	if(abs(n)<o) n=o*((n<0)?(-1):(1));
}

TRNUM NormAngle(TRNUM a)
{
// 	if(abs(a)<PI*2) return a;
// 	TRNUM ra=abs(a);
// 	if(ra>=PImult2)
// 	{
// 		int kra=ra/PImult2;
// 		ra-=PImult2*kra;
// 	}
// 	if(a<0) ra*=-1;
// 	return ra;

	TRNUM r=abs(a);
	r-=((int)(r/PImult2))*PImult2;
	if(r>PI) r-=PImult2;
	if(a<0) r*=-1;
	return r;
}

TRNUM NormAngle_0_2PI(TRNUM a)
{
	if(abs(a)>2*PI)	a-=((long)(a/(2*PI)))*2*PI;
	if(a<0) a+=2*PI;
	return a;
}

TRNUM signum(TRNUM n)
{
	if(n>0) return 1;
	if(n<0) return -1;
	return 0;
}

TRNUM arccos(TRNUM n)
{
	if(n<=-1) return PI;
	if(n>=1) return 0;
	return acos(n);
}
TRNUM arcsin(TRNUM n)
{
	if(n<=-1) return -PI/2;
	if(n>=1) return PI/2;
	return asin(n);
}

//inline TRNUM DEG_to_RAD(TRNUM deg){return deg*DEG_IN_RAD;}
//inline TRNUM RAD_to_DEG(TRNUM rad){return rad*RAD_IN_DEG;}

bool isEqual(TRNUM n1, TRNUM n2, TRNUM O)
{
	return abs(n1-n2)<O;
}

bool isEqualAngle(TRNUM a1, TRNUM a2)
{
	a1=NormAngle_0_2PI(a1);
	a2=NormAngle_0_2PI(a2);
	return isEqual(a1,a2,ANGLE_O);
}

TRNUM NormalDistribution( TRNUM x )
{
	static const TRNUM m=1/sqrt(2*PI);
	return m*pow(E,-x*x/2);
}




TRNUM MathFunction::FindNewtonRoot(TRNUM x_min, TRNUM x_max, bool *suc/*=0*/, TRNUM Eps/*=TRNUM_O*/, int MaxIter/*=10000*/, TRNUM dx/*=(x_max-x_min)/TRNUM(MaxIter) */ ) const
{
	if(suc) *suc=false;
	TRNUM roo=x_min;	
	TRNUM x=x_min;
	MathFunctionResult fx1;
	MathFunctionResult fx2;
	MathFunctionResult fxr;
	for(int i=0; i<MaxIter; i++)
	{
		fx1=f(x);
		if(fx1.mfrt!=MATHFUNC_NORMAL_RESULT){x+=dx; continue;}
		fx2=f(x+dx);
		if(fx2.mfrt!=MATHFUNC_NORMAL_RESULT){x+=2*dx; continue;}

		TRNUM dif=(fx2.r-fx1.r)/dx;
		if(dif==0) {x+=dx; continue;}
		roo=x-fx1.r/dif;
		if((roo>x_min)&&(roo<x_max))
		{
			fxr=f(roo);
			if(abs(fxr.r)<Eps)
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



MathFunctionResult MathFunction::Diff( TRNUM x, TRNUM dx/*=EQUAL_O*/ ) const
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
			r.r=TRNUM_INFINITY;
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
			r.r=TRNUM_INFINITY;
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
