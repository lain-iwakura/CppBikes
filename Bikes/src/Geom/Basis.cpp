#include <Geom/Basis.h>
#include <Geom/VectorPair.h>

namespace Bikes
{
//==============================================================================
rnum IConstBasis::getCoordinate1(const Vector& v) const
{
    return getX(v);
}
//------------------------------------------------------------------------------
rnum IConstBasis::getCoordinate2(const Vector& v) const
{
    return getY(v);
}
//------------------------------------------------------------------------------
rnum IConstBasis::getCoordinate3(const Vector& v) const
{
    return getZ(v);
}
//------------------------------------------------------------------------------
void IConstBasis::setCoordinate1(Vector& v, rnum x) const
{
    return setX(v, x);
}
//------------------------------------------------------------------------------
void IConstBasis::setCoordinate2(Vector& v, rnum y) const
{
    return setY(v, y);
}
//------------------------------------------------------------------------------
void IConstBasis::setCoordinate3(Vector& v, rnum z) const
{
    return setZ(v, z);
}
//------------------------------------------------------------------------------
void IConstBasis::setCoordinates(Vector& v, rnum x, rnum y, rnum z) const
{
    const Vector& _i = i();
    const Vector& _j = j();
    const Vector& _k = k();
    v.setGlobal(
        x*_i.x() + y*_j.x() + z*_k.x(),
        x*_i.y() + y*_j.y() + z*_k.y(),
        x*_i.z() + y*_j.z() + z*_k.z()
        );
}
//------------------------------------------------------------------------------
Bikes::rnum IConstBasis::getX(const Vector& v) const
{
    return v & i();
}
//------------------------------------------------------------------------------
Bikes::rnum IConstBasis::getY(const Vector& v) const
{
    return v & j();
}
//------------------------------------------------------------------------------
Bikes::rnum IConstBasis::getZ(const Vector& v) const
{
    return v & k();
}
//------------------------------------------------------------------------------
void IConstBasis::setX(Vector& v, rnum x) const
{
    v.setProjection(x, i());
}
//------------------------------------------------------------------------------
void IConstBasis::setY(Vector& v, rnum y) const
{
    v.setProjection(y, j());
}
//------------------------------------------------------------------------------
void IConstBasis::setZ(Vector& v, rnum z) const
{
    v.setProjection(z, k());
}
//==============================================================================
void IBasis::normalize()
{
    i().normalize();
    j().normalize();
    k().normalize();
}
//------------------------------------------------------------------------------
void IBasis::setScale(rnum scale)
{
    i().setLength(scale);
    j().setLength(scale);
    k().setLength(scale);
}
//------------------------------------------------------------------------------
void IBasis::scale(rnum scaleFactor)
{
    i() *= scaleFactor;
    j() *= scaleFactor;
    k() *= scaleFactor;
}
//------------------------------------------------------------------------------
void IBasis::setRightOrtonormal(const Vector& vi, const Vector& vj)
{
    i() = vi;
    k() = vi*vj;
    i().normalize();
    k().normalize();
    j() = k()*i();
}
//------------------------------------------------------------------------------
void IBasis::setRightOrtonormal(const VectorPair& ij)
{
    setRightOrtonormal(ij.i(), ij.j());
}
//------------------------------------------------------------------------------
void IBasis::setLeftOrtonormal(const Vector& vi, const Vector& vj)
{
    i() = vi;
    k() = vi*vj;
    i().normalize();
    k().normalize();
    j() = i()* k();
}
//------------------------------------------------------------------------------
void IBasis::setLeftOrtonormal(const VectorPair& ij)
{
    setLeftOrtonormal(ij.i(), ij.j());
}
//==============================================================================
Basis::Basis( const Vector& vi, const Vector& vj, const Vector& vk ):
	_i(vi),
	_j(vj),
	_k(vk)
{
}
//------------------------------------------------------------------------------
Basis::Basis( const VectorPair& pair_ij, const Vector& vk ):
	_i(pair_ij.i()),
	_j(pair_ij.j()),
	_k(vk)
{
}
//------------------------------------------------------------------------------
Basis::Basis( const Vector& vi, const VectorPair& pair_jk ):
	_i(vi),
	_j(pair_jk.i()),
	_k(pair_jk.j())
{
}
//------------------------------------------------------------------------------
Basis::Basis(const IConstBasis& ijk) :
	_i(ijk.i()),
	_j(ijk.j()),
	_k(ijk.k())
{
}
//------------------------------------------------------------------------------
Basis::Basis( const Vector& vi, const Vector& vj, bool right/*=true*/ )
{
    if (right)
        setRightOrtonormal(vi, vj);
    else
        setLeftOrtonormal(vi, vj);
}
//------------------------------------------------------------------------------
Basis::Basis( const VectorPair& pair_ij, bool right/*=true*/ )
{
    if (right)
        setRightOrtonormal(pair_ij);
    else
        setLeftOrtonormal(pair_ij);
}
//------------------------------------------------------------------------------
Vector& Basis::i()
{
    return _i;
}
//------------------------------------------------------------------------------
Vector const& Basis::i() const
{
    return _i;
}
//------------------------------------------------------------------------------
Vector& Basis::j()
{
    return _j;
}
//------------------------------------------------------------------------------
Vector const& Basis::j() const
{
    return _j;
}
//------------------------------------------------------------------------------
Vector& Basis::k()
{
    return _k;
}
//------------------------------------------------------------------------------
Vector const& Basis::k() const
{
    return _k;
}
//==============================================================================
TransientBasis::TransientBasis(
    const Vector& vi, 
    const Vector& vj, 
    const Vector& vk
    ):
    _i(vi),
    _j(vj),
    _k(vk)
{
}
//------------------------------------------------------------------------------
Vector const& TransientBasis::i() const
{
    return _i;
}
//------------------------------------------------------------------------------
Vector const& TransientBasis::j() const
{
    return _j;
}
//------------------------------------------------------------------------------
Vector const& TransientBasis::k() const
{
    return _k;
}
//==============================================================================


}