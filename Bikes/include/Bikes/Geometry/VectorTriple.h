#ifndef INCLUDEBIKES_VECTORTRIPLE_H
#define INCLUDEBIKES_VECTORTRIPLE_H

#include <Bikes/Geometry/Vector.h>
#include <Bikes/Geometry/VectorPair.h>

namespace Bikes
{
class VectorPair;

class VectorTriple
{
public:
	Vector i;
	Vector j;
	Vector k;

	VectorTriple(const Vector& vi, const Vector& vj, const Vector& vk);

	VectorTriple(const VectorPair& pair_ij, const Vector& vk);

	VectorTriple(const Vector& vi, const VectorPair& pair_jk);

	VectorTriple(const VectorTriple& ijk);

	virtual ~VectorTriple();

	void normalize();

	void setScale(rnum scale);

	void scaling(rnum scaleFactor);

	void setOrtonormalByIJ(const Vector& vi, const Vector& vj, bool right=true);

	void setOrtonormalByIJ(const VectorPair& ij, bool right=true);

};



}

#endif