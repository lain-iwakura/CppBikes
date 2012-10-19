#include "BasicMath.h"



void VoidInterchange(void* a, void* b, unsigned int n) //c=a; a=b; b=c;
{	
	char buf;
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++)
	{
		buf=cha[i];
		cha[i]=chb[i];
		chb[i]=buf;
	}
}

void VoidCopy(void *a, void *b, unsigned int n) // a=b;
{	
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++) cha[i]=chb[i];
}

bool VoidIsEqual(void *a, void *b, unsigned int n) // a==b
{
	char *cha=(char*)a;
	char *chb=(char*)b;
	for(int i=0; i<n; i++) if(cha[i]!=chb[i]) return false;
	return true;
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
	if(abs(a)<PI*2) return a;
	TRNUM ra=abs(a);
	while(ra>=PI*2){ra-=PI*2;}
	if(a<0) ra*=-1;
	return ra;
}

TRNUM NormAngle_0_2PI(TRNUM a)
{
	if(abs(a)>2*PI)	a-=((long)(a/(2*PI)))*2*PI;
	if(a<0) a+=2*PI;
	return a;
}

short signum(TRNUM n)
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

TRNUM DEG_to_RAD(TRNUM deg){return (deg/(TRNUM)180)*PI;}
TRNUM RAD_to_DEG(TRNUM rad){return (rad/PI)*(TRNUM)180;}
bool isEqual(TRNUM n1, TRNUM n2, TRNUM O){return (abs(n1-n2)<O);}
bool isEquelAngle(TRNUM a1, TRNUM a2)
{
	a1=NormAngle_0_2PI(a1);
	a2=NormAngle_0_2PI(a2);
	return isEqual(a1,a2,ANGLE_O);
}

///////////////////////////////////////////////////////////
/////////////////// ANGLE /////////////////////////////////
///////////////////////////////////////////////////////////
TRNUM cos(TAngle &A) {return A.Cos();}
TRNUM sin(TAngle &A){return A.Sin();}
TRNUM tan(TAngle &A){return A.Tan();}
TRNUM ctan(TAngle &A){return A.cTan();}
TRNUM rad(TAngle &A){return A.Rad();}
TRNUM deg(TAngle &A){return A.Deg();}




TAngle::TAngle(){/*def=false;*/}//SIN=0;COS=0;TAN=0;RAD=0;}
TAngle::TAngle(TRNUM cos_a, TRNUM ssin){/*COS=cos_a; sSIN=signum(ssin);*/ SetCos(cos_a,ssin); }
TAngle::~TAngle(){SetUndefAll();}

TAngle::TAngle(const TAngle &a)
{
	sSIN=a.sSIN;
	sCOS=a.sCOS;
	COS=a.COS;
	SIN=a.SIN;
	TAN=a.TAN;
	RAD=a.RAD;
}

void TAngle::SetUndefAll()
{
	sSIN.Clear();
	COS.Clear();
	SIN.Clear();
	TAN.Clear();
	RAD.Clear();
}

void TAngle::SetNull()
{
	SetUndefAll();
	COS=TRNUM(1);	
	SIN=TRNUM(0);
	TAN=TRNUM(0);
	RAD=TRNUM(0);
}

void TAngle::SetCos(TRNUM cos_a, TRNUM ssin)
{
	SetUndefAll();
	if(cos_a>1) cos_a=1;
	else if(cos_a<-1) cos_a=-1;	
	COS=cos_a;
	sSIN=signum(ssin);
}
void TAngle::SetSin(TRNUM sin_a, TRNUM scos)
{
	SetUndefAll();
	if(sin_a>1) sin_a=1;
	else if(sin_a<-1) sin_a=-1;	
	SIN=sin_a;	
	sCOS=signum(scos);
}



void TAngle::SetTan(TRNUM tan_a, TRNUM ssin)
{
	SetUndefAll();
	TAN=tan_a;
	sSIN=signum(ssin);
	sCOS=sSIN*signum(tan_a);
}

void TAngle::SetRad(TRNUM rad_a)
{
	SetUndefAll();
	RAD=rad_a;	
	TRNUM na=NormAngle_0_2PI(rad_a);
	sSIN=signum(PI-na);
	if((na>(PIdiv2))&&(na<(3*PIdiv2))) sCOS=-1;	
	else sCOS=1;							

}

