#ifndef INCLUDE_BIKES_TYPETOOLS_STACKTOOLS_H
#define INCLUDE_BIKES_TYPETOOLS_STACKTOOLS_H

#include <Bikes/TypeTools/Stack.h>


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
namespace Inner{
template<class StackT, num i, template<class> class HolderBaseT >
class StackHolder:
    public Inner::StackHolder<StackT, i - 1, HolderBaseT>
{
public:
    StackHolder()
    {
        HolderBaseT<StackT>:: template initialize<i>();
    }

    virtual ~StackHolder()
    {
        HolderBaseT<StackT>:: template deinitialize<i>();
    }
};
//------------------------------------------------------------------------------
template<class StackT, template<class> class HolderBaseT >
class StackHolder<StackT,0,HolderBaseT> :
    public HolderBaseT<StackT>
{
public:
    StackHolder()
    {
        HolderBaseT<StackT>:: template initialize<0>();
    }

    virtual ~StackHolder()
    {
        HolderBaseT<StackT>:: template deinitialize<0>();
    }
    };
template<class StackT, template<class> class HolderBaseT >
class StackHolder<StackT, -1, HolderBaseT> :
    public HolderBaseT<StackT>
{
public:
    StackHolder()
    {
    }

    virtual ~StackHolder()
    {
    }
};
} // Inner
//==============================================================================
template<class StackT, template<class> class HolderBaseT >
class ConstStackHolder
{
public:
    typedef Inner::StackHolder<
        StackT,
        Stack::Count<StackT>::result - 1,
        HolderBaseT
    > InnerStackHolder;

    static const HolderBaseT<StackT>& get()
    {
        return _holder;
    }

protected:
    static InnerStackHolder _holder;
};
//------------------------------------------------------------------------------
template<class StackT, template<class> class HolderBaseT >
typename ConstStackHolder<StackT, HolderBaseT>::InnerStackHolder ConstStackHolder<StackT, HolderBaseT>::_holder;
//------------------------------------------------------------------------------
template<class StackT, template<class> class HolderBaseT >
class StackHolder:
    public ConstStackHolder<StackT,HolderBaseT>
{
public:
    typedef ConstStackHolder<StackT, HolderBaseT> Base;

    typedef typename Base::InnerStackHolder  InnerStackHolder;

    static HolderBaseT<StackT>& get()
    {
        return Base::_holder;
    }
};
//==============================================================================
} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_STACKTOOLS_H
