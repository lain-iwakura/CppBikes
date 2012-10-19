#include "TrigonometricAngle_old.h"
#include <math.h>

using namespace CppBikes;


///////////////////////////////////////////////////////////
/////////////////// ANGLE /////////////////////////////////
///////////////////////////////////////////////////////////
RNUM CppBikes::cos(TAngle &A) {return A.Cos();}
RNUM CppBikes::sin(TAngle &A){return A.Sin();}
RNUM CppBikes::tan(TAngle &A){return A.Tan();}
RNUM CppBikes::ctan(TAngle &A){return A.cTan();}
RNUM CppBikes::rad(TAngle &A){return A.Rad();}
RNUM CppBikes::deg(TAngle &A){return A.Deg();}

RNUM CppBikes::normAngle(RNUM a, bool POSITIVE_PI_OFFSET/*=false*/, int PIx2_OFFSET/*=0*/)
{
	RNUM r=abs(a);
	r-=((int)(r/PImult2))*PImult2;
	if(r>PI) r-=PImult2;
	if(a<0) r*=-1;
	return r+ (PIx2_OFFSET + ((POSITIVE_PI_OFFSET&&r<0)?(1):(0)) )*PImult2;
}

RNUM nAngle(RNUM a, bool POSITIVE_PI_OFFSET)
{
	RNUM r=abs(a);
	r-=((int)(r/PImult2))*PImult2;
	if(r>PI) r-=PImult2;
	if(a<0) r*=-1;
	if(POSITIVE_PI_OFFSET&&r<0) r+=PImult2;
	return r;
}


TAngle::TAngle()
{
	sSIN=1;
	sCOS=1;
}
TAngle::TAngle(RNUM cos_a, RNUM ssin, bool positive_pi_offset)
{
	SetCos(cos_a,ssin);
	SetPositivePiOffset(positive_pi_offset);
	sSIN=1;
	sCOS=1;
}

TAngle::~TAngle()
{
	//SetUndefAll();
}


TAngle::TAngle(const TAngle &a)
{
	sSIN=a.sSIN;
	sCOS=a.sCOS;
	COS=a.COS;
	SIN=a.SIN;
	TAN=a.TAN;
	RAD=a.RAD;
	pi_offset=a.pi_offset;
}


void TAngle::SetPositivePiOffset(bool positive_pi_offset)
{
    if( RAD.Exist() && (positive_pi_offset!=pi_offset))
	{
		//RAD=nAngle(RAD,positive_pi_offset);
		if(positive_pi_offset)
		{
			if(RAD<RNUM(0)) RAD+=PImult2;
		}else
		{
			if(RAD>PI) RAD-=PImult2;
		}
	}
	pi_offset=positive_pi_offset;
}

void TAngle::SetUndefAll()
{
	sSIN=1;
	sCOS=1;
	COS.Clear();
	SIN.Clear();
	TAN.Clear();
	RAD.Clear();
}

void TAngle::SetNull()
{
	SetUndefAll();
	COS=RNUM(1);	
	SIN=RNUM(0);
	TAN=RNUM(0);
	RAD=RNUM(0);
}

void TAngle::SetCos(RNUM cos_a, RNUM ssin)
{
	SetUndefAll();
	if(cos_a>1) cos_a=1;
	else if(cos_a<-1) cos_a=-1;	
	COS=cos_a;
	sSIN=signum(ssin);
}
void TAngle::SetSin(RNUM sin_a, RNUM scos)
{
	SetUndefAll();
	if(sin_a>1) sin_a=1;
	else if(sin_a<-1) sin_a=-1;	
	SIN=sin_a;	
	sCOS=signum(scos);
}



void TAngle::SetTan(RNUM tan_a, RNUM scos)
{
	SetUndefAll();
	TAN=tan_a;
	sCOS=signum(scos);
	sSIN=sCOS*signum(tan_a);
}

void TAngle::SetCtan( RNUM ctan_a,RNUM cos_sign/*=1*/ )
{
	SetTan(ctan_a/not0(ctan_a),cos_sign);
}


