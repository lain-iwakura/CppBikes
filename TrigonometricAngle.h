#ifndef TRIGONAMETRICANGLE_H
#define TRIGONAMETRICANGLE_H
#include "BasicMath.h"
#include "PhantomObject.h"

typedef PhantomVal<TRNUM> TRNUM_CALC;



//template<bool POSITIVE_PI_OFFSET=false, int PIx2_OFFSET=0>
TRNUM normAngle(TRNUM a, bool POSITIVE_PI_OFFSET=false, int PIx2_OFFSET=0);


class TAngle
{
public:

	void SetCos(TRNUM cos_a, TRNUM sin_sign=1);
	void SetSin(TRNUM sin_a, TRNUM cos_sign=1);
	void SetTan(TRNUM tan_a, TRNUM cos_sign=1);
	void SetCtan(TRNUM ctan_a, TRNUM cos_sign=1);
	void SetPositivePiOffset(bool positive_pi_offset);

	void SetRad(TRNUM rad_a);
	void SetDeg(TRNUM grad_a);
	void SetUndefAll();
	void SetNull();
	bool isDefined();
	
	TAngle(TRNUM cos_a, TRNUM ssin=1,bool positive_pi_offset=false);
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
	
	
	operator TRNUM();	
	void operator = (TRNUM a);
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


protected:

	char sSIN;
	char sCOS;
	TRNUM_CALC SIN;
	TRNUM_CALC COS;
	TRNUM_CALC TAN;
	TRNUM_CALC RAD;
	
	bool pi_offset;
};

TRNUM cos(TAngle &A);
TRNUM sin(TAngle &A);
TRNUM tan(TAngle &A);
TRNUM ctan(TAngle &A);
TRNUM rad(TAngle &A);
TRNUM deg(TAngle &A);



/*
template<bool POSITIVE_PI_OFFSET=false, int PIx2_OFFSET=0>
class TAngleR: public TAngle
{
public:

	TRNUM Rad()
	{
		TRNUM r=TAngle::Rad();
		return  r + ( PIx2_OFFSET + ((POSITIVE_PI_OFFSET&&(r<0))?(1):(0)) )*PImult2;
	}

	TRNUM Deg(){return RAD_to_DEG(Rad());}






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




#endif
