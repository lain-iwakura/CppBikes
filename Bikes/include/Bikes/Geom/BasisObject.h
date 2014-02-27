#ifndef INCLUDE_BIKES_GEOM_BASISOBJECT_H
#define INCLUDE_BIKES_GEOM_BASISOBJECT_H

namespace Bikes
{

class Basis;
class BasisReference;

class BasisObject
{
public:
	BasisObject();
	virtual ~BasisObject();
	void setBasis(const BasisReference* br); //?
	const Basis* getBasis() const;
protected:
	virtual void _basisChanged(const Basis* oldBasis, const Basis* newBasis);	
private:
	BasisReference *_br;
};

}

#endif // <- INCLUDE_BIKES_GEOM_BASISOBJECT_H
