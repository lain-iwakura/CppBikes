#ifndef INCLUDEBIKES_VECTORTRIPLE_H
#define INCLUDEBIKES_VECTORTRIPLE_H

#include <Bikes/Geometry/Vector.h>
#include <Bikes/Geometry/VectorPair.h>

namespace Bikes
{
class VectorPair;

class Basis
{
public:
	Vector i;
	Vector j;
	Vector k;

	Basis(const Vector& vi, const Vector& vj, const Vector& vk);	

	Basis(const VectorPair& pair_ij, const Vector& vk);

	Basis(const Vector& vi, const VectorPair& pair_jk);

	Basis(const Basis& ijk);

	Basis(const Vector& vi, const Vector& vj, bool right=true);

	Basis(const VectorPair& pair_ij, bool right=true);

	virtual ~Basis();

	void normalize();

	void setScale(rnum scale);

	void scaling(rnum scaleFactor);

	void setOrtonormalByIJ(const Vector& vi, const Vector& vj, bool right=true);

	void setOrtonormalByIJ(const VectorPair& ij, bool right=true);

};



}

#endif