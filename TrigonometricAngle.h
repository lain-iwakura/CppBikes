#ifndef CPPBIKES_TRIGONOMETRICANGLE_H
#define CPPBIKES_TRIGONOMETRICANGLE_H

#include <CppBikes/BasicMath.h>

namespace CppBikes
{


// 	class TrAngleConst
// 	{
// 
// 	};


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


		TrAngle(RNUM rad_val, RNUM sin_val, RNUM cos_val, RNUM tan_val, char mdat=MD_ALLDEF);
		TrAngle(RNUM cos_val, bool sin_negative);
		TrAngle(RNUM rad_val);		
		TrAngle();

		operator RNUM (){return Rad();}
		operator TrAngle*(){return this;}
		TrAngle & operator = (RNUM ang_rad) {setRad(ang_rad); return *this;}

		void operator += (TrAngle &ta);
		void operator -= (TrAngle &ta);
		TrAngle operator + (TrAngle &ta);
		TrAngle operator - (TrAngle &ta);
		TrAngle operator -();

		bool operator > (TrAngle &ta);  //-
		bool operator < (TrAngle &ta);  //-


		void operator += (RNUM ang_rad);
		void operator -= (RNUM ang_rad);
		

		bool operator < (RNUM ang_rad);
		bool operator <= (RNUM ang_rad);
		bool operator > (RNUM ang_rad);
		bool operator >= (RNUM ang_rad);


		void setCos(RNUM cos_val, bool sin_negative=false);
		void setSin(RNUM sin_val, bool cos_negative=false);
		void setTan(RNUM tan_val, bool cos_negative=false);
		void setRad(RNUM rad);
		void setDeg(RNUM deg);

	
		RNUM Sin();
		RNUM Cos();
		RNUM Tg();
		RNUM Tan();
		RNUM Ctg();
		RNUM Rad();
		RNUM Deg();

		RNUM sSin();
		RNUM sCos();

		void trCalc();
	private:

		char _mdat;
		RNUM _sin;
		RNUM _cos;
		RNUM _tan;
		RNUM _rad;
	};


	inline RNUM Sin(TrAngle &ang){return ang.Sin();}
	inline RNUM Cos(TrAngle &ang){return ang.Cos();}
	inline RNUM Tan(TrAngle &ang){return ang.Tg();}
	inline RNUM Tg(TrAngle &ang){return ang.Tg();}
	inline RNUM Ctg(TrAngle &ang){return ang.Ctg();}
	inline RNUM Rad(TrAngle &ang){return ang.Rad();}
	inline RNUM Deg(TrAngle &ang){return ang.Deg();}


	//							rad		sin		cos		tan	
	static TrAngle g_tr0(		0,		0,		1,		0	);
	static TrAngle g_trPI(		PI,		0,		-1,		0	);
	static TrAngle g_tr2PI(		PImult2,0,		-1,		0	);
	static TrAngle g_trPIdiv2(	PIdiv2,	1,		0,		RNUM_INFINITY);
	static TrAngle g_trPIdiv3(	PIdiv3,	SQRT3/2.0,0.5,	SQRT3);
	static TrAngle g_trPIdiv4(	PIdiv4,	1./SQRT2,1./SQRT2,1.);
	static TrAngle g_trPIdiv6(	PIdiv6,	0.5,SQRT3/2,	1.0/SQRT3);

	static TrAngle g_tr1DEG(DEG_IN_RAD,sin(DEG_IN_RAD),cos(DEG_IN_RAD),tan(DEG_IN_RAD));
	static TrAngle g_tr1MIN(DEG_IN_RAD/60.0,sin(DEG_IN_RAD/60.0),cos(DEG_IN_RAD/60.0),tan(DEG_IN_RAD/60.0));
	static TrAngle g_tr1SEC(DEG_IN_RAD/3600.0,sin(DEG_IN_RAD/3600.0),cos(DEG_IN_RAD/3600.0),tan(DEG_IN_RAD/3600.0));

	

// 
// 	inline RNUM sin(RNUM ang){return ::sin(ang);}
// 	inline RNUM cos(RNUM ang){return ::cos(ang);}
// 	inline RNUM tan(RNUM ang){return ::tan(ang);}
// 	inline RNUM ctg(RNUM ang){return 1.0/not0(::tan(ang));}
// 	inline RNUM tg(RNUM ang){return ::tan(ang);}
// 	
}


#endif