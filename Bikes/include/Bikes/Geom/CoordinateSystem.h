#ifndef INCLUDE_BIKES_GEOM_COORDINATESYSTEM_H
#define INCLUDE_BIKES_GEOM_COORDINATESYSTEM_H
#include <Bikes/Types.h>

namespace Bikes{

class Vector;
class Point;
//==============================================================================
struct Coordinates
{
    Coordinates(rnum _c1 = 0, rnum _c2 = 0, rnum _c3 = 0);

    rnum c1;
    rnum c2;
    rnum c3;
};
//==============================================================================
class ICoordinateSystem
{
public:
    virtual ~ICoordinateSystem();
    
    virtual rnum getCoordinate1(const Vector& v) const = 0;
    virtual rnum getCoordinate2(const Vector& v) const = 0;
    virtual rnum getCoordinate3(const Vector& v) const = 0;

    virtual Coordinates getCoordinates(const Vector& v) const;

    virtual void setCoordinate1(Vector& v, rnum coord1) const = 0;
    virtual void setCoordinate2(Vector& v, rnum coord2) const = 0;
    virtual void setCoordinate3(Vector& v, rnum coord3) const = 0;

    virtual void setCoordinates(Vector& v, rnum coord1, rnum coord2, rnum coord3) const;
    void setCoordinates(Vector& v, const Coordinates& coordinates) const;

};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_GEOM_COORDINATESYSTEM_H
