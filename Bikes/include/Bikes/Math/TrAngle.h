#ifndef INCLUDEBIKES_TRANGLE_H
#define INCLUDEBIKES_TRANGLE_H

#include <Bikes/Math/Constants.h>


namespace Bikes
{

	class SoftTrAngle;


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

		virtual tannum tan() const = 0;

		virtual radian rad() const = 0;

		virtual degree deg() const;

		virtual void set(const TrAngle& ang) = 0;

		virtual void setRad(radian ang) = 0;		

		virtual void setSin(sinnum sin_ang, ValSign cosSign = positiveSign) = 0;

		virtual void setCos(sinnum cos_ang, ValSign sinSign = positiveSign) = 0;

		virtual void setTan(tannum tan_ang, ValSign cosSign = positiveSign) = 0;

		virtual SoftTrAngle getSum(const TrAngle& ang) const = 0;		

		virtual void setSum(const TrAngle& ang) = 0;

		virtual SoftTrAngle getDifference(const TrAngle& ang) const = 0;

		virtual void setDifference(const TrAngle& ang) = 0;

		virtual SoftTrAngle getProduct(rnum m) const = 0;

		virtual void setProduct(rnum m) = 0;

		virtual SoftTrAngle getNegative() const = 0;

		virtual void setNegative() = 0;

		virtual bool isEqual(const TrAngle& ang) const = 0; 

		virtual bool isLess(const TrAngle& ang) const = 0;

		virtual bool isLessOrEqual(const TrAngle& ang) const = 0;

		virtual bool isGreater(const TrAngle& ang) const = 0;

		virtual bool isGreaterOrEqual(const TrAngle& ang) const = 0;

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