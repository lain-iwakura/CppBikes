#ifndef INCLUDE_BIKES_TYPETOOLS_INFO_H
#define INCLUDE_BIKES_TYPETOOLS_INFO_H
#include <Bikes/Types.h>
#include <Bikes/TypeTools/Detect.h>
#include <Bikes/TypeTools/Compare.h>
#include <Bikes/TypeTools/Modify.h>

namespace Bikes{
namespace TT{
//==============================================================================
class InfoBase
{
public:
    static sznum typeCount();
protected:
    static sznum& _typeCount();
};
//------------------------------------------------------------------------------
template<class T>
class Info : public InfoBase
{
public:

    typedef T Type;
    typedef typename Clear<T>::ResultType Clear;

    enum{
        isReference = IsReference<T>::isReference,
        isConstReference = IsConstReference<T>::isConstReference,
        isPointer = IsPointer<T>::isPointer,
        isConstPointer = IsConstPointer<T>::isConstPointer,
        isConst = IsConst<T>::isConst,        
    };

    template<class OtherT>
    class OtherType
    {
    public:
        enum{
            isChildType = HierrarchyExists<T, OtherT>::result,
            isParentType = HierrarchyExists<OtherT, T>::result,
            isEqualType = Equal<T, OtherT>::result
        };
    };

    static const sznum id;
};
template<class T>
const sznum Info<T>::id = InfoBase::_typeCount()++;
//==============================================================================
} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_INFO_H
