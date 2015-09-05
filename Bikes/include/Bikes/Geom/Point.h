#ifndef INCLUDE_BIKES_GEOM_POINT_H
#define INCLUDE_BIKES_GEOM_POINT_H

#include <Bikes/Geom/Vector.h>

namespace Bikes
{

class Point: 
    public Vector // не имеет виртуального деструктора (!)
{
public:

};

}

#endif // <- INCLUDE_BIKES_GEOM_POINT_H
