#include <Bikes/BasicMath.h>

namespace Bikes
{


rnum acosh(rnum a)
{
	if(ABS(a)<1) return 0;
	return log(a+sqrt(a*a-1));
}

rnum asinh(rnum a)
{	
	return log(a+sqrt(a*a+1));
}

rnum not0(rnum n, rnum o/* =RNUM_O */)
{
	if(ABS(n)<o) return (n<0)?(-o):(o);
	return n;
}

void not0set(rnum &n, rnum o/* =RNUM_O */)
{
	if(ABS(n)<o) n=(n<0)?(-o):(o);
}

rnum normAngle(rnum a)
{
	if(a>PI)  return a-(int(a/PIm2+0.5))*PIm2;
	if(a<-PI) return a-(int(a/PIm2-0.5))*PIm2;
	return a;
}

rnum normAzimuthAngle(rnum a)
{
	if(ABS(a)>PIm2)	a-=((long)(a/(PIm2)))*PIm2;
	if(a<0.0) a+=PIm2;
	return a;
}

rnum signum(rnum n)
{
	if(n<0.0) return -1.0;
	return 1.0;
}

rnum arccos(rnum n)
{
	if(n<=-1.0) return PI;
	if(n>=1.0) return 0.0;
	return acos(n);
}
rnum arcsin(rnum n)
{
	if(n<=-1.0) return -PId2;
	if(n>=1.0) return PId2;
	return asin(n);
}


bool isEqual(rnum n1, rnum n2, rnum O)
{
	return ABS(n1-n2)<O;
}

bool isEqualAngle(rnum a1, rnum a2)
{
	a1=normAzimuthAngle(a1);
	a2=normAzimuthAngle(a2);
	return isEqual(a1,a2,ANGLE_O);
}

rnum normalDistribution( rnum x )
{
	static const rnum m=1.0/sqrt(PIm2);
	return m*pow(E,-x*x/2.0);
}


// DEV ->
#ifdef PREBIKES_DEV_MATHFUNCTION

rnum MathFunction::findNewtonRoot(rnum x_min, rnum x_max, bool *suc/*=0*/, rnum Eps/*=RNUM_O*/, int MaxIter/*=10000*/, rnum dx/*=(x_max-x_min)/rnum(MaxIter) */ ) const
{
	if(suc) *suc=false;
	rnum roo=x_min;	
	rnum x=x_min;
	MathFunctionResult fx1;
	MathFunctionResult fx2;
	MathFunctionResult fxr;
	for(int i=0; i<MaxIter; i++)
	{
		fx1=f(x);
		if(fx1.mfrt!=MATHFUNC_NORMAL_RESULT){x+=dx; continue;}
		fx2=f(x+dx);
		if(fx2.mfrt!=MATHFUNC_NORMAL_RESULT){x+=2*dx; continue;}

		rnum dif=(fx2.r-fx1.r)/dx;
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


MathFunctionResult MathFunction::diff( rnum x, rnum dx/*=EQUAL_O*/ ) const
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

#endif // BIKES_DEV_MATHFUNCTION
// <- DEV
}// Bikes

/////////////////////////////////////////////////////
