#ifndef INCLUDE_BIKES_GEOM_VECTORATPOINT_H
#define INCLUDE_BIKES_GEOM_VECTORATPOINT_H

#include <Bikes/Geom/Point.h>

namespace Bikes 
{

class VectorAtPoint: public Vector
{
public:

    Point anchor;

    VectorAtPoint();
    

};

}

#endif // <- INCLUDE_BIKES_GEOM_VECTORATPOINT_H
