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

    //tannum tan() const;

    radian rad() const;

    //virtual degree deg() const;

    void set(const TrAngle& ang); //= 0;

    void setRad(radian ang);

    //virtual void setDeg(degree ang);

    void setSin(sinnum sin_ang, ValSign cosSign = positiveSign);

    void setCos(sinnum cos_ang, ValSign sinSign = positiveSign);

    void setTan(tannum tan_ang, ValSign cosSign = positiveSign);

    SoftTrAngle getSum(const TrAngle& ang) const;		

    HardTrAngle& getSumAndSet(const TrAngle& ang);

    SoftTrAngle getDifference(const TrAngle& ang) const ;

    HardTrAngle& getDifferenceAndSet(const TrAngle& ang);

    SoftTrAngle getProduct(rnum m) const;


    HardTrAngle& getProductAndSet(rnum m);


    SoftTrAngle getNegative() const;

    void setNegative();

    //virtual bool isEqual(const TrAngle& ang) const; 

    //virtual bool isLess(const TrAngle& ang) const;

    //virtual bool isLessOrEqual(const TrAngle& ang) const;

    //virtual bool isGreater(const TrAngle& ang) const;

    //virtual bool isGreaterOrEqual(const TrAngle& ang) const;

//     template< num n > 
//     void getProductAndSetN()
//     {
//         ang.getProductAndSet(rnum(n));
//     }


private:
    rnum _rad;
    rnum _sin;
    rnum _cos;

    friend class SoftTrAngle;
};

}

#endif