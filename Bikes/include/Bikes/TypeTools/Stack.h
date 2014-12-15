#ifndef INCLUDE_BIKES_TYPETOOLS_STACK_H
#define INCLUDE_BIKES_TYPETOOLS_STACK_H
#include <Bikes/TypeTools/NullTypes.h>
#include <Bikes/TypeTools/Select.h>
#include <Bikes/MacrosBikes.h>

#define BIKES_TYPESTACK_1(T1) Bikes::TT::Stack::Element<T1,Bikes::TT::NullType>
#define BIKES_TYPESTACK_2(T1,T2) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_1(T2) >
#define BIKES_TYPESTACK_3(T1,T2,T3) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_2(T2,T3) >
#define BIKES_TYPESTACK_4(T1,T2,T3,T4) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_3(T2,T3,T4) >
#define BIKES_TYPESTACK_5(T1,T2,T3,T4,T5) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_4(T2,T3,T4,T5) >
#define BIKES_TYPESTACK_6(T1,T2,T3,T4,T5,T6) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_5(T2,T3,T4,T5,T6) >
#define BIKES_TYPESTACK_7(T1,T2,T3,T4,T5,T6,T7) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_6(T2,T3,T4,T5,T6,T7) >
#define BIKES_TYPESTACK_8(T1,T2,T3,T4,T5,T6,T7,T8) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_7(T2,T3,T4,T5,T6,T7,T8) >
#define BIKES_TYPESTACK_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) Bikes::TT::Stack::Element<T1,BIKES_TYPESTACK_8(T2,T3,T4,T5,T6,T7,T8,T9) > 

#define TBIKES_TYPESTACK_T9 BIKES_TYPESTACK_9(T1,T2,T3,T4,T5,T6,T7,T8,T9)

#define INNERBIKES_TO_S(T) \
    typename Bikes::TT::Inner::ToStackToStack<T>::ResultStack

#define TBIKES_TO_TYPESTACK_T9 \
    BIKES_TYPESTACK_9(INNERBIKES_TO_S(T1), INNERBIKES_TO_S(T2), INNERBIKES_TO_S(T3), INNERBIKES_TO_S(T4), INNERBIKES_TO_S(T5), INNERBIKES_TO_S(T6), INNERBIKES_TO_S(T7), INNERBIKES_TO_S(T8), INNERBIKES_TO_S(T9))


namespace Bikes{
namespace TT{
namespace Stack{
//==============================================================================
template<class LeftT, class  RightT>
struct Element
{
    typedef LeftT Head;
    typedef Element<RightT,NullType> Tail;
};
//------------------------------------------------------------------------------
template<class T>
struct Element<NullType, T>
{
    typedef T Head;
    typedef NullType Tail;
};
//------------------------------------------------------------------------------
template<class T>
struct Element<T, NullType>
{
    typedef T Head;
    typedef NullType Tail;
};
//------------------------------------------------------------------------------
template<>
struct Element<NullType, NullType>
{
    typedef NullType Head;
    typedef NullType Tail;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3 >
struct Element<T1,Element<T2, T3> >
{
    typedef T1 Head;
    typedef typename Select<
        IsNullType<typename Element<T2, T3>::Head>::result,
        NullType,
        Element<T2, T3>
        >::ResultType Tail;    
};
template<class T1, class T2 >
struct Element<NullType, Element<T1, T2> >
{
    typedef typename Element<T1, T2>::Head Head;
    typedef typename Element<T1, T2>::Tail Tail;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3 >
struct Element<Element<T1, T2>, T3>
{

    typedef typename Select<
    Equal<typename Element<T1, T2>::Head, NullType>::result,
    T3,
    typename Element<T1, T2>::Head
    >
    ::ResultType Head;

    typedef Element<typename Element<T1, T2>::Tail, T3> Tail;
};
//------------------------------------------------------------------------------
template<class T1, class T2>
struct Element<Element<T1, T2>, NullType>
{
    typedef typename Element<T1, T2>::Head Head;
    typedef typename Element<T1, T2>::Tail Tail;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3, class T4>
struct Element<Element<T1, T2>, Element<T3,T4> >
{
    typedef typename Select<
    Equal<typename Element<T1, T2>::Head, NullType>::result,
    typename Element<T3, T4>::Head,
    typename Element<T1, T2>::Head
    >
    ::ResultType Head;

