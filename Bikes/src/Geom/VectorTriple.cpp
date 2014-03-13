#include <Bikes/Geom/VectorTriple.h>

namespace Bikes
{

IConstVectorTriple::~IConstVectorTriple()
{
}

IVectorTriple::~IVectorTriple()
{
}


Vector const& TransientConstVectorTriple::first() const
{
    return vi;
}

Vector const& TransientConstVectorTriple::second() const
{
    return vj;
}

Vector const& TransientConstVectorTriple::third() const
{
    return vk;
}


Vector const& VectorTriple::first() const
{
    return vi;
}

Vector& VectorTriple::first()
{
    return vi;
}

Vector const& VectorTriple::second() const
{
    return vj;
}

Vector& VectorTriple::second()
{
    return vj;
}

Vector const& VectorTriple::third() const
{
    return vk;
}

Vector& VectorTriple::third()
{
    return vk;
}





TransientVectorTriple::TransientVectorTriple(Vector& _vi, Vector& _vj, Vector& _vk):
vi(_vi),
vj(_vj),
vk(_vk)
{

}

Vector const& TransientVectorTriple::first() const
{
	return vi;
}

Vector& TransientVectorTriple::first()
{
	return vi;
}

Vector const& TransientVectorTriple::second() const
{
	return vj;
}

Vector& TransientVectorTriple::second()
{
	return vj;
}

Vector const& TransientVectorTriple::third() const
{
	return vk;
}

Vector& TransientVectorTriple::third()
{
	return vk;
}

}
