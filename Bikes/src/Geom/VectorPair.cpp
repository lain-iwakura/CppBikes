#include <Bikes/Geom/VectorPair.h>

namespace Bikes
{


IConstVectorPair::~IConstVectorPair()
{
}


// Vector const& IConstVectorPair::i() const
// {
//     return first();
// }
// 
// Vector const& IConstVectorPair::j() const
// {
//     return second();
// }

//=========================================================================
IVectorPair::~IVectorPair()
{
}

// Vector& IVectorPair::i()
// {
//     return first();
// }
// 
// Vector& IVectorPair::j()
// {
//     return second();
// }
//=========================================================================
VectorPair::VectorPair()
{
}

VectorPair::VectorPair( const Vector &v1, const Vector &v2 ):
	vi(v1),
	vj(v2)
{
}

VectorPair::VectorPair( IConstVectorPair const& ij ):
    vi(ij.first()),
    vj(ij.second())
{
}



Vector const& VectorPair::first() const
{
    return vi;
}

Vector& VectorPair::first()
{
    return vi;
}



Vector const& VectorPair::second() const
{
    return vj;
}

Vector& VectorPair::second()
{
    return vj;
}
//=========================================================================
TransientConstVectorPair::TransientConstVectorPair( Vector const& vi, Vector const& vj ):
    vi(vi),
    vj(vj)
{    
}

TransientConstVectorPair::TransientConstVectorPair( IConstVectorPair const& ij ):
    vi(ij.first()),
    vj(ij.second())
{
}


Vector const& TransientConstVectorPair::first() const
{
    return vi;
}

Vector const& TransientConstVectorPair::second() const
{
    return vj;
}


TransientVectorPair::TransientVectorPair( Vector& vi, Vector& vj ):
    vi(vi),
    vj(vj)
{
}

TransientVectorPair::TransientVectorPair( IVectorPair& ij ):
    vi(ij.first()),
    vj(ij.second())
{
}

Vector const& TransientVectorPair::first() const
{
    return vi;
}

Vector& TransientVectorPair::first()
{
    return vi;
}

Vector const& TransientVectorPair::second() const
{
    return vj;
}

Vector& TransientVectorPair::second()
{
    return vj;
}







}