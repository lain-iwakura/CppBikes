#ifndef INCLUDE_BIKES_GEOM_BASIS_H
#define INCLUDE_BIKES_GEOM_BASIS_H

#include <Bikes/Geom/Vector.h>
#include <Bikes/Geom/VectorPair.h>

namespace Bikes
{
class VectorPair;
//==============================================================================
class IConstBasis
{
public:

    virtual ~IConstBasis();

    virtual Vector const& i() const = 0;
    virtual Vector const& j() const = 0;
    virtual Vector const& k() const = 0;

};
//==============================================================================
class IBasis: public IConstBasis
{
public:

    virtual ~IBasis();

    virtual Vector& i() = 0;
    virtual Vector& j() = 0;
    virtual Vector& k() = 0;

    virtual void normalize();

    virtual void setScale(rnum scale);

    virtual void scale(rnum scaleFactor);

    virtual void setRightOrtonormal(const Vector& vi, const Vector& vj);

    virtual void setRightOrtonormal(const VectorPair& ij);

    virtual void setLeftOrtonormal(const Vector& vi, const Vector& vj);

    virtual void setLeftOrtonormal(const VectorPair& ij);
};
//==============================================================================
class Basis: public IBasis
{
public:

	Basis(const Vector& vi, const Vector& vj, const Vector& vk);	

	Basis(const VectorPair& pair_ij, const Vector& vk);

	Basis(const Vector& vi, const VectorPair& pair_jk);

    Basis(const IConstBasis& ijk);

	Basis(const Vector& vi, const Vector& vj, bool right=true);

	Basis(const VectorPair& pair_ij, bool right=true);

    Vector const& i() const;
    Vector const& j() const;
    Vector const& k() const;

    Vector& i();
    Vector& j();
    Vector& k();

protected:
    Vector _i;
    Vector _j;
    Vector _k;
};
//==============================================================================
class TransientBasis: public IConstBasis
{
public:

    TransientBasis(const Vector& vi, const Vector& vj, const Vector& vk);

    Vector const& i() const;
    Vector const& j() const;
    Vector const& k() const;    

protected:
    const Vector& _i;
    const Vector& _j;
    const Vector& _k;
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_GEOM_BASIS_H
