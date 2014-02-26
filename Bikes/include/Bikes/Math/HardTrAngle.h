#ifndef INCLUDEBIKES_HARDTRANGLE_H
#define INCLUDEBIKES_HARDTRANGLE_H

#include <Bikes/Math/TrAngle.h>


namespace Bikes
{

class SoftTrAngle;

class HardTrAngle: public TrAngle
{
public:


    HardTrAngle();

    HardTrAngle(radian ang);

    HardTrAngle(cosnum cos_ang, ValSign sinSign);
    
              
    sinnum sin() const;

    cosnum cos() const;

    radian rad() const;

    HardTrAngle& operator = (const TrAngle& ang); //= 0;

    void setRad(radian ang);

    void setSin(sinnum sin_ang, ValSign cosSign = positiveSign);

    void setCos(sinnum cos_ang, ValSign sinSign = positiveSign);

    void setTan(tannum tan_ang, ValSign cosSign = positiveSign);

    HardTrAngle& operator += (const TrAngle& ang);    

    HardTrAngle& operator -= (const TrAngle& ang);

    HardTrAngle& operator *= (rnum m);
    
    HardTrAngle& setNegative();   

    HardTrAngle* clone() const;

private:
    rnum _rad;
    rnum _sin;
    rnum _cos;

    friend class SoftTrAngle;
};

}

#endif