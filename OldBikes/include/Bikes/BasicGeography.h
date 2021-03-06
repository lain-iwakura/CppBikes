#ifndef PREBIKES_BASICGEOGRAPHY_H
#define PREBIKES_BASICGEOGRAPHY_H
#include <Bikes/BasicGeometry.h>
#include <string>


namespace Bikes
{


// Константы эллипсоида земли:
const double GEO_A=6378245; // большая полуось [м]
const double GEO_ALPHA=/*1.0/2.0;//*/(1.0/298.29974); // =(EE_A-EE_B)/EE_A
const double GEO_B=(1.0-GEO_ALPHA)*GEO_A; // малая полуось [м]
const double GEO_R=(GEO_A+GEO_B)/2.0; // средний радиус [м]
const double GEO_EE=GEO_ALPHA*(2.0-GEO_ALPHA); // e^2


struct DegMinSecAngle
{
	int deg;
	short min;
	short sec;
	bool negative;

	DegMinSecAngle(int  d=0, short  m=0, short  s=0, bool neg=false);
	DegMinSecAngle(double a_rad){setFromRad(a_rad);}	
	void operator = (double a_rad){setFromRad(a_rad);}
	operator double() const { return toRad();}
	DegMinSecAngle operator -(){return DegMinSecAngle(deg,min,sec,!negative);}

	void setFromRad(double a_rad);
	void setFromDeg(double a_deg);
	double toRad() const;
	double toDeg() const;
		
	std::string toString(bool print_sign=true, bool print_zero=false) const;
	

	int sign() const;
};


struct PhiLamPoint // географические координаты (phi,lambda)
{
	PhiLamPoint(double Phi=0,double Lamda=0):phi(Phi),lam(Lamda){}
	rnum phi;
	rnum lam;
};

struct PhiLamHPoint // географические координаты (phi,lambda,h)
{
	PhiLamHPoint(rnum Phi=0,rnum Lambda=0, rnum H=0):phi(Phi),lam(Lambda),h(H){}
	rnum phi;
	rnum lam;
	rnum h;
};


struct PhiLamRectangle
{
    PhiLamRectangle(const PhiLamPoint& p1, const PhiLamPoint& p2);    
    PhiLamRectangle(rnum phi_1, rnum phi_2, rnum lam_1, rnum lam_2);
    PhiLamRectangle();
    void set(rnum phi_1, rnum phi_2, rnum lam_1, rnum lam_2);

    bool isContain(const PhiLamPoint& p);

    PhiLamPoint anchor;
    rnum dPhi;
    rnum dLam;

    PhiLamRectangle& operator += (const PhiLamRectangle& rec);
};

PhiLamRectangle getPhiLamRectangleForPoints(std::vector<PhiLamPoint> points);



bool isRightLamDirection(rnum lam_l, rnum lam_r);

rnum deltaLam(rnum lam_1, rnum lam_2);

// Для сферы:
Point PhiLam_to_PointS(rnum phi, rnum lam);  // преобразовать (фи,лямда) в (x,y,z)
PhiLamPoint Point_to_PhiLamS(const Point &p); // преобразовать (x,y,z) в (фи,лямда)

// Для эллипсоида:
Point PhiLam_to_PointE(rnum phi, rnum lam); // преобразовывает географические координаты (phi,lambda) в геоцентрические (x,y,z) // h=0;
Point PhiLam_to_PointE(rnum phi, rnum lam, rnum h); // преобразовывает географические координаты (phi,lambda,h) в геоцентрические (x,y,z)
Point PhiLam_to_PointE(const PhiLamPoint &phi_lam);  // преобразовывает географические координаты (phi,lambda) в геоцентрические (x,y,z) // h=0;
Point PhiLam_to_PointE(const PhiLamHPoint &phi_lam_h); // преобразовывает географические координаты (phi,lambda,h) в геоцентрические (x,y,z)
PhiLamPoint Point_to_PhiLamE(const Point &p); // преобразовать (x,y,z) в (фи,лямда)


Vector EllipsePhiTan(const Point &p); // единичный касательный вектор к меридиану
Vector EllipseLamTan(const Point &p); // единичный касательный вектор к паралеле
rnum parallelR(rnum phi);


rnum getEarthRadiusAt(const Point& p);

void MovePointToEllipsoidSurface(Point &p); // переместить точку на поверхность эллипсоида 


class TrAngle;
Point PhiLam_to_PointE(TrAngle *phi, TrAngle *lam);
Point PhiLam_to_PointE_old( rnum phi, rnum lam );


void ellipseRange_approx(const Point& p1, // в геоцентрической СК
                         const Point& p2, // в геоцентрической СК
                         rnum range,  // [м] дальность
                         List<Point>& out_contour, // контур досягаемости
                         ApproximationMethodType approxMethod = ApproxMethod_avg,
                         rnum da = PI/90 // шаг аппроксимации
                         );

void ellipseRange_approx(const PhiLamPoint& p1,
                         const PhiLamPoint& p2,
                         rnum range,  // [м] дальность
                         List<PhiLamPoint>& out_contour, // контур досягаемости
                         ApproximationMethodType approxMethod = ApproxMethod_avg,
                         rnum da = PI/90 // шаг аппроксимации
                         );

void circleRange_approx(const Point &p,
                        rnum range,
                        List<Point>& out_contour,
                        ApproximationMethodType approxMethod = ApproxMethod_avg,
                        rnum da = PI/90 // шаг аппроксимации
                        );

void circleRange_approx(const PhiLamPoint &p,
                        rnum range,
                        List<PhiLamPoint>& out_contour,
                        ApproximationMethodType approxMethod = ApproxMethod_avg,
                        rnum da = PI/90 // шаг аппроксимации
                        );

}
#endif

// если разбить весь шар по секундам получится  839 808 000 000 точек
//												  

// Длина меридиана ->
/*
	Meters a = ellipsoid->A();  
	Units e2 = ellipsoid->E2();
	double p[4];//{b0,b2,b4,b6}

	p[0] = 1 + 3.*e2/4. + 45.*sqr(e2)/64. + 175.*pow(e2,3)/256.;
	p[1] = 3.*e2/4. + 15.*sqr(e2)/16. + 525.*pow(e2,3)/512.;
	p[2] = 15.*sqr(e2)/64. + 105.*pow(e2,3)/256.;
	p[3] = 35.*pow(e2,3)/512.;

	return a*(1-e2)*(p[0]*B-p[1]/2.*sin(2*B)+p[2]/4.*sin(4*B)-p[3]/6.*sin(6*B));
*/
// <- длина меридиана


// радиус параллели ->
// N*cos(B);
// <-
