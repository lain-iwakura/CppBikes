#ifndef INCLUDE_BIKES_GEOM_BASIS_H
#define INCLUDE_BIKES_GEOM_BASIS_H

#include <Bikes/Geom/Vector.h>
#include <Bikes/Geom/VectorPair.h>
#include <Bikes/Geom/CoordinateSystem.h>

namespace Bikes
{
class VectorPair;
//==============================================================================
class IConstBasis: public ICoordinateSystem
{
public:

    virtual ~IConstBasis();

    virtual Vector const& i() const = 0;
    virtual Vector const& j() const = 0;
    virtual Vector const& k() const = 0;

    virtual Vector const& inv_i() const = 0;
    virtual Vector const& inv_j() const = 0;
    virtual Vector const& inv_k() const = 0;


    rnum getCoordinate1(const Vector& v) const;
    rnum getCoordinate2(const Vector& v) const;
    rnum getCoordinate3(const Vector& v) const;

    void setCoordinate1(Vector& v, rnum x) const;
    void setCoordinate2(Vector& v, rnum y) const;
    void setCoordinate3(Vector& v, rnum z) const;

    void setCoordinates(Vector& v, rnum x, rnum y, rnum z) const;

    rnum getX(const Vector& v) const;
    rnum getY(const Vector& v) const;
    rnum getZ(const Vector& v) const;

    void setX(Vector& v, rnum x) const;
    void setY(Vector& v, rnum y) const;
    void setZ(Vector& v, rnum z) const;

};
//==============================================================================
namespace Inner{
class InvBasisBase : virtual public IConstBasis
{
public:

    InvBasisBase();

    Vector const& inv_i() const;
    Vector const& inv_j() const;
    Vector const& inv_k() const;

protected:
    void recalc_inv_later();
private:    
    void _recalc_inv() const;
    Vector _inv_i;
    Vector _inv_j;
    Vector _inv_k;
    bool _recalc;
};
//==============================================================================
class BaseBasis : virtual public IConstBasis
{
public:

    virtual Vector& ri() = 0; //X
    virtual Vector& rj() = 0; //X
    virtual Vector& rk() = 0; //X


    virtual void normalize();

    virtual void setScale(rnum scale);

    virtual void scale(rnum scaleFactor);

    virtual void setRightOrtonormal(const Vector& vi, const Vector& vj);

    virtual void setRightOrtonormal(const VectorPair& ij);

    virtual void setLeftOrtonormal(const Vector& vi, const Vector& vj);

    virtual void setLeftOrtonormal(const VectorPair& ij);
};
} // Inner
//==============================================================================
class Basis: 
    public Inner::BaseBasis,
    public Inner::InvBasisBase
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

    Vector& ri();
    Vector& rj();
    Vector& rk();

protected:
    Vector _i;
    Vector _j;
    Vector _k;
};
//==============================================================================
class TransientBasis : public Inner::InvBasisBase
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

