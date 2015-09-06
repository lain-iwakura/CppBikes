#ifndef INCLUDE_BIKES_GEOM_VECTORPAIR_H
#define INCLUDE_BIKES_GEOM_VECTORPAIR_H

#include <Bikes/Geom/Vector.h>

namespace Bikes
{
//==============================================================================
class IConstVectorPair
{
public:
    virtual ~IConstVectorPair();

    virtual Vector const& i() const = 0;
    virtual Vector const& j() const = 0;

};
//==============================================================================
class IVectorPair: public virtual IConstVectorPair
{
public:    

    virtual Vector& i() = 0;
    virtual Vector& j() = 0;
};
//==============================================================================
class VectorPair: public IVectorPair
{
public:
	VectorPair();

    VectorPair(IConstVectorPair const& ij);

	VectorPair(Vector const& _vi, Vector const& _vj);

    Vector& i();
    Vector& j();

    Vector const& i() const;
    Vector const& j() const;

protected:
    Vector _i;
    Vector _j;
};
//==============================================================================
class TransientVectorPair: public IConstVectorPair
{
public:

    TransientVectorPair(IConstVectorPair const& ij);

    TransientVectorPair(Vector const& _vi, Vector const& _vj);

    Vector const& i() const;
    Vector const& j() const;    

protected:
    Vector const& _i;
    Vector const& _j;
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_GEOM_VECTORPAIR_H
