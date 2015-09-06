#include <Bikes/Geom/Vector.h>
#include <Bikes/Geom/Basis.h>
#include <Bikes/Geom/Point.h>
#include <Bikes/Geom/VectorPair.h>
#include <Bikes/Mathem.h>


namespace Bikes
{
//=============================================================================
Vector::Vector( rnum globalX /*= 0*/, rnum globalY /*= 0*/, rnum globalZ /*= 0*/ ):
	_gx(globalX),
	_gy(globalY),
	_gz(globalZ)
{
}
//-----------------------------------------------------------------------------
Vector::Vector(rnum localX, rnum localY, rnum localZ, const IConstBasis& b) :
	_gx ( b.i()._gx*localX + b.j()._gx*localY + b.k()._gx*localZ ),
	_gy ( b.i()._gy*localX + b.j()._gy*localY + b.k()._gy*localZ ),
	_gz ( b.i()._gz*localX + b.j()._gz*localY + b.k()._gz*localZ )
{	
}
//-----------------------------------------------------------------------------
Vector::Vector( const Point &p1, const Point &p2 ):
	_gx( p2._gx - p1._gx ),
	_gy( p2._gy - p1._gy ),
	_gz( p2._gz - p1._gz )
{
}
//-----------------------------------------------------------------------------
Vector::Vector( const Vector &v ):
	_gx(v._gx),
	_gy(v._gy),
	_gz(v._gz)
{
	//?
}
//-----------------------------------------------------------------------------
Vector& Vector::operator=( const Vector &v )
{
	_gx = v._gx;
	_gy = v._gy;
	_gz = v._gz;
	return *this;
}
//-----------------------------------------------------------------------------
Vector::~Vector()
{	
}
//==============================================================================
rnum& Vector::rx()
{
    return _gx;
}
//-----------------------------------------------------------------------------
rnum& Vector::ry()
{
    return _gy;
}
//-----------------------------------------------------------------------------
rnum& Vector::rz()
{
    return _gz;
}
//==============================================================================
rnum Vector::x() const
{
	return _gx;
}
//-----------------------------------------------------------------------------
rnum Vector::lx(const IConstBasis &b) const
{
    return *this & b.i();
}
//-----------------------------------------------------------------------------
rnum Vector::lx(const IConstBasis *b) const
{
    if (b)
        return lx(*b);
	return _gx;
}
//-----------------------------------------------------------------------------
rnum Vector::y() const
{
	return _gy;
}
//-----------------------------------------------------------------------------
rnum Vector::ly(const IConstBasis &b) const
{
    return *this & b.j();
}
//-----------------------------------------------------------------------------
rnum Vector::ly(const IConstBasis *b) const
{
    if (b)
        return ly(*b);
	return _gy;
}
//-----------------------------------------------------------------------------
rnum Vector::z() const
{
	return _gz;
}
//-----------------------------------------------------------------------------
rnum Vector::lz(const IConstBasis &b) const
{
    return *this & b.k();
}
//-----------------------------------------------------------------------------
rnum Vector::lz(const IConstBasis *b) const
{
	if(b)
		return lz(*b);
	return _gz;
}
//=============================================================================
void Vector::setGlobal( rnum globalX, rnum globalY, rnum globalZ )
{
	_gx = globalX;
	_gy = globalY;
	_gz = globalZ;
}
//-----------------------------------------------------------------------------
void Vector::setLocal(rnum localX, rnum localY, rnum localZ, const IConstBasis& b)
{
    const Vector& i = b.i();
    const Vector& j = b.j();
    const Vector& k = b.k();
	_gx = i._gx*localX + j._gx*localY + k._gx*localZ;
	_gy = i._gy*localX + j._gy*localY + k._gy*localZ;
	_gz = i._gz*localX + j._gz*localY + k._gz*localZ;
}
//-----------------------------------------------------------------------------
void Vector::setLocalX(rnum localX, const IConstBasis& b)
{	
    setProjection(localX, b.i());
}
//-----------------------------------------------------------------------------
void Vector::setLocalY(rnum localY, const IConstBasis& b)
{
    setProjection(localY, b.j());
}
//-----------------------------------------------------------------------------
void Vector::setLocalZ(rnum localZ, const IConstBasis& b)
{
    setProjection(localZ, b.k());
}
//-----------------------------------------------------------------------------
void Vector::setProjection(rnum projectionLength, const Vector& v)
{
    rnum dz = projectionLength - (v._gx*_gx + v._gy*_gy + v._gz*_gz);
    _gx += v._gx*dz;
    _gy += v._gy*dz;
    _gz += v._gz*dz;
}
//-----------------------------------------------------------------------------
void Vector::normalize()
{
	rnum l = length();
	if(l != 0)
	{
		_gx /= l;
		_gy /= l;
		_gz /= l;
	}
#ifdef PREBIKES_VECTOR_NORMILIZE0
	else
	{
		*this = PREBIKES_VECTOR_NORMILIZE0;
	}
#endif
}
//-----------------------------------------------------------------------------
void Vector::setLength( rnum len )
{
	rnum cur_len=length();
	if(cur_len != 0)
	{
		len /= cur_len;
		_gx *= len;
		_gy *= len;
		_gz *= len;
	}
}
//-----------------------------------------------------------------------------
void Vector::scale( rnum scaleFactor )
{
	_gx*=scaleFactor;
	_gy*=scaleFactor;
	_gz*=scaleFactor;
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
		vj *= sin_a;
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
		vj *= a.sin();
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
	
	rnum dy = _gy*cos_a - _gz*sin_a;
	rnum dz = _gz*cos_a + _gy*sin_a;

	_gy += dy;
	_gz += dz;	
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

	rnum dz = _gz*cos_a - _gx*sin_a;
	rnum dx = _gx*cos_a + _gz*sin_a;

	_gz += dz;
	_gx += dx;	
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

	rnum dx = _gx*cos_a - _gy*sin_a;
	rnum dy = _gy*cos_a + _gx*sin_a;

	_gx += dx;
	_gy += dy;	
}
//=============================================================================
rnum Vector::length() const
{
	return sqrt( _gx*_gx + _gy*_gy + _gz*_gz);
}
//-----------------------------------------------------------------------------
rnum Vector::l() const
{
	return sqrt( _gx*_gx + _gy*_gy + _gz*_gz);
}
//-----------------------------------------------------------------------------
Vector Vector::e() const
{
	Vector v(_gx,_gy,_gz);
	v.normalize();
	return v;
}
//-----------------------------------------------------------------------------
bool Vector::isCollinear( const Vector& v2, rnum cos_angleEpsilon ) const
{
	rnum c = ((*this) & v2) / ( length() * v2.length() );
	return c >= cos_angleEpsilon || c <= -cos_angleEpsilon;
}
//-----------------------------------------------------------------------------
rnum Vector::angle( const Vector& v ) const
{
	return arccos( ( v._gx*_gx + v._gy*_gy + v._gz*_gz ) / (length() * v.length()) );
}
//-----------------------------------------------------------------------------
rnum Vector::cosAngle( const Vector& v ) const
{
	return ( v._gx*_gx + v._gy*_gy + v._gz*_gz ) / (length() * v.length());
}
//-----------------------------------------------------------------------------
bool Vector::isEqual( const Vector&v ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return (v._gx == _gx) && (v._gy == _gy) && (v._gz == _gz);
#else
	return isEqual(v._gx, _gx, PREBIKES_VECTOR_EQUAL_EPSILON)  
		&& isEqual(v._gy, _gy, PREBIKES_VECTOR_EQUAL_EPSILON) 
		&& isEqual(v._gz, _gz, PREBIKES_VECTOR_EQUAL_EPSILON);
#endif
}
//-----------------------------------------------------------------------------
bool Vector::isEqual( const Vector& v, rnum epsilon ) const
{
	return Bikes::isEqual(v._gx, _gx, epsilon)  
		&& Bikes::isEqual(v._gy, _gy, epsilon) 
		&& Bikes::isEqual(v._gz, _gz, epsilon);
}
//=============================================================================
Vector Vector::operator+( const Vector &v ) const
{
	return Vector( _gx + v._gx, _gy + v._gy, _gz + v._gz);
}
//-----------------------------------------------------------------------------
Vector Vector::operator-( const Vector &v ) const
{
	return Vector( _gx - v._gx, _gy - v._gy, _gz - v._gz);
}
//-----------------------------------------------------------------------------
Vector Vector::operator*( rnum n ) const
{
	return Vector( _gx*n, _gy*n, _gz*n );
}
//-----------------------------------------------------------------------------
Vector Vector::operator/( rnum n ) const
{
	return Vector( _gx/n, _gy/n, _gz/n);
}
//-----------------------------------------------------------------------------
rnum Vector::operator& ( const Vector &v ) const
{
	return v._gx*_gx + v._gy*_gy + v._gz*_gz;
}
//-----------------------------------------------------------------------------
Vector Vector::operator*( const Vector &v ) const
{
	return  Vector(
		_gy*v._gz - _gz*v._gy,
		_gz*v._gx - _gx*v._gz,
		_gx*v._gy - _gy*v._gx
		);
}
//-----------------------------------------------------------------------------
Vector& Vector::operator+=( const Vector &v )
{
	_gx += v._gx;
	_gy += v._gy;
	_gz += v._gz;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator-=( const Vector &v )
{
	_gx -= v._gx;
	_gy -= v._gy;
	_gz -= v._gz;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator*=( rnum n )
{
	_gx *= n;
	_gy *= n;
	_gz *= n;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator/=( rnum n )
{
	_gx /= n;
	_gy /= n;
	_gz /= n;
	return *this;
}
//-----------------------------------------------------------------------------
Vector& Vector::operator*=( const Vector& v ) 
{
	rnum nx = _gy*v._gz - _gz*v._gy;
	rnum ny = _gz*v._gx - _gx*v._gz;
	_gz      = _gx*v._gy - _gy*v._gx;
	_gx = nx;
	_gy = ny;
	return *this;
}
//-----------------------------------------------------------------------------
Vector Vector::operator-() const
{
	return Vector(-_gx,-_gy,-_gz);
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
bool Vector::operator<( const Vector &v ) const
{
	return length() < v.length();
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
bool Vector::operator<=( const Vector &v ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return length() <= v.length();
#else	
	return length() <= v.length() + PREBIKES_VECTOR_EQUAL_EPSILON;
#endif
}
//-----------------------------------------------------------------------------
bool Vector::operator > ( rnum l ) const
{
	return length() > l;
}
//-----------------------------------------------------------------------------
bool Vector::operator>( const Vector &v ) const
{
	return length() > v.length();
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
bool Vector::operator>=( const Vector &v ) const
{
#ifndef PREBIKES_VECTOR_EQUAL_EPSILON
	return length() >= v.length();
#else	
	return length() >= v.length() - PREBIKES_VECTOR_EQUAL_EPSILON;
#endif
}
//-----------------------------------------------------------------------------
TransientVectorPair Vector::operator&&(const Vector& v) const
{
    return TransientVectorPair(*this, v);
}
//=============================================================================
bool isRightHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 )
{
	return ((v1*v2) & v3) > 0;
}
//-----------------------------------------------------------------------------
bool isLeftHandVectors( const Vector& v1, const Vector& v2, const Vector& v3 )
{
	return ((v1*v2) & v3) < 0;
}
//=============================================================================

}// <- namespace Bikes;