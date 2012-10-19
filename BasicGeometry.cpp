#include "BasicGeometry.h"


//////////////////////////////////////////////////////////////////////////
////////////////////////// POINT /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Point::Point(TMETRIC plx, TMETRIC ply, TMETRIC plz, const Basis *b, bool notransient)
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



Point&  Point::Rotate_W(const Vector &w,TAMETRIC a)
{	
	if(w.fulcrum!=*this)
	{	
		Vector pv(w.fulcrum,*this); pv.rotate_W(w,a);
		*this=pv;
	}
	return *this;
}


Point& Point::Rotate_X(TAMETRIC a)
{
	if(basis) return Rotate_W(basis->i,a);
	return Rotate_W(v_gi,a);
}
Point& Point::Rotate_Y(TAMETRIC a)
{
	if(basis) return Rotate_W(basis->j,a);
	return Rotate_W(v_gj,a);
}
Point& Point::Rotate_Z(TAMETRIC a)
{
	if(basis) return Rotate_W(basis->k,a);
	return Rotate_W(v_gk,a);
}



bool Point::operator ==(const Point &p) const
{
	if(Abs(p.gx-gx)<TMETRIC_O&&Abs(p.gy-gy)<TMETRIC_O&&Abs(p.gz-gz)<TMETRIC_O) return true; 
	return false;
}

bool Point::operator !=(const Point &p) const
{
	return !(*this==p);
}

TMETRIC Point::lx(const Basis *b) const {if(b) return (b->O&&*this)&b->i; return gx;}
TMETRIC Point::ly(const Basis *b) const {if(b) return (b->O&&*this)&b->j; return gy;}
TMETRIC Point::lz(const Basis *b) const {if(b) return (b->O&&*this)&b->k; return gz;}
TMETRIC Point::x() const {return lx(basis);}
TMETRIC Point::y() const {return ly(basis);}
TMETRIC Point::z() const {return lz(basis);}

Point& Point::Set(TMETRIC px, TMETRIC py,TMETRIC pz, const Basis *b)
{
	*this=Point(px,py,pz,b,true);
	return *this;
}
Point& Point::SetGlobal(TMETRIC pgx, TMETRIC pgy, TMETRIC pgz)
{
	gx=pgx;gy=pgy;gz=pgz;
	return *this;
}
Point& Point::SetLocal(TMETRIC localx, TMETRIC localy, TMETRIC localz)
{
	if(basis) *this=Point(localx,localy,localz,basis);	
	else {gx=localx; gy=localy; gz=localz;}
	return *this;
}
Point& Point::SetLocalX(TMETRIC localx)
{
	if(basis)
	{
//		*this=Point(localx,y(),z(),basis);
		*this+=basis->i*(localx-x());
	}else gx=localx;	
	return *this;
}
Point& Point::SetLocalY(TMETRIC localy)
{
	if(basis)
	{
	//	*this=Point(x(),localy,z(),basis);
		*this+=basis->j*(localy-y());
	}else gy=localy;
	return *this;
}
Point& Point::SetLocalZ(TMETRIC localz)
{
	if(basis)
	{
		//*this=Point(x(),y(),localz,basis);
		*this+=basis->k*(localz-z());
	}else gz=localz;	
	return *this;
}


bool Point::isEqual(const Point &p1, const Point &p2, TMETRIC e)
{
	if(e==0) return p1.gx==p2.gx&&p1.gy==p2.gy&&p1.gz==p2.gz;
	return isEqual(p1.gx,p2.gx,e)&&isEqual(p1.gy,p2.gy,e)&&isEqual(p1.gz,p2.gz,e);
}


TMETRIC Point::PolarR() const
{
	TMETRIC px=x();
	TMETRIC py=y();
	return sqrt(px*px+py*py);
}