void TAngle::SetRad(RNUM rad_a)
{
	SetUndefAll();
	RAD=nAngle(rad_a,pi_offset);	
	//RNUM na=normAngle(rad_a);//NormAngle_0_2PI(rad_a);
	if(pi_offset)
	{
		if(RAD>PIdiv2&&RAD<PI3div2) sCOS=-1;
		else sCOS=1;
		if(RAD>PI) sSIN=-1;
		else sSIN=1;
	}else
	{
		if(abs(RAD)>PIdiv2) sCOS=-1;
		else sCOS=1;
		if(RAD<RNUM(0)) sSIN=-1;
		else sSIN=1;
	}
//	sSIN=signum(PI-na);
//	if((na>(PIdiv2))&&(na<(3*PIdiv2))) sCOS=-1;	
//	else sCOS=1;
}

void TAngle::SetDeg(RNUM deg_a)
{	
	SetRad(DEG_to_RAD(deg_a));
}

bool TAngle::isDefined()
{
// 	if(SIN.Exist()) return true;
// 	if(COS.Exist()) return true;	
// 	if(RAD.Exist()) return true;
// 	if(TAN.Exist()) return true;
	return SIN.Exist()||COS.Exist()||RAD.Exist()||TAN.Exist();
}


RNUM TAngle::sSin()
{
//	if(SIN.Exist()) return signum(SIN);  //?
//	return sSIN.Val(1);	
	return sSIN;
}

RNUM TAngle::sCos()
{
//	if(COS.Exist()) return signum(COS); //?
//	return sCOS.Val(1);
	return sCOS; 
}

RNUM TAngle::Cos()
{
	if(COS.Exist()) return COS.Obj();

	if(SIN.Exist()) COS=sqrt(1-Sin()*Sin())*sCOS;
	else if(TAN.Exist()) COS=sqrt(1/(Tan()*Tan()+1))*sCOS;
	else if(RAD.Exist())
		COS.Obj()=::cos(Rad());
	else return 1;


	return COS.Obj();
}

RNUM TAngle::Sin()
{
	if(SIN.Exist()) return SIN.Obj();

	if(COS.Exist()) SIN=sqrt(1-COS.Obj()*COS.Obj())*sSIN;
	else if(TAN.Exist()) SIN=sqrt((TAN.Obj()*TAN.Obj())/(1+(TAN.Obj()*TAN.Obj())))*sSIN;
	else if(RAD.Exist()) SIN=::sin(Rad());
	else return 0;

	return SIN.Obj();
}

RNUM TAngle::Tan() 
{
	if(TAN.Exist()) return TAN.Obj();

	if(COS.Exist()||SIN.Exist()) 
	{
		if(isEqual(Cos(),0,RNUM_O)) TAN=RNUM_INFINITY; 
		else TAN=Sin()/Cos();		
	}
	else if(RAD.Exist())
		TAN.Obj()=::tan(Rad());
	else return 0;
	return TAN.Obj();
}

RNUM TAngle::cTan()
{
	if(isEqual(Tan(),0,RNUM_O)) return RNUM_INFINITY;
	return 1/Tan();
} 

RNUM TAngle::Rad() // +(?)
{
	if(RAD.Exist()) return RAD;

	if(SIN.Exist()) {RAD=arcsin(Sin()); if(sCos()<0) RAD=PI-RAD.Val(); else if(RAD<0) RAD+=PImult2;}
	else if(COS.Exist()) {RAD=arccos(Cos()); if(sSin()<0) RAD=PImult2-RAD.Val();}
	else if(TAN.Exist()) {RAD=atan(Tan()); if(RAD>0){if(sSin()<0)RAD+=PI;}else{if(sSin()>0)RAD+=PI; else RAD+=2*PI;}}
	else return 0;
	//	RAD=NormAngle_0_2PI(RAD);
	return RAD;
}

RNUM TAngle::Deg()
{
	return RAD_to_DEG(Rad());	
}

