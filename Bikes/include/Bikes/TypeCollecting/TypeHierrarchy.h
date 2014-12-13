#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPEHIERRARCHY_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPEHIERRARCHY_H
#include <Bikes/TypeCollecting/NullTypes.h>

namespace Bikes
{
//==============================================================================
template<class BaseType, class ChildType—andidate>
class TypeHierrarchy
{
private:
    static Inner::SmallType _isChildType(BaseType*);
    static Inner::BigType _isChildType(void*);
public:
    enum{
        exists = sizeof(_isChildType((ChildType—andidate*)0)) == sizeof(Inner::SmallType)
    };    
};
template<class T>
class TypeHierrarchy<T,T>
{
public:
    enum{
        exists = false
    };
};
//==============================================================================
template<class T1, class T2>
struct TypeEqual
{
    enum{
        result = false
    };
};
template<class T>
struct TypeEqual<T, T>
{
    enum{
        result = true
    };
};
//==============================================================================
} // Bikes
#endif // <- INCLUDE_BIKES_TYPECOLLECTING_TYPEHIERRARCHY_H
