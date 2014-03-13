#ifndef INCLUDE_BIKES_GEOM_VECTORTRIPLE_H
#define INCLUDE_BIKES_GEOM_VECTORTRIPLE_H

#include <Bikes/Geom/Vector.h>

namespace Bikes
{

class IConstVectorTriple
{
public:
    virtual ~IConstVectorTriple();

    virtual Vector const& first() const = 0;

    virtual Vector const& second() const = 0;

    virtual Vector const& third() const = 0;

    inline Vector const& i() const {return first();}
    inline Vector const& j() const {return second();}
    inline Vector const& k() const {return third();}

    //TODO: funcs & operators
};

class IVectorTriple: public IConstVectorTriple
{
public:
    virtual ~IVectorTriple();

    virtual Vector& first() = 0;

    virtual Vector& second() = 0;

    virtual Vector& third() = 0;

    inline Vector& i() {return first();}
    inline Vector& j() {return second();}
    inline Vector& k() {return third();}

    //TODO: funcs & operators
};


class TransientConstVectorTriple: public IConstVectorTriple
{
public:
    Vector const& vi;
    Vector const& vj;
    Vector const& vk;

    TransientConstVectorTriple(Vector const& _vi, Vector const& _vj, Vector const& _vk);

    Vector const& first() const;
    Vector const& second() const;
    Vector const& third() const;
};

class TransientVectorTriple : public IVectorTriple
{
public:
	Vector& vi;
	Vector& vj;
	Vector& vk;

	TransientVectorTriple(Vector& _vi, Vector& _vj, Vector& _vk);

	Vector const& first() const;
	Vector const& second() const;
	Vector const& third() const;

	Vector& first();
	Vector& second();
	Vector& third();
};

class VectorTriple: public IVectorTriple
{
public:

    Vector vi;
    Vector vj;
    Vector vk;

    Vector const& first() const;
    Vector const& second() const;
    Vector const& third() const;
    Vector& first();
    Vector& second();
    Vector& third();
};

}

#endif // <- INCLUDE_BIKES_GEOM_VECTORTRIPLE_H
