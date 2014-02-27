#ifndef INCLUDE_BIKES_GEOM_BASISREFERENCE_H
#define INCLUDE_BIKES_GEOM_BASISREFERENCE_H

namespace Bikes
{

class Basis;
class BasisObject;

class BasisReference
{
public:
	virtual ~BasisReference();
	virtual BasisReference* newReference(const BasisObject& obj) const = 0;
	virtual const Basis* getBasis() const = 0;	
};

} 

#endif // <- INCLUDE_BIKES_GEOM_BASISREFERENCE_H
