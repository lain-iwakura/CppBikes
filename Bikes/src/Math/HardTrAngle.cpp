#include <Bikes/Math/HardTrAngle.h>
#include <Bikes/BMath.h>


namespace Bikes
{

HardTrAngle::HardTrAngle():
    _sin(0.0),
    _cos(1.0),
    _rad(0.0)
{
}

HardTrAngle::HardTrAngle( radian ang )
{
    setRad(ang);
}

HardTrAngle::HardTrAngle( cosnum cos_ang, ValSign sinSign )
{
    setCos(cos_ang,sinSign);
}

Bikes::sinnum HardTrAngle::sin() const
{
    return _sin;
}

Bikes::cosnum HardTrAngle::cos() const
{
    return _cos;
}

Bikes::radian HardTrAngle::rad() const
{
    return _rad;
}

HardTrAngle& HardTrAngle::operator=( const TrAngle& ang )
{
    _sin = ang.sin();
    _cos = ang.cos();
    _rad = ang.rad();
    return *this;
}

void HardTrAngle::setRad( radian ang )
{
    _rad = ang;
    _cos = ::cos(ang);
    _sin = sqrt(1.0 - _cos*_cos);
    if( normAngle(_rad) < 0 )
        _sin = -_sin;
}

void HardTrAngle::setSin( sinnum sin_ang, ValSign cosSign /*= positiveSign*/ )
{
    _sin = inRange(sin_ang, -1.0, 1.0);
    _cos = sqrt(1.0 - _sin*_sin);
    
    if( cosSign == negativeSign )
        _cos = -_cos;

    _rad = acos(_cos);

    if( _sin < 0 )
        _rad = - _rad;
}

void HardTrAngle::setCos( sinnum cos_ang, ValSign sinSign /*= positiveSign*/ )
{
    _cos = inRange(cos_ang, -1.0, 1.0);
    _sin = sqrt(1.0 - _cos*_cos);
    _rad = acos(_cos);

    if(sinSign == negativeSign)
    {
        _sin = -_sin;
        _rad = -_rad;
    }    
}

void HardTrAngle::setTan( tannum tan_ang, ValSign cosSign /*= positiveSign*/ )
{
    rnum cc = 1.0/(1.0 + tan_ang*tan_ang);
    _cos = sqrt(cc);
    _sin = sqrt(1.0 - cc);
    
    if(cosSign == negativeSign)
        _cos = -_cos;
    
    _rad = acos(_cos);
    
    if( (tan_ang < 0) == (_cos > 0) )
    {
        _sin = -_sin;
        _rad = -_rad;
    }
}

HardTrAngle& HardTrAngle::operator+=( const TrAngle& ang )
{
    _rad += ang.rad();
    
    rnum s = ang.sin();
    rnum c = ang.cos();
    rnum save_sin=_sin;

    _sin = _sin*c + _cos*s;
    _cos = _cos*c - save_sin*s;

    return *this;
}


HardTrAngle& HardTrAngle::operator-=( const TrAngle& ang )
{
    _rad -= ang.rad();

    rnum s = ang.sin();
    rnum c = ang.cos();
    rnum save_sin=_sin;

    _sin = _sin*c - _cos*s;
    _cos = _cos*c + save_sin*s;

    return *this;
}


HardTrAngle& HardTrAngle::operator*=( rnum m )
{    
    setRad(m*_rad);
    return *this;
}


HardTrAngle& HardTrAngle::setNegative()
{
    _rad = -_rad;
    _sin = -_sin;
    return *this;
}

HardTrAngle* HardTrAngle::clone() const
{
    return new HardTrAngle(*this);
}

}