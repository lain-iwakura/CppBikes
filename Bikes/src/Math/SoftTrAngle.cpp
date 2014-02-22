#include <Bikes/Math/SoftTrAngle.h>
#include <Bikes/BMath.h>

namespace Bikes
{

enum 
{
    noCalc      = 0,
    sinCalc	    = 1<<0,
    cosCalc     = 1<<1,
    tanCalc     = 1<<2,
    radCalc     = 1<<3,
    sinM        = 1<<4,
    cosM        = 1<<5,

    allCalc	= sinCalc|cosCalc|tanCalc|radCalc,
    trCalc = sinCalc|cosCalc|tanCalc,
    sinCosCalc = sinCalc|cosCalc,


    noSinCalc	=	0xFF^sinCalc,
    noCosCalc	=	0xFF^cosCalc,
    noTanCalc	=	0xFF^tanCalc,
    noRadCalc   =	0xFF^radCalc,
    noSinM      =	0xFF^sinM,			
    noCosM      =	0xFF^cosM,
    noTrCalc    =   0xFF^trCalc,
    noSinCosCalc=   0xFF^sinCosCalc

    
};

SoftTrAngle::SoftTrAngle():
    _rad(0.0),
    _sin(0.0),
    _cos(1.0),
    _tan(0.0),
    _state(allCalc),
    _dirty(this)
{
}

SoftTrAngle::SoftTrAngle( radian ang ):
    _rad(ang),
    _sin(0.0),
    _cos(1.0),
    _tan(0.0),
    _state(radCalc),
    _dirty(this)
{
    if(_rad<0)
    {
        _state |= sinM;
        if(_rad<-PId2)
            _state |= cosM;
    }else if(_rad > PId2)
    {
        _state |= cosM;
    }
}

SoftTrAngle::SoftTrAngle( cosnum cos_ang, ValSign sinSign ):
    _rad(0.0),
    _sin(0.0),
    _cos(inRange(cos_ang,-1.0,1.0)),
    _tan(0.0),
    _state(cosCalc),
    _dirty(this)
{
    if(sinSign == negativeSign)
        _state |= sinM;

    if(_cos < 0)
        _state |= cosM;
}

SoftTrAngle::SoftTrAngle( const SoftTrAngle& ang ):
    _rad(ang._rad),
    _sin(ang._sin),
    _cos(ang._cos),
    _tan(ang._tan),
    _state(ang._state),
    _dirty(this)
{
}

SoftTrAngle::SoftTrAngle( const HardTrAngle& ang ):
    _rad(ang._rad),
    _sin(ang._sin),
    _cos(ang._cos),
    _tan(ang._sin/not0(ang._cos)),
    _state(allCalc),
    _dirty(this)
{
    if(_sin<0)
        _state |= sinM;

    if(_cos<0)
        _state |= cosM;
}

SoftTrAngle::SoftTrAngle( rnum rad, rnum sin, rnum cos ):
    _rad(rad),
    _sin(sin),
    _cos(cos),
    _tan(sin/not0(cos)),
    _state(allCalc),
    _dirty(this)
{
    if(_sin<0)
        _state |= sinM;

    if(_cos<0)
        _state |= cosM;
}

void SoftTrAngle::_calcRad()
{
    if(_state&radCalc == 0)
    {
        _state |= radCalc;
        if(_state&cosCalc)
        {
            _rad = acos(_cos);
            if(_state&sinM)
                _rad = -_rad;
        }else if(_state&sinCalc)
        {
            _rad = asin(_sin);
            if(_state&cosM)
            {
                if(_rad < 0)
                    _rad = - PI - _rad;
                else
                    _rad = PI - _rad;
            }
        }else if(_state&tanCalc)
        {
            _rad = atan(_tan);
            if(_state&cosM)
            {
                if(_rad < 0)
                    _rad = - PI - _rad;
                else
                    _rad = PI - _rad;
            }
        }else
        {
            _rad = 0.0;
        }
    }
}

void SoftTrAngle::_calcSin()
{
    if(_state&sinCalc == 0)
    {
        _state |= sinCalc;
        if(_state&cosCalc)
        {
            _sin = sqrt(1.0 - _cos*_cos);
            if(_state&sinM)
                _sin = -_sin;
        }else if(_state&tanCalc)
        {
            rnum tt=_tan*_tan;
            _sin = sqrt(tt/(tt + 1.0));
            if(_state&sinM)
                _sin = -_sin;
        }else if(_state&radCalc)
        {
            _sin = ::sin(_rad);
        }else
        {
            _sin = 0.0;
        }
    }
}

void SoftTrAngle::_calcCos()
{
    if(_state&cosCalc == 0)
    {
        _state |= cosCalc;
        if(_state&sinCalc)
        {
            _cos = sqrt(1.0 - _sin*_sin);
            if(_state&cosM)
                _cos = -_cos;
        }else if(_state&tanCalc)
        {
           _cos = sqrt(1.0/(1.0 + _tan*_tan));
           if(_state&cosM)
               _cos = - _cos;
        }else if(_state&radCalc)
        {
            _cos = ::cos(_rad);
        }else
        {
            _cos = 1.0;
        }
    }
}

void SoftTrAngle::_calcTan()
{
    if(_state&tanCalc == 0)
    {
        _state |= tanCalc;
        if(_state&cosCalc)
        {
            if(_state&sinCalc == 0)
            {
                _state |= sinCalc;
                _sin = sqrt(1.0 - _cos*_cos);
                if(_state&sinM)
                    _sin = -_sin;
            }
            _tan = _sin/not0(_cos);
        }else if(_state&sinCalc)
        {
            if(_state&cosCalc == 0)
            {
                _state |= cosCalc;
                _cos = sqrt(1.0 - _sin*_sin);
                if(_state&cosM)
                    _cos = -_cos;
            }
            _tan = _sin/not0(_cos);
        }else if(_state&radCalc)
        {
            _tan = ::tan(_rad);
        }else
        {
            _tan = 0.0;
        }
    }
}

sinnum SoftTrAngle::sin() const
{
    _dirty->_calcSin();
    return _sin;
}

cosnum SoftTrAngle::cos() const
{
    _dirty->_calcCos();
    return _cos;
}

tannum SoftTrAngle::tan() const
{
    _dirty->_calcTan();
    return _tan;
}

void SoftTrAngle::setRad( radian ang )
{
    _rad = ang;
    _state = radCalc;
    rnum na = normAngle(_rad);
    if(na < 0)
    {
        _state |= sinM;
        if( na < -PId2)
            _state |=  cosM;
    }else if( na > PId2)
    {
        _state |= cosM;
    }
}

void SoftTrAngle::setSin( sinnum sin_ang, ValSign cosSign /*= positiveSign*/ )
{
    _sin = inRange(sin_ang, -1.0, 1.0);
    _state = sinCalc;
    if(cosSign == negativeSign)
        _state |= cosM;
    if(_sin < 0)
        _state |= sinM;
}

void SoftTrAngle::setCos( sinnum cos_ang, ValSign sinSign /*= positiveSign*/ )
{
    _cos =  inRange(cos_ang, -1.0, 1.0);
    _state = cosCalc;
    if(sinSign == negativeSign)
        _state |= sinM;
    if(_cos < 0)
        _state |= cosM;
}

void SoftTrAngle::setTan( tannum tan_ang, ValSign cosSign /*= positiveSign*/ )
{
    _tan = tan_ang;
    _state = tanCalc;
    if(cosSign == negativeSign)
    {
        _state |=cosM;
        if(_tan > 0)
            _state |=sinM;
    }else if(_tan < 0)
    {
        _state |= sinM;
    }
}


void SoftTrAngle::set( const TrAngle& ang )
{
    if(const SoftTrAngle* sang = dynamic_cast<const SoftTrAngle*>(&ang))
    {
        set(*sang);
    }else
    {
        _rad = ang.rad();
        _sin = ang.sin();
        _cos = ang.cos();
        _tan = ang.tan();
        _state = allCalc;
        if(_sin<0)
            _state |= sinM;
        if(_cos<0)
            _state |= cosM;
    }
}

void SoftTrAngle::set( const SoftTrAngle& ang )
{
    _rad = ang._rad;
    _sin = ang._sin;
    _cos = ang._cos;
    _tan = ang._tan;
    _state = ang._state;
}

void SoftTrAngle::set( const HardTrAngle& ang )
{
    _rad = ang._rad;
    _sin = ang._sin;
    _cos = ang._cos;
    _tan = ang._sin / not0(ang._cos);
    _state = allCalc;
    if(_sin < 0)
        _state |= sinM;
    if(_cos < 0)
        _state |= cosM;
}


Bikes::SoftTrAngle SoftTrAngle::getSum( const TrAngle& ang ) const
{
    SoftTrAngle ra(*this);
    return ra.getSumAndSet(ang);
}

Bikes::SoftTrAngle SoftTrAngle::getSum( const SoftTrAngle& ang ) const
{
    SoftTrAngle ra(*this);
    return ra.getSumAndSet(ang);
}

Bikes::SoftTrAngle SoftTrAngle::getSum( const HardTrAngle& ang ) const
{
    SoftTrAngle ra(*this);
    return ra.getSumAndSet(ang);
    
}

SoftTrAngle& SoftTrAngle::getSumAndSet( const TrAngle& ang )
{
    if(const SoftTrAngle* sa = dynamic_cast<const SoftTrAngle*>(&ang))
    {
        return getSumAndSet(*sa);
    }else
    {
        if(_state&radCalc)
            _rad += ang.rad();

        if(_state&trCalc)
           _trSum(ang.sin(),ang.cos());

    }
    return *this;
}

SoftTrAngle& SoftTrAngle::getSumAndSet( const SoftTrAngle& ang )
{
    if(_state&radCalc)
    {
        if(_state&trCalc)
        {
            if(ang._state&radCalc)
                _rad += ang._rad;
            else
                _state &= noRadCalc;

            if(ang._state&trCalc)
                _trSum(ang.sin(),ang.cos());
            else
                _state &= noTrCalc;
        }else
        {
            _rad += ang.rad();
        }
    }else
    {
        _trSum(ang.sin(),ang.cos());
    }
    return *this;
}

SoftTrAngle& SoftTrAngle::getSumAndSet( const HardTrAngle& ang )
{
    if(_state&radCalc)
        _rad += ang._rad;

    if(_state&trCalc)
        _trSum(ang._sin,ang._cos);

    return *this;
}

Bikes::SoftTrAngle SoftTrAngle::getDifference( const TrAngle& ang ) const
{
    SoftTrAngle ra(*this);
    return ra.getDifferenceAndSet(ang);
}

Bikes::SoftTrAngle SoftTrAngle::getDifference( const SoftTrAngle& ang ) const
{
    SoftTrAngle ra(*this);
    return ra.getDifferenceAndSet(ang);
}

Bikes::SoftTrAngle SoftTrAngle::getDifference( const HardTrAngle& ang ) const
{
    SoftTrAngle ra(*this);
    return ra.getDifferenceAndSet(ang);
}

SoftTrAngle& SoftTrAngle::getDifferenceAndSet( const TrAngle& ang )
{
    if(const SoftTrAngle* sa = dynamic_cast<const SoftTrAngle*>(&ang))
    {
        return getDifferenceAndSet(*sa);
    }else
    {
        if(_state&radCalc)
            _rad -= ang.rad();

        if(_state&trCalc)
            _trDif(ang.sin(),ang.cos());

    }
    return *this;
}

SoftTrAngle& SoftTrAngle::getDifferenceAndSet( const SoftTrAngle& ang )
{
    if(_state&radCalc)
    {
        if(_state&trCalc)
        {
            if(ang._state&radCalc)
                _rad -= ang._rad;
            else
                _state &= noRadCalc;

            if(ang._state&trCalc)
                _trDif(ang.sin(),ang.cos());
            else
                _state &= noTrCalc;
        }else
        {
            _rad -= ang.rad();
        }
    }else
    {
        _trDif(ang.sin(),ang.cos());
    }
    return *this;
}

SoftTrAngle& SoftTrAngle::getDifferenceAndSet( const HardTrAngle& ang )
{
    if(_state&radCalc)
        _rad -= ang._rad;

    if(_state&trCalc)
        _trDif(ang._sin,ang._cos);

    return *this;
}

Bikes::SoftTrAngle SoftTrAngle::getNegative() const
{
    SoftTrAngle ra(*this);
    ra.setNegative();
    return ra;
}

void SoftTrAngle::setNegative()
{
    _sin = -_sin;

    if(_state&sinM)
        _state &= noSinM;
    else
        _state |= sinM;
        
    _rad = -_rad;
    
}

void SoftTrAngle::_trSum( sinnum s2, cosnum c2 )
{
    rnum s1 = sin();
    rnum c1 = cos();

    _sin = s1*c2 + c1*s2;
    _cos = c1*c2 - s1*s2;

    _state &= noTanCalc;

    if(_sin < 0)
        _state |= sinM;
    else
        _state &= noSinM;

    if(_cos < 0)
        _state |= cosM;
    else
        _state &= noCosM;
}

void SoftTrAngle::_trDif( sinnum s2, cosnum c2 )
{
    rnum s1 = sin();
    rnum c1 = cos();

    _sin = s1*c2 - c1*s2;
    _cos = c1*c2 + s1*s2;

    _state &= noTanCalc;

    if(_sin < 0)
        _state |= sinM;
    else
        _state &= noSinM;

    if(_cos < 0)
        _state |= cosM;
    else
        _state &= noCosM;
}





}