#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPESTACK_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPESTACK_H
#include <Bikes/TypeCollecting/NullTypes.h>




#define BIKES_TYPESTACK_1(T1) Bikes::TypeStack::Element<T1,Bikes::NullType>
#define BIKES_TYPESTACK_2(T1,T2) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_1(T2) >
#define BIKES_TYPESTACK_3(T1,T2,T3) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_2(T2,T3) >
#define BIKES_TYPESTACK_4(T1,T2,T3,T4) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_3(T2,T3,T4) >
#define BIKES_TYPESTACK_5(T1,T2,T3,T4,T5) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_4(T2,T3,T4,T5) >
#define BIKES_TYPESTACK_6(T1,T2,T3,T4,T5,T6) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_5(T2,T3,T4,T5,T6) >
#define BIKES_TYPESTACK_7(T1,T2,T3,T4,T5,T6,T7) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_6(T2,T3,T4,T5,T6,T7) >
#define BIKES_TYPESTACK_8(T1,T2,T3,T4,T5,T6,T7,T8) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_7(T2,T3,T4,T5,T6,T7,T8) >
#define BIKES_TYPESTACK_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) Bikes::TypeStack::Element<T1,BIKES_TYPESTACK_8(T2,T3,T4,T5,T6,T7,T8,T9) > 

#define MACROSBIKES_TYPESTACK_T9 Bikes::TypeStack::Element<T1, Bikes::TypeStack::Element<T2, Bikes::TypeStack::Element<T3, Bikes::TypeStack::Element<T4, Bikes::TypeStack::Element<T5, Bikes::TypeStack::Element<T6, Bikes::TypeStack::Element<T7, Bikes::TypeStack::Element<T8, Bikes::TypeStack::Element<T9,Bikes::NullType> > > > > > > > >


namespace Bikes{
namespace TypeStack{
//==============================================================================
template<class LeftT, class  RightT>
struct Element;
//==============================================================================
template<class T>
struct Detector
{
    enum{
        isTypeStack = false
    };
};
template<class T1, class T2>
struct Detector<Element<T1, T2> >
{
    enum{
        isTypeStack = true
    };
};
//==============================================================================
template<class T>
struct NotNull
{
    typedef T ResultType;
};
template<class T1, class T2>
struct NotNull<Element<T1,T2> >
{
    typedef typename SelectType<
        TypeEqual<typename Element<T1, T2>::HeadType, NullType>::result,
        NullType,
        Element<T1, T2>
        >
        ::ResultType ResultType;
};
//==============================================================================
template<class LeftT, class  RightT>
struct Element
{
    typedef LeftT HeadType;
    typedef Element<RightT,NullType> TailType;

//     typedef typename SelectType<
//         Detector<RightT>::isTypeStack || TypeEqual<RightT, NullType>::result,
//         RightT,
//         Element<RightT, NullType>
//     >
//     ::ResultType TailType;
};
//------------------------------------------------------------------------------
template<class T>
struct Element<NullType, T>
{
    typedef T HeadType;
    typedef NullType TailType;
};
//------------------------------------------------------------------------------
template<class T>
struct Element<T, NullType>
{
    typedef T HeadType;
    typedef NullType TailType;
};
//------------------------------------------------------------------------------
template<>
struct Element<NullType, NullType>
{
    typedef NullType HeadType;
    typedef NullType TailType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3 >
struct Element<T1,Element<T2, T3> >
{
    typedef T1 HeadType;
    typedef typename NotNull<Element<T2, T3> >::ResultType TailType;
};
template<class T1, class T2 >
struct Element<NullType, Element<T1, T2> >
{
    typedef typename Element<T1, T2>::HeadType HeadType;
    typedef typename Element<T1, T2>::TailType TailType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3 >
struct Element<Element<T1, T2>, T3>
{

