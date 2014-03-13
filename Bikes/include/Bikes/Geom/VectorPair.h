#ifndef INCLUDE_BIKES_GEOM_VECTORPAIR_H
#define INCLUDE_BIKES_GEOM_VECTORPAIR_H

#include <Bikes/Geom/Vector.h>

namespace Bikes
{

class IConstVectorPair
{
public:
    virtual ~IConstVectorPair();

    inline Vector const& vi() const {return first();}
    inline Vector const& vj() const {return second();}

    virtual Vector const& first() const = 0;

    virtual Vector const& second() const = 0;

};


class IVectorPair: public virtual IConstVectorPair
{
public:

    virtual ~IVectorPair();

    inline Vector& vi() {return first();}
    inline Vector& vj() {return second();}

    virtual Vector& first() = 0;

    virtual Vector& second() = 0;
};


class VectorPair: public IVectorPair
{
public:

	Vector vi;
	Vector vj;

	VectorPair();

    VectorPair(IConstVectorPair const& ij);

	VectorPair(Vector const& _vi, Vector const& _vj);

    Vector const& first() const;
    Vector const& second() const;
    Vector& first();
    Vector& second();
};


class TransientConstVectorPair: public IConstVectorPair
{
public:
    Vector const& vi;
    Vector const& vj;

    TransientConstVectorPair(IConstVectorPair const& ij);

    TransientConstVectorPair(Vector const& _vi, Vector const& _vj);

    Vector const& first() const;
    Vector const& second() const;    
};

class TransientVectorPair: public IVectorPair
{
public:
    Vector& vi;
    Vector& vj;

    TransientVectorPair(IVectorPair& ij);

    TransientVectorPair(Vector& vi, Vector& vj);

    Vector const& first() const;
    Vector const& second() const;
    Vector& first();
    Vector& second();
};




}

#endif // <- INCLUDE_BIKES_GEOM_VECTORPAIR_H
