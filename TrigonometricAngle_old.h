#ifndef TRIGONAMETRICANGLE_H
#define TRIGONAMETRICANGLE_H
#include "BasicMath.h"
#include "PhantomObject.h"




namespace CppBikes
{

typedef PhantomVal<RNUM> RNUM_CALC;



//template<bool POSITIVE_PI_OFFSET=false, int PIx2_OFFSET=0>
RNUM normAngle(RNUM a, bool POSITIVE_PI_OFFSET=false, int PIx2_OFFSET=0);


class TAngle
{
public:

	void SetCos(RNUM cos_a, RNUM sin_sign=1);
	void SetSin(RNUM sin_a, RNUM cos_sign=1);
	void SetTan(RNUM tan_a, RNUM cos_sign=1);
	void SetCtan(RNUM ctan_a, RNUM cos_sign=1);
	void SetPositivePiOffset(bool positive_pi_offset);

	void SetRad(RNUM rad_a);
	void SetDeg(RNUM grad_a);
	void SetUndefAll();
	void SetNull();
	bool isDefined();
	
	TAngle(RNUM cos_a, RNUM ssin=1,bool positive_pi_offset=false);
	TAngle(const TAngle &A);
	TAngle();
	~TAngle();	
	RNUM Cos();
	RNUM Sin();
	RNUM Tan();
	RNUM cTan();	
	RNUM Rad();
	RNUM Deg();

	RNUM sSin();
	RNUM sCos();

//	int Grad();
//	int Min();
//	int Sec();

	void setOpposite();
	void plusPI(int nPI=1);
	//	void plusedPI(int nPI=1);
	void plusPIdiv2(int nPIdiv2=1);
	TAngle plusedPIdiv2(int nPidiv2=1);
	void mult2(int n2=1);
	TAngle multd2(int n2=1);
	void div2(int n2=1);
	TAngle divd2(int n2=1);
	
	
	operator RNUM();	
	void operator = (RNUM a);
	void operator +=(RNUM a);
	void operator +=(TAngle &A);
	void operator -=(RNUM a);
	void operator -=(TAngle &A);
	void operator *=(RNUM k);
	void operator /=(RNUM k);
	bool operator ==(RNUM a);
	bool operator ==(TAngle &A);
	bool operator >(TAngle &A);
	bool operator >(RNUM a);
	bool operator <(TAngle &A);
	bool operator <(RNUM a);
	bool operator >=(TAngle &A);
	bool operator >=(RNUM a);
	bool operator <=(TAngle &A);
	bool operator <=(RNUM a);
	TAngle operator +(TAngle &A);
	TAngle operator -(TAngle &A);
	TAngle operator *(RNUM k);
	TAngle operator /(RNUM k);


protected:

	char sSIN;
	char sCOS;
	RNUM_CALC SIN;
	RNUM_CALC COS;
	RNUM_CALC TAN;
	RNUM_CALC RAD;
	
	bool pi_offset;
};

RNUM cos(TAngle &A);
RNUM sin(TAngle &A);
RNUM tan(TAngle &A);
RNUM ctan(TAngle &A);
RNUM rad(TAngle &A);
RNUM deg(TAngle &A);



/*
template<bool POSITIVE_PI_OFFSET=false, int PIx2_OFFSET=0>
class TAngleR: public TAngle
{
public:

	RNUM Rad()
	{
		RNUM r=TAngle::Rad();
		return  r + ( PIx2_OFFSET + ((POSITIVE_PI_OFFSET&&(r<0))?(1):(0)) )*PImult2;
	}

	RNUM Deg(){return RAD_to_DEG(Rad());}






	//template<bool PIx2O_small> bool operator < (const TAngleR<POSITIVE_PI_OFFSET,PIx2O> &tar)


	template<int PIx2O>
	bool isLessThan(const TAngleR<POSITIVE_PI_OFFSET,PIx2O> &tar)
	{

	}

	template<>
	bool operator < (const TAngleR<POSITIVE_PI_OFFSET,PIx2_OFFSET> &tar)
	{
	}


// 	template<int PIx2O>
// 	bool operator < (const TAngleR<POSITIVE_PI_OFFSET,PIx2O> &tar)
// 	{
// 
// 	}
// 
// 	template<>
// 	bool operator < (const TAngleR<POSITIVE_PI_OFFSET,PIx2_OFFSET> &tar)
// 	{
// 	}
};

*/



}
#endif
