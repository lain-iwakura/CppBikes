#ifndef INCLUDEBIKES_VECTORPAIR_H
#define INCLUDEBIKES_VECTORPAIR_H

#include <Bikes/Geom/Vector.h>

namespace Bikes
{

class VectorPair
{
public:

	Vector i;
	Vector j;

	VectorPair();

	VectorPair(const Vector &v1, const Vector &v2);


};

}

#endif