void TAngle::SetDeg(TRNUM deg_a)
{	
	SetRad(DEG_to_RAD(deg_a));
}

bool TAngle::isDefined()
{
	if(SIN.Exist()) return true;
	if(COS.Exist()) return true;	
	if(RAD.Exist()) return true;
	if(TAN.Exist()) return true;
	return false;
}


TRNUM TAngle::sSin()
{
	if(SIN.Exist()) return signum(SIN);  //?
	return sSIN.Val(1);	
}

TRNUM TAngle::sCos()
{
	if(COS.Exist()) return signum(COS); //?
	return sCOS.Val(1);
}

TRNUM TAngle::Cos()
{
	if(COS.Exist()) return COS;
	
	if(SIN.Exist()) COS=sqrt(1-Sin()*Sin())*sCos();
	else if(TAN.Exist()) COS=sqrt(1/(Tan()*Tan()+1))*sCos();
	else if(RAD.Exist()) COS=cos(Rad());
	else return 1;
	
		
	return COS;
}

TRNUM TAngle::Sin()
{
	if(SIN.Exist()) return SIN;
	
	if(COS.Exist()) SIN=sqrt(1-Cos()*Cos())*sSin();
	else if(TAN.Exist()) SIN=sqrt((Tan()*Tan())/(1+(Tan()*Tan())))*sSin();
	else if(RAD.Exist()) SIN=sin(Rad());
	else return 0;
	
	return SIN;
}

TRNUM TAngle::Tan() 
{
	if(TAN.Exist()) return TAN;
	
		if(COS.Exist()||SIN.Exist()) 
		{
			if(isEqual(Cos(),0,TRNUM_O)) TAN=TRNUM_INFINITY; 
			else TAN=Sin()/Cos();		
		}
		else if(RAD.Exist()) TAN=tan(Rad());
		else return 0;
	return TAN;
}

TRNUM TAngle::cTan()
{
	if(isEqual(Tan(),0,TRNUM_O)) return TRNUM_INFINITY;
	return 1/Tan();
} 

TRNUM TAngle::Rad() // +(?)
{
	if(RAD.Exist()) return RAD;
			
			 if(SIN.Exist()) {RAD=arcsin(Sin()); if(sCos()<0) RAD=PI-RAD.Val(); else if(RAD<TRNUM_0) RAD+=PImult2;}
		else if(COS.Exist()) {RAD=arccos(Cos()); if(sSin()<0) RAD=PImult2-RAD.Val();}
		else if(TAN.Exist()) {RAD=atan(Tan()); if(RAD>TRNUM_0){if(sSin()<0)RAD+=PI;}else{if(sSin()>0)RAD+=PI; else RAD+=2*PI;}}
		else return 0;
//	RAD=NormAngle_0_2PI(RAD);
	return RAD;
}

TRNUM TAngle::Deg()
{
	return RAD_to_DEG(Rad());	
}

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
	return (int)((Deg()-Grad()-(TRNUM)Min()/60)*3600);
}


////////////////////////////////////////////////////// -
void TAngle::setOpposite() //?
{
	if(SIN.Exist()) SIN=-Sin();
	if(TAN.Exist()) TAN=-Tan();
	if(RAD.Exist()) RAD=-Rad();
	sSIN=-sSin();	
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
		
		sSIN.Clear();//?
		sCOS.Clear();//?
		//TRNUM *sCOS=0;
		TRNUM_CALC saveCOS(COS);
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
	sSIN.Clear(); //?
	sCOS.Clear(); //?
	TRNUM_CALC saveSIN(SIN);
	TRNUM_CALC saveCOS(COS);
	if(COS.Exist()) COS=COS*COS*2-1;
	else if(SIN.Exist()) COS=1-SIN*SIN*2;
	if(saveSIN.Exist()&&saveCOS.Exist()) SIN=saveSIN*saveCOS*2;
	else SIN.Clear();
	if(TAN.Exist()) TAN=TAN*TRNUM(2)/(1-TAN*TAN);

	mult2(n2-1);
}

TAngle TAngle::divd2(int n2){TAngle r(*this); r.div2(n2); return r;} 
void TAngle::div2(int n2)
{
	if(n2==0) return;
	if(n2<0) mult2(n2);
	//~~~
	div2(n2-1);
}

void TAngle::operator +=(TRNUM a){SetRad(Rad()+a);}

