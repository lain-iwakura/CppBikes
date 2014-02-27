#ifndef INCLUDE_BIKES_MATHEM_CONSTANTS_H
#define INCLUDE_BIKES_MATHEM_CONSTANTS_H

#include <Bikes/Types.h>


#define CONSTBIKES_PI       3.1415926535897932384626433832795  // (double) 3.1415926535897932

#define CONSTBIKES_E        2.7182818284590452353602874713527  // (double) 2.7182818284590452

#define CONSTBIKES_SQRT2    1.4142135623730950488016887242097  

#define CONSTBIKES_SQRT3    1.7320508075688772935274463415059  

namespace Bikes
{
	const rnum PI = CONSTBIKES_PI;
	
	const rnum E = CONSTBIKES_E;

	const rnum SQRT2 = CONSTBIKES_SQRT2;

	const rnum SQRT3 = CONSTBIKES_SQRT3;

	const rnum RNUM_O = 1.0E-30; //-35

	const rnum RNUM_INFINITY = 1.0/RNUM_O;

	const rnum EQUAL_O = 1.0E-12;

	const rnum ANGLE_O = 1.0E-10;

	const rnum DEG_PER_RAD = 180.0/PI;

	const rnum RAD_PER_DEG = PI/180.0;
	
	const rnum ANG_1DEG = RAD_PER_DEG;

	const rnum ANG_1MIN = ANG_1DEG/60.0;

	const rnum ANG_1SEC = ANG_1MIN/60.0;

	const rnum PId2 = PI/2.0;

	const rnum PId3 = PI/3.0;

	const rnum PId4 = PI/4.0;

	const rnum PId6 = PI/6.0;

	const rnum PIm2 = PI*2.0;

	const rnum PI3d2 = PId2*3.0;
}

#endif // <- INCLUDE_BIKES_MATHEM_CONSTANTS_H
