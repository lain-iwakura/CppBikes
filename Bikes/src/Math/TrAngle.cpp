#include <Bikes/Math/TrAngle.h>
#include <Bikes/BMath.h>


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
    getSumAndSet(ang);
    return *this;
}

TrAngle& TrAngle::operator+=( radian ang )
{
    setRad(rad()+ang);
    return *this;
}

TrAngle& TrAngle::operator-=( const TrAngle& ang )
{
    return getDifferenceAndSet(ang);    
}

TrAngle& TrAngle::operator-=( radian ang )
{
    setRad(rad()-ang);
    return *this;
}

TrAngle& TrAngle::operator*=( rnum m )
{
    return getProductAndSet(m);    
}

TrAngle& TrAngle::operator/=( rnum m )
{
    if(m!=0)
        return getProductAndSet(1.0/m);
    return *this;
}

SoftTrAngle TrAngle::operator+( const TrAngle& ang ) const
{
    return getSum(ang);
}

radian TrAngle::operator+( radian ang ) const
{
    return rad() + ang;
}

SoftTrAngle TrAngle::operator-( const TrAngle& ang ) const
{
    return getDifference(ang);
}

radian TrAngle::operator-( radian ang ) const
{
    return rad() - ang;
}

SoftTrAngle TrAngle::operator*( rnum m ) const
{
    return getProduct(m);
}

SoftTrAngle TrAngle::operator/( rnum m ) const
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

degree TrAngle::deg() const
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

tannum TrAngle::tan() const
{
	return sin()/cos();
}

void TrAngle::setTan( tannum tan_ang, ValSign cosSign /*= positiveSign*/ )
{
    rnum c = sqrt(1.0/(1.0 + tan_ang*tan_ang));

    if(cosSign==negativeSign)
        c = -c;

    setCos(c,getSign(c*tan_ang));
}

Bikes::SoftTrAngle TrAngle::getProduct( rnum m ) const
{
    return SoftTrAngle(rad()*m);
}

Bikes::SoftTrAngle TrAngle::getProduct( num n ) const
{
    return getProduct( rnum(n) );
}

TrAngle& TrAngle::getProductAndSet( rnum m )
{
    setRad(rad()*m);
    return *this;
}

TrAngle& TrAngle::getProductAndSet( num n )
{
    return getProductAndSet( rnum(n) );
}


}