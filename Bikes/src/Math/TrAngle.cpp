#include <Bikes/Math/TrAngle.h>
#include <Bikes/Math/Tools.h>
#include <Bikes/Math/SoftTrAngle.h>


namespace Bikes
{


TrAngle::~TrAngle()
{
}

TrAngle::operator radian() const
{
	return rad();
}

TrAngle& TrAngle::operator=( const TrAngle& ang )
{
	set(ang);
	return *this;
}

TrAngle& TrAngle::operator=( radian ang )
{
	setRad(ang);
	return *this;
}

TrAngle& TrAngle::operator+=( const TrAngle& ang )
{
	setSum(ang);
	return *this;
}

TrAngle& TrAngle::operator+=( radian ang )
{
	setRad(rad()+ang);
	return *this;
}

TrAngle& TrAngle::operator-=( const TrAngle& ang )
{
	setDifference(ang);
	return *this;
}

TrAngle& TrAngle::operator-=( radian ang )
{
	setRad(rad()-ang);
	return *this;
}

TrAngle& TrAngle::operator*=( rnum m )
{
	setProduct(m);
	return *this;
}

TrAngle& TrAngle::operator/=( rnum m )
{
	if(m!=0)
		setProduct(1.0/m);
	return *this;
}

Bikes::SoftTrAngle TrAngle::operator+( const TrAngle& ang ) const
{
	return getSum(ang);
}

Bikes::radian TrAngle::operator+( radian ang ) const
{
	return rad() + ang;
}

Bikes::SoftTrAngle TrAngle::operator-( const TrAngle& ang ) const
{
	return getDifference(ang);
}

Bikes::radian TrAngle::operator-( radian ang ) const
{
	return rad() - ang;
}

Bikes::SoftTrAngle TrAngle::operator*( rnum m ) const
{
	return getProduct(m);
}

Bikes::SoftTrAngle TrAngle::operator/( rnum m ) const
{
	if(m!=0)
		return getProduct(1.0/m);
	return SoftTrAngle(*this);
}

bool TrAngle::operator==( const TrAngle& ang ) const
{
	return isEqual(ang);
}

bool TrAngle::operator==( radian ang ) const
{
	return rad() == ang;
}

bool TrAngle::operator<( const TrAngle& ang ) const
{
	return isLess(ang);
}

bool TrAngle::operator<( radian ang ) const
{
	return rad() < ang;
}

bool TrAngle::operator<=( const TrAngle& ang ) const
{
	return isLessOrEqual(ang);
}

bool TrAngle::operator<=( radian ang ) const
{
	return rad() <= ang;
}

bool TrAngle::operator>( const TrAngle& ang ) const
{
	return isGreater(ang);
}

bool TrAngle::operator>( radian ang ) const
{
	return rad() > ang;
}

bool TrAngle::operator>=( const TrAngle& ang ) const
{
	return isGreaterOrEqual(ang);
}

bool TrAngle::operator>=( radian ang ) const
{
	return rad() >= ang;
}

Bikes::degree TrAngle::deg() const
{
	return RAD_to_DEG(rad());
}

void TrAngle::setDeg( degree ang )
{
	setRad(DEG_to_RAD(ang));
}

void TrAngle::set( sinnum sin_ang, cosnum cos_ang )
{
	setCos(cos_ang,getSign(sin_ang));
}

void TrAngle::set( const TrAngle& ang )
{
	set(ang.sin(),ang.cos());
}

Bikes::tannum TrAngle::tan() const
{
	return sin()/cos();
}


}