#include <Bikes/Geometry/BasisObject.h>
#include <Bikes/Geometry/BasisReference.h>
#include <Bikes/Geometry/Basis.h>


namespace Bikes
{


BasisObject::BasisObject():
	_br(0)
{
}

BasisObject::~BasisObject()
{
	if(_br)
		delete _br;
}

void BasisObject::_basisChanged( const Basis* oldBasis, const Basis* newBasis )
{
}

const Basis* BasisObject::getBasis() const
{
	if(_br)
		return _br->getBasis();
	return 0;
}

void BasisObject::setBasis( const BasisReference* br )
{
	const Basis* oldBasis=0;
	const Basis* newBasis=0;

	if(_br)
		oldBasis = _br->getBasis();
	if(br)
		newBasis = br->getBasis();

	if(oldBasis != newBasis)
		_basisChanged(oldBasis,newBasis);
}

} // <- namespace Bikes