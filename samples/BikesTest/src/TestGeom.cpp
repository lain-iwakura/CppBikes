#include <Bikes/Geom/Vector.h>
#include <Bikes/Geom/Basis.h>
#include "Tests.h"
#include <iostream>
#include <Bikes/Testing.h>

using namespace Bikes;


void test_Geom()
{
    Vector v(1, 2, 3);

    Basis b(
        Vector(11,11,11),
        -Vector(22, 0, 1),
        Vector(0, -33, 1)
        );

    b.setCoordinates(v, 1, 2, 3);

    
    BIKES_COUT_VAR(v.x());
    BIKES_COUT_VAR(v.y());
    BIKES_COUT_VAR(v.z());

    BIKES_COUT_VAR(b.i() & v);

    rnum ll = b.i().l(); 
    ll *= ll;
    BIKES_COUT_VAR( (b.i() & v)/ll );

    BIKES_COUT_VAR(( (b.i()&v) - (b.i()&b.j())*2 -  (b.i()&b.k())*3) / ll);

    BIKES_COUT_VAR(b.getX(v));
    BIKES_COUT_VAR(b.getY(v));
    BIKES_COUT_VAR(b.getZ(v));

    b.setX(v, 13);
    BIKES_COUT_VAR(b.getX(v));
    BIKES_COUT_VAR(b.getY(v));
    BIKES_COUT_VAR(b.getZ(v));
}