    typedef typename Select<
        Equal<typename Element<T1, T2>::Head, NullType>::result,
        typename Element<T3, T4>::Tail,
        Element<typename Element<T1, T2>::Tail, Element<T3, T4> >
        >
        ::ResultType Tail;
};
//==============================================================================
template<class T>
struct Count
{
    enum{
        result = 1
    };
};
//------------------------------------------------------------------------------
template<>
struct Count<NullType>
{
    enum{
        result = 0
    };
};
//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct Count<Element<LeftT, RightT> >
{
    enum{
        result = Count<typename Element<LeftT, RightT>::Head>::result
        + Count<typename Element<LeftT, RightT>::Tail >::result
    };
};
//==============================================================================
template<class StackT, class RequiredT>
struct IndexOf
{
    enum{
        result = -1
    };
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3>
struct IndexOf<T1, Element<T2,T3> >
{
    enum{
        result = 
            (Equal<typename Element<T2, T3>::Head, T1>::result) ? (0) : (
                (IndexOf<T1, typename Element<T2, T3>::Tail>::result == -1)? 
                (-1) : 
                (IndexOf<T1, typename Element<T2, T3>::Tail>::result + 1)
                )
    };
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3>
struct IndexOf<Element<T2, T3>, T1 >
{
    enum{
        result = IndexOf<T1, Element<T2, T3>>::result
    };
};
//==============================================================================
template<class StackT, num i>
struct TypeAt
{
    typedef NullType ResultType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, num i>
struct TypeAt<Element<T1,T2>, i>
{
    typedef typename Select<
    i < 0,
    NullType,
    typename TypeAt<typename Element<T1, T2>::Tail, i - 1 >::ResultType
    >
    ::ResultType ResultType;
};
//------------------------------------------------------------------------------
template<class T1, class T2>
struct TypeAt<Element<T1, T2>, 0>
{
    typedef typename Element<T1, T2>::Head ResultType;
};
//==============================================================================
template<class StackT, class RemoveT>
struct Remove
{
    typedef NullType ResultStack;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class RemoveT>
struct Remove<Element<T1, T2>, RemoveT>
{
    typedef typename Select<
        Equal<typename Element<T1, T2>::Head, RemoveT>::result
        ,
        typename Element<T1, T2>::Tail
        ,
        Element<
            typename Element<T1, T2>::Head,
            typename Remove<typename Element<T1,T2>::Tail, RemoveT>::ResultStack
            >
        >
        ::ResultType ResultStack;
};
//==============================================================================
template<class StackT>
struct RemoveDuplicates
{
    typedef StackT ResultStack;
};
//------------------------------------------------------------------------------
template<class T1, class T2>
struct RemoveDuplicates<Element<T1,T2> >
{
    typedef typename Select<
        IndexOf<
            typename Element<T1, T2>::Tail, 
            typename Element<T1, T2>::Head
            >::result != -1
        ,
        typename RemoveDuplicates<typename Element<T1, T2>::Tail>::ResultStack
        ,
        Element<
            typename Element<T1, T2>::Head,
            typename RemoveDuplicates<
                typename Element<T1, T2>::Tail
                >::ResultStack
            >
        >
        ::ResultType ResultStack;
};
//==============================================================================
template<class StackT, class T>
struct Append
{
    typedef Element<StackT, T> ResultStack;
};
//==============================================================================
template<class StackT, template <class,class> class CompareT> 
struct FindMin
{
    typedef StackT ResultType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, template <class, class> class CompareT>
struct FindMin<Element<T1,T2>, CompareT>
{
    typedef typename Select<
        IsNullType<typename Element<T1, T2>::Tail>::result
        ,
        typename Element<T1, T2>::Head
        ,
        typename MinType<            
            typename FindMin<typename Element<T1, T2>::Tail,CompareT>::ResultType,
            typename Element<T1, T2>::Head,
            CompareT
            >::ResultType 
        >::ResultType ResultType;
};
//==============================================================================
template<class StackT, template <class, class> class CompareT>
struct FindMax
{
    typedef StackT ResultType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, template <class, class> class CompareT>
struct FindMax<Element<T1, T2>, CompareT>
{
    typedef typename Select<
        IsNullType<typename Element<T1, T2>::Tail>::result
        ,
        typename Element<T1, T2>::Head
        ,
        typename MaxType<            
            typename FindMax<typename Element<T1, T2>::Tail, CompareT>::ResultType,
            typename Element<T1, T2>::Head,
            CompareT
            >::ResultType
        >::ResultType ResultType;
};
//==============================================================================
template<class StackT, template <class,class> class CompareT >
struct SortDescending
{
    typedef StackT ResultStack;
};
//------------------------------------------------------------------------------
template<class T1, class T2, template <class, class> class CompareT >
struct SortDescending<Element<T1,T2>, CompareT>
{
    typedef typename Select <
        IsNullType<typename Element<T1, T2>::Tail >::result
        ,
        Element<T1, T2>
        ,
        Element<
            typename FindMax<Element<T1, T2>, CompareT>::ResultType
            ,
            typename SortDescending< 
                typename Remove<
                    Element<T1, T2>, 
                    typename FindMax<Element<T1, T2>, CompareT>::ResultType
                    >::ResultStack,
                CompareT
                >::ResultStack
            >
        >::ResultType ResultStack;
};
//==============================================================================
template<class StackT, template <class, class> class CompareT >
struct SortAscending
{
    typedef StackT ResultStack;
};
//------------------------------------------------------------------------------
template<class T1, class T2, template <class, class> class CompareT >
struct SortAscending<Element<T1, T2>, CompareT>
{
    typedef typename Select <
        IsNullType<typename Element<T1, T2>::Tail >::result
        ,
        Element<T1, T2>
        ,
        Element<
            typename FindMin<Element<T1, T2>, CompareT>::ResultType
            ,
            typename SortAscending<
                typename Remove<
                    Element<T1, T2>,
                    typename FindMin<Element<T1, T2>, CompareT>::ResultType
                    >::ResultStack,
                CompareT
                >::ResultStack
            >
        > ::ResultType ResultStack;
};
//==============================================================================
} // Stack
//============================================================================== 
template<TBIKES_CT9_DEFTYPE(NullType)> struct ToStack;
//============================================================================== 
namespace Inner{
    template<class T>
    struct ToStackToStack
    {
        typedef T ResultStack;
    };
    template<class T1, class T2>
    struct ToStackToStack<ToStack<T1, T2> >
    {
        typedef typename ToStack<T1, T2>::ResultStack ResultStack;
    };
}
//============================================================================== 
template<TBIKES_CT9>
struct ToStack
{
    typedef TBIKES_TO_TYPESTACK_T9 ResultStack;
};
//============================================================================== 
} // TT
} // Bikes

#endif // <- INCLUDE_BIKES_TYPETOOLS_STACK_H
