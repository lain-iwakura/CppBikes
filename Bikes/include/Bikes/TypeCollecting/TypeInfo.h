#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPEINFO_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPEINFO_H
#include <Bikes/Types.h>

namespace Bikes{
//==============================================================================
namespace Inner{

typedef char SmallType;
struct BigType { char c[2]; };
} // Inner
//==============================================================================
template<class BaseType, class ChildType>
class Hierrarchy
{
private:
    static Inner::SmallType _isChildType(BaseType*);
    static Inner::BigType _isChildType(void*);
public:
    enum{
        exists = sizeof(_isChildType((ChildType*)0)) == sizeof(Inner::SmallType)
    };    
};
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
class TypeInfo : public: TypeInfoBase
{
public:

    static const sznum id;

    template<class OtherT>
    class OtherType
    {
    public:
        enum{
            isChildType = Hierrarchy<T, OtherT>::exists,
            isParentType = Hierrarchy<OtherT, T>::exists
        };
    };
};
template<class T>
const sznum TypeInfo<T>::id = TypeInfoBase::_typeCount()++;
//==============================================================================
} // Bikes

#endif