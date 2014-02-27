#ifndef INCLUDE_BIKES_MATHEM_SOFTTRANGLE_H
#define INCLUDE_BIKES_MATHEM_SOFTTRANGLE_H

#include <Bikes/Mathem/TrAngle.h>

namespace Bikes
{

class HardTrAngle;

class SoftTrAngle: public TrAngle
{
public:

    SoftTrAngle();

    SoftTrAngle(radian ang);

    SoftTrAngle(cosnum cos_ang, ValSign sinSign);

    SoftTrAngle(const SoftTrAngle& ang);

    SoftTrAngle(const HardTrAngle& ang);

    sinnum sin() const;

    cosnum cos() const;

    tannum tan() const;

    radian rad() const;

    SoftTrAngle& operator=(const TrAngle& ang); //= 0;

    SoftTrAngle& operator=(const SoftTrAngle& ang);

    SoftTrAngle& operator=(const HardTrAngle& ang);

    void setRad(radian ang);

    void setSin(sinnum sin_ang, ValSign cosSign = positiveSign);

    void setCos(sinnum cos_ang, ValSign sinSign = positiveSign);

    void setTan(tannum tan_ang, ValSign cosSign = positiveSign);

    SoftTrAngle& operator+=(const TrAngle& ang);

    SoftTrAngle& operator+=(const SoftTrAngle& ang);

    SoftTrAngle& operator+=(const HardTrAngle& ang);

    SoftTrAngle& operator-=(const TrAngle& ang);

    SoftTrAngle& operator-=(const SoftTrAngle& ang);

    SoftTrAngle& operator-=(const HardTrAngle& ang);

    SoftTrAngle&  setNegative();

    SoftTrAngle* clone() const;


private:

    SoftTrAngle(rnum rad, rnum sin, rnum cos);

    void _calcRad();
    void _calcSin();
    void _calcCos();
    void _calcTan();

    void _trSum(sinnum s2, cosnum c2);

    void _trDif(sinnum s2, cosnum c2);

	rnum _rad;
	rnum _sin;
	rnum _cos;
	rnum _tan;

    char _state;

	SoftTrAngle *_dirty;

    friend class TrAngle;
    friend class HardTrAngle;
};

inline sinnum sin(const SoftTrAngle &ta) {return ta.sin();}

inline cosnum cos(const SoftTrAngle &ta) {return ta.cos();}

inline tannum tan(const SoftTrAngle &ta) {return ta.tan();}

inline radian rad(const SoftTrAngle &ta) {return ta.rad();}

inline degree deg(const SoftTrAngle &ta) {return ta.deg();}

}

#endif // <- INCLUDE_BIKES_MATHEM_SOFTTRANGLE_H
