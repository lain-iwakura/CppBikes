#ifndef INCLUDEBIKES_TRANGLE_H
#define INCLUDEBIKES_TRANGLE_H

#include <Bikes/Math/Constants.h>


namespace Bikes
{

	class SoftTrAngle;


	class TrAngle
	{
	public:

		virtual ~TrAngle();

		virtual sinnum sin() const = 0;

		virtual cosnum cos() const = 0;

		virtual tannum tan() const = 0;

		virtual radian rad() const = 0;

		virtual degree deg() const = 0;

		virtual void setRad(radian ang) = 0;

		virtual void setSin(sinnum sin_ang, ValSign cosSign = positiveSign) = 0;

		virtual void setCos(sinnum cos_ang, ValSign sinSign = positiveSign) = 0;

		virtual void setTan(tannum tan_ang, ValSign cosSign = positiveSign) = 0;
			
		virtual SoftTrAngle getSum(const TrAngle& ang) const = 0;

		virtual void setSum(const TrAngle& ang) = 0;

		virtual SoftTrAngle getDifference(const TrAngle& ang) const = 0;
		
		virtual void setDifference(const TrAngle& ang) = 0;

		virtual SoftTrAngle getProduct(rnum m) const = 0;

		virtual void setProduct(rnum m) = 0;

		virtual SoftTrAngle getNegative() const = 0;

		virtual void setNegative() = 0;

		virtual bool isEqual(const TrAngle& ang) const; //?
		
	};



	class HardTrAngle
	{
	public:
		HardTrAngle();
		HardTrAngle(rnum _rad_val,rnum _sin_val, rnum _cos_val, rnum _tan_val);
		HardTrAngle(rnum ang_rad);	

        void set(rnum ang_rad);
		HardTrAngle& operator =(rnum ang_rad);

		operator rnum () const;
		
	private:
		rnum _rad;
		rnum _sin;
		rnum _cos;
		rnum _tan;
	};


	class SoftTrAngle
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
		HardTrAngle *_dirtyThis;
	};


	/*
	//							rad		sin		cos		tan	
	const HardTrAngle g_tr0(		0,		0,		1,		0	);
	const HardTrAngle g_trPI(		PI,		0,		-1,		0	);
	const HardTrAngle g_tr2PI(		PIm2,0,		-1,		0	);
	const HardTrAngle g_trPIdiv2(	PId2,	1,		0,		RNUM_INFINITY);
	const HardTrAngle g_trPIdiv3(	PId3,	SQRT3/2.0,0.5,	SQRT3);
	const HardTrAngle g_trPIdiv4(	PId4,	1./SQRT2,1./SQRT2,1.);
	const HardTrAngle g_trPIdiv6(	PId6,	0.5,SQRT3/2,	1.0/SQRT3);

	const HardTrAngle g_tr1DEG(RAD_PER_DEG,sin(RAD_PER_DEG),cos(RAD_PER_DEG),tan(RAD_PER_DEG));
	const HardTrAngle g_tr1MIN(RAD_PER_DEG/60.0,sin(RAD_PER_DEG/60.0),cos(RAD_PER_DEG/60.0),tan(RAD_PER_DEG/60.0));
	const HardTrAngle g_tr1SEC(RAD_PER_DEG/3600.0,sin(RAD_PER_DEG/3600.0),cos(RAD_PER_DEG/3600.0),tan(RAD_PER_DEG/3600.0));



	
	using ::sin;
	using ::cos;
	using ::tan;
	*/

	inline sinnum sin(const TrAngle &ta){return ta.sin();}
	inline cosnum cos(const TrAngle &ta){return ta.cos();}
	inline tannum tan(const TrAngle &ta){return ta.tan();}
	inline radian rad(const TrAngle &ta){return ta.rad();}
	inline degree deg(const TrAngle &ta){return ta.deg();}

}


#endif