#ifndef INCLUDE_BIKES_CONVERSION_H
#define INCLUDE_BIKES_CONVERSION_H

#include <Bikes/TypeTools/Compare.h>
#include <Bikes/TypeTools/Modify.h>

namespace Bikes
{
//==============================================================================
template<
    class FromType,
    class ToType,
    bool staticConv = HierrarchyExists<ToType, FromType>::result || Equal<FromType, ToType>::result
>
struct Optimum—onversion
{
    static ToType* cast(FromType* obj)
    {
        return static_cast<ToType*>(obj);
    }

    static const ToType* cast(const FromType* obj)
    {
        return static_cast<const ToType*>(obj);
    }
};
//------------------------------------------------------------------------------
template<
    class FromType,
    class ToType
>
struct Optimum—onversion<FromType, ToType, false>
{
    static ToType* cast(FromType* obj)
    {
        return dynamic_cast<ToType*>(obj);
    }

    static const ToType* cast(const FromType* obj)
    {
        return dynamic_cast<const ToType*>(obj);
    }
};
//==============================================================================
template <class ToTypePtr, class FromType>
ToTypePtr optimum_cast(FromType* p)
{
    return Optimum—onversion<
        typename TT::Clear<FromType>::ResultType,
        typename TT::Clear<ToTypePtr>::ResultType
        >::cast(p);
}
//==============================================================================
}

#endif // <- INCLUDE_BIKES_CONVERSION_H
