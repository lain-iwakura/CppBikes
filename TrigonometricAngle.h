#ifndef CPPBIKES_TRIGONOMETRICANGLE_H
#define CPPBIKES_TRIGONOMETRICANGLE_H

#include <CppBikes/BasicMath.h>

namespace CppBikes
{

	class TrAngle
	{
	public:

		enum MData
		{		
			MD_UNDEF	=	0,
			MD_DEF		=	1<<0,
			MD_SINCALC	=	1<<1,
			MD_COSCALC	=	1<<2,
			MD_TANCALC	=	1<<3,
			MD_RADCALC	=	1<<4,
			MD_SINM		=	1<<5,
			MD_COSM		=	1<<6
		};


		TrAngle(RNUM cos_val=1, bool sin_negative=false);

		operator RNUM (){return Rad();}
		TrAngle & operator = (RNUM ang_rad) {setRad(ang_rad); return *this;}


		void setCos(RNUM cos_val, bool sin_negative=false);
		void setSin(RNUM sin_val, bool cos_negative=false);
		void setTan(RNUM tan_val, bool cos_negative=false);
		void setRad(RNUM rad);
		void setDeg(RNUM deg);

	
		RNUM Sin();
		RNUM Cos();
		RNUM Tg();
		RNUM Ctg();
		RNUM Rad();
		RNUM Deg();

		RNUM sigSin();
		RNUM sigCos();

	//private:

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

// 
// 	inline RNUM sin(RNUM ang){return ::sin(ang);}
// 	inline RNUM cos(RNUM ang){return ::cos(ang);}
// 	inline RNUM tan(RNUM ang){return ::tan(ang);}
// 	inline RNUM ctg(RNUM ang){return 1.0/not0(::tan(ang));}
// 	inline RNUM tg(RNUM ang){return ::tan(ang);}
// 	
}


#endif