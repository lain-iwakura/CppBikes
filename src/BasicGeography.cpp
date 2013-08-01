#include <Bikes/BasicGeography.h>
#include <Bikes/TrigonometricAngle.h>
#include <string>
#include <cstdio>


namespace Bikes
{



DegMinSecAngle::DegMinSecAngle(int  d/*=0*/, short  m/*=0*/, short  s/*=0*/, bool neg/*=false*/) 
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

double DegMinSecAngle::toRad() const
{
	return DEG_to_RAD(toDeg());
}

double DegMinSecAngle::toDeg() const
{	
	return ((double)deg + (double)min/60.0 + (double)sec/3600.0)*( negative?(-1.0):(1.0) );
}

int DegMinSecAngle::sign() const
{
	return negative?(-1):(1);
}

std::string DegMinSecAngle::toString(bool print_sign, bool print_zero) const
{
	//std::string str;
	char str_sign[2]={'\0','\0'};
	char str_deg[50]="";
	char str_min[5]="";
	char str_sec[5]="";

	char rstr[70]="";

	if(print_sign&&negative) str_sign[0]='-';
	
	if(print_zero)
	{
		sprintf(str_deg,"%d°",deg);
		sprintf(str_min,"%2d\'",int(min));
		sprintf(str_sec,"%2d\"",int(sec));
	}else
	{
		sprintf(str_deg,"%d°",deg);
		if(min)sprintf(str_min,"%2d\'",int(min));
		if(sec)sprintf(str_sec,"%2d\"",int(sec));
	}
	
	sprintf(rstr,"%s%s%s%s",str_sign,str_deg,str_min,str_sec);
	
	return std::string(rstr);
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
	rnum rx=sqrt(p.gx*p.gx+p.gy*p.gy);
	vrx/=rx;
	rnum tan_zrx=GEO_B*rx/(GEO_A*GEO_A*sqrt(1-rx*rx/(GEO_A*GEO_A))); // +/-
	Vector vz=v_gk*tan_zrx;
	if(p.gz>0) vrx*=-1;
	Vector vt=vrx+vz;
	vt.anchor=p;
	vt.normalize();
	return vt;
}
inline Point PhiLam_to_PointS( rnum phi, rnum lam )
{
	return Point(GEO_R*cos(lam)*cos(phi),GEO_R*sin(lam)*cos(phi),GEO_R*sin(phi));
}

PhiLamPoint Point_to_PhiLamS( const Point &p )
{
	return PhiLamPoint(asin(p.gz/GEO_R),acos(p.gx/sqrt(p.gx*p.gx+p.gy*p.gy))*signum(p.gy));
}


Point PhiLam_to_PointE(const PhiLamPoint &phi_lam)
{
	return PhiLam_to_PointE(phi_lam.phi, phi_lam.lam);
}


Point PhiLam_to_PointE( rnum phi, rnum lam )
{
	phi=normAngle(phi);
	lam=normAngle(lam);

	rnum cosB=cos(phi);
	rnum sinB=sqrt(1.0-cosB*cosB);//sin(phi);
	if(phi<0.0) sinB=-sinB;
	rnum cosL=cos(lam);
	rnum sinL=sqrt(1.0-cosL*cosL);//sin(lam);
	if(lam<0.0) sinL=-sinL; 
	//rnum H=0;
	rnum N=GEO_A/sqrt(1.0-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1.0-GEO_EE)*N/*+H*/)*sinB);
}


Point PhiLam_to_PointE_old( rnum phi, rnum lam )
{
	//phi=NormAngle(phi);
	//lam=NormAngle(lam);

	rnum cosB=cos(phi);
	rnum sinB=sin(phi);
	//if(phi<0) sinB=-sinB;
	rnum cosL=cos(lam);
	rnum sinL=sin(lam);
	//if(lam<0) sinL=-sinL; 
	//rnum H=0;
	rnum N=GEO_A/sqrt(1.0-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1.0-GEO_EE)*N/*+H*/)*sinB);
}


PhiLamPoint Point_to_PhiLamE( const Point &p )
{
	rnum D=sqrt(p.gx*p.gx+p.gy*p.gy);
	//if(D==0) D=METRIC_O;
	return PhiLamPoint(atan(p.gz/not0((1.0-GEO_EE)*D)),acos(p.gx/not0(D))*signum(p.gy));
}

Point PhiLam_to_PointE( rnum phi, rnum lam, rnum h )
{
	phi=normAngle(phi);
	lam=normAngle(lam);

	rnum cosB=cos(phi);
	rnum sinB=sqrt(1.0-cosB*cosB);//sin(phi);
	if(phi<0.0) sinB=-sinB;
	rnum cosL=cos(lam);	
	rnum sinL=sqrt(1.0-cosL*cosL);//sin(lam);
	if(lam<0.0) sinL=-sinL; 
	rnum N=GEO_A/sqrt(1.0-GEO_EE*sinB*sinB);
	return Point((N+h)*cosB*cosL,(N+h)*cosB*sinL,((1.0-GEO_EE)*N+h)*sinB);
}

Point PhiLam_to_PointE( const PhiLamHPoint &phi_lam_h )
{
	return PhiLam_to_PointE(phi_lam_h.phi,phi_lam_h.lam,phi_lam_h.h);
}

Point PhiLam_to_PointE( TrAngle *phi, TrAngle *lam )
{
	rnum cosB=phi->cos();
	rnum sinB=phi->sin();
	rnum cosL=lam->cos();
	rnum sinL=lam->sin();
	rnum N=GEO_A/sqrt(1.0-GEO_EE*sinB*sinB);
	return Point((N/*+H*/)*cosB*cosL,(N/*+H*/)*cosB*sinL,((1.0-GEO_EE)*N/*+H*/)*sinB);

}


void MovePointToEllipsoidSurface(Point &p)
{
	Vector vr(p);
	vr.normalize();
	static const rnum a=1.0/(GEO_A*GEO_A);
	static const rnum b=1.0/(GEO_B*GEO_B);
	rnum sinA=vr&v_gk;
	rnum r=1.0/sqrt(sinA*sinA*(b-a)+a);
	vr*=r;
	p=vr.destination();
}

rnum parallelR( rnum phi )
{
	rnum sinBsinB=sin(phi);
	sinBsinB*=sinBsinB;		
	return  GEO_A*sqrt((1.0-sinBsinB)/(1.0-GEO_EE*sinBsinB));
}



}//Bikes
