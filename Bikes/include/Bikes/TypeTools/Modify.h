#ifndef INCLUDE_BIKES_TYPETOOLS_MODIFY_H
#define INCLUDE_BIKES_TYPETOOLS_MODIFY_H

namespace Bikes{
namespace TT{
//==============================================================================
template<class T>
struct NotPointer
{
    typedef T ResultType;
};
//------------------------------------------------------------------------------
template<class T>
struct NotPointer<T*>
{
    typedef T ResultType;
};
//==============================================================================
template<class T>
struct NotReference
{
    typedef T ResultType;
};
//------------------------------------------------------------------------------
template<class T>
struct NotReference<T&>
{
    typedef T ResultType;
};
//==============================================================================
template<class T>
struct NotConst
{
    typedef T ResultType;
};
//------------------------------------------------------------------------------
template<class T>
struct NotConst<const T>
{
    typedef T ResultType;
};
//==============================================================================
template<class T>
struct NotConstPointer
{
    typedef T ResultType;
};
//------------------------------------------------------------------------------
template<class T>
struct NotConstPointer<const T*>
{
    typedef T ResultType;
};
//==============================================================================
template<class T>
struct NotConstReference
{
    typedef T ResultType;
};
//------------------------------------------------------------------------------
template<class T>
struct NotConstReference<const T&>
{
    typedef T ResultType;
};
//==============================================================================
template<class T>
struct NotConstNotPointerNotReference
{
    typedef typename NotConst< 
        typename NotPointer< 
            typename NotReference<T>::ResultType
            >::ResultType
        >::ResultType ResultType;
};
//==============================================================================
namespace Inner{
template<class T, class clearT>
struct ClearTypeAux
{
    typedef typename ClearTypeAux<
    clearT,
    typename NotConstNotPointerNotReference<clearT>::ResultType
    >::ResultType ResultType;
};
template<class T>
struct ClearTypeAux<T, T>
{
    typedef T ResultType;
};
} // Inner
//==============================================================================
template<class T>
struct Clear
{
    typedef typename Inner::ClearTypeAux<
        T, 
        typename NotConstNotPointerNotReference<T>::ResultType
        >::ResultType ResultType;
};
//==============================================================================
} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_MODIFY_H
