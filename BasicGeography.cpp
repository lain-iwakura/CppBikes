#include "BasicGeography.h"
#include <CppBikes/TrigonometricAngle.h>



namespace CppBikes
{



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
  int const seconds(floor(a_deg * 3600 + .5));
  sec = seconds % 60;
  int const d_m(seconds / 60);
	deg = d_m / 60;
	min = d_m % 60;
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



Vector CppBikes::EllipseLamTan(const Point &p)
{
	return (v_gk*p.v().e()).e();
}

Vector CppBikes::EllipsePhiTan(const Point &p)
{
	if(p.gz==0) return Vector(0,0,1,p);
	Vector vrx(p.gx,p.gy,0);
	RNUM rx=sqrt(p.gx*p.gx+p.gy*p.gy);
	vrx/=rx;
	RNUM tan_zrx=GEO_B*rx/(GEO_A*GEO_A*sqrt(1-rx*rx/(GEO_A*GEO_A))); // +/-
	Vector vz=v_gk*tan_zrx;
	if(p.gz>0) vrx*=-1;
	Vector vt=vrx+vz;
	vt.anchor=p;
	vt.normalize();
	return vt;
}
inline Point CppBikes::PhiLam_to_PointS( RNUM phi, RNUM lam )
{
	return Point(GEO_R*cos(lam)*cos(phi),GEO_R*sin(lam)*cos(phi),GEO_R*sin(phi));
}

PhiLamCoord CppBikes::Point_to_PhiLamS( const Point &p )
{
	return PhiLamCoord(asin(p.gz/GEO_R),acos(p.gx/sqrt(p.gx*p.gx+p.gy*p.gy))*signum(p.gy));
}


Point CppBikes::PhiLam_to_PointE(const PhiLamCoord &phi_lam)
{
	return PhiLam_to_PointE(phi_lam.phi, phi_lam.lam);
}


Point CppBikes::PhiLam_to_PointE( RNUM phi, RNUM lam )
{
	phi=NormAngle(phi);
	lam=NormAngle(lam);

	RNUM cosB=cos(phi);
	RNUM sinB=sqrt(1-cosB*cosB);//sin(phi);
	if(phi<0) sinB=-sinB;
	RNUM cosL=cos(lam);
	RNUM sinL=sqrt(1-cosL*cosL);//sin(lam);
	if(lam<0) sinL=-sinL; 
	//RNUM H=0;
	RNUM N=GEO_A/sqrt(1-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1-GEO_EE)*N/*+H*/)*sinB);
}


Point CppBikes::PhiLam_to_PointE_old( RNUM phi, RNUM lam )
{
	//phi=NormAngle(phi);
	//lam=NormAngle(lam);

	RNUM cosB=cos(phi);
	RNUM sinB=sin(phi);
	//if(phi<0) sinB=-sinB;
	RNUM cosL=cos(lam);
	RNUM sinL=sin(lam);
	//if(lam<0) sinL=-sinL; 
	//RNUM H=0;
	RNUM N=GEO_A/sqrt(1-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1-GEO_EE)*N/*+H*/)*sinB);
}


PhiLamCoord CppBikes::Point_to_PhiLamE( const Point &p )
{
	RNUM D=sqrt(p.gx*p.gx+p.gy*p.gy);
	//if(D==0) D=METRIC_O;
	return PhiLamCoord(atan(p.gz/not0((1-GEO_EE)*D)),acos(p.gx/not0(D))*signum(p.gy));
}

Point PhiLam_to_PointE( RNUM phi, RNUM lam, RNUM h )
{
	phi=NormAngle(phi);
	lam=NormAngle(lam);

	RNUM cosB=cos(phi);
	RNUM sinB=sqrt(1-cosB*cosB);//sin(phi);
	if(phi<0) sinB=-sinB;
	RNUM cosL=cos(lam);	
	RNUM sinL=sqrt(1-cosL*cosL);//sin(lam);
	if(lam<0) sinL=-sinL; 
	RNUM N=GEO_A/sqrt(1-GEO_EE*sinB*sinB);
	return Point((N+h)*cosB*cosL,(N+h)*cosB*sinL,((1-GEO_EE)*N+h)*sinB);
}

Point PhiLam_to_PointE( const PhiLamHCoord &phi_lam_h )
{
	return PhiLam_to_PointE(phi_lam_h.phi,phi_lam_h.lam,phi_lam_h.h);
}

Point PhiLam_to_PointE( TrAngle *phi, TrAngle *lam )
{
	RNUM cosB=phi->cos();
	RNUM sinB=phi->sin();
	RNUM cosL=lam->cos();
	RNUM sinL=lam->sin();
	RNUM N=GEO_A/sqrt(1-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1-GEO_EE)*N/*+H*/)*sinB);

}


void CppBikes::MovePointToEllipsoidSurface(Point &p)
{
	Vector vr(p);
	vr.normalize();
	static RNUM a=1/(GEO_A*GEO_A);
	static RNUM b=1/(GEO_B*GEO_B);
	RNUM sinA=vr&v_gk;
	RNUM r=1/sqrt(sinA*sinA*(b-a)+a);
	vr*=r;
	p=vr.destination();
}


}