/*
int TAngle::Grad()
{
	return (int)Deg();
}

int TAngle::Min()
{
	return (int)((Deg()-Grad())*60);
}

int TAngle::Sec() // (?)
{
	return (int)((Deg()-Grad()-(RNUM)Min()/60)*3600);
}
*/

////////////////////////////////////////////////////// -
void TAngle::setOpposite() //?
{
	if(SIN.Exist()) SIN=-Sin();
	if(TAN.Exist()) TAN=-Tan();
	if(RAD.Exist()) RAD=-Rad();
	sSIN*=-1;	
}

void TAngle::plusPI(int nPI)
{
	if(RAD.Exist()) RAD+=PI*nPI;
	if(nPI%2)
	{
		if(SIN.Exist()) SIN=-Sin();
		if(COS.Exist()) COS=-Cos();	
	}
} 

void TAngle::plusPIdiv2(int nPIdiv2) // (?)
{
	plusPI(nPIdiv2/2);
	if(nPIdiv2%2)
	{
		int s=((nPIdiv2>0)?1:(-1));
		if(RAD.Exist()) RAD+=PIdiv2*s;

		sSIN;//?
		sCOS;//?
		//RNUM *sCOS=0;
		RNUM_CALC saveCOS(COS);
		if(SIN.Exist()){COS=(-SIN)*s;} else COS.Clear();
		if(saveCOS){SIN=saveCOS.Val()*s;} else SIN.Clear();
		if(TAN.Exist())	TAN=-(1/(TAN.Val())); //!!! div 0
	}
}

TAngle TAngle::multd2(int n2){TAngle r(*this); r.mult2(n2); return r;} 
void TAngle::mult2(int n2)
{
	if(n2==0) return;
	if(n2<0) div2(-n2);
	if(RAD.Exist()) RAD*=2;
	sSIN; //?
	sCOS; //?
	RNUM_CALC saveSIN(SIN);
	RNUM_CALC saveCOS(COS);
	if(COS.Exist()) COS=COS*COS*2-1;
	else if(SIN.Exist()) COS=1-SIN*SIN*2;
	if(saveSIN.Exist()&&saveCOS.Exist()) SIN=saveSIN*saveCOS*2;
	else SIN.Clear();
	if(TAN.Exist()) TAN=TAN*RNUM(2)/(1-TAN*TAN);

	mult2(n2-1);
}

