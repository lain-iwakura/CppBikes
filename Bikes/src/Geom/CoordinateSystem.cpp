#include <Bikes/Geom/CoordinateSystem.h>


namespace Bikes{
//==============================================================================
Coordinates::Coordinates(rnum _c1 /*= 0*/, rnum _c2 /*= 0*/, rnum _c3 /*= 0*/):
c1(_c1),
c2(_c2),
c3(_c3)
{
}
//==============================================================================
ICoordinateSystem::~ICoordinateSystem()
{
}

Bikes::Coordinates ICoordinateSystem::getCoordinates(const Vector& v) const
{
    return Coordinates(getCoordinate1(v), getCoordinate2(v), getCoordinate3(v));
}

void ICoordinateSystem::setCoordinates(Vector& v, rnum coord1, rnum coord2, rnum coord3) const
{
    setCoordinate1(v, coord1);
    setCoordinate2(v, coord2);
    setCoordinate3(v, coord3);
}

void ICoordinateSystem::setCoordinates(Vector& v, const Coordinates& coordinates) const
{
    setCoordinates(v, coordinates.c1, coordinates.c2, coordinates.c3);
}

//==============================================================================
}