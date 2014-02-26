#ifndef INCLUDEBIKES_TRANGLE_H
#define INCLUDEBIKES_TRANGLE_H

#include <Bikes/Mathem/Constants.h>

namespace Bikes                 
{

	class SoftTrAngle;
    class HardTrAngle;

	class TrAngle
	{
	public:

		virtual ~TrAngle();
 
        operator radian () const;

        virtual TrAngle& operator = (const TrAngle& ang) = 0;

        virtual TrAngle& operator = (const HardTrAngle& ang);

        virtual TrAngle& operator = (const SoftTrAngle& ang);

        virtual TrAngle& operator = (radian ang);

        virtual TrAngle& operator += (const TrAngle& ang) = 0;

        virtual TrAngle& operator += (const HardTrAngle& ang);

        virtual TrAngle& operator += (const SoftTrAngle& ang);

        virtual TrAngle& operator += (radian ang);

        virtual TrAngle& operator -= (const TrAngle& ang) = 0;

        virtual TrAngle& operator -= (const HardTrAngle& ang);

        virtual TrAngle& operator -= (const SoftTrAngle& ang);

        virtual TrAngle& operator -= (radian ang);

        virtual TrAngle& operator *= (rnum m);

        virtual TrAngle& operator *= (lnum n);

        virtual TrAngle& operator /= (rnum m);

        virtual TrAngle& operator /= (lnum n);

        virtual SoftTrAngle operator + (const TrAngle& ang) const;

        virtual SoftTrAngle operator + (const HardTrAngle& ang) const;

        virtual SoftTrAngle operator + (const SoftTrAngle& ang) const;

        radian operator + (radian ang) const;

        virtual SoftTrAngle operator - (const TrAngle& ang) const;

        virtual SoftTrAngle operator - (const HardTrAngle& ang) const;

        virtual SoftTrAngle operator - (const SoftTrAngle& ang) const;

        radian operator - (radian ang) const;

        virtual SoftTrAngle operator * (rnum m) const;

        virtual SoftTrAngle operator * (lnum n) const;

        virtual SoftTrAngle operator / (rnum m) const;

        virtual SoftTrAngle operator / (lnum n) const;

        virtual bool operator == (const TrAngle& ang) const;

        bool operator == (radian ang) const;

        virtual bool operator < (const TrAngle& ang) const;

        bool operator < (radian ang) const;

        virtual bool operator <= (const TrAngle& ang) const;

        bool operator <= (radian ang) const;

        virtual bool operator > (const TrAngle& ang) const;

        bool operator > (radian ang) const;

        virtual bool operator >= (const TrAngle& ang) const;

		bool operator >= (radian ang) const;       

        virtual SoftTrAngle operator-() const;

		virtual sinnum sin() const = 0;

		virtual cosnum cos() const = 0;

		virtual tannum tan() const;

		virtual radian rad() const = 0;

		virtual degree deg() const;

		virtual void setRad(radian ang) = 0;

		virtual void setDeg(degree ang);

		virtual void setSin(sinnum sin_ang, ValSign cosSign = positiveSign) = 0;

		virtual void setCos(sinnum cos_ang, ValSign sinSign = positiveSign) = 0;

		virtual void setTan(tannum tan_ang, ValSign cosSign = positiveSign);

		virtual TrAngle& setNegative() = 0;

        virtual TrAngle* clone() const = 0;
        
	protected:

		virtual void set(sinnum sin_ang, cosnum cos_ang); // (???)		
		
	};

	
	inline sinnum sin(const TrAngle &ta) {return ta.sin();}

	inline cosnum cos(const TrAngle &ta) {return ta.cos();}

	inline tannum tan(const TrAngle &ta) {return ta.tan();}

	inline radian rad(const TrAngle &ta) {return ta.rad();}

	inline degree deg(const TrAngle &ta) {return ta.deg();}


}

#endif