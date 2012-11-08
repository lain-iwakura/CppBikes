#ifndef BASICGEOGRAPHY_H
#define BASICGEOGRAPHY_H
#include "BasicMath.h"
#include "BasicGeometry.h"

//#include "TrigonometricAngle.h"

//class string;

namespace CppBikes
{

	

// если разбить весь шар по секундам получится 1679616000000 точек

// Константы эллипсоида земли:
const double GEO_A=6378245; // большая полуось [м]
const double GEO_ALPHA=/*1.0/2.0;//*/(1.0/298.29974); // =(EE_A-EE_B)/EE_A
const double GEO_B=(1.0-GEO_ALPHA)*GEO_A; // малая полуось [м]
const double GEO_R=(GEO_A+GEO_B)/2.0; // средний радиус [м]
const double GEO_EE=GEO_ALPHA*(2.0-GEO_ALPHA); // e^2


struct DegMinSecAngle
{
	int deg;
	char min;
	char sec;
	bool negative;

	DegMinSecAngle(int  d=0, char  m=0, char  s=0, bool neg=false);
	DegMinSecAngle(double a_rad){setFromRad(a_rad);}	
	void operator = (double a_rad){setFromRad(a_rad);}
	operator double() const { return toRad();}

	void setFromRad(double a_rad);
	void setFromDeg(double a_deg);
	double toRad() const;
	double toDeg() const;
		
	std::string toString(bool print_sign=true, bool print_zero=false) const;
	

	int sign() const;
};


struct PhiLamCoord // географические координаты (phi,lambda)
{
	PhiLamCoord(double Phi=0,double Lamda=0):phi(Phi),lam(Lamda){}
	RNUM phi;
	RNUM lam;
};

struct PhiLamHCoord // географические координаты (phi,lambda,h)
{
	PhiLamHCoord(RNUM Phi=0,RNUM Lambda=0, RNUM H=0):phi(Phi),lam(Lambda),h(H){}
	RNUM phi;
	RNUM lam;
	RNUM h;
};



// Для сферы:
Point PhiLam_to_PointS(RNUM phi, RNUM lam);  // преобразовать (фи,лямда) в (x,y,z)
PhiLamCoord Point_to_PhiLamS(const Point &p); // преобразовать (x,y,z) в (фи,лямда)

// Для эллипсоида:
Point PhiLam_to_PointE(RNUM phi, RNUM lam); // преобразовывает географические координаты (phi,lambda) в геоцентрические (x,y,z) // h=0;
Point PhiLam_to_PointE(RNUM phi, RNUM lam, RNUM h); // преобразовывает географические координаты (phi,lambda,h) в геоцентрические (x,y,z)
Point PhiLam_to_PointE(const PhiLamCoord &phi_lam);  // преобразовывает географические координаты (phi,lambda) в геоцентрические (x,y,z) // h=0;
Point PhiLam_to_PointE(const PhiLamHCoord &phi_lam_h); // преобразовывает географические координаты (phi,lambda,h) в геоцентрические (x,y,z)
PhiLamCoord Point_to_PhiLamE(const Point &p); // преобразовать (x,y,z) в (фи,лямда)


Vector EllipsePhiTan(const Point &p); // единичный касательный вектор к меридиану
Vector EllipseLamTan(const Point &p); // единичный касательный вектор к паралеле

void MovePointToEllipsoidSurface(Point &p); // переместить точку на поверхность эллипсоида 


class TrAngle;
Point PhiLam_to_PointE(TrAngle *phi, TrAngle *lam);
Point PhiLam_to_PointE_old( RNUM phi, RNUM lam );
}
#endif