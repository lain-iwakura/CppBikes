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

Bikes::rnum getEarthRadiusAt( const Point& p )
{
    static const rnum a=1.0/(GEO_A*GEO_A);
    static const rnum b=1.0/(GEO_B*GEO_B);

    Vector vr(p);
    vr.normalize();
    rnum sinA=vr&v_gk;
    return 1.0/sqrt(sinA*sinA*(b-a)+a);    
}


void MovePointToEllipsoidSurface(Point &p)
{
    static const rnum a=1.0/(GEO_A*GEO_A);
    static const rnum b=1.0/(GEO_B*GEO_B);

	Vector vr(p);
	vr.normalize();
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

bool PhiLamRectangle::isContain( const PhiLamPoint& p ) const
{
    rnum dlam=deltaLam(anchor.lam,p.lam);
    return  (dlam>=0) && 
            (dlam<=dLam) &&
            (p.phi>=anchor.phi) &&
            (p.phi<=anchor.phi+dPhi);    
}

PhiLamRectangle getPhiLamRectangleForPoints(const std::vector<PhiLamPoint>& points )
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



void ellipseRange_approx(const Point& p1,/* в геоцентрической СК */ 
                         const Point& p2,/* в геоцентрической СК */ 
                         rnum range, /* [м] дальность */ 
                         List<Point>& out_contour, /* контур досягаемости */ 
                         ApproximationMethodType approxMethod, /*= ApproxMethod_avg*/
                         rnum da_
                         )
{
//*
//    std::vector<rnum> l1;
//    std::vector<rnum> l2;
//    std::vector<rnum> bad_alpha;

    out_contour.clear();
    

    Vector v1(p1);
    Vector v2(p2);
    rnum r1 = v1.length();
    rnum r2 = v2.length();
    rnum r = (r1+r2)/2.0;
    Vector vw=v2*v1;//v1*v2;  
   // vw=vw*v1;
   
    rnum dalpha=da_;//PIm2/90.0;
    rnum da_min=dalpha/100.0;
    rnum da_max=dalpha*100.0;


    rnum dL=(range/2.0)*dalpha;

    
 
    

    //int i=0;
    //int j=0;

    rnum cos_phi0=inRange<rnum>((v1&v2)/(r1*r2), 0, 1.0);

    if(arccos(cos_phi0)*MAX(r1,r2) + METRIC_O > range)
        return;

    rnum sin2_phi0=1.0-cos_phi0*cos_phi0;
    rnum sin_phi0=sqrt(sin2_phi0);

    rnum sin_phiCrit = sin(0.5*range/r);    
    rnum sin2_phiCrit = sin_phiCrit*sin_phiCrit;    
    rnum cos_alphaCrit = (sin2_phi0+sin2_phiCrit-2.0*(1.0-sqrt(inRange<rnum>(1.0-sin2_phiCrit,0,1.0))))/(2.0*sin_phi0*sin_phiCrit); 
    rnum alphaCrit = arccos(cos_alphaCrit);


    rnum sin_lr=sin(range/r);
    rnum cos_lr=sqrt(1.0-sin_lr*sin_lr);
    rnum a=1.0-cos_lr;
    rnum c=sin2_phi0+2.0*cos_lr-2.0;

    
    rnum e2=0;
    {     
        rnum b=2.0*(sin_lr-sin_phi0*(-1.0));
        rnum d=b*b-4.0*a*c;
        rnum phi1=arcsin((-b+sqrt(d))/(2.0*a));
        Vector vv(v1);
        vv.rotate_W(vw,phi1);
        e2=(ABS(phi1)+ (vv^v2) )*r - range;
    }

    vw.rotate_W(v1,-(PI-alphaCrit));
    rnum e1=0;
    {        
        rnum b=2.0*(sin_lr-sin_phi0*cos_alphaCrit);
        rnum d=b*b-4.0*a*c;
        rnum phi1=arcsin((-b+sqrt(d))/(2.0*a));
        Vector vv(v1);
        vv.rotate_W(vw,phi1);
        e1=(ABS(phi1) + (vv^v2) )*r - range;
    } 

    rnum drange=0;

    switch(approxMethod)
    {
    case ApproxMethod_avg:
        {
            drange = -(e1+e2)/2.0;
        }break;
    case ApproxMethod_min:
        {
            drange = -(MAX(e1,e2) + METRIC_O);
        }break;
    case ApproxMethod_max:
        {
            drange = -(MIN(e1,e2) - METRIC_O);
        }break;
    }

    range += drange;
    
    sin_lr=sin(range/r);
    cos_lr=sqrt(1.0-sin_lr*sin_lr);
    a=1.0-cos_lr;
    c=sin2_phi0+2.0*cos_lr-2.0;




    for(rnum alpha=alphaCrit; alpha<PI; alpha+=dalpha) 
    {                             
        rnum b=2.0*(sin_lr-sin_phi0*cos(alpha));
        rnum d=b*b-4.0*a*c;

        if(d>=0)
        {
            //rnum phi1=/*arcsin(*/(-b+sqrt(d))/(2.0*a)/*)*/;
            rnum phi1=arcsin((-b+sqrt(d))/(2.0*a));
            Vector vv(v1);
            vv.rotate_W(vw,phi1);
            dalpha=inRange(dL/not0(phi1*r),da_min,da_max);
            out_contour+=vv.destination();         
        }else
        {
        }
        vw.rotate_W(v1,dalpha);    
    }
    
    Basis be;
    Vector v0= (v1/r1) + (v2/r2);    
    be.setOrtoBasis_ByIJ(v0,v1*v2);
    be.setOrtoBasis_ByIJ(-be.k,be.j);

    for(sznum i=0; i<out_contour.size(); i++)
    {
        if( out_contour[i].lx(be)>0 || out_contour[i].ly(be)<0)
        {
            out_contour.removeAt(i);
            i--;
        }
    }


    for(num i=out_contour.size()-1; i>=0; i--)
        out_contour += Point(out_contour[i].lx(be),-out_contour[i].ly(be),out_contour[i].lz(be),&be);


    for(num i=out_contour.size()-1; i>=0; i--)
        out_contour += Point(-out_contour[i].lx(be),out_contour[i].ly(be),out_contour[i].lz(be),&be);


    for(sznum i=0; i<out_contour.size(); i++)
        MovePointToEllipsoidSurface(out_contour[i]);

    
    //*/
}

void ellipseRange_approx( 
                               const PhiLamPoint& p1, 
                               const PhiLamPoint& p2, 
                               rnum range, /* [м] дальность */ 
                               List<PhiLamPoint>& out_contour, /* контур досягаемости */ 
                               ApproximationMethodType approxMethod, /*= ApproxMethod_avg */
                               rnum da
                               )
{
    out_contour.clear();
    List<Point> ps;
    ellipseRange_approx(PhiLam_to_PointE(p1),PhiLam_to_PointE(p2),range,ps,approxMethod,da);
    for(sznum i=0; i<ps.size(); i++)    
        out_contour += Point_to_PhiLamE(ps[i]);    
}



void circleRange_approx(const Point &p_, 
                        rnum range, 
                        List<Point>& out_contour, 
                        ApproximationMethodType approxMethod, /*= ApproxMethod_avg */
                        rnum da
                        )
{    
//    static const rnum da=DEG_to_RAD(2.0);

    Point p(p_);
    MovePointToEllipsoidSurface(p);
    Vector vp(p);
    Vector w=vp*v_gk;

    rnum rp=vp.length();
    rnum rt=rp;
    rnum rb=rp;

    rnum ra=range/rp;
    

    {    
        Vector vvp(vp);
        vvp.rotate_W(w,ra);
        rt=getEarthRadiusAt(vvp.destination());
    }

    {    
        Vector vvp(vp);
        vvp.rotate_W(-w,ra);
        rb=getEarthRadiusAt(vvp.destination());
    }

    
    
    if(approxMethod == ApproxMethod_min)
    {
        ra=range/MAX(rp,rt,rb);        
    }else if(approxMethod == ApproxMethod_max)
    {
        ra=(range/cos(da/2.0))/(MIN(rp,rt,rb));
    }else
    {  
        ra=(range/cos(da/2.0))/(AVG(rp,rt,rb));
    }
    
    
    for(rnum a=0; a<PIm2; a+=da)
    {
        Vector vvp(vp);
        vvp.rotate_W(w,ra);
        Point *dp =new Point(vvp.destination());
        MovePointToEllipsoidSurface(*dp);
        out_contour.take(dp);
        w.rotate_W(vp,da);
    }
}

void circleRange_approx(const PhiLamPoint &p, 
                        rnum range, 
                        List<PhiLamPoint>& out_contour, 
                        ApproximationMethodType approxMethod, /*= ApproxMethod_avg */
                        rnum da 
                        )
{
    List<Point> c;
    circleRange_approx(PhiLam_to_PointE(p),range,c,approxMethod,da);
    for(sznum i=0; i<c.size(); i++)
        out_contour.push_back(Point_to_PhiLamE(c[i]));
}

bool findEllipsoidIntersection(const Vector& line, Point& crossPoint1, Point& crossPoint2)
{
    static const rnum eaa = GEO_A*GEO_A;    
    static const rnum eab = eaa / (GEO_B*GEO_B);

    bool suc = false;    

    if (line.gz != 0.0)
    {
        rnum kx = line.gx / line.gz;
        rnum ky = line.gy / line.gz;

        rnum bx = line.anchor.gx - kx*line.anchor.gz;
        rnum by = line.anchor.gy - ky*line.anchor.gz;

        rnum a = (kx*kx + ky*ky) + eab;
        rnum b = (kx*bx + ky*by) / a;
        rnum c = (bx*bx + by*by - eaa) / a;

        rnum d4 = b*b - c;

        if (d4 >= 0.0)
        {
            rnum sd = sqrt(d4);
            rnum z1 = -b - sd;
            rnum z2 = -b + sd;

            crossPoint1.gx = kx*z1 + bx;
            crossPoint1.gy = ky*z1 + by;
            crossPoint1.gz = z1;

            crossPoint2.gx = kx*z2 + bx;
            crossPoint2.gy = ky*z2 + by;
            crossPoint2.gz = z2;

            suc = true;
        }
    }
    else if (line.gx != 0.0)
    {
        rnum ky = line.gy / line.gx;
        //rnum kz = 0; //line.gz / line.gx;

        rnum by = line.anchor.gy - ky*line.anchor.gx;
        rnum bz = line.anchor.gz; //- 0*line.anchor.gx;

        rnum a = 1.0 + ky*ky;
        rnum b = ky*by / a;
        rnum c = (by*by + bz*bz*eab - eaa) / a;

        rnum d4 = b*b - c;

        if (d4 >= 0.0)
        {
            rnum sd = sqrt(d4);
            rnum x1 = -b - sd;
            rnum x2 = -b + sd;

            crossPoint1.gx = x1;
            crossPoint1.gy = ky*x1 + by;
            crossPoint1.gz = bz;

            crossPoint2.gx = x2;
            crossPoint2.gy = ky*x2 + by;
            crossPoint2.gz = bz;

            suc = true;
        }
    }
    else if (line.gy != 0.0)
    {
        //rnum kz = 0;
        //rnum kx = 0;

        rnum bz = line.anchor.gz;
        rnum bx = line.anchor.gx;

        rnum d4 = eaa - eab*bz*bz - bx*bx;

        if (d4 >= 0.0)
        {
            rnum y = sqrt(d4);         

            crossPoint1.gx = bx;
            crossPoint1.gy = y;
            crossPoint1.gz = bz;

            crossPoint2.gx = bx;
            crossPoint2.gy = -y;
            crossPoint2.gz = bz;

            suc = true;
        }
    }
        
    return suc;
}



}//Bikes
