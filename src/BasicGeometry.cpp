#include <Bikes/BasicGeometry.h>

namespace Bikes
{


//////////////////////////////////////////////////////////////////////////
////////////////////////// POINT /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

Point::Point(rnum plx, rnum ply, rnum plz, const Basis *b, bool notransient)
{
	_transient=!notransient;
	basis=0;
	gx=plx;
	gy=ply;
	gz=plz;
	replaceGBasis(b);	
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
	if(basis) basis->add(this);
	
}


Point::Point(const Point &p)
{
	_transient=false;
	basis=p.basis; 
	_null=p._null;
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;	
	if(basis) basis->add(this);

}

Point::Point(const Vector &v, bool notransient)
{
	_transient=!notransient;
	basis=0;
	*this=v.destination();
}

Point::~Point()
{
	if(basis) basis->remove(this);
}

void Point::operator = (const Point &p)
{
	//basis=0;
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;	
	_null=p._null;
	setBasis(p.basis);
}

void Point::operator = (const Vector &v)
{
	*this=v.destination();
}


Vector Point::operator && (const Point &p) const {return Vector(*this,p,false);}
Point Point::operator [](const Basis &b) const {return inBasis(&b);}
Point Point::operator [](const Basis *b) const {return inBasis(b);}
Point& Point::operator >>(const Basis &b)  {return setBasis(&b);}
Point& Point::operator >>(const Basis *b)  {return setBasis(b);}	

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



Point& Point::setGlobalBasis()
{
	if(basis) basis->remove(this);
	basis=0;
	return *this;
}

Vector Point::v() const {return Vector(*this,false);} 

Point& Point::setBasis(const Basis *b)
{
	if(basis) basis->remove(this);
	basis=b;
	if(basis) basis->add(this);
	return *this;
}

Point Point::inBasis(const Basis *b) const
{
	Point rp(true,*this,false);
	rp.setBasis(b);
	return rp;
}

Point Point::inGlobalBasis() const
{
	Point rp(true,*this,false);
	rp.setGlobalBasis();
	return rp;
}

Point& Point::replaceGBasis(const Basis *b)
{
	if(basis) basis->remove(this);
	if(b)
	{		
		Vector v(b->i*gx+b->j*gy+b->k*gz);
		gx=v.gx+b->O.gx;
		gy=v.gy+b->O.gy;
		gz=v.gz+b->O.gz;
		b->add(this);
	}
	basis=b;	
	return *this;
}

Point& Point::replaceBasis(const Basis *b)
{	
	if(basis) basis->remove(this);
	if(b)
	{		
		Vector v(b->i*x()+b->j*y()+b->k*z());
		gx=v.gx+b->O.gx;
		gy=v.gy+b->O.gy;
		gz=v.gz+b->O.gz;
		b->add(this);
	} else if(basis)
	{
		setGlobal(x(),y(),z());
	}
	basis=b;	
	return *this;
}

Point Point::inReplacedBasis(const Basis *b) const
{
	Point rp(true,*this,false); rp.replaceBasis(b);
	return rp;
}



Point&  Point::rotate_W(const Vector &w,rnum a)
{	
	if(w.anchor!=*this)
	{	
		Vector pv(w.anchor,*this); pv.rotate_W(w,a);
		*this=pv;
	}
	return *this;
}


Point& Point::rotate_X(rnum a)
{
	if(basis) return rotate_W(basis->i,a);
	return rotate_W(v_gi,a);
}
Point& Point::rotate_Y(rnum a)
{
	if(basis) return rotate_W(basis->j,a);
	return rotate_W(v_gj,a);
}
Point& Point::rotate_Z(rnum a)
{
	if(basis) return rotate_W(basis->k,a);
	return rotate_W(v_gk,a);
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

rnum Point::lx(const Basis *b) const 
{	
	if(b)return (gx - b->O.gx)*(b->i.gx) + (gy - b->O.gy)*(b->i.gy) + (gz - b->O.gz)*(b->i.gz);
	return gx;
}

rnum Point::ly(const Basis *b) const
{
	if(b)return (gx - b->O.gx)*(b->j.gx) + (gy - b->O.gy)*(b->j.gy) + (gz - b->O.gz)*(b->j.gz);
	return gy;
}

rnum Point::lz(const Basis *b) const 
{
	if(b) return (gx - b->O.gx)*(b->k.gx) + (gy - b->O.gy)*(b->k.gy) + (gz - b->O.gz)*(b->k.gz);
	return gz;
}

rnum Point::lx(const Basis &b) const 
{	
	return (gx - b.O.gx)*(b.i.gx) + (gy - b.O.gy)*(b.i.gy) + (gz - b.O.gz)*(b.i.gz);	
}

rnum Point::ly(const Basis &b) const
{
	return (gx - b.O.gx)*(b.j.gx) + (gy - b.O.gy)*(b.j.gy) + (gz - b.O.gz)*(b.j.gz);	
}

rnum Point::lz(const Basis &b) const 
{
	return (gx - b.O.gx)*(b.k.gx) + (gy - b.O.gy)*(b.k.gy) + (gz - b.O.gz)*(b.k.gz);	
}

rnum Point::x() const {return lx(basis);}
rnum Point::y() const {return ly(basis);}
rnum Point::z() const {return lz(basis);}

Point& Point::set(rnum px, rnum py,rnum pz, const Basis *b)
{
	*this=Point(px,py,pz,b,true);
	return *this;
}
Point& Point::setGlobal(rnum pgx, rnum pgy, rnum pgz)
{
	gx=pgx;gy=pgy;gz=pgz;
	return *this;
}
Point& Point::setLocal(rnum localx, rnum localy, rnum localz)
{
	if(basis) *this=Point(localx,localy,localz,basis);	
	else {gx=localx; gy=localy; gz=localz;}
	return *this;
}
Point& Point::setLocalX(rnum localx)
{
	if(basis)
	{
//		*this=Point(localx,y(),z(),basis);
		*this+=basis->i*(localx-x());
	}else gx=localx;	
	return *this;
}
Point& Point::setLocalY(rnum localy)
{
	if(basis)
	{
	//	*this=Point(x(),localy,z(),basis);
		*this+=basis->j*(localy-y());
	}else gy=localy;
	return *this;
}
Point& Point::setLocalZ(rnum localz)
{
	if(basis)
	{
		//*this=Point(x(),y(),localz,basis);
		*this+=basis->k*(localz-z());
	}else gz=localz;	
	return *this;
}


bool Point::isEqual(const Point &p1, const Point &p2, rnum e)
{
	if(e==0) return p1.gx==p2.gx&&p1.gy==p2.gy&&p1.gz==p2.gz;
	return isEqual(p1.gx,p2.gx,e)&&isEqual(p1.gy,p2.gy,e)&&isEqual(p1.gz,p2.gz,e);
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


Vector::Vector(rnum vx, rnum vy, rnum vz, const Point &fp,const Basis *b, bool notransient)
:anchor(true,fp,notransient)
{
	_transient=!notransient;
	basis=0;
	_null=false;
	anchor=fp;
	if(b)
	{
		*this=b->i*vx+b->j*vy+b->k*vz;
		b->add(this); 
	}else
	{
		gx=vx; 
		gy=vy; 
		gz=vz; 
	}
	basis=b;
	anchor.setBasis(b);
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
	setBasis(v.basis);
	_null=v._null;	
}

void Vector::operator = (const Point &p)
{
	gx=p.gx;
	gy=p.gy;
	gz=p.gz;
	anchor=p_gO;
	setGlobalBasis();
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
	if(basis) basis->add(this);
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
	if(basis) basis->add(this);
}

Vector::~Vector()
{
	if(basis) basis->remove(this);
}

Vector Vector::operator +(const Vector &v) const { return Vector(gx+v.gx,gy+v.gy,gz+v.gz,anchor,0,false);}
Vector Vector::operator -(const Vector &v) const { return Vector(gx-v.gx,gy-v.gy,gz-v.gz,anchor,0,false);}
void Vector::operator += (const Vector &v){ gx+=v.gx; gy+=v.gy; gz+=v.gz;}
void Vector::operator -= (const Vector &v){ gx-=v.gx; gy-=v.gy; gz-=v.gz;}
rnum Vector::operator &(const Vector &v)const {return v.gx*gx+v.gy*gy+v.gz*gz;}
Vector Vector::operator *(const Vector &v)const { return Vector(gy*v.gz-gz*v.gy,gz*v.gx-gx*v.gz,gx*v.gy-gy*v.gx,anchor,0,false);}
Vector Vector::operator *(rnum n)const {return Vector(gx*n,gy*n,gz*n,anchor,0,false);}
Vector Vector::operator /(rnum n)const {not0set(n); return Vector(gx/n,gy/n,gz/n,anchor,0,false);}
void Vector::operator *=(rnum n){gx*=n;gy*=n;gz*=n;}
void Vector::operator /=(rnum n){not0set(n); gx/=n; gy/=n; gz/=n;}
bool Vector::operator ==(const Vector &v)const {return (ABS(v.gx-gx)<METRIC_O)&&(ABS(v.gy-gy)<METRIC_O)&&(ABS(v.gz-gz)<METRIC_O);}
bool Vector::operator !=(const Vector &v)const {return !(*this==v);}
Vector Vector::operator -() const {return (*this)*(-1);}
//////// extra operators ///////
Point Vector::operator % (const Vector &v) const {return intersection(v);}
bool Vector::operator || (const Vector &v) const {return isParallel(*this,v);}
bool Vector::operator |=(const Vector &v) const {return isRightVectors(*this,v);}
Basis Vector::operator && (const Vector &v) const {return ortoBasis_ByIJ(*this,v);}
Basis Vector::operator && (const Point &p) const {return ortoBasis_ByIJ(*this,Vector(anchor,p));}
#ifdef BIKES_USE_TRANGLE
TrAngle Vector::operator ^ (const Vector &v) const {return angle(*this,v);}
#else
rnum Vector::operator ^ (const Vector &v) const {return angle(*this,v);}
#endif
Vector Vector::operator [] (const Basis &b) const {return inBasis(&b);}
Vector Vector::operator [] (const Basis *b) const {return inBasis(b);}
Vector& Vector::operator >> (const Basis &b)  {return setBasis(&b);}
Vector& Vector::operator >> (const Basis *b)  {return setBasis(b);}
Vector Vector::operator !() const { return Vector(true,*this,false).invert();}
bool Vector::operator > (const Vector &v) const {return length()>v.length();}
bool Vector::operator < (const Vector &v) const {return length()<v.length();}
////////////////////////////////

Point Vector::destination() const {Point p(anchor.gx+gx,anchor.gy+gy,anchor.gz+gz,0,false); p.setBasis(basis); return p;}
Vector Vector::e() const {return Vector(true,(*this)/length(),false);}
rnum Vector::length() const {return sqrt(gx*gx+gy*gy+gz*gz);}
Vector& Vector::normalize(){*this/=length(); return *this;}

Vector& Vector::setGlobalBasis()
{
	if(basis) basis->remove(this);
 	anchor.setGlobalBasis();
	basis=0;
	return *this;
}

Vector& Vector::setBasis(const Basis *b)
{	
	if(b==basis) return *this;
	if(basis) basis->remove(this); 	
	basis=b;
	if(basis) basis->add(this);
	anchor.setBasis(b);	
	return *this;
}

Vector& Vector::replaceGBasis(const Basis *b) //-!
{
	if(basis){basis->remove(this);}	
	if(b)
	{
		*this=b->i*gx+b->j*gy+b->k*gz;
		b->add(this);
	}
	basis=b;
	anchor.replaceGBasis(b);	
	return *this;
}

Vector& Vector::replaceBasis(const Basis *b) //-!
{
	if(b==basis) return *this; //!	
	if(b)
	{
		*this=b->i*x()+b->j*y()+b->k*z();
		b->add(this);
	}else if(basis)
	{
		setGlobal(x(),y(),z());
	}
	if(basis){basis->remove(this);}
	basis=b;
	anchor.replaceBasis(b);
	return *this;
}

Vector Vector::inBasis(const Basis *b)const {Vector rv(true,*this,false);rv.setBasis(b);return rv;}
Vector Vector::inGlobalBasis()const {Vector rv(true,*this,false);rv.setGlobalBasis();return rv;}
Vector Vector::inReplacedBasis(const Basis *b)const {Vector rv(true,*this,false); rv.replaceBasis(b); return rv;}


Vector& Vector::rotate_W(const Vector &w, rnum a) //+?
{	
	if(!isParallel(*this,w))
	{
		rnum wl=w.length();
		Vector ew=w/wl;
		rnum l=length();		
		rnum zsh=ew&(*this);
		rnum rsh=sqrt(l*l-zsh*zsh);
		Vector vzsh=ew*zsh;
		Vector vrsh=*this-vzsh;
		a=normAngle(a);
		rnum aa=ABS(a);
		int sa=a>0?1:-1;
		aa=normAngle(aa);
		while(aa>=PI/2){aa-=PI/2;vrsh=ew*vrsh*sa;}
		if(aa>PI/4){aa-=PI/4; vrsh=((ew*vrsh*sa)+vrsh).e()*rsh;}
		vrsh=(vrsh+(ew*vrsh).e()*rsh*tan(aa)*sa).e()*rsh;
		Vector nv=vrsh+vzsh;
		setGlobal(nv.gx,nv.gy,nv.gz);
	}
	if(w.anchor!=anchor)
	{	
		Vector vf(w.anchor,anchor);
		vf.rotateWithoutFulcrum_W(w,a);
		anchor=vf.destination();
	}	
	return *this;
}


Vector& Vector::rotateWithoutFulcrum_W(const Vector &w, rnum a) //+?
{	
	if(!isParallel(*this,w))
	{
		rnum wl=w.length();
		Vector ew=w/wl;
		rnum l=length();		
		rnum zsh=ew&(*this);
		rnum rsh=sqrt(l*l-zsh*zsh);
		Vector vzsh=ew*zsh;
		Vector vrsh=*this-vzsh;
		a=normAngle(a);
		rnum aa=ABS(a);
		int sa=a>0?1:-1;
		while(aa>=PI/2){aa-=PI/2;vrsh=ew*vrsh*sa;}
		if(aa>PI/4){aa-=PI/4; vrsh=((ew*vrsh*sa)+vrsh).e()*rsh;}
		vrsh=(vrsh+(ew*vrsh).e()*rsh*tan(aa)).e()*rsh*sa;
		Vector nv=vrsh+vzsh;
		setGlobal(nv.gx,nv.gy,nv.gz);
	}
	return *this;
}


Vector& Vector::rotate_X(rnum a)
{
	if(basis) return rotate_W(basis->i,a);
	return rotate_W(Vector(1,0,0),a);
}
Vector& Vector::rotate_Y(rnum a)
{
	if(basis) return rotate_W(basis->j,a);
	return rotate_W(Vector(0,1,0),a);
}
Vector& Vector::rotate_Z(rnum a)
{
	if(basis) return rotate_W(basis->k,a);
	return rotate_W(Vector(0,0,1),a);
}

#ifdef BIKES_USE_TRANGLE
TrAngle Vector::angle(const Vector &v1, const Vector &v2) 
{
	return TrAngle(v1.e()&v2.e());
}
#else
rnum Vector::angle(const Vector &v1, const Vector &v2) 
{
	return arccos(v1.e()&v2.e());
}
#endif
//TAngle Vector::AngleA(const Vector &v) const{ return TAngle(e()&v.e());}

Point Vector::intersection(const Vector &v) const//+?
{
	if(isParallel(*this,v))  return Point(false);
	Basis b; b.setOrtoBasis_ByIJ(*this,v);
	rnum a=angle(v);
	//v.SetBasis(&b); 		
	Point rp(v.anchor.lx(&b)-v.anchor.ly(&b)/tan(a),0,0,&b,false); rp.setGlobalBasis(); //!
	return rp;
}

bool Vector::isParallel(const Vector &v1, const Vector &v2) // +
{
	rnum v1v2=v1.e()&v2.e();
	if(isEqual(ABS(v1v2),1,METRIC_O)) return true;
	return false;
}

rnum Vector::parallelDistance(const Vector &v1, const Vector &v2) //+?
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
rnum Vector::x()const {/*if(basis)*/ return lx(basis); /*return gx;*/}
rnum Vector::y()const {/*if(basis)*/ return ly(basis); /*return gy;*/}
rnum Vector::z()const {/*if(basis)*/ return lz(basis); /*return gz;*/}

rnum Vector::lx(const Basis *b) const
{
	if(b) return b->i&(*this);
	return gx;
}
rnum Vector::ly(const Basis *b) const
{
	if(b) return b->j&(*this);
	return gy;
}
rnum Vector::lz(const Basis *b) const
{
	if(b) return b->k&(*this);
	return gz;
}

rnum Vector::lx(const Basis &b) const
{
	return b.i&(*this);	
}
rnum Vector::ly(const Basis &b) const
{
	return b.j&(*this);	
}
rnum Vector::lz(const Basis &b) const
{
	return b.k&(*this);	
}

Vector& Vector::setGlobal(rnum vgx, rnum vgy, rnum vgz)
{
	gx=vgx; gy=vgy; gz=vgz;
	return *this;
}

Vector& Vector::setLocal(rnum localx, rnum localy, rnum localz)
{
	if(basis)
	{
		*this=Vector(localx,localy,localz,anchor,basis);
	}
	else {gx=localx; gy=localy; gz=localz;}
	return *this;
}

Vector& Vector::setLocalX(rnum localx)
{
	if(basis)
	{	
		//*this=Vector(localx,y(),z(),anchor,basis);
		*this+=basis->i*(localx-x());
	}else gx=localx;
	return *this;
}

Vector& Vector::setLocalY(rnum localy)
{
	if(basis)
	{	
		//*this=Vector(x(),localy,z(),anchor,basis);
		*this+=basis->j*(localy-y());
	}else gy=localy;
	return *this;
}

Vector& Vector::setLocalZ(rnum localz)
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


bool Vector::isTransient() const
{
	return _transient;
}

bool Vector::isNull() const
{
	return _null;
}

Point Vector::rangeIntersection( const Vector &v ) const
{
	Point rp=intersection(v);
	if(rp.isNull()) return rp;
	Vector v1(anchor,rp);
	rnum v1tv=v1&e();
	if(v1tv<0||v1tv>this->length()) 
	{
		//rp._null=true;
		return Point(false,rp);
	}else
	{
		rnum v1v=v1&v.e();
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
	O.setGlobalBasis();
	i.setGlobalBasis().anchor=O;
	j.setGlobalBasis().anchor=O;
	k.setGlobalBasis().anchor=O;
}

Basis::Basis(const Basis &b)
:i(b.i),j(b.j),k(b.k),O(b.O), vectors(new List<Vector*>), points(new List<Point*>)
{

}

Basis::~Basis()
{
	removeAll();
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
const Basis& Basis::operator << (Point &p) const {p.setBasis(this); return *this;}
const Basis& Basis::operator << (Vector &v) const {v.setBasis(this); return *this;}
Vector Basis::operator [] (Vector &v) const  {return v.inBasis(this);}
Point  Basis::operator [] (const Point &p) const {return p.inBasis(this);}
////////////////////////////////


Basis& Basis::setOrtoBasis_ByIJ(const Vector &bi, const Vector &bj)
{
//	RemoveAll(); //?
	i=bi;
	j=bj;
	k=i*j;	
	j=k*i;	

	O=bi.anchor; O.setGlobalBasis();
	i.setGlobalBasis().normalize().anchor=O;
	j.setGlobalBasis().normalize().anchor=O;
	k.setGlobalBasis().normalize().anchor=O;
	return *this;
}

Basis& Basis::setOrtoBasis_InXY_ByI(const Vector &bi)
{
//	RemoveAll(); //?
	i=bi;
	k=v_gk;
	j=k*i;
	i=j*k;
	i.normalize();
	j.normalize();
	O=bi.anchor;
	i.setGlobalBasis().anchor=O;
	j.setGlobalBasis().anchor=O;
	k.setGlobalBasis().anchor=O;
	return *this;
}

Basis& Basis::setOrtoBasis_InXY_ByI_l(const Vector &bi)
{
	setOrtoBasis_InXY_ByI(bi);
	j*=-1;
	k*=-1;
	return *this;
}

Basis& Basis::setOrtoBasisL_ByIJ(const Vector &bi, const Vector &bj){setOrtoBasis_ByIJ(bi,bj);k*=-1; return *this;}
Basis& Basis::setOrtoBasisL_InXY_ByI(const Vector &bi){setOrtoBasis_InXY_ByI(bi);j*=-1; return *this;}
Basis& Basis::setO(const Point &pO){O=pO.inGlobalBasis(); i.anchor=O;	j.anchor=O; k.anchor=O; return *this;}
Basis& Basis::setOrtoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY){return setOrtoBasis_ByIJ(Vector(pO,pX),Vector(pO,pY));}
void Basis::add(Point *p) const
{
	//p->basis=this;//?
	if(!(p->isTransient()))
	{
		if(!points->contains(p)) (*points)+=p;
	}
}
void Basis::add(Vector *v) const
{	
	//v->basis=this;//?
	if(!(v->isTransient()))
	{
		if(!vectors->contains(v)) (*vectors)+=v;
	}
}
void Basis::remove(Point *p) const
{
	if(p->basis==this)
	{	
		//p->basis=0;//?
		if(!(p->isTransient()))	points->remove(p);
	}
}
void Basis::remove(Vector *v) const
{
	if(v->basis==this)
	{	
		//v->basis=0;//?
		if(!(v->isTransient()))	vectors->remove(v);
	}
}
void Basis::removeAll() const
{
 	for(int i=0; i<vectors->count(); i++) if((*vectors)[i]->basis==this)/*?*/ (*vectors)[i]->basis=0;
 	for(int i=0; i<points->count(); i++) if((*points)[i]->basis==this)/*?*/ (*points)[i]->basis=0;
 	vectors->clear();
 	points->clear();
}

Basis ortoBasis_ByIJ(const Vector &bi,const Vector &bj){Basis b; b.setOrtoBasis_ByIJ(bi,bj); return b;}
Basis ortoBasisL_ByIJ(const Vector &bi, const Vector &bj){Basis b; b.setOrtoBasisL_ByIJ(bi,bj); return b;}
Basis ortoBasis_InXY_ByI(const Vector &bi){Basis b; b.setOrtoBasis_InXY_ByI(bi); return b;}
Basis ortoBasisL_InXY_ByI(const Vector &bi){Basis b; b.setOrtoBasisL_InXY_ByI(bi); return b;}
Basis ortoBasis_ByOXY(const Point &pO, const Point &pX, const Point &pY){Basis b; b.setOrtoBasis_ByOXY(pO,pX,pY); return b;}


CylindricalPoint toCylindricalPoint(const Point &p)
{
	CylindricalPoint r;
	r.z=p.z();
	rnum lx=p.x(), ly=p.y();
	r.r=sqrt(lx*lx+ly*ly);
	r.a=arccos(lx/r.r);
	if(ly<0) r.a*=-1;
	return r;
}

CylindricalPoint toCylindricalPoint_Arc(const Point &p)
{
	CylindricalPoint cc=toCylindricalPoint(p);
	if(cc.a<0) cc.a+=2*PI;
	return cc;
}

Point fromCylindricalPoint_Arc(rnum a, rnum r, rnum z,const Basis *b){return Point(r*cos(a),r*sin(a),z,b);}
//Point FromCylCoord_Arc(TAngle &a, rnum r, rnum z,const Basis *b){return Point(r*cos(a),r*sin(a),z,b);}

}
