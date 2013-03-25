#include "Signals.h"


namespace CppBikes
{




	ConnectableObject::~ConnectableObject()
	{
		std::map<BaseSignal*,int>::iterator pIter;
		for(pIter=signals_counter.begin(); pIter!=signals_counter.end(); pIter++)
		{
			pIter->first->disconnectAll_(parent_);
		}
	}

	ConnectableObject::ConnectableObject():parent_(0)
	{
		
	}



}