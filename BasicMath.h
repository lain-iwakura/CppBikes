//#pragma once
#ifndef BASICMATH_H
#define BASICMATH_H
#include <math.h>
//#include "CalcVal.h"
#include "PhantomObject.h"

 
#define CONST_PI  3.1415926535897932384626433832795  // (double) 3.1415926535897931
#define CONST_E   2.7182818284590452353602874713527  //

//#define CONST_O   0.0000000001
#define INTERCHANGET(T,X,Y) T _BUFX=X; X=Y; Y=_BUFX;
#define INTERCHANGE(X,Y) VoidInterchange(&X,&Y,sizeof(X))
#define ISEQUAL(X,Y) VoidIsEqual(&X,&Y,sizeof(X))
#define COPY(X,Y) VoidCopy(&X,&Y,sizeof(X))
void VoidInterchange(void* a, void* b, unsigned int size);
bool VoidIsEqual(void *a, void *b, unsigned int n);
void VoidCopy(void *a, void *b, unsigned int n);

typedef double TRNUM;

typedef CalcVal<TRNUM> TRNUM_CALC;
const TRNUM PI=CONST_PI;
const TRNUM E=CONST_E;
const TRNUM TRNUM_O=1E-35;
const TRNUM TRNUM_INFINITY=1/TRNUM_O; 
const TRNUM EQUAL_O=1E-12;
const TRNUM ANGLE_O=1E-10;
const TRNUM TRNUM_0=0;
const TRNUM RAD_IN_DEG=TRNUM(180)/PI;
const TRNUM DEG_IN_RAD=PI/TRNUM(180);

const TRNUM TRNUM_SQRT2=sqrt(TRNUM(2));
const TRNUM TRNUM_SQRT3=sqrt(TRNUM(3));
const TRNUM PIdiv2=PI/2;
const TRNUM PIdiv3=PI/3;
const TRNUM PIdiv4=PI/4;
const TRNUM PIdiv6=PI/6;
const TRNUM PImult2=PI*2;


const int APROX_N=100000;
const TRNUM APROX_DANGEL=PIdiv2/TRNUM(APROX_N);
TRNUM *const SINAPROX=new TRNUM[APROX_N];
void _DEF_SINAPROX();
TRNUM sinaprox(TRNUM a);

TRNUM NormAngle(TRNUM a);
TRNUM NormAngle_0_2PI(TRNUM a);
short signum(TRNUM n);
TRNUM arccos(TRNUM n);
TRNUM arcsin(TRNUM n);
TRNUM DEG_to_RAD(TRNUM deg);
TRNUM RAD_to_DEG(TRNUM rad);
bool isEqual(TRNUM n1, TRNUM n2, TRNUM O=EQUAL_O);
bool isEqualAngle(TRNUM a1, TRNUM a2);
TRNUM not0(TRNUM n, TRNUM o=TRNUM_O);
void not0set(TRNUM &n, TRNUM o=TRNUM_O);

class TAngle;

TRNUM cos(TAngle &A);
TRNUM sin(TAngle &A);
TRNUM tan(TAngle &A);
TRNUM ctan(TAngle &A);
TRNUM rad(TAngle &A);
TRNUM deg(TAngle &A);




class TAngle
{
public:
	void SetCos(TRNUM cos_a, TRNUM ssin=1);
	void SetSin(TRNUM sin_a, TRNUM scos=1);
	void SetTan(TRNUM tan_a, TRNUM ssin=1 );
//	void SetSinCos(TRNUM sin_a, TRNUM cos_a);
	void SetRad(TRNUM rad_a);
	void SetDeg(TRNUM grad_a);
	void SetUndefAll();
	void SetNull();
	bool isDefined();
	TAngle(TRNUM cos_a, TRNUM ssin=1);
	TAngle(const TAngle &A);
	TAngle();
	~TAngle();	
	TRNUM Cos();
	TRNUM Sin();
	TRNUM Tan();
	TRNUM cTan();	
	TRNUM Rad();
	TRNUM Deg();

	TRNUM sSin();
	TRNUM sCos();
	
	int Grad();
	int Min();
	int Sec();

	void setOpposite();
	void plusPI(int nPI=1);
//	void plusedPI(int nPI=1);
	void plusPIdiv2(int nPIdiv2=1);
	TAngle plusedPIdiv2(int nPidiv2=1);
	void mult2(int n2=1);
	TAngle multd2(int n2=1);
	void div2(int n2=1);
	TAngle divd2(int n2=1);
	void operator +=(TRNUM a);
	void operator +=(TAngle &A);
	void operator -=(TRNUM a);
	void operator -=(TAngle &A);
	void operator *=(TRNUM k);
	void operator /=(TRNUM k);
	bool operator ==(TRNUM a);
	bool operator ==(TAngle &A);
	bool operator >(TAngle &A);
	bool operator >(TRNUM a);
	bool operator <(TAngle &A);
	bool operator <(TRNUM a);
	bool operator >=(TAngle &A);
	bool operator >=(TRNUM a);
	bool operator <=(TAngle &A);
	bool operator <=(TRNUM a);
	TAngle operator +(TAngle &A);
	TAngle operator -(TAngle &A);
	TAngle operator *(TRNUM k);
	TAngle operator /(TRNUM k);
	

//protected:
//	bool def;
	CalcVal<short> sSIN;
	CalcVal<short> sCOS;
	TRNUM_CALC SIN;
	TRNUM_CALC COS;
	TRNUM_CALC TAN;
	TRNUM_CALC RAD;
};

#endif