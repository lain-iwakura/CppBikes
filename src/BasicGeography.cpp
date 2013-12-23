#include <Bikes/BasicGeography.h>
#include <Bikes/BasicMath.h>
#include <Bikes/TrigonometricAngle.h>
#include <Bikes/MemoryBikes.h>
#include <string>
#include <cstdio>

#include <iomanip>
#include <sstream>

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
  int const seconds(int(a_deg * 3600 + .5));
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
    std::ostringstream stream;

	if(print_sign&&negative)
        stream << '-';
	
	if(print_zero)
	{		
        stream << deg << "°";		
        stream << std::setw(2) << int(min) << "\'";		
        stream << std::setw(2) << int(sec) << "\"";
	}else
	{
        stream << deg << "°";	
		if(min)
            stream << std::setw(2) << int(min) << "\'";
		if(sec)
            stream << std::setw(2) << int(sec) << "\"";
	}		
    stream << '\0';
	return stream.str();
}


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




PhiLamRectangle::PhiLamRectangle( const PhiLamPoint& p1, const PhiLamPoint& p2 )
{
    set(p1.phi,p2.phi,p1.lam,p2.lam);
}

PhiLamRectangle::PhiLamRectangle( rnum phi_1, rnum phi_2, rnum lam_1, rnum lam_2 )
{
    set(phi_1,phi_2,lam_1,lam_2);
}

PhiLamRectangle::PhiLamRectangle():
dPhi(0),
dLam(0)
{

}

void PhiLamRectangle::set( rnum phi_1, rnum phi_2, rnum lam_1, rnum lam_2 )
{
    if(phi_1>phi_2)
        swap_(phi_1,phi_2);

    anchor.phi=phi_1;
    anchor.lam=lam_1;

    dPhi=phi_2-phi_1;
    dLam=lam_2-lam_1;
    if(dLam<0)
    {
        dLam=PIm2-dLam;
    }
}

PhiLamRectangle& PhiLamRectangle::operator+=( const PhiLamRectangle& rec )
{
    if(anchor.phi<rec.anchor.phi)
    {
        if(anchor.phi+dPhi<rec.anchor.phi+rec.dPhi)
        {
            dPhi=rec.anchor.phi+rec.dPhi-anchor.phi;
        }
    }else
    {
        if(rec.anchor.phi+rec.dPhi<anchor.phi+dPhi)
        {
            dPhi+=anchor.phi-rec.anchor.phi;
        }else
        {
            dPhi=rec.dPhi;
        }
        anchor.phi=rec.anchor.phi;
    }

    rnum dl=deltaLam(anchor.lam,rec.anchor.lam);

    if(dl>0)
    {
        if(dLam<dl+rec.dLam)
        {
            dLam=dl+rec.dLam;
        }
    }else
    {
        if(rec.dLam<-dl+dLam)
        {
            dLam+=-dl;
        }else
        {
            dLam=rec.dLam;
        }
        anchor.lam=rec.anchor.lam;
    }
    return *this;
}

bool PhiLamRectangle::isContain( const PhiLamPoint& p )
{
    rnum dlam=deltaLam(anchor.lam,p.lam);
    return  (dlam>=0) && 
            (dlam<=dLam) &&
            (p.phi>=anchor.phi) &&
            (p.phi<=anchor.phi+dPhi);    
}

PhiLamRectangle getPhiLamRectangleForPoints( std::vector<PhiLamPoint> points )
{    
    PhiLamRectangle r;
    if(points.size())
    {   
        rnum phi_min=points[0].phi;
        rnum phi_max=phi_min;
        rnum lam_l=points[0].lam;
        rnum lam_r=lam_l;        

        for(sznum i=0; i<points.size(); i++)
        {
            if(phi_min>points[i].phi)
            {
                phi_min=points[i].phi;
            }
            else if(phi_max<points[i].phi)
            {
                phi_max=points[i].phi;
            }
        
            rnum lam=points[i].lam;
            if(isRightLamDirection(lam,lam_l))
            {
                lam_l=lam;
            }else if(isRightLamDirection(lam_r,lam))
            {
                lam_r=lam;
            } 
        }

        r.anchor.lam=lam_l;
        if(lam_l<lam_r)
        {          
            r.dLam=lam_r-lam_l;            
        }else
        {
            r.dLam=PIm2-(lam_l-lam_r);
        }

        r.anchor.phi=phi_min;
        r.dPhi=phi_max-phi_min;
               

    }
    return r;
}

bool isRightLamDirection( rnum lam_l, rnum lam_r )
{
    if(lam_r>lam_l)
    {
        return (lam_r-lam_l)<PI;
    }else
    {
        return (lam_l-lam_r)>PI;
    }
    return false;
}

Bikes::rnum deltaLam( rnum lam_1, rnum lam_2 )
{
    rnum d=ABS(lam_2-lam_1);
    if(d>PI)
        d=PIm2-d;
    if(!isRightLamDirection(lam_1,lam_2))
        d*=-1;
    return d;
}


}//Bikes
