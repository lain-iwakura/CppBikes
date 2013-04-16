#include "BasicGeometry.h"

namespace Bikes
{


//////////////////////////////////////////////////////////////////////////
////////////////////////// POINT /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Point::Point(RNUM plx, RNUM ply, RNUM plz, const Basis *b, bool notransient)
{
	_transient=!notransient;
	basis=0;
	gx=plx;
	gy=ply;
	gz=plz;
	ReplaceGBasis(b);	
	_null=false;	
}

Point::Point(bool IsNotNull, const Point &p,bool notransient)
{
	_transient=!notransient;
	basis=p.basis; 
	_null=!IsNotNull;
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;	
	if(basis) basis->Add(this);
	
}


Point::Point(const Point &p)
{
	_transient=false;
	basis=p.basis; 
	_null=p._null;
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;	
	if(basis) basis->Add(this);

}

Point::Point(const Vector &v, bool notransient)
{
	_transient=!notransient;
	basis=0;
	*this=v.destination();
}

Point::~Point()
{
	if(basis) basis->Remove(this);
}

void Point::operator = (const Point &p)
{
	//basis=0;
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;	
	_null=p._null;
	SetBasis(p.basis);
}

void Point::operator = (const Vector &v)
{
	*this=v.destination();
}


Vector Point::operator && (const Point &p) const {return Vector(*this,p,false);}
Point Point::operator [](const Basis &b) const {return inBasis(&b);}
Point Point::operator [](const Basis *b) const {return inBasis(b);}
Point& Point::operator >>(const Basis &b)  {return SetBasis(&b);}
Point& Point::operator >>(const Basis *b)  {return SetBasis(b);}	

Point Point::operator + (const Vector &v) const {return Point(Vector(*this)+v,false);}
Point Point::operator - (const Vector &v) const {return Point(Vector(*this)-v,false);}
void Point::operator +=(const Vector &v)
{
	gx+=v.gx;
	gy+=v.gy;
	gz+=v.gz;
}

void Point::operator -=(const Vector &v)
{
	gx-=v.gx;
	gy-=v.gy;
	gz-=v.gz;
}



Point& Point::SetGlobalBasis()
{
	if(basis) basis->Remove(this);
	basis=0;
	return *this;
}

Vector Point::v() const {return Vector(*this,false);} 

Point& Point::SetBasis(const Basis *b)
{
	if(basis) basis->Remove(this);
	basis=b;
	if(basis) basis->Add(this);
	return *this;
}

Point Point::inBasis(const Basis *b) const
{
	Point rp(true,*this,false);
	rp.SetBasis(b);
	return rp;
}

Point Point::inGlobalBasis() const
{
	Point rp(true,*this,false);
	rp.SetGlobalBasis();
	return rp;
}

Point& Point::ReplaceGBasis(const Basis *b)
{
	if(basis) basis->Remove(this);
	if(b)
	{		
		Vector v(b->i*gx+b->j*gy+b->k*gz);
		gx=v.gx+b->O.gx;
		gy=v.gy+b->O.gy;
		gz=v.gz+b->O.gz;
		b->Add(this);
	}
	basis=b;	
	return *this;
}

Point& Point::ReplaceBasis(const Basis *b)
{	
	if(basis) basis->Remove(this);
	if(b)
	{		
		Vector v(b->i*x()+b->j*y()+b->k*z());
		gx=v.gx+b->O.gx;
		gy=v.gy+b->O.gy;
		gz=v.gz+b->O.gz;
		b->Add(this);
	} else if(basis)
	{
		SetGlobal(x(),y(),z());
	}
	basis=b;	
	return *this;
}

Point Point::inReplacedBasis(const Basis *b) const
{
	Point rp(true,*this,false); rp.ReplaceBasis(b);
	return rp;
}



Point&  Point::Rotate_W(const Vector &w,RNUM a)
{	
	if(w.anchor!=*this)
	{	
		Vector pv(w.anchor,*this); pv.rotate_W(w,a);
		*this=pv;
	}
	return *this;
}


Point& Point::Rotate_X(RNUM a)
{
	if(basis) return Rotate_W(basis->i,a);
	return Rotate_W(v_gi,a);
}
Point& Point::Rotate_Y(RNUM a)
{
	if(basis) return Rotate_W(basis->j,a);
	return Rotate_W(v_gj,a);
}
Point& Point::Rotate_Z(RNUM a)
{
	if(basis) return Rotate_W(basis->k,a);
	return Rotate_W(v_gk,a);
}



bool Point::operator ==(const Point &p) const
{
	if(ABS(p.gx-gx)<METRIC_O&&ABS(p.gy-gy)<METRIC_O&&ABS(p.gz-gz)<METRIC_O) return true; 
	return false;
}

bool Point::operator !=(const Point &p) const
{
	return !(*this==p);
}

RNUM Point::lx(const Basis *b) const 
{	
	if(b)return (gx - b->O.gx)*(b->i.gx) + (gy - b->O.gy)*(b->i.gy) + (gz - b->O.gz)*(b->i.gz);
	return gx;
}

RNUM Point::ly(const Basis *b) const
{
	if(b)return (gx - b->O.gx)*(b->j.gx) + (gy - b->O.gy)*(b->j.gy) + (gz - b->O.gz)*(b->j.gz);
	return gy;
}

RNUM Point::lz(const Basis *b) const 
{
	if(b) return (gx - b->O.gx)*(b->k.gx) + (gy - b->O.gy)*(b->k.gy) + (gz - b->O.gz)*(b->k.gz);
	return gz;
}

RNUM Point::lx(const Basis &b) const 
{	
	return (gx - b.O.gx)*(b.i.gx) + (gy - b.O.gy)*(b.i.gy) + (gz - b.O.gz)*(b.i.gz);	
}

RNUM Point::ly(const Basis &b) const
{
	return (gx - b.O.gx)*(b.j.gx) + (gy - b.O.gy)*(b.j.gy) + (gz - b.O.gz)*(b.j.gz);	
}

RNUM Point::lz(const Basis &b) const 
{
	return (gx - b.O.gx)*(b.k.gx) + (gy - b.O.gy)*(b.k.gy) + (gz - b.O.gz)*(b.k.gz);	
}

RNUM Point::x() const {return lx(basis);}
RNUM Point::y() const {return ly(basis);}
RNUM Point::z() const {return lz(basis);}

Point& Point::Set(RNUM px, RNUM py,RNUM pz, const Basis *b)
{
	*this=Point(px,py,pz,b,true);
	return *this;
}
Point& Point::SetGlobal(RNUM pgx, RNUM pgy, RNUM pgz)
{
	gx=pgx;gy=pgy;gz=pgz;
	return *this;
}
Point& Point::SetLocal(RNUM localx, RNUM localy, RNUM localz)
{
	if(basis) *this=Point(localx,localy,localz,basis);	
	else {gx=localx; gy=localy; gz=localz;}
	return *this;
}
Point& Point::SetLocalX(RNUM localx)
{
	if(basis)
	{
//		*this=Point(localx,y(),z(),basis);
		*this+=basis->i*(localx-x());
	}else gx=localx;	
	return *this;
}
Point& Point::SetLocalY(RNUM localy)
{
	if(basis)
	{
	//	*this=Point(x(),localy,z(),basis);
		*this+=basis->j*(localy-y());
	}else gy=localy;
	return *this;
}
Point& Point::SetLocalZ(RNUM localz)
{
	if(basis)
	{
		//*this=Point(x(),y(),localz,basis);
		*this+=basis->k*(localz-z());
	}else gz=localz;	
	return *this;
}


bool Point::isEqual(const Point &p1, const Point &p2, RNUM e)
{
	if(e==0) return p1.gx==p2.gx&&p1.gy==p2.gy&&p1.gz==p2.gz;
	return isEqual(p1.gx,p2.gx,e)&&isEqual(p1.gy,p2.gy,e)&&isEqual(p1.gz,p2.gz,e);
}


RNUM Point::PolarR() const
{
	RNUM px=x();
	RNUM py=y();
	return sqrt(px*px+py*py);
}

RNUM Point::PolarAlpha() const
{
	RNUM px=x();
	RNUM py=y();
	RNUM l=sqrt(px*px+py*py);
	RNUM a=arccos(px/l);
	if(py<0) a=2*PI-a;
	return a;
}

bool Point::isNull() const
{
	return _null;
}

bool Point::isTransient() const
{
	return _transient;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////// VECTOR //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


Vector::Vector(RNUM vx, RNUM vy, RNUM vz, const Point &fp,const Basis *b, bool notransient)
:anchor(true,fp,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=false;
	anchor=fp;
	if(b)
	{
		*this=b->i*vx+b->j*vy+b->k*vz;
		b->Add(this); 
	}else
	{
		gx=vx; 
		gy=vy; 
		gz=vz; 
	}
	basis=b;
	anchor.SetBasis(b);
//	if(b) ReplaceGBasis(b);//basis->vectors+=this;
}

Vector::Vector(const Vector &v)
{
	_transient=false;
	basis=0;
	*this=v;
}

void Vector::operator = (const Vector &v)
{
	gx=v.gx;
	gy=v.gy;
	gz=v.gz;
	anchor=v.anchor;
	SetBasis(v.basis);
	_null=v._null;	
}

void Vector::operator = (const Point &p)
{
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;
	anchor=p_gO;
	SetGlobalBasis();
	_null=p.isNull();
}

Vector::Vector(bool NotNull, const Vector &v, bool notransient)
:anchor(true,v.anchor,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=!NotNull;
	gx=v.gx;
	gy=v.gy;
	gz=v.gz;
//	anchor=v.anchor;
	basis=v.basis;
	if(basis) basis->Add(this);
}

Vector::Vector(const Point &p,bool notransient)
:anchor(0,0,0,0,notransient)
{
	_transient=!notransient;
	basis=0;
	gx=p.gx; gy=p.gy; gz=p.gz; 	
	_null=p.isNull();
}

Vector::Vector(const Point &p1, const Point &p2,const Basis *b, bool notransient)
:anchor(true,p1,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=false;
//	anchor=p1; 
	gx=p2.gx-p1.gx; 
	gy=p2.gy-p1.gy; 
	gz=p2.gz-p1.gz;
	basis=b;
	if(basis) basis->Add(this);
}

Vector::~Vector()
{
	if(basis) basis->Remove(this);
}

Vector Vector::operator +(const Vector &v) const { return Vector(gx+v.gx,gy+v.gy,gz+v.gz,anchor,0,false);}
Vector Vector::operator -(const Vector &v) const { return Vector(gx-v.gx,gy-v.gy,gz-v.gz,anchor,0,false);}
void Vector::operator += (const Vector &v){ gx+=v.gx; gy+=v.gy; gz+=v.gz;}
void Vector::operator -= (const Vector &v){ gx-=v.gx; gy-=v.gy; gz-=v.gz;}
RNUM Vector::operator &(const Vector &v)const {return v.gx*gx+v.gy*gy+v.gz*gz;}
Vector Vector::operator *(const Vector &v)const { return Vector(gy*v.gz-gz*v.gy,gz*v.gx-gx*v.gz,gx*v.gy-gy*v.gx,anchor,0,false);}
Vector Vector::operator *(RNUM n)const {return Vector(gx*n,gy*n,gz*n,anchor,0,false);}
Vector Vector::operator /(RNUM n)const {not0set(n); return Vector(gx/n,gy/n,gz/n,anchor,0,false);}
void Vector::operator *=(RNUM n){gx*=n;gy*=n;gz*=n;}
void Vector::operator /=(RNUM n){not0set(n); gx/=n; gy/=n; gz/=n;}
bool Vector::operator ==(const Vector &v)const {return (ABS(v.gx-gx)<METRIC_O)&&(ABS(v.gy-gy)<METRIC_O)&&(ABS(v.gz-gz)<METRIC_O);}
bool Vector::operator !=(const Vector &v)const {return !(*this==v);}
Vector Vector::operator -() const {return (*this)*(-1);}
//////// extra operators ///////
Point Vector::operator % (const Vector &v) const {return Intersection(v);}
bool Vector::operator || (const Vector &v) const {return isParallel(*this,v);}
bool Vector::operator |=(const Vector &v) const {return isRightVectors(*this,v);}
Basis Vector::operator && (const Vector &v) const {return OrtoBasis_ByIJ(*this,v);}
Basis Vector::operator && (const Point &p) const {return OrtoBasis_ByIJ(*this,Vector(anchor,p));}
#ifdef CPPBIKES_USE_TRANGLE
TrAngle Vector::operator ^ (const Vector &v) const {return Angle(*this,v);}
#else
RNUM Vector::operator ^ (const Vector &v) const {return Angle(*this,v);}
#endif
Vector Vector::operator [] (const Basis &b) const {return inBasis(&b);}
Vector Vector::operator [] (const Basis *b) const {return inBasis(b);}
Vector& Vector::operator >> (const Basis &b)  {return SetBasis(&b);}
Vector& Vector::operator >> (const Basis *b)  {return SetBasis(b);}
Vector Vector::operator !() const { return Vector(true,*this,false).invert();}
bool Vector::operator > (const Vector &v) const {return length()>v.length();}
bool Vector::operator < (const Vector &v) const {return length()<v.length();}
////////////////////////////////

Point Vector::destination() const {Point p(anchor.gx+gx,anchor.gy+gy,anchor.gz+gz,0,false); p.SetBasis(basis); return p;}
Vector Vector::e() const {return Vector(true,(*this)/length(),false);}
RNUM Vector::length() const {return sqrt(gx*gx+gy*gy+gz*gz);}
Vector& Vector::normalize(){*this/=length(); return *this;}

Vector& Vector::SetGlobalBasis()
{
	if(basis) basis->Remove(this);
 	anchor.SetGlobalBasis();
	basis=0;
	return *this;
}

Vector& Vector::SetBasis(const Basis *b)
{	
	if(b==basis) return *this;
	if(basis) basis->Remove(this); 	
	basis=b;
	if(basis) basis->Add(this);
	anchor.SetBasis(b);	
	return *this;
}

Vector& Vector::ReplaceGBasis(const Basis *b) //-!
{
	if(basis){basis->Remove(this);}	
	if(b)
	{
		*this=b->i*gx+b->j*gy+b->k*gz;
		b->Add(this);
	}
	basis=b;
	anchor.ReplaceGBasis(b);	
	return *this;
}

Vector& Vector::ReplaceBasis(const Basis *b) //-!
{
	if(b==basis) return *this; //!	
	if(b)
	{
		*this=b->i*x()+b->j*y()+b->k*z();
		b->Add(this);
	}else if(basis)
	{
		SetGlobal(x(),y(),z());
	}
	if(basis){basis->Remove(this);}
	basis=b;
	anchor.ReplaceBasis(b);
	return *this;
}

Vector Vector::inBasis(const Basis *b)const {Vector rv(true,*this,false);rv.SetBasis(b);return rv;}
Vector Vector::inGlobalBasis()const {Vector rv(true,*this,false);rv.SetGlobalBasis();return rv;}
Vector Vector::inReplacedBasis(const Basis *b)const {Vector rv(true,*this,false); rv.ReplaceBasis(b); return rv;}


Vector& Vector::rotate_W(const Vector &w, RNUM a) //+?
{	
	if(!isParallel(*this,w))
	{
		RNUM wl=w.length();
		Vector ew=w/wl;
		RNUM l=length();		
		RNUM zsh=ew&(*this);
		RNUM rsh=sqrt(l*l-zsh*zsh);
		Vector vzsh=ew*zsh;
		Vector vrsh=*this-vzsh;
		a=NormAngle(a);
		RNUM aa=ABS(a);
		int sa=a>0?1:-1;
		aa=NormAngle(aa);
		while(aa>=PI/2){aa-=PI/2;vrsh=ew*vrsh*sa;}
		if(aa>PI/4){aa-=PI/4; vrsh=((ew*vrsh*sa)+vrsh).e()*rsh;}
		vrsh=(vrsh+(ew*vrsh).e()*rsh*tan(aa)*sa).e()*rsh;
		Vector nv=vrsh+vzsh;
		SetGlobal(nv.gx,nv.gy,nv.gz);
	}
	if(w.anchor!=anchor)
	{	
		Vector vf(w.anchor,anchor);
		vf.rotateWithoutFulcrum_W(w,a);
		anchor=vf.destination();
	}	
	return *this;
}


Vector& Vector::rotateWithoutFulcrum_W(const Vector &w, RNUM a) //+?
{	
	if(!isParallel(*this,w))
	{
		RNUM wl=w.length();
		Vector ew=w/wl;
		RNUM l=length();		
		RNUM zsh=ew&(*this);
		RNUM rsh=sqrt(l*l-zsh*zsh);
		Vector vzsh=ew*zsh;
		Vector vrsh=*this-vzsh;
		a=NormAngle(a);
		RNUM aa=ABS(a);
		int sa=a>0?1:-1;
		while(aa>=PI/2){aa-=PI/2;vrsh=ew*vrsh*sa;}
		if(aa>PI/4){aa-=PI/4; vrsh=((ew*vrsh*sa)+vrsh).e()*rsh;}
		vrsh=(vrsh+(ew*vrsh).e()*rsh*tan(aa)).e()*rsh*sa;
		Vector nv=vrsh+vzsh;
		SetGlobal(nv.gx,nv.gy,nv.gz);
	}
	return *this;
}


Vector& Vector::rotate_X(RNUM a)
{
	if(basis) return rotate_W(basis->i,a);
	return rotate_W(Vector(1,0,0),a);
}
Vector& Vector::rotate_Y(RNUM a)
{
	if(basis) return rotate_W(basis->j,a);
	return rotate_W(Vector(0,1,0),a);
}
Vector& Vector::rotate_Z(RNUM a)
{
	if(basis) return rotate_W(basis->k,a);
	return rotate_W(Vector(0,0,1),a);
}

#ifdef CPPBIKES_USE_TRANGLE
TrAngle Vector::Angle(const Vector &v1, const Vector &v2) 
{
	return TrAngle(v1.e()&v2.e());
}
#else
RNUM Vector::Angle(const Vector &v1, const Vector &v2) 
{
	return arccos(v1.e()&v2.e());
}
#endif
//TAngle Vector::AngleA(const Vector &v) const{ return TAngle(e()&v.e());}

Point Vector::Intersection(const Vector &v) const//+?
{
	if(isParallel(*this,v))  return Point(false);
	Basis b; b.SetOrtoBasis_ByIJ(*this,v);
	RNUM a=Angle(v);
	//v.SetBasis(&b); 		
	Point rp(v.anchor.lx(&b)-v.anchor.ly(&b)/tan(a),0,0,&b,false); rp.SetGlobalBasis(); //!
	return rp;
}

bool Vector::isParallel(const Vector &v1, const Vector &v2) // +
{
	RNUM v1v2=v1.e()&v2.e();
	if(isEqual(ABS(v1v2),1,METRIC_O)) return true;
	return false;
}

RNUM Vector::ParallelDistance(const Vector &v1, const Vector &v2) //+?
{
//	if(!isParallel(v1,v2)) return 0;
    Basis b(v1&&v2.anchor);
    return v2.anchor.ly(&b);
}

Vector& Vector::invert()
{
	anchor=destination();
	(*this)*=-1;
	return *this;
}

/// + + +
RNUM Vector::x()const {/*if(basis)*/ return lx(basis); /*return gx;*/}
RNUM Vector::y()const {/*if(basis)*/ return ly(basis); /*return gy;*/}
RNUM Vector::z()const {/*if(basis)*/ return lz(basis); /*return gz;*/}

RNUM Vector::lx(const Basis *b) const
{
	if(b) return b->i&(*this);
	return gx;
}
RNUM Vector::ly(const Basis *b) const
{
	if(b) return b->j&(*this);
	return gy;
}
RNUM Vector::lz(const Basis *b) const
{
	if(b) return b->k&(*this);
	return gz;
}

RNUM Vector::lx(const Basis &b) const
{
	return b.i&(*this);	
}
RNUM Vector::ly(const Basis &b) const
{
	return b.j&(*this);	
}
RNUM Vector::lz(const Basis &b) const
{
	return b.k&(*this);	
}

Vector& Vector::SetGlobal(RNUM vgx, RNUM vgy, RNUM vgz)
{
	gx=vgx; gy=vgy; gz=vgz;
	return *this;
}

Vector& Vector::SetLocal(RNUM localx, RNUM localy, RNUM localz)
{
	if(basis)
	{
		*this=Vector(localx,localy,localz,anchor,basis);
	}
	else {gx=localx; gy=localy; gz=localz;}
	return *this;
}

Vector& Vector::SetLocalX(RNUM localx)
{
	if(basis)
	{	
		//*this=Vector(localx,y(),z(),anchor,basis);
		*this+=basis->i*(localx-x());
	}else gx=localx;
	return *this;
}

Vector& Vector::SetLocalY(RNUM localy)
{
	if(basis)
	{	
		//*this=Vector(x(),localy,z(),anchor,basis);
		*this+=basis->j*(localy-y());
	}else gy=localy;
	return *this;
}

Vector& Vector::SetLocalZ(RNUM localz)
{
	if(basis)
	{	
		//*this=Vector(x(),y(),localz,anchor,basis);
		*this+=basis->k*(localz-z());
	}else gz=localz;
	return *this;
}


bool Vector::isRightVectors(Vector v1, Vector v2, Vector v3/* =Vector(0,0,1) */)
{
	return ((v1*v2)&v3)>0;
}


RNUM Vector::Lamda()
{
	RNUM xx=x();
	RNUM yy=y();
	return arccos(xx/(sqrt(xx*xx+yy*yy)))*signum(yy);
}

RNUM Vector::Lamda2PI()
{
	RNUM xx=x();
	RNUM yy=y();
	return (yy>0) ? (arccos(xx/(sqrt(xx*xx+yy*yy)))) : (2*PI-arccos(xx/(sqrt(xx*xx+yy*yy))));
}

RNUM Vector::Phi()
{
	return arcsin(z()/length());
}

bool Vector::isTransient() const
{
	return _transient;
}

bool Vector::isNull() const
{
	return _null;
}

Point Vector::RangeIntersection( const Vector &v ) const
{
	Point rp=Intersection(v);
	if(rp.isNull()) return rp;
	Vector v1(anchor,rp);
	RNUM v1tv=v1&e();
	if(v1tv<0||v1tv>this->length()) 
	{
		//rp._null=true;
		return Point(false,rp);
	}else
	{
		RNUM v1v=v1&v.e();
		if(v1v<0||v1v>v.length()) return Point(false,rp);
	}
	return rp;
}


//////////////////////////////////////////////////////////////////////////
//////////////////// BASIS ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Basis::Basis(const Vector &bi,const Vector &bj, const Vector &bk, const Point &bO)
:i(bi),j(bj),k(bk),O(bO), vectors(new List<Vector*>), points(new List<Point*>)
{	
	O.SetGlobalBasis();
	i.SetGlobalBasis().anchor=O;
	j.SetGlobalBasis().anchor=O;
	k.SetGlobalBasis().anchor=O;
}

Basis::Basis(const Basis &b)
:i(b.i),j(b.j),k(b.k),O(b.O), vectors(new List<Vector*>), points(new List<Point*>)
{

}

Basis::~Basis()
{
	RemoveAll();
	delete vectors;
	delete points;
}


void Basis::operator =(const Basis &b)
{
//	RemoveAll(); //?
	i=b.i;
	j=b.j;
	k=b.k;
	O=b.O;
}

//////// extra operators ///////
const Basis& Basis::operator << (Point &p) const {p.SetBasis(this); return *this;}
const Basis& Basis::operator << (Vector &v) const {v.SetBasis(this); return *this;}
Vector Basis::operator [] (Vector &v) const  {return v.inBasis(this);}
Point  Basis::operator [] (const Point &p) const {return p.inBasis(this);}
////////////////////////////////


Basis& Basis::SetOrtoBasis_ByIJ(const Vector &bi, const Vector &bj)
{
//	RemoveAll(); //?
	i=bi;
	j=bj;
	k=i*j;	
	j=k*i;	

	O=bi.anchor; O.SetGlobalBasis();
	i.SetGlobalBasis().normalize().anchor=O;
	j.SetGlobalBasis().normalize().anchor=O;
	k.SetGlobalBasis().normalize().anchor=O;
	return *this;
}

Basis& Basis::SetOrtoBasis_InXY_ByI(const Vector &bi)
{
//	RemoveAll(); //?
	i=bi;
	k=v_gk;
	j=k*i;
	i=j*k;
	i.normalize();
	j.normalize();
	O=bi.anchor;
	i.SetGlobalBasis().anchor=O;
	j.SetGlobalBasis().anchor=O;
	k.SetGlobalBasis().anchor=O;
	return *this;
}

Basis& Basis::SetOrtoBasis_InXY_ByI_l(const Vector &bi)
{
	SetOrtoBasis_InXY_ByI(bi);
	j*=-1;
	k*=-1;
	return *this;
}

Basis& Basis::SetOrtoBasisL_ByIJ(const Vector &bi, const Vector &bj){SetOrtoBasis_ByIJ(bi,bj);k*=-1; return *this;}
Basis& Basis::SetOrtoBasisL_InXY_ByI(const Vector &bi){SetOrtoBasis_InXY_ByI(bi);j*=-1; return *this;}
Basis& Basis::SetO(const Point &pO){O=pO.inGlobalBasis(); i.anchor=O;	j.anchor=O; k.anchor=O; return *this;}
Basis& Basis::SetOrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY){return SetOrtoBasis_ByIJ(Vector(pO,pX),Vector(pO,pY));}
void Basis::Add(Point *p) const
{
	//p->basis=this;//?
	if(!(p->isTransient()))
	{
		if(!points->contains(p)) (*points)+=p;
	}
}
void Basis::Add(Vector *v) const
{	
	//v->basis=this;//?
	if(!(v->isTransient()))
	{
		if(!vectors->contains(v)) (*vectors)+=v;
	}
}
void Basis::Remove(Point *p) const
{
	if(p->basis==this)
	{	
		//p->basis=0;//?
		if(!(p->isTransient()))	points->remove(p);
	}
}
void Basis::Remove(Vector *v) const
{
	if(v->basis==this)
	{	
		//v->basis=0;//?
		if(!(v->isTransient()))	vectors->remove(v);
	}
}
void Basis::RemoveAll() const
{
 	for(int i=0; i<vectors->count(); i++) if((*vectors)[i]->basis==this)/*?*/ (*vectors)[i]->basis=0;
 	for(int i=0; i<points->count(); i++) if((*points)[i]->basis==this)/*?*/ (*points)[i]->basis=0;
 	vectors->clear();
 	points->clear();
}

Basis Bikes::OrtoBasis_ByIJ(const Vector &bi,const Vector &bj){Basis b; b.SetOrtoBasis_ByIJ(bi,bj); return b;}	
Basis Bikes::OrtoBasisL_ByIJ(const Vector &bi, const Vector &bj){Basis b; b.SetOrtoBasisL_ByIJ(bi,bj); return b;}	
Basis Bikes::OrtoBasis_InXY_ByI(const Vector &bi){Basis b; b.SetOrtoBasis_InXY_ByI(bi); return b;}		
Basis Bikes::OrtoBasisL_InXY_ByI(const Vector &bi){Basis b; b.SetOrtoBasisL_InXY_ByI(bi); return b;}	
Basis Bikes::OrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY){Basis b; b.SetOrtoBasis_ByOXY(pO,pX,pY); return b;}	


CylCoord Bikes::ToCylCoord(const Point &p)
{
	CylCoord r;
	r.z=p.z();
	RNUM lx=p.x(), ly=p.y();
	r.r=sqrt(lx*lx+ly*ly);
	r.a=arccos(lx/r.r);
	if(ly<0) r.a*=-1;
	return r;
}

CylCoord Bikes::ToCylCoord_Arc(const Point &p)
{
	CylCoord cc=ToCylCoord(p);
	if(cc.a<0) cc.a+=2*PI;
	return cc;
}

Point Bikes::FromCylCoord_Arc(RNUM a, RNUM r, RNUM z,const Basis *b){return Point(r*cos(a),r*sin(a),z,b);}
//Point FromCylCoord_Arc(TAngle &a, RNUM r, RNUM z,const Basis *b){return Point(r*cos(a),r*sin(a),z,b);}

}