TAMETRIC Point::PolarAlpha() const
{
	TMETRIC px=x();
	TMETRIC py=y();
	TMETRIC l=sqrt(px*px+py*py);
	TAMETRIC a=arccos(px/l);
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


Vector::Vector(TMETRIC vx, TMETRIC vy, TMETRIC vz, const Point &fp,const Basis *b, bool notransient)
:fulcrum(true,fp,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=false;
	fulcrum=fp;
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
	fulcrum.SetBasis(b);
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
	fulcrum=v.fulcrum;
	SetBasis(v.basis);
	_null=v._null;	
}

Vector::Vector(bool NotNull, const Vector &v, bool notransient)
:fulcrum(true,v.fulcrum,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=!NotNull;
	gx=v.gx;
	gy=v.gy;
	gz=v.gz;
//	fulcrum=v.fulcrum;
	basis=v.basis;
	if(basis) basis->Add(this);
}

Vector::Vector(const Point &p,bool notransient)
:fulcrum(0,0,0,0,notransient)
{
	_transient=!notransient;
	basis=0;
	gx=p.gx; gy=p.gy; gz=p.gz; 	
	_null=p.isNull();
}

Vector::Vector(const Point &p1, const Point &p2,const Basis *b, bool notransient)
:fulcrum(true,p1,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=false;
//	fulcrum=p1; 
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

Vector Vector::operator +(const Vector &v) const { return Vector(gx+v.gx,gy+v.gy,gz+v.gz,fulcrum,0,false);}
Vector Vector::operator -(const Vector &v) const { return Vector(gx-v.gx,gy-v.gy,gz-v.gz,fulcrum,0,false);}
void Vector::operator += (const Vector &v){ gx+=v.gx; gy+=v.gy; gz+=v.gz;}
void Vector::operator -= (const Vector &v){ gx-=v.gx; gy-=v.gy; gz-=v.gz;}
TMETRIC Vector::operator &(const Vector &v)const {return v.gx*gx+v.gy*gy+v.gz*gz;}
Vector Vector::operator *(const Vector &v)const { return Vector(gy*v.gz-gz*v.gy,gz*v.gx-gx*v.gz,gx*v.gy-gy*v.gx,fulcrum,0,false);}
Vector Vector::operator *(TMETRIC n)const {return Vector(gx*n,gy*n,gz*n,fulcrum,0,false);}
Vector Vector::operator /(TMETRIC n)const {not0set(n); return Vector(gx/n,gy/n,gz/n,fulcrum,0,false);}
void Vector::operator *=(TMETRIC n){gx*=n;gy*=n;gz*=n;}
void Vector::operator /=(TMETRIC n){not0set(n); gx/=n; gy/=n; gz/=n;}
bool Vector::operator ==(const Vector &v)const {return (Abs(v.gx-gx)<TMETRIC_O)&&(Abs(v.gy-gy)<TMETRIC_O)&&(Abs(v.gz-gz)<TMETRIC_O);}
bool Vector::operator !=(const Vector &v)const {return !(*this==v);}
Vector Vector::operator -() const {return (*this)*(-1);}
//////// extra operators ///////
Point Vector::operator % (const Vector &v) const {return Intersection(v);}
bool Vector::operator || (const Vector &v) const {return isParallel(*this,v);}
bool Vector::operator |=(const Vector &v) const {return isRightVectors(*this,v);}
Basis Vector::operator && (const Vector &v) const {return OrtoBasis_ByIJ(*this,v);}
Basis Vector::operator && (const Point &p) const {return OrtoBasis_ByIJ(*this,Vector(fulcrum,p));}
TAMETRIC Vector::operator ^ (const Vector &v) const {return Angle(*this,v);}
Vector Vector::operator [] (const Basis &b) const {return inBasis(&b);}
Vector Vector::operator [] (const Basis *b) const {return inBasis(b);}
Vector& Vector::operator >> (const Basis &b)  {return SetBasis(&b);}
Vector& Vector::operator >> (const Basis *b)  {return SetBasis(b);}
Vector Vector::operator !() const { return Vector(true,*this,false).invert();}
bool Vector::operator > (const Vector &v) const {return length()>v.length();}
bool Vector::operator < (const Vector &v) const {return length()<v.length();}
////////////////////////////////

Point Vector::destination() const {Point p(fulcrum.gx+gx,fulcrum.gy+gy,fulcrum.gz+gz,0,false); p.SetBasis(basis); return p;}
Vector Vector::e() const {return Vector(true,(*this)/length(),false);}
TMETRIC Vector::length() const {return sqrt(gx*gx+gy*gy+gz*gz);}
Vector& Vector::normalize(){*this/=length(); return *this;}

Vector& Vector::SetGlobalBasis()
{
	if(basis) basis->Remove(this);
 	fulcrum.SetGlobalBasis();
	basis=0;
	return *this;
}

Vector& Vector::SetBasis(const Basis *b)
{	
	if(b==basis) return *this;
	if(basis) basis->Remove(this); 	
	basis=b;
	if(basis) basis->Add(this);
	fulcrum.SetBasis(b);	
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
	fulcrum.ReplaceGBasis(b);	
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
	fulcrum.ReplaceBasis(b);
	return *this;
}

Vector Vector::inBasis(const Basis *b)const {Vector rv(true,*this,false);rv.SetBasis(b);return rv;}
Vector Vector::inGlobalBasis()const {Vector rv(true,*this,false);rv.SetGlobalBasis();return rv;}
Vector Vector::inReplacedBasis(const Basis *b)const {Vector rv(true,*this,false); rv.ReplaceBasis(b); return rv;}


Vector& Vector::rotate_W(const Vector &w, TAMETRIC a) //+?
{	
	if(!isParallel(*this,w))
	{
		TMETRIC wl=w.length();
		Vector ew=w/wl;
		TMETRIC l=length();		
		TMETRIC zsh=ew&(*this);
		TMETRIC rsh=sqrt(l*l-zsh*zsh);
		Vector vzsh=ew*zsh;
		Vector vrsh=*this-vzsh;
		a=NormAngle(a);
		TAMETRIC aa=Abs(a);
		int sa=a>0?1:-1;
		aa=NormAngle(aa);
		while(aa>=PI/2){aa-=PI/2;vrsh=ew*vrsh*sa;}
		if(aa>PI/4){aa-=PI/4; vrsh=((ew*vrsh*sa)+vrsh).e()*rsh;}
		vrsh=(vrsh+(ew*vrsh).e()*rsh*tan(aa)*sa).e()*rsh;
		Vector nv=vrsh+vzsh;
		SetGlobal(nv.gx,nv.gy,nv.gz);
	}
	if(w.fulcrum!=fulcrum)
	{	
		Vector vf(w.fulcrum,fulcrum);
		vf.rotateWithoutFulcrum_W(w,a);
		fulcrum=vf.destination();
	}	
	return *this;
}


Vector& Vector::rotateWithoutFulcrum_W(const Vector &w, TAMETRIC a) //+?
{	
	if(!isParallel(*this,w))
	{
		TMETRIC wl=w.length();
		Vector ew=w/wl;
		TMETRIC l=length();		
		TMETRIC zsh=ew&(*this);
		TMETRIC rsh=sqrt(l*l-zsh*zsh);
		Vector vzsh=ew*zsh;
		Vector vrsh=*this-vzsh;
		a=NormAngle(a);
		TAMETRIC aa=Abs(a);
		int sa=a>0?1:-1;
		while(aa>=PI/2){aa-=PI/2;vrsh=ew*vrsh*sa;}
		if(aa>PI/4){aa-=PI/4; vrsh=((ew*vrsh*sa)+vrsh).e()*rsh;}
		vrsh=(vrsh+(ew*vrsh).e()*rsh*tan(aa)).e()*rsh*sa;
		Vector nv=vrsh+vzsh;
		SetGlobal(nv.gx,nv.gy,nv.gz);
	}
	return *this;
}


Vector& Vector::rotate_X(TAMETRIC a)
{
	if(basis) return rotate_W(basis->i,a);
	return rotate_W(Vector(1,0,0),a);
}
Vector& Vector::rotate_Y(TAMETRIC a)
{
	if(basis) return rotate_W(basis->j,a);
	return rotate_W(Vector(0,1,0),a);
}
Vector& Vector::rotate_Z(TAMETRIC a)
{
	if(basis) return rotate_W(basis->k,a);
	return rotate_W(Vector(0,0,1),a);
}


TAMETRIC Vector::Angle(const Vector &v1, const Vector &v2) 
{
//	if(v1.gx==0&&v1.gy==0&&v1.gz==0) return 0;
//	if(v2.gx==0&&v2.gy==0&&v2.gz==0) return 0;
	return arccos(v1.e()&v2.e());
}
//TAngle Vector::AngleA(const Vector &v) const{ return TAngle(e()&v.e());}

Point Vector::Intersection(const Vector &v) const//+?
{
	if(isParallel(*this,v))  return Point(false);
	Basis b; b.SetOrtoBasis_ByIJ(*this,v);
	TAMETRIC a=Angle(v);
	//v.SetBasis(&b); 		
	Point rp(v.fulcrum.lx(&b)-v.fulcrum.ly(&b)/tan(a),0,0,&b,false); rp.SetGlobalBasis(); //!
	return rp;
}

bool Vector::isParallel(const Vector &v1, const Vector &v2) // +
{
	TMETRIC v1v2=v1.e()&v2.e();
	if(isEqual(Abs(v1v2),1,TMETRIC_O)) return true;
	return false;
}

TMETRIC Vector::ParallelDistance(const Vector &v1, const Vector &v2) //+?
{
//	if(!isParallel(v1,v2)) return 0;
    Basis b(v1&&v2.fulcrum);
    return v2.fulcrum.ly(&b);
}

Vector& Vector::invert()
{
	fulcrum=destination();
	(*this)*=-1;
	return *this;
}

/// + + +
TMETRIC Vector::x()const {return lx(basis);}
TMETRIC Vector::y()const {return ly(basis);}
TMETRIC Vector::z()const {return lz(basis);}

TMETRIC Vector::lx(const Basis *b) const
{
	if(b)	return b->i&(*this);
	return gx;
}
TMETRIC Vector::ly(const Basis *b) const
{
	if(b)	return b->j&(*this);
	return gy;
}
TMETRIC Vector::lz(const Basis *b) const
{
	if(b)	return b->k&(*this);
	return gz;
}

Vector& Vector::SetGlobal(TMETRIC vgx, TMETRIC vgy, TMETRIC vgz)
{
	gx=vgx; gy=vgy; gz=vgz;
	return *this;
}

Vector& Vector::SetLocal(TMETRIC localx, TMETRIC localy, TMETRIC localz)
{
	if(basis)
	{
		*this=Vector(localx,localy,localz,fulcrum,basis);
	}
	else {gx=localx; gy=localy; gz=localz;}
	return *this;
}

Vector& Vector::SetLocalX(TMETRIC localx)
{
	if(basis)
	{	
		//*this=Vector(localx,y(),z(),fulcrum,basis);
		*this+=basis->i*(localx-x());
	}else gx=localx;
	return *this;
}

Vector& Vector::SetLocalY(TMETRIC localy)
{
	if(basis)
	{	
		//*this=Vector(x(),localy,z(),fulcrum,basis);
		*this+=basis->j*(localy-y());
	}else gy=localy;
	return *this;
}

Vector& Vector::SetLocalZ(TMETRIC localz)
{
	if(basis)
	{	
		//*this=Vector(x(),y(),localz,fulcrum,basis);
		*this+=basis->k*(localz-z());
	}else gz=localz;
	return *this;
}


bool Vector::isRightVectors(Vector v1, Vector v2, Vector v3/* =Vector(0,0,1) */)
{
	return ((v1*v2)&v3)>0;
}


TAMETRIC Vector::Lamda()
{
	TMETRIC xx=x();
	TMETRIC yy=y();
	return arccos(xx/(sqrt(xx*xx+yy*yy)))*signum(yy);
}

TAMETRIC Vector::Lamda2PI()
{
	TMETRIC xx=x();
	TMETRIC yy=y();
	return (yy>0) ? (arccos(xx/(sqrt(xx*xx+yy*yy)))) : (2*PI-arccos(xx/(sqrt(xx*xx+yy*yy))));
}

TAMETRIC Vector::Phi()
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
	Vector v1(fulcrum,rp);
	TMETRIC v1tv=v1&e();
	if(v1tv<0||v1tv>this->length()) 
	{
		//rp._null=true;
		return Point(false,rp);
	}else
	{
		TMETRIC v1v=v1&v.e();
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
	i.SetGlobalBasis().fulcrum=O;
	j.SetGlobalBasis().fulcrum=O;
	k.SetGlobalBasis().fulcrum=O;
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

	O=bi.fulcrum; O.SetGlobalBasis();
	i.SetGlobalBasis().normalize().fulcrum=O;
	j.SetGlobalBasis().normalize().fulcrum=O;
	k.SetGlobalBasis().normalize().fulcrum=O;
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
	O=bi.fulcrum;
	i.SetGlobalBasis().fulcrum=O;
	j.SetGlobalBasis().fulcrum=O;
	k.SetGlobalBasis().fulcrum=O;
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
Basis& Basis::SetO(const Point &pO){O=pO.inGlobalBasis(); i.fulcrum=O;	j.fulcrum=O; k.fulcrum=O; return *this;}
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

Basis OrtoBasis_ByIJ(const Vector &bi,const Vector &bj){Basis b; b.SetOrtoBasis_ByIJ(bi,bj); return b;}	
Basis OrtoBasisL_ByIJ(const Vector &bi, const Vector &bj){Basis b; b.SetOrtoBasisL_ByIJ(bi,bj); return b;}	
Basis OrtoBasis_InXY_ByI(const Vector &bi){Basis b; b.SetOrtoBasis_InXY_ByI(bi); return b;}		
Basis OrtoBasisL_InXY_ByI(const Vector &bi){Basis b; b.SetOrtoBasisL_InXY_ByI(bi); return b;}	
Basis OrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY){Basis b; b.SetOrtoBasis_ByOXY(pO,pX,pY); return b;}	


CylCoord ToCylCoord(const Point &p)
{
	CylCoord r;
	r.z=p.z();
	TMETRIC lx=p.x(), ly=p.y();
	r.r=sqrt(lx*lx+ly*ly);
	r.a=arccos(lx/r.r);
	if(ly<0) r.a*=-1;
	return r;
}

CylCoord ToCylCoord_Arc(const Point &p)
{
	CylCoord cc=ToCylCoord(p);
	if(cc.a<0) cc.a+=2*PI;
	return cc;
}

Point FromCylCoord_Arc(TAMETRIC a, TMETRIC r, TMETRIC z,const Basis *b){return Point(r*cos(a),r*sin(a),z,b);}
//Point FromCylCoord_Arc(TAngle &a, TMETRIC r, TMETRIC z,const Basis *b){return Point(r*cos(a),r*sin(a),z,b);}