    typedef typename SelectType<
    TypeEqual<typename Element<T1, T2>::HeadType, NullType>::result,
    T3,
    typename Element<T1, T2>::HeadType
    >
    ::ResultType HeadType;

    typedef Element<typename Element<T1, T2>::TailType, T3> TailType;
};
//------------------------------------------------------------------------------
template<class T1, class T2>
struct Element<Element<T1, T2>, NullType>
{
    typedef typename Element<T1, T2>::HeadType HeadType;
    typedef typename Element<T1, T2>::TailType TailType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3, class T4>
struct Element<Element<T1, T2>, Element<T3,T4> >
{
    typedef typename SelectType<
    TypeEqual<typename Element<T1, T2>::HeadType, NullType>::result,
    typename Element<T3, T4>::HeadType,
    typename Element<T1, T2>::HeadType
    >
    ::ResultType HeadType;

    typedef typename SelectType<
        TypeEqual<typename Element<T1, T2>::HeadType, NullType>::result,
        typename Element<T3, T4>::TailType,
        Element<typename Element<T1, T2>::TailType, Element<T3, T4> >
        >
        ::ResultType TailType;
};
//==============================================================================
template<class T>
struct Lenght
{
    enum{
        result = 1
    };
};
//------------------------------------------------------------------------------
template<>
struct Lenght<NullType>
{
    enum{
        result = 0
    };
};
//------------------------------------------------------------------------------
template<class LeftT, class RightT>
struct Lenght<Element<LeftT, RightT> >
{
    enum{
        result = Lenght<typename Element<LeftT, RightT>::HeadType>::result
        + Lenght<typename Element<LeftT, RightT>::TailType >::result
    };
};
//==============================================================================
template<class StackT, class RequiredT>
struct IndexByType
{
    enum{
        result = -1
    };
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3>
struct IndexByType<T1, Element<T2,T3> >
{
    enum{
        result = (TypeEqual<typename Element<T2, T3>::HeadType, T1>::result) ? (0) : 
        ((IndexByType<T1, typename Element<T2, T3>::TailType>::result == -1) ? (-1) : (IndexByType<T1, typename Element<T2, T3>::TailType>::result + 1))
    };
};
//------------------------------------------------------------------------------
template<class T1, class T2, class T3>
struct IndexByType<Element<T2, T3>, T1 >
{
    enum{
        result = IndexByType<T1, Element<T2, T3>>::result
    };
};
//==============================================================================
template<class StackT, num i>
struct TypeByIndex
{
    typedef NullType ResultType;
};
//------------------------------------------------------------------------------
template<class T1, class T2, num i>
struct TypeByIndex<Element<T1,T2>, i>
{
    typedef typename SelectType<
    i < 0,
    NullType,
    typename TypeByIndex<typename Element<T1, T2>::TailType, i - 1 >::ResultType
    >
    ::ResultType ResultType;
};
//------------------------------------------------------------------------------
template<class T1, class T2>
struct TypeByIndex<Element<T1, T2>, 0>
{
    typedef typename Element<T1, T2>::HeadType ResultType;
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
    typedef typename SelectType<
    TypeEqual<typename Element<T1, T2>::HeadType, RemoveT>::result,
    typename Element<T1, T2>::TailType,
    Element<typename Element<T1, T2>::HeadType, typename Remove<typename Element<T1, T2>::TailType, RemoveT>::ResultStack >
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
    typedef typename SelectType<
    IndexByType<typename Element<T1, T2>::TailType, typename Element<T1, T2>::HeadType>::result >= 0,
    typename RemoveDuplicates<typename Element<T1, T2>::TailType>::ResultStack,
    Element<typename Element<T1, T2>::HeadType, typename RemoveDuplicates<typename Element<T1, T2>::TailType>::ResultStack>
    >
    ::ResultType ResultStack;
};
//==============================================================================
} // TypeStack
} // Bikes

#endif // <- INCLUDE_BIKES_TYPECOLLECTING_TYPESTACK_H