void TAngle::operator -=(TRNUM a) {*this+=-a;}

void TAngle::operator *=(TRNUM k){SetRad(Rad()*k);}

void TAngle::operator /= (TRNUM k){SetRad(Rad()/k);}



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
	return (Sin()<A.Sin());	
}
bool TAngle::operator <(TRNUM a){ return (Rad()<a);}

bool TAngle::operator >(TAngle &A)
{
	if(RAD.Exist()||A.RAD.Exist()){return (Rad()>A.Rad());}
	return (Sin()>A.Sin());	
}
bool TAngle::operator >(TRNUM a){ return (Rad()>a);}

bool TAngle::operator ==(TAngle &A)
{
	if(RAD.Exist()&&A.RAD.Exist()) return isEquelAngle(Rad(),A.Rad());
	return isEqual(Sin(),A.Sin(),ANGLE_O)&&isEqual(Cos(),A.Cos(),ANGLE_O);
}

bool TAngle::operator ==(TRNUM a)
{
	if(RAD.Exist()) return isEquelAngle(Rad(),a);
	else
	{
// 		TRNUM na=NormAngle_0_2PI(a);
// 		if(isEqual(na,0,ANGLE_O)) return isEqual(Sin(),0,ANGLE_O)&&isEqual(Cos(),1,ANGLE_O);
// 		if(isEqual(na,PI/2,ANGLE_O)) return isEqual(Sin(),1,ANGLE_O)&&isEqual(Cos(),0,ANGLE_O);
// 		if(isEqual(na,PI,ANGLE_O)) return isEqual(Sin(),0,ANGLE_O)&&isEqual(Cos(),-1,ANGLE_O);
// 		if(isEqual(na,3*PI/2,ANGLE_O)) return isEqual(Sin(),-1,ANGLE_O)&&isEqual(Cos(),0,ANGLE_O);
// 		if(isEqual(na,2*PI,ANGLE_O)) return isEqual(Sin(),0,ANGLE_O)&&isEqual(Cos(),1,ANGLE_O);
// 		if(isEqual(na,PI/4,ANGLE_O)) return isEqual(Sin(),TRNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),TRNUM_SQRT2/2,ANGLE_O);
// 		if(isEqual(na,3*PI/4,ANGLE_O)) return isEqual(Sin(),TRNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),-TRNUM_SQRT2/2,ANGLE_O);
// 		if(isEqual(na,5*PI/4,ANGLE_O)) return isEqual(Sin(),-TRNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),-TRNUM_SQRT2/2,ANGLE_O);
// 		if(isEqual(na,7*PI/4,ANGLE_O)) return isEqual(Sin(),-TRNUM_SQRT2/2,ANGLE_O)&&isEqual(Cos(),TRNUM_SQRT2/2,ANGLE_O);
// 		if(isEqual(na,PI/6,ANGLE_O)) return isEqual(Sin(),0.5,ANGLE_O)&&isEqual(Cos(),TRNUM_SQRT3/2,ANGLE_O);
// 		if(isEqual(na,PI/3,ANGLE_O)) return isEqual(Sin(),TRNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),0.5,ANGLE_O);				
// 		if(isEqual(na,2*PI/3,ANGLE_O)) return isEqual(Sin(),TRNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),-0.5,ANGLE_O);				
// 		if(isEqual(na,5*PI/6,ANGLE_O)) return isEqual(Sin(),0.5,ANGLE_O)&&isEqual(Cos(),-TRNUM_SQRT3/2,ANGLE_O);				
// 		if(isEqual(na,7*PI/6,ANGLE_O)) return isEqual(Sin(),-0.5,ANGLE_O)&&isEqual(Cos(),-TRNUM_SQRT3/2,ANGLE_O);				
// 		if(isEqual(na,4*PI/3,ANGLE_O)) return isEqual(Sin(),-TRNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),-0.5,ANGLE_O);				
// 		if(isEqual(na,5*PI/3,ANGLE_O)) return isEqual(Sin(),-TRNUM_SQRT3/2,ANGLE_O)&&isEqual(Cos(),0.5,ANGLE_O);				
// 		if(isEqual(na,2*PI-PI/6,ANGLE_O)) return isEqual(Sin(),-0.5,ANGLE_O)&&isEqual(Cos(),TRNUM_SQRT3/2,ANGLE_O);				
	}
	return isEquelAngle(Rad(),a);
}

