#include <Bikes/Geom/PointPair.h>

namespace Bikes
{
    
IConstPointPair::~IConstPointPair()
{
}


IPointPair::~IPointPair()
{
}



Point& TransientPointPair::first()
{
    return p1;
}

const Point& TransientPointPair::first() const
{
    return p1;
}

Point& TransientPointPair::second()
{
    return p2;
}

const Point& TransientPointPair::second() const
{
    return p2;
}

TransientPointPair::TransientPointPair( Point& _p1, Point& _p2 ) :
    p1(_p1),
    p2(_p2)
{
}

TransientPointPair::TransientPointPair( IPointPair& pp ):
    p1(pp.first()),
    p2(pp.second())
{
}



TransientConstPointPair::TransientConstPointPair( IConstPointPair const& pp ):
    p1(pp.first()),
    p2(pp.second())
{
}

TransientConstPointPair::TransientConstPointPair( Point const& _p1, Point const& _p2 ):
    p1(_p1),
    p2(_p2)
{
}

Point const& TransientConstPointPair::first() const
{
    return p1;
}

Point const& TransientConstPointPair::second() const
{
    return p2;
}


PointPair::PointPair()
{
}

PointPair::PointPair( Point const& _p1, Point const& _p2 ):
    p1(_p1),
    p2(_p2)
{
}

PointPair::PointPair( IConstPointPair const& pp ):
    p1(pp.first()),
    p2(pp.second())
{
}

Point const& PointPair::first() const
{
    return p1;
}

Point& PointPair::first()
{
    return p1;
}

Point const& PointPair::second() const
{
    return p2;
}

Point& PointPair::second()
{
    return p2;
}

}