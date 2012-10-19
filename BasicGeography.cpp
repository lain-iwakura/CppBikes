#include "BasicGeography.h"





DegMinSecAngle::DegMinSecAngle(int  d/*=0*/, char  m/*=0*/, char  s/*=0*/, bool neg/*=false*/) 
:deg(d),min(m),sec(s),negative(neg)
{

}


void DegMinSecAngle::setFromRad( double a_rad )
{
	setFromDeg(RAD_to_DEG(a_rad));
}

void DegMinSecAngle::setFromDeg( double a_deg )
{
	if(negative=a_deg<0) a_deg*=-1;	
	deg=a_deg;
	min=(a_deg-deg)*60.0;
	sec=((a_deg-deg)*60.0-min)*60.0+0.5;
}

double DegMinSecAngle::toRad()
{
	return DEG_to_RAD(toDeg());
}

double DegMinSecAngle::toDeg()
{	
	return ((double)deg + (double)min/60.0 + (double)sec/3600.0)*( negative?(-1.0):(1.0) );
}

int DegMinSecAngle::sign()
{
	return negative?(-1):(1);
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////



Vector EllipseLamTan(const Point &p)
{
	return (v_gk*p.v().e()).e();
}

Vector EllipsePhiTan(const Point &p)
{
	if(p.gz==0) return Vector(0,0,1,p);
	Vector vrx(p.gx,p.gy,0);
	TMETRIC rx=sqrt(p.gx*p.gx+p.gy*p.gy);
	vrx/=rx;
	TMETRIC tan_zrx=GEO_B*rx/(GEO_A*GEO_A*sqrt(1-rx*rx/(GEO_A*GEO_A))); // +/-
	Vector vz=v_gk*tan_zrx;
	if(p.gz>0) vrx*=-1;
	Vector vt=vrx+vz;
	vt.fulcrum=p;
	vt.normalize();
	return vt;
}
inline Point PhiLam_to_PointS( TAMETRIC phi, TAMETRIC lam )
{
	return Point(GEO_R*cos(lam)*cos(phi),GEO_R*sin(lam)*cos(phi),GEO_R*sin(phi));
}

PhiLamCoord Point_to_PhiLamS( const Point &p )
{
	return PhiLamCoord(asin(p.gz/GEO_R),acos(p.gx/sqrt(p.gx*p.gx+p.gy*p.gy))*signum(p.gy));
}


Point PhiLam_to_PointE(const PhiLamCoord &phi_lam)
{
	return PhiLam_to_PointE(phi_lam.phi, phi_lam.lam);
}


Point PhiLam_to_PointE( TAMETRIC phi, TAMETRIC lam )
{
	TMETRIC cosB=cos(phi);
	TMETRIC sinB=sin(phi);
	TMETRIC cosL=cos(lam);
	TMETRIC sinL=sin(lam);
	//TMETRIC H=0;
	TMETRIC N=GEO_A/sqrt(1-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1-GEO_EE)*N/*+H*/)*sinB);
}

PhiLamCoord Point_to_PhiLamE( const Point &p )
{
	TMETRIC D=sqrt(p.gx*p.gx+p.gy*p.gy);
	if(D==0) D=TMETRIC_O;
	return PhiLamCoord(atan(p.gz/((1-GEO_EE)*D)),acos(p.gx/D)*signum(p.gy));
}


void MovePointToEllipsoidSurface(Point &p)
{
	Vector vr(p);
	vr.normalize();
	static TMETRIC a=1/(GEO_A*GEO_A);
	static TMETRIC b=1/(GEO_B*GEO_B);
	TMETRIC sinA=vr&v_gk;
	TMETRIC r=1/sqrt(sinA*sinA*(b-a)+a);
	vr*=r;
	p=vr.destination();
}