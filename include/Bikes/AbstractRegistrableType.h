#ifndef _BIKES_ABSTRACTREGISTRABLETYPE_H_
#define _BIKES_ABSTRACTREGISTRABLETYPE_H_

#include <Bikes/TypeCollector.h>

namespace Bikes
{
//*


#define BIKES_REGISTRABLETYPE_DECL(ThisType)\
	virtual int getTypeId() const {return typeIdFor<ThisType>();}\
	static int typeId(){return typeIdFor<ThisType>();}\
	virtual const char* getTypeName() const{return typeName();}\
	static const char* typeName() {static const char* tn=#ThisType; return tn;}


template<class ACollectorClass>
class AbstractRegistrableType
{
    typedef /*typename*/ TypeCollector<AbstractRegistrableType<ACollectorClass> >/*::TypeCollection<1>*/ TypesCollection;
//	typedef typename TypeCollector<AbstractRegistrableType<ACollectorClass> >::TypeCollection<2> CollectorCollection;
public:

	virtual~AbstractRegistrableType(){}
	
//	template<class TCollectorClass>
//	int typeIdForCollector() const
//	{
//		return ids[CollectorCollection::typeId<TCollectorClass>()][typeId()]; //TypeCollector<TCollectorClass>::typeId<thisType>()
//	}
	
	virtual int getTypeId() const = 0;

	virtual const char* getTypeName() const = 0;

	static int typesCount()
	{
		return TypesCollection::typeCount();
	}


//~~~~~~~~~~~~~
/*
	static int typeIdByTypeName(const char * tname)
	{
	}
	static const char* typeNameByTypeId(int tId)
	{
	}
//*/
protected:

	template<class ThisType> 
    static int typeIdFor(){return TypesCollection::template typeId<ThisType>();}

//private:
// [TCollectorClass_id][ObjectType_id] typeIdForCollector
//	static std::vector<std::vector<int> > ids;
	
};



}

#endif
