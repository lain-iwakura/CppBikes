#ifndef INCLUDE_BIKES_TYPETOOLS_STACKTOOLS_H
#define INCLUDE_BIKES_TYPETOOLS_STACKTOOLS_H

#include <Bikes/TypeTools/TypeStack.h>


#define BIKES_TYPESTACK_1(T1) Bikes::TT::TypeStack::Element<T1,Bikes::TT::NullType>
#define BIKES_TYPESTACK_2(T1,T2) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_1(T2) >
#define BIKES_TYPESTACK_3(T1,T2,T3) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_2(T2,T3) >
#define BIKES_TYPESTACK_4(T1,T2,T3,T4) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_3(T2,T3,T4) >
#define BIKES_TYPESTACK_5(T1,T2,T3,T4,T5) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_4(T2,T3,T4,T5) >
#define BIKES_TYPESTACK_6(T1,T2,T3,T4,T5,T6) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_5(T2,T3,T4,T5,T6) >
#define BIKES_TYPESTACK_7(T1,T2,T3,T4,T5,T6,T7) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_6(T2,T3,T4,T5,T6,T7) >
#define BIKES_TYPESTACK_8(T1,T2,T3,T4,T5,T6,T7,T8) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_7(T2,T3,T4,T5,T6,T7,T8) >
#define BIKES_TYPESTACK_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) Bikes::TT::TypeStack::Element<T1,BIKES_TYPESTACK_8(T2,T3,T4,T5,T6,T7,T8,T9) > 

#define TBIKES_TYPESTACK_T9 BIKES_TYPESTACK_9(T1,T2,T3,T4,T5,T6,T7,T8,T9)

#define INNERBIKES_TO_S(T) \
    typename Inner::ToStackToStack<T>::ResultStack

#define TBIKES_TO_TYPESTACK_T9 \
    BIKES_TYPESTACK_9(INNERBIKES_TO_S(T1), INNERBIKES_TO_S(T2), INNERBIKES_TO_S(T3), INNERBIKES_TO_S(T4), INNERBIKES_TO_S(T5), INNERBIKES_TO_S(T6), INNERBIKES_TO_S(T7), INNERBIKES_TO_S(T8), INNERBIKES_TO_S(T9))


namespace Bikes{
//namespace TT{
//============================================================================== 
template<TBIKES_CT9_DEFTYPE(TT::NullType)> struct ToTypeStack;
//============================================================================== 
namespace Inner{
template<class T>
struct ToStackToStack
{
    typedef T ResultStack;
};
template<class T1, class T2>
struct ToStackToStack<ToTypeStack<T1, T2> >
{
    typedef typename ToTypeStack<T1, T2>::ResultStack ResultStack;
};
}
//============================================================================== 
template<TBIKES_CT9>
struct ToTypeStack
{
    typedef TBIKES_TO_TYPESTACK_T9 ResultStack;
};
//==============================================================================
//} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_STACKTOOLS_H
