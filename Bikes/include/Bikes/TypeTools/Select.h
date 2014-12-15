#ifndef INCLUDE_BIKES_TYPETOOLS_SELECT_H
#define INCLUDE_BIKES_TYPETOOLS_SELECT_H

namespace Bikes{
namespace TT{
//==============================================================================
template<bool selectLeft, class LeftT, class RightT>
struct Select
{
    typedef LeftT ResultType;
};
//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct Select<false, LeftT, RightT>
{
    typedef RightT ResultType;
};
//==============================================================================
template<class T1, class T2, template <class,class> class CompareT>
struct MinType
{
    typedef typename Select<CompareT<T1,T2>::greater,T2,T1>::ResultType ResultType;
};
//==============================================================================
template<class T1, class T2, template <class, class> class CompareT>
struct MaxType
{
    typedef typename Select<CompareT<T1, T2>::less,T2,T1>::ResultType ResultType;
};
//==============================================================================
} // TT
} // Bikes

#endif // <- INCLUDE_BIKES_TYPETOOLS_SELECT_H
