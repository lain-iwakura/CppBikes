#ifndef INCLUDEBIKES_HARDTRANGLE_H
#define INCLUDEBIKES_HARDTRANGLE_H

#include <Bikes/Math/TrAngle.h>

namespace Bikes
{

class HardTrAngle: TrAngle
{
public:
	HardTrAngle();
	HardTrAngle(rnum _rad_val,rnum _sin_val, rnum _cos_val, rnum _tan_val);
	HardTrAngle(rnum ang_rad);	

	void set(rnum ang_rad);
	HardTrAngle& operator =(rnum ang_rad);

	operator rnum () const;

private:
	rnum _rad;
	rnum _sin;
	rnum _cos;
	rnum _tan;
};

}

#endif