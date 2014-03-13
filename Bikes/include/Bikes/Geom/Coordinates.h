#ifndef INCLUDE_BIKES_GEOM_COORDINATES_H
#define INCLUDE_BIKES_GEOM_COORDINATES_H

#include <Bikes/Types.h>

namespace Bikes
{
    

struct CartesianCoordinates 
{
    CartesianCoordinates(rnum _x=0, rnum _y=0, rnum _z=0);

    rnum x;
    rnum y;
    rnum z;

};

struct CylindricalCoordinates
{
    CylindricalCoordinates(rnum _phi=0, rnum _r=0, rnum _z=0); 

    rnum phi;
    rnum r;
    rnum z;


};

CylindricalCoordinates toCylindricalCoordinates(const CartesianCoordinates& cartesian);

CartesianCoordinates toCartesianCoordinates(const CylindricalCoordinates& cylindrical);

}


#endif // <- INCLUDE_BIKES_GEOM_COORDINATES_H
