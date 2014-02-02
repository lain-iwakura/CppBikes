#ifndef INCLUDEBIKES_BASISOBJECT_H
#define INCLUDEBIKES_BASISOBJECT_H

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

#endif