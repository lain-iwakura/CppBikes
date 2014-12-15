#ifndef INCLUDE_BIKES_TYPETOOLS_COMPARE_H
#define INCLUDE_BIKES_TYPETOOLS_COMPARE_H
#include <Bikes/TypeTools/NullTypes.h>

namespace Bikes{
namespace TT{
//==============================================================================
template<class BaseType, class ChildType>
class HierrarchyExists
{
private:
    static SmallType _isChildType(BaseType*);
    static BigType _isChildType(void*);
public:
    enum{
        result = 
            sizeof(_isChildType((ChildType*)0)) ==
            sizeof(SmallType)
    };    
};
//------------------------------------------------------------------------------
template<class T>
class HierrarchyExists<T,T>
{
public:
    enum{
        result = false
    };
};
//==============================================================================
template<class T1, class T2>
struct Equal
{
    enum{
        result = false
    };
};
//------------------------------------------------------------------------------
template<class T>
struct Equal<T, T>
{
    enum{
        result = true
    };
};
//==============================================================================
template<class T1, class T2>
struct CompareByHierrarchy
{
    enum{
        greater = HierrarchyExists<T1, T2>::result,
        less = HierrarchyExists<T2, T1>::result,
        equal = Equal<T1, T2>::result,
        greater_or_equal = greater || equal,
        less_or_equal = less || equal,
        disparate = !(greater || less || equal)
    };
};
//==============================================================================
} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_COMPARE_H
