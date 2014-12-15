#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPETOOLS_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPETOOLS_H
#include <Bikes/TypeCollecting/TypeDetectors.h>

namespace Bikes
{
//==============================================================================
template<class T> struct NotConstNotPointerNotReference;
//------------------------------------------------------------------------------
namespace Inner{
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
} // Inner
//==============================================================================
template<class T>
struct NotConstNotPointerNotReference
{
    typedef typename ConstDetector< typename PointerDetector< 
        typename ReferenceDetector<T>::NotReference
        >::NotPointer>::NotConst ResultType;
};
//------------------------------------------------------------------------------
template<class T>
struct ClearType
{
    typedef typename Inner::ClearTypeAux<
        T, 
        typename NotConstNotPointerNotReference<T>::ResultType
        >::ResultType ResultType;
};
//==============================================================================
template<bool selectLeft, class LeftT, class RightT>
struct SelectType
{
    typedef LeftT ResultType;
};
template<class LeftT, class RightT>
struct SelectType<false,LeftT,RightT>
{
    typedef RightT ResultType;
};
//==============================================================================
template<class T1, class T2, template <class,class> class CompareT>
struct MinType
{
    typedef typename SelectType<
        CompareT<T1,T2>::greater,
        T2,
        T1
        >::ResultType ResultType;
};
//==============================================================================
template<class T1, class T2, template <class, class> class CompareT>
struct MaxType
{
    typedef typename SelectType<
        CompareT<T1, T2>::less,
        T2,
        T1
        >::ResultType ResultType;
};
//==============================================================================
template<class T>
struct IsNullType
{
    enum{
        result = TypeEqual<T, NullType>::result
    };
};
//==============================================================================
template<class T>
struct IsEmptyType
{
    enum{
        result = TypeEqual<T, EmptyType>::result
    };
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_TYPECOLLECTING_TYPETOOLS_H