TAngle TAngle::divd2(int n2){TAngle r(*this); r.div2(n2); return r;} 
void TAngle::div2(int n2)
{
	if(n2==0) return;
	if(n2<0) mult2(-n2);
	//~~~
	div2(n2-1);
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


TAngle::operator RNUM()
{
	return Rad();
}

void TAngle::operator = (RNUM a)
{
	SetRad(a);
}


void TAngle::operator +=(RNUM a){SetRad(Rad()+a);}

void TAngle::operator -=(RNUM a) {*this+=-a;}

void TAngle::operator *=(RNUM k){SetRad(Rad()*k);}

void TAngle::operator /= (RNUM k){SetRad(Rad()/k);}


void TAngle::operator +=(TAngle &A) ///??
{
	// 	if(!A.isDefined()) return;
	// 	if(undef) SetNull();	
	// 	if(RAD||A.RAD){*RAD=Rad()+A.Rad();}
	// 	if((SIN||COS)&&(A.SIN||A.COS))
	// 	{	
	// 		if(!SIN) Sin();
	// 		if(A>0)
	// 		{		
	// 			*SIN=Sin()*A.Cos()+Cos()*A.Sin();
	// 			*COS=Cos()*A.Cos()-Sin()*A.Sin();
	// 		}else
	// 		{
	// 			*SIN=Sin()*A.Cos()-Cos()*A.Sin();
	// 			*COS=Cos()*A.Cos()+Sin()*A.Sin();
	// 		}
	// 		if(TAN) Tan();
	// 	}else
	// 	{
	// 		if(SIN){ delete SIN; SIN=0;}
	// 		if(COS){ delete COS; COS=0;}
	// 	}
}

bool TAngle::operator <(TAngle &A)
{
	if(RAD.Exist()||A.RAD.Exist()){return (Rad()<A.Rad());}
	return (Cos()<A.Cos());	
}
bool TAngle::operator <(RNUM a){ return (Rad()<a);}

bool TAngle::operator >(TAngle &A)
{
	if(RAD.Exist()||A.RAD.Exist()){return (Rad()>A.Rad());}
	return (Sin()>A.Sin());	
}
bool TAngle::operator >(RNUM a){ return (Rad()>a);}

bool TAngle::operator ==(TAngle &A)
{
	if(RAD.Exist()&&A.RAD.Exist()) return isEqualAngle(Rad(),A.Rad());
	return isEqual(Sin(),A.Sin(),ANGLE_O)&&isEqual(Cos(),A.Cos(),ANGLE_O);
}

bool TAngle::operator ==(RNUM a)
{
// 	if(RAD.Exist()) return isEqualAngle(Rad(),a);
// 	else
// 	{
		// 		RNUM na=NormAngle_0_2PI(a);
		// 		if(isEqual(na,0,ANGLE_O)) return isEqual(Sin(),0,ANGLE_O)&&isEqual(Cos(),1,ANGLE_O);
		// 		if(isEqual(na,PI/2,ANGLE_O)) return isEqual(Sin(),1,ANGLE_O)&&isEqual(Cos(),0,ANGLE_O);
		// 		if(isEqual(na,PI,ANGLE_O)) return isEqual(Sin(),0,ANGLE_O)&&isEqual(Cos(),-1,ANGLE_O);
		// 		if(isEqual(na,3*PI/2,ANGLE_O)) return isEqual(Sin(),-1,ANGLE_O)&&isEqual(Cos(),0,ANGLE_O);
		// 		if(isEqual(na,2*PI,ANGLE_O)) return isEqual(Sin(),0,ANGLE_O)&&isEqual(Cos(),1,ANGLE_O);
		// 		if(isEqual(na,PI/4,ANGLE_O)) return isEqual(Sin(),RNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),RNUM_SQRT2/2,ANGLE_O);
		// 		if(isEqual(na,3*PI/4,ANGLE_O)) return isEqual(Sin(),RNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),-RNUM_SQRT2/2,ANGLE_O);
		// 		if(isEqual(na,5*PI/4,ANGLE_O)) return isEqual(Sin(),-RNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),-RNUM_SQRT2/2,ANGLE_O);
		// 		if(isEqual(na,7*PI/4,ANGLE_O)) return isEqual(Sin(),-RNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),RNUM_SQRT2/2,ANGLE_O);
		// 		if(isEqual(na,PI/6,ANGLE_O)) return isEqual(Sin(),0.5,ANGLE_O)&&isEqual(Cos(),RNUM_SQRT3/2,ANGLE_O);
		// 		if(isEqual(na,PI/3,ANGLE_O)) return isEqual(Sin(),RNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),0.5,ANGLE_O);				
		// 		if(isEqual(na,2*PI/3,ANGLE_O)) return isEqual(Sin(),RNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),-0.5,ANGLE_O);				
		// 		if(isEqual(na,5*PI/6,ANGLE_O)) return isEqual(Sin(),0.5,ANGLE_O)&&isEqual(Cos(),-RNUM_SQRT3/2,ANGLE_O);				
		// 		if(isEqual(na,7*PI/6,ANGLE_O)) return isEqual(Sin(),-0.5,ANGLE_O)&&isEqual(Cos(),-RNUM_SQRT3/2,ANGLE_O);				
		// 		if(isEqual(na,4*PI/3,ANGLE_O)) return isEqual(Sin(),-RNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),-0.5,ANGLE_O);				
		// 		if(isEqual(na,5*PI/3,ANGLE_O)) return isEqual(Sin(),-RNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),0.5,ANGLE_O);				
		// 		if(isEqual(na,2*PI-PI/6,ANGLE_O)) return isEqual(Sin(),-0.5,ANGLE_O)&&isEqual(Cos(),RNUM_SQRT3/2,ANGLE_O);				
//	}
	return isEqualAngle(Rad(),a);
}

