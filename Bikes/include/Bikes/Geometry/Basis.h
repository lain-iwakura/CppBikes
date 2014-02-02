#ifndef INCLUDEBIKES_BASIS_H
#define INCLUDEBIKES_BASIS_H

#include <Bikes/Geometry/Vector.h>
#include <Bikes/Geometry/Point.h>
#include <Bikes/Geometry/BasisReference.h>

namespace Bikes
{
class Basis: public BasisReference
{
public:
	Vector i;
	Vector j;
	Vector k;
	Point O;

};
}


#endif