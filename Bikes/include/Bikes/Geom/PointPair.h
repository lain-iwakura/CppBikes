#ifndef INCLUDE_BIKES_GEOM_POINTPAIR_H
#define INCLUDE_BIKES_GEOM_POINTPAIR_H

#include <Bikes/Geom/VectorPair.h>
#include <Bikes/Geom/Point.h>

namespace Bikes
{

class IConstPointPair: public virtual IConstVectorPair
{
public:

    virtual ~IConstPointPair();

    virtual Point const& first() const = 0;

    virtual Point const& second() const = 0;

};

class  IPointPair: public IConstPointPair, public IVectorPair
{
public:
    virtual ~IPointPair();

    virtual Point& first() = 0;

    virtual Point& second() = 0;

};

class TransientConstPointPair: public IConstPointPair
{
public:
    Point const& p1;
    Point const& p2; 

    TransientConstPointPair(IConstPointPair const& pp);

    TransientConstPointPair(Point const& _p1, Point const& _p2);

    Point const& first() const;
    Point const& second() const;
};

class TransientPointPair: public IPointPair
{
public:
    Point& p1;
    Point& p2; 

    TransientPointPair(IPointPair& pp);

    TransientPointPair(Point& _p1, Point& _p2);

    Point const& first() const;
    Point const& second() const;
    Point& first();
    Point& second();
};

class PointPair: public IPointPair
{
public:
    Point p1;
    Point p2;

    PointPair();

    PointPair(Point const& _p1, Point const& _p2);
    
    PointPair(IConstPointPair const& pp);

    Point const& first() const;
    Point const& second() const;
    Point& first();
    Point& second();
};

}
#endif // <- INCLUDE_BIKES_GEOM_POINTPAIR_H
