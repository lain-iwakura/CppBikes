#ifndef INCLUDE_BIKES_GEOM_AFFINECOORDINATESYSTEM_H
#define INCLUDE_BIKES_GEOM_AFFINECOORDINATESYSTEM_H

#include <Bikes/Geom/CoordinateSystem.h>
#include <Bikes/Geom/Basis.h>
#include <Bikes/Geom/Point.h>

namespace Bikes{

class AffineCoordinateSystem:
    public ICoordinateSystem,
    public Basis
{
public:

    rnum getCoordinate1(const Vector& v) const; // x
    rnum getCoordinate2(const Vector& v) const; // y
    rnum getCoordinate3(const Vector& v) const; // z

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

    const Point& getOrigin() const;

protected:
    Point _origin;
};

}



#endif // <- INCLUDE_BIKES_GEOM_AFFINECOORDINATESYSTEM_H
