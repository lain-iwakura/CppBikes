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

	ConnectableObject::ConnectableObject():parent_(0),cur_emitter_(0)
	{
		
	}

	BaseEmitter* ConnectableObject::emitter()
	{
		return cur_emitter_;
	}




	BaseSignal::BaseSignal() :emitter_(0)
	{

	}

	BaseSignal::~BaseSignal()
	{
		if(emitter_) delete emitter_;
	}

	BaseEmitter* BaseSignal::emitter() const
	{
		return emitter_;
	}


	BaseSlot::~BaseSlot()
	{
		delete emitters;
	}

	BaseSlot::BaseSlot()
	{
		emitters=new std::vector<BaseEmitter*> ();
	}

}