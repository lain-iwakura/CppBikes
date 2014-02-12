#include <math.h>
#include <Bikes/Math/Tools.h>


namespace Bikes
{
	
rnum acosh(rnum a)
{
	if(ABS(a)<1.0) 
		return 0;

	return log(a+sqrt(a*a-1.0));
}

rnum asinh(rnum a)
{	
	return log(a+sqrt(a*a+1.0));
}

rnum not0(rnum n, rnum o/* =RNUM_O */)
{	
	if(n == 0.0)
		return o;

	return n;
}

rnum notSmall(rnum n, rnum o/* =RNUM_O */)
{
	if(n < 0.0)
	{
		if(n > -o)
			return -o;
	}else
	{
		if(n < o)
			return o;
	}
	return n;
}

void setNot0(rnum& n, rnum o/* =RNUM_O */)
{
	if(n == 0.0)
		n = o;
}

void setNotSmall(rnum& n, rnum o/* =RNUM_O */)
{
	if(n < 0.0)
	{
		if(n > -o)
			n = -o;
	}else
	{
		if(n < o)
			n = o;
	}
}

rnum normAngle(rnum a)
{
	if(a>PI)
		return a - intPart(a/PIm2 + 0.5)*PIm2;

	if(a<-PI)
		return a - intPart(a/PIm2 - 0.5)*PIm2;

	return a;
}


void setNormAngle( radian& a )
{
	if(a>PI)
		a -= intPart(a/PIm2 + 0.5)*PIm2;

	else if(a<-PI)
		a -= intPart(a/PIm2 - 0.5)*PIm2;
}


radian normAzimuthAngle(radian a)
{
	if(a > PIm2 || a < -PIm2)	
		a -= intPart(a/(PIm2))*PIm2;

	if(a < 0.0) 
		a += PIm2;

	return a;
}

void setNormAzimuthAngle(radian& a)
{
	if(a > PIm2 || a < -PIm2)	
		a -= intPart(a/(PIm2))*PIm2;

	if(a < 0.0) 
		a += PIm2;	
}

rnum signum(rnum n)
{
	if(n<0.0) 
		return -1.0;

	return 1.0;
}

rnum arccos(rnum n)
{
	if(n <= -1.0) 
		return PI;

	if(n >= 1.0) 
		return 0.0;

	return acos(n);
}
rnum arcsin(rnum n)
{
	if(n <= -1.0) 
		return -PId2;

	if(n >= 1.0) 
		return PId2;

	return asin(n);
}


bool isEqual(rnum n1, rnum n2, rnum O)
{
	return ABS(n1-n2)<O;
}

bool isEqualAngle(rnum a1, rnum a2, rnum O /*= ANGLE_O*/)
{
	return isEqual(normAzimuthAngle(a1),normAzimuthAngle(a2),O);
}

rnum normalDistribution( rnum x )
{
	static const rnum m = 1.0/sqrt(PIm2);

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
