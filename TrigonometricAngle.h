#ifndef CPPBIKES_TRIGONOMETRICANGLE_H
#define CPPBIKES_TRIGONOMETRICANGLE_H

#include <Bikes/BasicMath.h>

namespace Bikes
{


	struct TrAngleConst
	{
		TrAngleConst();
		TrAngleConst(rnum _rad_val,rnum _sin_val, rnum _cos_val, rnum _tan_val);
		TrAngleConst(rnum ang_rad);	

		TrAngleConst& operator =(rnum ang_rad);

		operator rnum () const;
		
		rnum rad_val;
		rnum sin_val;
		rnum cos_val;
		rnum tan_val;
	};


	class TrAngle
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
		


		TrAngle(rnum rad_val, rnum sin_val, rnum cos_val, rnum tan_val, char mdat=MD_ALLDEF);
		TrAngle(rnum cos_val, bool sin_negative);
		TrAngle(rnum rad_val);		
		TrAngle();

		operator rnum (){return rad();}
		operator TrAngle*(){return this;}
		TrAngle & operator = (rnum ang_rad) {setRad(ang_rad); return *this;}

		void operator += (TrAngle &ta);
		void operator -= (TrAngle &ta);
		TrAngle operator + (TrAngle &ta);
		TrAngle operator - (TrAngle &ta);
		void operator += (const TrAngleConst &ta);
		void operator -= (const TrAngleConst &ta);
		TrAngle operator + (const TrAngleConst &ta);
		TrAngle operator - (const TrAngleConst &ta);
		TrAngle operator-();

		bool operator > (TrAngle &ta);  //-
		bool operator < (TrAngle &ta);  //-

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
	};



	//							rad		sin		cos		tan	
	const TrAngleConst g_tr0(		0,		0,		1,		0	);
	const TrAngleConst g_trPI(		PI,		0,		-1,		0	);
	const TrAngleConst g_tr2PI(		PImult2,0,		-1,		0	);
	const TrAngleConst g_trPIdiv2(	PIdiv2,	1,		0,		RNUM_INFINITY);
	const TrAngleConst g_trPIdiv3(	PIdiv3,	SQRT3/2.0,0.5,	SQRT3);
	const TrAngleConst g_trPIdiv4(	PIdiv4,	1./SQRT2,1./SQRT2,1.);
	const TrAngleConst g_trPIdiv6(	PIdiv6,	0.5,SQRT3/2,	1.0/SQRT3);

	const TrAngleConst g_tr1DEG(DEG_IN_RAD,sin(DEG_IN_RAD),cos(DEG_IN_RAD),tan(DEG_IN_RAD));
	const TrAngleConst g_tr1MIN(DEG_IN_RAD/60.0,sin(DEG_IN_RAD/60.0),cos(DEG_IN_RAD/60.0),tan(DEG_IN_RAD/60.0));
	const TrAngleConst g_tr1SEC(DEG_IN_RAD/3600.0,sin(DEG_IN_RAD/3600.0),cos(DEG_IN_RAD/3600.0),tan(DEG_IN_RAD/3600.0));


	inline rnum sin(TrAngle &ta){return ta.sin();}
	inline rnum cos(TrAngle &ta){return ta.cos();}
	inline rnum tan(TrAngle &ta){return ta.tg();}
	inline rnum rad(TrAngle &ta){return ta.rad();}
	inline rnum deg(TrAngle &ta){return ta.deg();}

	inline rnum sin(TrAngleConst &tac){return tac.sin_val;}
	inline rnum cos(TrAngleConst &tac){return tac.cos_val;}
	inline rnum tan(TrAngleConst &tac){return tac.tan_val;}
	inline rnum rad(TrAngleConst &tac){return tac.rad_val;}
	inline rnum deg(TrAngleConst &tac){return RAD_to_DEG(tac.rad_val);}

	using ::sin;
	using ::cos;
	using ::tan;

}


#endif