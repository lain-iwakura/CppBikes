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

TrAngle& TrAngle::operator=( const HardTrAngle& ang )
{
    return *this = static_cast<const TrAngle& >(ang);
}

TrAngle& TrAngle::operator=( const SoftTrAngle& ang )
{
    return *this = static_cast<const TrAngle& >(ang);
}

TrAngle& TrAngle::operator=( radian ang )
{
    setRad(ang);
    return *this;
}


TrAngle& TrAngle::operator+=( radian ang )
{
    setRad(rad()+ang);
    return *this;
}

TrAngle& TrAngle::operator+=( const HardTrAngle& ang )
{
    return *this += static_cast<const TrAngle& >(ang);
}

TrAngle& TrAngle::operator+=( const SoftTrAngle& ang )
{
    return *this += static_cast<const TrAngle& >(ang);
}



TrAngle& TrAngle::operator-=( radian ang )
{
    setRad(rad()-ang);
    return *this;
}

TrAngle& TrAngle::operator-=( const HardTrAngle& ang )
{
    return *this -= static_cast<const TrAngle& >(ang);
}

TrAngle& TrAngle::operator-=( const SoftTrAngle& ang )
{
    return *this -= static_cast<const TrAngle& >(ang);
}


TrAngle& TrAngle::operator*=( rnum m )
{
    setRad(rad()*m);
    return *this;
}

TrAngle& TrAngle::operator*=( lnum n )
{
    return *this *= rnum(n);
}

TrAngle& TrAngle::operator/=( rnum m )
{
    if(m!=0)
        return *this *= 1.0/m;
    return *this;
}

TrAngle& TrAngle::operator/=( lnum n )
{
    return *this /= rnum(n);
}

SoftTrAngle TrAngle::operator+( const TrAngle& ang ) const
{
    SoftTrAngle r(*this);
    return r += ang;
}

radian TrAngle::operator+( radian ang ) const
{
    return rad() + ang;
}

Bikes::SoftTrAngle TrAngle::operator+( const HardTrAngle& ang ) const
{
    SoftTrAngle r(*this);
    return r += ang;
}

Bikes::SoftTrAngle TrAngle::operator+( const SoftTrAngle& ang ) const
{
    SoftTrAngle r(ang);
    return r += *this;
}

SoftTrAngle TrAngle::operator-( const TrAngle& ang ) const
{
    SoftTrAngle r(*this);
    return r -= ang;
}

radian TrAngle::operator-( radian ang ) const
{
    return rad() - ang;
}

Bikes::SoftTrAngle TrAngle::operator-( const HardTrAngle& ang ) const
{
    SoftTrAngle r(*this);
    return r -= ang;
}

Bikes::SoftTrAngle TrAngle::operator-( const SoftTrAngle& ang ) const
{
    SoftTrAngle r(ang);
    return (r -= *this).setNegative();
}


SoftTrAngle TrAngle::operator*( rnum m ) const
{
    SoftTrAngle r(*this);
    return r *= m;
}

Bikes::SoftTrAngle TrAngle::operator*( lnum n ) const
{
    SoftTrAngle r(*this);
    return r *= n;
}

SoftTrAngle TrAngle::operator/( rnum m ) const
{
    SoftTrAngle r(*this);
    return r /= m;    
}

Bikes::SoftTrAngle TrAngle::operator/( lnum n ) const
{
    SoftTrAngle r(*this);
    return r /= n;    
}

bool TrAngle::operator==( const TrAngle& ang ) const
{
    return rad() == ang.rad();
}

bool TrAngle::operator==( radian ang ) const
{
    return rad() == ang;
}

bool TrAngle::operator<( const TrAngle& ang ) const
{
    return rad() < ang.rad();
}

bool TrAngle::operator<( radian ang ) const
{
    return rad() < ang;
}

bool TrAngle::operator<=( const TrAngle& ang ) const
{
    return rad() <= ang.rad();
}

bool TrAngle::operator<=( radian ang ) const
{
    return rad() <= ang;
}


bool TrAngle::operator>( const TrAngle& ang ) const
{
    return rad() > ang.rad();
}

bool TrAngle::operator>( radian ang ) const
{
    return rad() > ang;
}

bool TrAngle::operator>=( const TrAngle& ang ) const
{
    return rad() >= ang.rad();
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

SoftTrAngle TrAngle::operator-() const
{
    SoftTrAngle r(*this);
    return r.setNegative();
}




}