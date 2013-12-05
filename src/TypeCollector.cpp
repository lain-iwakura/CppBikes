#include "TypeCollector.h"



namespace Bikes
{

	int BaseTypeGlobalRegister::tc=0;
	
	int BaseTypeGlobalRegister::typeCount()
	{
		return tc;
	}

}// Bikes