#ifndef INCLUDEBIKES_SOFTTRANGLE_H
#define INCLUDEBIKES_SOFTTRANGEL_H

#include <Bikes/Math/TrAngle.h>

namespace Bikes
{


class SoftTrAngle: TrAngle
{

public:

	enum MData
	{
		MD_NULL		=	0,
		MD_SINCALC	=	1<<0,
		MD_COSCALC	=	1<<1,
		MD_TANCALC	=	1<<2,
		MD_RADCALC	=	1<<3,
		MD_SINM		=	1<<4,
		MD_COSM		=	1<<5,
		MD_TRCALC	=	1<<6,
		MD_RESERVED	=	1<<7,

		MD_NSINCALC	=	0xFF^MD_SINCALC,
		MD_NCOSCALC	=	0xFF^MD_COSCALC,
		MD_NTANCALC	=	0xFF^MD_TANCALC,
		MD_NRADCALC	=	0xFF^MD_RADCALC,
		MD_NSINM	=	0xFF^MD_SINM,			
		MD_NCOSM	=	0xFF^MD_COSM,			
		MD_NTRCALC	=	0xFF^MD_TRCALC,
		MD_NRESERVED=	0xFF^MD_RESERVED,

		MD_ALLDEF	=	MD_SINCALC|MD_COSCALC|MD_TANCALC|MD_RADCALC|MD_TRCALC
	};



	SoftTrAngle(rnum rad_val, rnum sin_val, rnum cos_val, rnum tan_val, char mdat=MD_ALLDEF);
	SoftTrAngle(rnum cos_val, bool sin_negative);
	SoftTrAngle(rnum rad_val);		
	SoftTrAngle();

	operator rnum (){return rad();}
	operator SoftTrAngle*(){return this;}
	SoftTrAngle & operator = (rnum ang_rad) {setRad(ang_rad); return *this;}

	void operator += (SoftTrAngle &ta);
	void operator -= (SoftTrAngle &ta);
	SoftTrAngle operator + (SoftTrAngle &ta);
	SoftTrAngle operator - (SoftTrAngle &ta);
	void operator += (const HardTrAngle &ta);
	void operator -= (const HardTrAngle &ta);
	SoftTrAngle operator + (const HardTrAngle &ta);
	SoftTrAngle operator - (const HardTrAngle &ta);
	SoftTrAngle operator-();

	bool operator > (SoftTrAngle &ta);  //-
	bool operator < (SoftTrAngle &ta);  //-

	void operator += (rnum ang_rad);
	void operator -= (rnum ang_rad);		

	bool operator < (rnum ang_rad);
	bool operator <= (rnum ang_rad);
	bool operator > (rnum ang_rad);
	bool operator >= (rnum ang_rad);



	void setCos(rnum cos_val, bool sin_negative=false);
	void setSin(rnum sin_val, bool cos_negative=false);
	void setTan(rnum tan_val, bool cos_negative=false);
	void setRad(rnum rad);
	void setDeg(rnum deg);


	rnum sin();
	rnum cos();
	rnum tg();
	rnum tan();
	rnum ctg();
	rnum rad();
	rnum deg();

	rnum sSin();
	rnum sCos();

	void trCalc();

private:

	char _mdat;
	rnum _sin;
	rnum _cos;
	rnum _tan;
	rnum _rad;
	SoftTrAngle *_dirtyThis;
};

}
#endif