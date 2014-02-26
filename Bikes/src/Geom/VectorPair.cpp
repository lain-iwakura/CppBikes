#include <Bikes/Geom/VectorPair.h>

namespace Bikes
{
	
VectorPair::VectorPair()
{

}

VectorPair::VectorPair( const Vector &v1, const Vector &v2 ):
	i(v1),
	j(v2)
{

}

}