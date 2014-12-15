#ifndef INCLUDE_BIKES_TYPETOOLS_DETECT_H
#define INCLUDE_BIKES_TYPETOOLS_DETECT_H
#include <Bikes/TypeTools/NullTypes.h>

namespace Bikes{
namespace TT{
//==============================================================================
template<class T>
struct IsConst
{
    enum{
        result = false
    };
};
//------------------------------------------------------------------------------
template<class T>
struct IsConst<const T>
{
    enum{
        result = true
    };
};
//==============================================================================
template<class T>
struct IsPointer
{
    enum{
        result = false
    };
};
//------------------------------------------------------------------------------
template<class T>
struct IsPointer<T*>
{
    enum{
        result = true
    };
};
//==============================================================================
template<class T>
struct IsConstPointer
{
    enum{
        result = false
    };
};
//------------------------------------------------------------------------------
template<class T>
struct IsConstPointer<const T*>
{
    enum{
        result = true
    };
};
//==============================================================================
template<class T>
struct IsReference
{
    enum{
        isReference = false
    };
    typedef T NotReference;
};
//------------------------------------------------------------------------------
template<class T>
struct IsReference<T&>
{
    enum{
        isReference = true
    };
    typedef T NotReference;
};
//==============================================================================
template<class T>
struct IsConstReference
{
    enum{
        isConstReference = false
    };
};
//------------------------------------------------------------------------------
template<class T>
struct IsConstReference<const T&>
{
    enum{
        isConstReference = true
    };
};
//==============================================================================
template<class T>
struct IsNullType
{
    enum{
        result = false
    };
};
//------------------------------------------------------------------------------
template<>
struct IsNullType<NullType>
{
    enum{
        result = true
    };
};
//==============================================================================
template<class T>
struct IsEmptyType
{
    enum{
        result = false
    };
};
//------------------------------------------------------------------------------
template<>
struct IsEmptyType<EmptyType>
{
    enum{
        result = true
    };
};
//==============================================================================
} // TT
} // Bikes

#endif // <- INCLUDE_BIKES_TYPETOOLS_DETECT_H
