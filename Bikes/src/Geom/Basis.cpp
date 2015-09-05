#include <Geom/Basis.h>
#include <Geom/VectorPair.h>

namespace Bikes
{
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
    setRightOrtonormal(ij.vi, ij.vj);
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
    setLeftOrtonormal(ij.vi, ij.vj);
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
	_i(pair_ij.vi),
	_j(pair_ij.vj),
	_k(vk)
{
}
//------------------------------------------------------------------------------
Basis::Basis( const Vector& vi, const VectorPair& pair_jk ):
	_i(vi),
	_j(pair_jk.vi),
	_k(pair_jk.vj)
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
TransientConstBasis::TransientConstBasis(
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
Vector const& TransientConstBasis::i() const
{
    return _i;
}
//------------------------------------------------------------------------------
Vector const& TransientConstBasis::j() const
{
    return _j;
}
//------------------------------------------------------------------------------
Vector const& TransientConstBasis::k() const
{
    return _k;
}
//==============================================================================
TransientBasis::TransientBasis(
    Vector& vi, 
    Vector& vj, 
    Vector& vk
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
Vector& TransientBasis::i()
{
    return _i;
}
//------------------------------------------------------------------------------
Vector const& TransientBasis::j() const
{
    return _j;
}
//------------------------------------------------------------------------------
Vector& TransientBasis::j()
{
    return _j;
}
//------------------------------------------------------------------------------
Vector const& TransientBasis::k() const
{
    return _k;
}
//------------------------------------------------------------------------------
Vector& TransientBasis::k()
{
    return _k;
}
//==============================================================================
}