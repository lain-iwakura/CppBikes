#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPEINFO_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPEINFO_H
#include <Bikes/Types.h>
#include <Bikes/TypeCollecting/TypeDetectors.h>
#include <Bikes/TypeCollecting/TypeHierrarchy.h>
#include <Bikes/TypeCollecting/TypeTools.h>

namespace Bikes{
//==============================================================================
class TypeInfoBase
{
public:
    static sznum typeCount();
protected:
    static sznum& _typeCount();
};
//------------------------------------------------------------------------------
template<class T>
class TypeInfo : public TypeInfoBase
{
public:

    typedef T Type;
    typedef typename ClearType<T>::ResultType ClearType;

    typedef typename ReferenceDetector<T>::NotReference NotReference;
    typedef typename PointerDetector<NotReference>::NotPointer NotPointerNotReference;    
    typedef typename ConstDetector<NotPointerNotReference>::NotConst NotConstNotPointerNotReference;

    enum{
        isReference = ReferenceDetector<T>::isReference,
        isConstReference = ConstReferenceDetector<T>::isConstReference,
        isPointer = PointerDetector<T>::isPointer,
        isConstPointer = ConstPointerDetector<T>::isConstPointer,
        isConst = ConstDetector<T>::isConst,        
    };

    template<class OtherT>
    class OtherType
    {
    public:
        enum{
            isChildType = TypeHierrarchy<T, OtherT>::exists,
            isParentType = TypeHierrarchy<OtherT, T>::exists,
            isEqualType = TypeEqual<T, OtherT>::result
        };
    };

    static const sznum id;
};
template<class T>
const sznum TypeInfo<T>::id = TypeInfoBase::_typeCount()++;
//==============================================================================
} // Bikes
#endif // <- INCLUDE_BIKES_TYPECOLLECTING_TYPEINFO_H
