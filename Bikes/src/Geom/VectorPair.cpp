#include <Bikes/Geom/VectorPair.h>

namespace Bikes
{
//==============================================================================
IConstVectorPair::~IConstVectorPair()
{
}
//==============================================================================
VectorPair::VectorPair()
{
}

VectorPair::VectorPair( const Vector &v1, const Vector &v2 ):
	_i(v1),
	_j(v2)
{
}

VectorPair::VectorPair( IConstVectorPair const& ij ):
    _i(ij.i()),
    _j(ij.j())
{
}

Vector const& VectorPair::i() const
{
    return _i;
}

Vector& VectorPair::i()
{
    return _i;
}



Vector const& VectorPair::j() const
{
    return _j;
}

Vector& VectorPair::j()
{
    return _j;
}
//==============================================================================
TransientVectorPair::TransientVectorPair( Vector const& vi, Vector const& vj ):
    _i(vi),
    _j(vj)
{    
}

TransientVectorPair::TransientVectorPair( IConstVectorPair const& ij ):
    _i(ij.i()),
    _j(ij.j())
{
}


Vector const& TransientVectorPair::i() const
{
    return _i;
}

Vector const& TransientVectorPair::j() const
{
    return _j;
}
//==============================================================================
}
