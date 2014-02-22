#ifndef INCLUDEBIKES_SOFTTRANGLE_H
#define INCLUDEBIKES_SOFTTRANGLE_H

#include <Bikes/Math/TrAngle.h>

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

    //virtual degree deg() const;

    void set(const TrAngle& ang); //= 0;

    void set(const SoftTrAngle& ang);

    void set(const HardTrAngle& ang);

    void setRad(radian ang);

    //virtual void setDeg(degree ang);

    void setSin(sinnum sin_ang, ValSign cosSign = positiveSign);

    void setCos(sinnum cos_ang, ValSign sinSign = positiveSign);

    void setTan(tannum tan_ang, ValSign cosSign = positiveSign);

    SoftTrAngle getSum(const TrAngle& ang) const;

    SoftTrAngle getSum(const SoftTrAngle& ang) const;

    SoftTrAngle getSum(const HardTrAngle& ang) const;

    SoftTrAngle& getSumAndSet(const TrAngle& ang);

    SoftTrAngle& getSumAndSet(const SoftTrAngle& ang);

    SoftTrAngle& getSumAndSet(const HardTrAngle& ang);

    SoftTrAngle getDifference(const TrAngle& ang) const ;

    SoftTrAngle getDifference(const SoftTrAngle& ang) const ;

    SoftTrAngle getDifference(const HardTrAngle& ang) const ;

    SoftTrAngle& getDifferenceAndSet(const TrAngle& ang);

    SoftTrAngle& getDifferenceAndSet(const SoftTrAngle& ang);

    SoftTrAngle& getDifferenceAndSet(const HardTrAngle& ang);

//    SoftTrAngle getProduct(rnum m) const;

   // SoftTrAngle getProduct(num n) const;

//    HardTrAngle& getProductAndSet(rnum m);

  //  HardTrAngle& getProductAndSet(num n);

    SoftTrAngle getNegative() const;

    void setNegative();

    //virtual bool isEqual(const TrAngle& ang) const; 

    //virtual bool isLess(const TrAngle& ang) const;

    //virtual bool isLessOrEqual(const TrAngle& ang) const;

    //virtual bool isGreater(const TrAngle& ang) const;

    //virtual bool isGreaterOrEqual(const TrAngle& ang) const;


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

}
#endif