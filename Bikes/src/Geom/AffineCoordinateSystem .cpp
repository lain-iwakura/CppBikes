#include <Bikes/Geom/AffineCoordinateSystem.h>

namespace Bikes
{

Bikes::rnum AffineCoordinateSystem::getCoordinate1(const Vector& v) const
{
    return getX(v);
}

Bikes::rnum AffineCoordinateSystem::getCoordinate2(const Vector& v) const
{
    return getY(v);
}

Bikes::rnum AffineCoordinateSystem::getCoordinate3(const Vector& v) const
{
    return getZ(v);
}

void AffineCoordinateSystem::setCoordinate1(Vector& v, rnum x) const
{
    setX(v, x);
}

void AffineCoordinateSystem::setCoordinate2(Vector& v, rnum y) const
{
    setY(v, y);
}

void AffineCoordinateSystem::setCoordinate3(Vector& v, rnum z) const
{
    setZ(v, z);
}

void AffineCoordinateSystem::setCoordinates(Vector& v, rnum x, rnum y, rnum z) const
{
    v.rx() = x*(this->i().x()) + y*(this->j().x()) + z*(this->k().x()) + _origin.x();
    v.ry() = x*(this->i().y()) + y*(this->j().y()) + z*(this->k().y()) + _origin.y();
    v.rz() = x*(this->i().z()) + y*(this->j().z()) + z*(this->k().z()) + _origin.z();
}

Bikes::rnum AffineCoordinateSystem::getX(const Vector& v) const
{
    return (v.x()-_origin.x()) * (this->_i.x()) +
        (v.y() - _origin.y()) * (this->_i.y()) +
        (v.z() - _origin.z()) * (this->_i.z());
}

Bikes::rnum AffineCoordinateSystem::getY(const Vector& v) const
{
    return (v.x() - _origin.x()) * (this->_j.x()) +
        (v.y() - _origin.y()) * (this->_j.y()) +
        (v.z() - _origin.z()) * (this->_j.z());
}

Bikes::rnum AffineCoordinateSystem::getZ(const Vector& v) const
{
    return (v.x() - _origin.x()) * (this->_k.x()) +
        (v.y() - _origin.y()) * (this->_k.y()) +
        (v.z() - _origin.z()) * (this->_k.z());
}

void AffineCoordinateSystem::setX(Vector& v, rnum x) const
{

}

void AffineCoordinateSystem::setY(Vector& v, rnum y) const
{

}

void AffineCoordinateSystem::setZ(Vector& v, rnum z) const
{

}

const Point& AffineCoordinateSystem::getOrigin() const
{
    return _origin;
}

}