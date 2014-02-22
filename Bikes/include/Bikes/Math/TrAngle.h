#ifndef INCLUDEBIKES_TRANGLE_H
#define INCLUDEBIKES_TRANGLE_H

#include <Bikes/Math/Constants.h>


namespace Bikes                 
{

	class SoftTrAngle;
    class HardTrAngle;


	class TrAngle
	{
	public:

		virtual ~TrAngle();


 
        operator radian () const;

        TrAngle& operator = (const TrAngle& ang);

        TrAngle& operator = (radian ang);

        TrAngle& operator += (const TrAngle& ang);

        TrAngle& operator += (radian ang);

        TrAngle& operator -= (const TrAngle& ang);

        TrAngle& operator -= (radian ang);

        TrAngle& operator *= (rnum m);

        TrAngle& operator /= (rnum m);

        SoftTrAngle operator + (const TrAngle& ang) const;

        radian operator + (radian ang) const;

        SoftTrAngle operator - (const TrAngle& ang) const;

        radian operator - (radian ang) const;

        SoftTrAngle operator * (rnum m) const;

        SoftTrAngle operator / (rnum m) const;

        bool operator == (const TrAngle& ang) const;

        bool operator == (radian ang) const;

        bool operator < (const TrAngle& ang) const;

        bool operator < (radian ang) const;

        bool operator <= (const TrAngle& ang) const;

        bool operator <= (radian ang) const;

        bool operator > (const TrAngle& ang) const;

        bool operator > (radian ang) const;

        bool operator >= (const TrAngle& ang) const;

		bool operator >= (radian ang) const;                                


		virtual sinnum sin() const = 0;

		virtual cosnum cos() const = 0;

		virtual tannum tan() const;

		virtual radian rad() const = 0;

		virtual degree deg() const;

		virtual void set(const TrAngle& ang); //= 0;

		virtual void setRad(radian ang) = 0;

		virtual void setDeg(degree ang);

		virtual void setSin(sinnum sin_ang, ValSign cosSign = positiveSign) = 0;

		virtual void setCos(sinnum cos_ang, ValSign sinSign = positiveSign) = 0;

		virtual void setTan(tannum tan_ang, ValSign cosSign = positiveSign);

		virtual SoftTrAngle getSum(const TrAngle& ang) const;	

        virtual SoftTrAngle getSum(const HardTrAngle& ang) const;	

        virtual SoftTrAngle getSum(const SoftTrAngle& ang) const;	

		virtual TrAngle& getSumAndSet(const TrAngle& ang) = 0;

        virtual TrAngle& getSumAndSet(const HardTrAngle& ang);

        virtual TrAngle& getSumAndSet(const SoftTrAngle& ang);

		virtual SoftTrAngle getDifference(const TrAngle& ang) const;

        virtual SoftTrAngle getDifference(const HardTrAngle& ang) const;

        virtual SoftTrAngle getDifference(const SoftTrAngle& ang) const;

		virtual TrAngle& getDifferenceAndSet(const TrAngle& ang) = 0;

        virtual TrAngle& getDifferenceAndSet(const HardTrAngle& ang);

        virtual TrAngle& getDifferenceAndSet(const SoftTrAngle& ang);

		virtual SoftTrAngle getProduct(rnum m) const;

        virtual SoftTrAngle getProduct(num n) const;

		virtual TrAngle& getProductAndSet(rnum m);

        virtual TrAngle& getProductAndSet(num n);

		virtual SoftTrAngle getNegative() const = 0;

		virtual void setNegative() = 0;

		virtual bool isEqual(const TrAngle& ang) const; 

		virtual bool isLess(const TrAngle& ang) const;

		virtual bool isLessOrEqual(const TrAngle& ang) const;

		virtual bool isGreater(const TrAngle& ang) const;

		virtual bool isGreaterOrEqual(const TrAngle& ang) const;
        
	protected:

		virtual void set(sinnum sin_ang, cosnum cos_ang);		
		
	};

	
	inline sinnum sin(const TrAngle &ta) {return ta.sin();}

	inline cosnum cos(const TrAngle &ta) {return ta.cos();}

	inline tannum tan(const TrAngle &ta) {return ta.tan();}

	inline radian rad(const TrAngle &ta) {return ta.rad();}

	inline degree deg(const TrAngle &ta) {return ta.deg();}

}


#endif