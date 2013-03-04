#ifndef TYPEREGISTER_H
#define TYPEREGISTER_H
#include <CppBikes/TypeCollector.h>


namespace CppBikes
{	

//================================================================
	class GlobalTypeCollector: public TypeCollector<GlobalTypeCollector>
	{
	};
//================================================================
	typedef GlobalTypeCollector::TypeDataMap TypeDataMap;
//================================================================
	template<class T>
	class TypeDataArray: public GlobalTypeCollector::TypeDataArray<T>
	{
	};
//================================================================
	template<class T>
	class TypeRegister: public GlobalTypeCollector::TypeRegister<T>
	{
	};
//================================================================
	template<int collectionId>
	class TypeCollection: public GlobalTypeCollector::TypeCollection<collectionId>
	{
	};
//================================================================
	int typeCount();
//================================================================
	template<class T>
	int typeId()
	{
		return TypeRegister<T>::typeId;
	}
//================================================================

}



#endif