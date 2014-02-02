#include <Bikes/Geometry/Vector.h>
#include <Bikes/Geometry/Basis.h>
#include <Bikes/Math/BasicMath.h>

namespace Bikes
{

//=============================================================================
Vector::Vector( rnum globalX /*= 0*/, rnum globalY /*= 0*/, rnum globalZ /*= 0*/ ):
	gx(globalX),
	gy(globalY),
	gz(globalZ)
{
}
//-----------------------------------------------------------------------------
Vector::Vector( rnum localX, rnum localY, rnum localZ, const Basis& b ):
	gx ( b.i.gx*localX + b.j.gx*localY + b.k.gx*localZ ),
	gy ( b.i.gy*localX + b.j.gy*localY + b.k.gy*localZ ),
	gz ( b.i.gz*localX + b.j.gz*localY + b.k.gz*localZ )
{	
}
//-----------------------------------------------------------------------------
Vector::Vector( const Point &p1, const Point &p2 ):
	gx( p2.gx - p1.gx ),
	gy( p2.gy - p1.gy ),
	gz( p2.gz - p1.gz )
{
}
//-----------------------------------------------------------------------------
Vector::Vector( const Vector &v ):
	gx(v.gx),
	gy(v.gy),
	gz(v.gz)
{
	//?
}
//-----------------------------------------------------------------------------
Vector& Vector::operator=( const Vector &v )
{
	gx = v.gx;
	gy = v.gy;
	gz = v.gz;
	return *this;
}
//-----------------------------------------------------------------------------
Vector::~Vector()
{	
}
//=============================================================================
rnum Vector::x() const
{
	return gx;
}
//-----------------------------------------------------------------------------
rnum Vector::x( const Basis &b ) const
{
	return b.i.gx*gx + b.i.gy*gy + b.i.gz*gz;
}
//-----------------------------------------------------------------------------
rnum Vector::x( const Basis *b ) const
{
	if(b)
		return b->i.gx*gx + b->i.gy*gy + b->i.gz*gz;
	return gx;
}
//-----------------------------------------------------------------------------
rnum Vector::y() const
{
	return gy;
}
//-----------------------------------------------------------------------------
rnum Vector::y( const Basis &b ) const
{
	return b.j.gx*gx + b.j.gy*gy + b.j.gz*gz;
}
//-----------------------------------------------------------------------------
rnum Vector::y( const Basis *b ) const
{
	if(b)
		return b->j.gx*gx + b->j.gy*gy + b->j.gz*gz;
	return gy;
}
//-----------------------------------------------------------------------------
rnum Vector::z() const
{
	return gz;
}
//-----------------------------------------------------------------------------
rnum Vector::z( const Basis &b ) const
{
	return b.k.gx*gx + b.k.gy*gy + b.k.gz*gz;
}
//-----------------------------------------------------------------------------
rnum Vector::z( const Basis *b ) const
{
	if(b)
		return b->k.gx*gx + b->k.gy*gy + b->k.gz*gz;
	return gz;
}
//=============================================================================
void Vector::setGlobal( rnum globalX, rnum globalY, rnum globalZ )
{
	gx = globalX;
	gy = globalY;
	gz = globalZ;
}
//-----------------------------------------------------------------------------
void Vector::setLocal( rnum localX, rnum localY, rnum localZ )
{
	setGlobal(localX,localY,localZ);
}
//-----------------------------------------------------------------------------
void Vector::setLocal( rnum localX, rnum localY, rnum localZ, const Basis& b )
{
	gx = b.i.gx*localX + b.j.gx*localY + b.k.gx*localZ;
	gy = b.i.gy*localX + b.j.gy*localY + b.k.gy*localZ;
	gz = b.i.gz*localX + b.j.gz*localY + b.k.gz*localZ;
}
//-----------------------------------------------------------------------------
void Vector::setLocalX( rnum localX )
{
	gx = localX;
}
//-----------------------------------------------------------------------------
void Vector::setLocalX( rnum localX, const Basis& b )
{	
	rnum dx = localX - ( b.i.gx*gx + b.i.gy*gy + b.i.gz*gz );
	gx += b.i.gx*dx; 
	gy += b.i.gy*dx;
	gz += b.i.gz*dx;
}
//-----------------------------------------------------------------------------
void Vector::setLocalY( rnum localY )
{	
	gy = localY;
}
//-----------------------------------------------------------------------------
void Vector::setLocalY( rnum localY, const Basis& b )
{
	rnum dy = localY - ( b.j.gx*gx + b.j.gy*gy + b.j.gz*gz );
	gx += b.j.gx*dy; 
	gy += b.j.gy*dy;
	gz += b.j.gz*dy;
}
//-----------------------------------------------------------------------------
void Vector::setLocalZ( rnum localZ )
{
	gz = localZ;
}
//-----------------------------------------------------------------------------
void Vector::setLocalZ( rnum localZ, const Basis& b )
{
	rnum dz = localZ - ( b.k.gx*gx + b.k.gy*gy + b.k.gz*gz );
	gx += b.k.gx*dz; 
	gy += b.k.gy*dz;
	gz += b.k.gz*dz;
}
//-----------------------------------------------------------------------------
void Vector::normalize()
{
	rnum l = length();
	if(l != 0)
	{
		gx /= l;
		gy /= l;
		gz /= l;
	}
#ifdef PREBIKES_VECTOR_NORMILIZE0
	else
	{
		*this = PREBIKES_VECTOR_NORMILIZE0;
	}
#endif
}
//-----------------------------------------------------------------------------
void Vector::rotate_W( const Vector &w, rnum a )
{
	rnum wl = w.l();
	if(wl != 0)
	{	
		a = normAngle(a);
		rnum cos_a = cos(a);
		rnum sin_a = sqrt(1.0 - cos_a*cos_a);
		if(a < 0)
			sin_a = -sin_a;

		Vector ew(w);
		ew /= wl;		
		Vector vj = ew * (*this);				
		Vector vi = vj * ew;
		vi *= cos_a - 1.0;
		vj *= sin_a - 1.0;
		*this += vi;
		*this += vj;
	}
}
//-----------------------------------------------------------------------------
void Vector::rotate_W( const Vector &w, const TrAngle& a )
{
	rnum wl = w.l();
	if(wl != 0)
	{	
		Vector ew(w);
		ew /= wl;
		Vector vj = ew * (*this);				
		Vector vi = vj * ew;
		vi *= a.cos() - 1.0;
		vj *= a.sin() - 1.0;
		*this += vi;
		*this += vj;
	}
}
//-----------------------------------------------------------------------------
void Vector::rotate_globalX( rnum a )
{
	a = normAngle(a);
	rnum cos_a = cos(a);
	rnum sin_a = sqrt(1.0 - cos_a*cos_a);
	if(a < 0)
		sin_a = -sin_a;

	cos_a -= 1.0;
	sin_a -= 1.0;
	
	rnum dy = gy*cos_a - gz*sin_a;
	rnum dz = gz*cos_a + gy*sin_a;

	gy += dy;
	gz += dz;	
}
//-----------------------------------------------------------------------------
void Vector::rotate_globalY( rnum a )
{
	a = normAngle(a);
	rnum cos_a = cos(a);
	rnum sin_a = sqrt(1.0 - cos_a*cos_a);
	if(a < 0)
		sin_a = -sin_a;

	cos_a -= 1.0;
	sin_a -= 1.0;

	rnum dz = gz*cos_a - gx*sin_a;
	rnum dx = gx*cos_a + gz*sin_a;

	gz += dz;
	gx += dx;	
}
//-----------------------------------------------------------------------------
void Vector::rotate_globalZ( rnum a )
{
	a = normAngle(a);
	rnum cos_a = cos(a);
	rnum sin_a = sqrt(1.0 - cos_a*cos_a);
	if(a < 0)
		sin_a = -sin_a;

	cos_a -= 1.0;
	sin_a -= 1.0;

	rnum dx = gx*cos_a - gy*sin_a;
	rnum dy = gy*cos_a + gx*sin_a;

	gx += dx;
	gy += dy;	
}
//=============================================================================
rnum Vector::length() const
{
	return sqrt( gx*gx + gy*gy + gz*gz);
}
//-----------------------------------------------------------------------------
rnum Vector::l() const
{
	return sqrt( gx*gx + gy*gy + gz*gz);
}
//-----------------------------------------------------------------------------
Vector Vector::e() const
{
	Vector v(gx,gy,gz);
	v.normalize();
	return v;
}
//=============================================================================
Vector Vector::operator+( const Vector &v ) const
{
	return Vector( gx + v.gx, gy + v.gy, gz + v.gz);
}
//-----------------------------------------------------------------------------
Vector Vector::operator-( const Vector &v ) const
{
	return Vector( gx - v.gx, gy - v.gy, gz - v.gz);
}
//-----------------------------------------------------------------------------
Vector Vector::operator*( rnum n ) const
{
	return Vector( gx*n, gy*n, gz*n );
}
//-----------------------------------------------------------------------------
Vector Vector::operator/( rnum n ) const
{
	return Vector( gx/n, gy/n, gz/n);
}
//-----------------------------------------------------------------------------
rnum Vector::operator&( const Vector &v ) const
{
	return v.gx*gx + v.gy*gy + v.gz*gz;
}
//-----------------------------------------------------------------------------
Vector Vector::operator*( const Vector &v ) const
{
	return  Vector(
		gy*v.gz - gz*v.gy,
		gz*v.gx - gx*v.gz,
		gx*v.gy - gy*v.gx
		);
}
//-----------------------------------------------------------------------------
Vector& Vector::operator+=( const Vector &v )
{
	gx += v.gx;
	gy += v.gy;
	gz += v.gz;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator-=( const Vector &v )
{
	gx -= v.gx;
	gy -= v.gy;
	gz -= v.gz;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator*=( rnum n )
{
	gx *= n;
	gy *= n;
	gz *= n;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator/=( rnum n )
{
	gx /= n;
	gy /= n;
	gz /= n;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator*=( const Vector& v ) 
{
	rnum nx = gy*v.gz - gz*v.gy;
	rnum ny = gz*v.gx - gx*v.gz;
	gz      = gx*v.gy - gy*v.gx;
	gx = nx;
	gy = ny;
	return *this;
}
//-----------------------------------------------------------------------------
Vector Vector::operator-() const
{
	return Vector(-gx,-gy,-gz);
}
//-----------------------------------------------------------------------------

bool Vector::isEqual( const Vector&v ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return (v.gx == gx) && (v.gy == gy) && (v.gz == gz);
#else
	return isEqual(v.gx, gx, PREBIKES_VECTOR_EQUAL_EPSILON)  
		&& isEqual(v.gy, gy, PREBIKES_VECTOR_EQUAL_EPSILON) 
		&& isEqual(v.gz, gz, PREBIKES_VECTOR_EQUAL_EPSILON);
#endif
}
//-----------------------------------------------------------------------------
bool Vector::isEqual( const Vector& v, rnum epsilon ) const
{
	return isEqual(v.gx, gx, epsilon)  
		&& isEqual(v.gy, gy, epsilon) 
		&& isEqual(v.gz, gz, epsilon);
}
//-----------------------------------------------------------------------------
bool Vector::operator == ( const Vector &v ) const
{
	return isEqual(v);
}
//-----------------------------------------------------------------------------
bool Vector::operator != ( const Vector &v ) const
{
	return !isEqual(v);
}
//-----------------------------------------------------------------------------
bool Vector::operator == ( rnum l ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return length() == l;
#else
	return isEqual(length(), l, PREBIKES_VECTOR_EQUAL_EPSILON);
#endif
}
//-----------------------------------------------------------------------------
bool Vector::operator != ( rnum l ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return length() != l;
#else
	return !isEqual(length(), l, PREBIKES_VECTOR_EQUAL_EPSILON);
#endif
}
//-----------------------------------------------------------------------------
bool Vector::operator < ( rnum l ) const
{
	return length() < l;
}
//-----------------------------------------------------------------------------
bool Vector::operator <= ( rnum l ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return length() <= l;
#else	
	return length() <= l + PREBIKES_VECTOR_EQUAL_EPSILON;
#endif
}
//-----------------------------------------------------------------------------
bool Vector::operator > ( rnum l ) const
{
	return length() > l;
}
//-----------------------------------------------------------------------------
bool Vector::operator >= ( rnum l ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return length() >= l;
#else	
	return length() >= l - PREBIKES_VECTOR_EQUAL_EPSILON;
#endif
}

//-----------------------------------------------------------------------------




//-----------------------------------------------------------------------------


//=============================================================================

}// <- namespace Bikes;