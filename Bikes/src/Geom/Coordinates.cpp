#include <Bikes/Geom/Coordinates.h>
#include <Bikes/Mathem.h>


namespace Bikes
{



CartesianCoordinates::CartesianCoordinates( rnum _x/*=0*/, rnum _y/*=0*/, rnum _z/*=0*/ ):
    x(_x),
    y(_y),
    z(_z)
{
}


CylindricalCoordinates toCylindricalCoordinates(const CartesianCoordinates& c)
{         
    rnum phi = 0;
    rnum r = sqrt(c.x*c.x+c.y*c.y);   

    if(r != 0)
    {
        phi = arccos(c.x/r);
        if(c.y < 0)
            phi = -phi;
    }
    
    return CylindricalCoordinates(phi,r,c.z);
}


CylindricalCoordinates::CylindricalCoordinates( rnum _phi/*=0*/, rnum _r/*=0*/, rnum _z/*=0*/ ):
    phi(_phi),
    r(_r),
    z(_z)
{
}


CartesianCoordinates toCartesianCoordinates(const CylindricalCoordinates& c)
{
    rnum co=cos(c.phi);
    rnum si=sqrt(1.0 - co*co);
    if(normAngle(c.phi) < 0)
        si = - si;

    return CartesianCoordinates(c.r*co,c.r*si,c.z);
}



}
