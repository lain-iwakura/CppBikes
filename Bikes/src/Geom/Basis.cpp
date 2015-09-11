#include <Geom/Basis.h>
#include <Geom/VectorPair.h>

namespace Bikes
{
//==============================================================================
IConstBasis::~IConstBasis()
{
}
//------------------------------------------------------------------------------
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
     return v & inv_i();
}
//------------------------------------------------------------------------------
Bikes::rnum IConstBasis::getY(const Vector& v) const
{
    return v & inv_j();
}
//------------------------------------------------------------------------------
Bikes::rnum IConstBasis::getZ(const Vector& v) const
{
    return v & inv_k();
}
//------------------------------------------------------------------------------
void IConstBasis::setX(Vector& v, rnum x) const
{
    v += i() * (x - getX(v));
}
//------------------------------------------------------------------------------
void IConstBasis::setY(Vector& v, rnum y) const
{
    v += j() * (y - getY(v));
}
//------------------------------------------------------------------------------
void IConstBasis::setZ(Vector& v, rnum z) const
{
    v += k() * (z - getZ(v));
}
//==============================================================================
namespace Inner{
//==============================================================================
void BaseBasis::normalize()
{
    ri().normalize();
    rj().normalize();
    rk().normalize();
}
//------------------------------------------------------------------------------
void BaseBasis::setScale(rnum scale)
{
    ri().setLength(scale);
    rj().setLength(scale);
    rk().setLength(scale);
}
//------------------------------------------------------------------------------
void BaseBasis::scale(rnum scaleFactor)
{
    ri() *= scaleFactor;
    rj() *= scaleFactor;
    rk() *= scaleFactor;
}
//------------------------------------------------------------------------------
void BaseBasis::setRightOrtonormal(const Vector& vi, const Vector& vj)
{
    ri() = vi;
    rk() = vi*vj;
    ri().normalize();
    rk().normalize();
    rj() = rk()*ri();
}
//------------------------------------------------------------------------------
void BaseBasis::setRightOrtonormal(const VectorPair& ij)
{
    setRightOrtonormal(ij.i(), ij.j());
}
//------------------------------------------------------------------------------
void BaseBasis::setLeftOrtonormal(const Vector& vi, const Vector& vj)
{
    ri() = vi;
    rk() = vi*vj;
    ri().normalize();
    rk().normalize();
    rj() = ri()* rk();
}
//------------------------------------------------------------------------------
void BaseBasis::setLeftOrtonormal(const VectorPair& ij)
{
    setLeftOrtonormal(ij.i(), ij.j());
}
//==============================================================================
Vector const& InvBasisBase::inv_i() const
{
    _recalc_inv();
    return _inv_i;
}

Vector const& InvBasisBase::inv_j() const
{
    _recalc_inv();
    return _inv_j;
}

Vector const& InvBasisBase::inv_k() const
{
    _recalc_inv();
    return _inv_k;
}

void InvBasisBase::_recalc_inv() const
{
    InvBasisBase* const _ = const_cast<InvBasisBase*>(this);
    if (_recalc)
    {
        _->_recalc = false;
        const Vector& _i = i();
        const Vector& _j = j();
        const Vector& _k = k();
        rnum d = _i & _j* _k;
        if (d != 0)
        {
            _->_inv_i = _j*_k; _->_inv_i /= d;
            _->_inv_j = _k*_i; _->_inv_j /= d;
            _->_inv_k = _i*_j; _->_inv_k /= d;
        }else
        {
            _->_inv_i.setGlobal(0, 0, 0);
            _->_inv_j.setGlobal(0, 0, 0);
            _->_inv_k.setGlobal(0, 0, 0);
        }
    }
}

void InvBasisBase::recalc_inv_later()
{
    _recalc = true;
}

InvBasisBase::InvBasisBase():
_recalc(true)
{
}

//==============================================================================
} // Inner
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
Vector& Basis::ri()
{
    recalc_inv_later();
    return _i;
}
//------------------------------------------------------------------------------
Vector const& Basis::i() const
{
    return _i;
}
//------------------------------------------------------------------------------
Vector& Basis::rj()
{
    recalc_inv_later();
    return _j;
}
//------------------------------------------------------------------------------
Vector const& Basis::j() const
{
    return _j;
}
//------------------------------------------------------------------------------
Vector& Basis::rk()
{
    recalc_inv_later();
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