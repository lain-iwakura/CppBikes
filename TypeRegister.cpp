#include "TypeRegister.h"

namespace CppBikes
{
	int BaseTypeRegister::typeIter=0;

	int BaseTypeRegister::typeCount()
	{
		return typeIter;
	}	
}