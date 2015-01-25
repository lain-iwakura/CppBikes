#ifndef INCLUDE_BIKES_CREATION_CREATIONPOLICY_H
#define INCLUDE_BIKES_CREATION_CREATIONPOLICY_H

#include <Bikes/Types.h>
#include <Bikes/Assert.h>

namespace Bikes{
namespace CreationPolicy{
//==============================================================================
template<class T>
struct ObjectByNew
{
    typedef T value_type;

    static T* new_instance()
    {
        return new T;
    }
};
//------------------------------------------------------------------------------
#if 0
template<class T>
struct ObjectByPlacementNew
{
    typedef T value_type;

    static T* new_instance()
    {
        T *obj = static_cast<T*>(new(sizeof(T)))
        new (obj) T();
        return obj;
    }
};
#endif
//==============================================================================
template<class T>
struct ArrayByNew
{
    typedef T value_type;

    static T* new_instance(sznum sz)
    {
        return new T[sz];
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayByPlacementNew
{
    typedef T value_type;

    static T* new_instance(sznum sz)
    {
        T* arr = static_cast<T*>(new(sizeof(T)*sz));
        for (sznum i = 0; i < sz; i++)
            new (arr + i) T();
        return arr;
    }
};
//==============================================================================
template<class T>
struct ByNew
{
    typedef T value_type;

    static value_type* new_instance()
    {
        return ObjectByNew<T>::new_instance();
    }

    static value_type* new_instance(sznum sz)
    {
        return ArrayByNew<T>::new_instance(sz);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ByPlacementNew
{
    typedef T value_type;

    static value_type* new_instance()
    {
        return ObjectByNew<T>::new_instance(); // (?) (!)
    }

    static value_type* new_instance(sznum sz)
    {
        return ArrayByPlacementNew<T>::new_instance(sz);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct Null
{
    typedef T value_type;

    static T* new_instance()
    {
        return 0;
    }

    static T* new_instance(sznum sz)
    {
        return 0;
    }
};
//==============================================================================
template<class SingleCreationPolicyT, class ArrayCreationPolicyT>
struct Pair
{
    typedef typename SingleCreationPolicyT::value_type value_type;

    static value_type* new_instance()
    {
        return SingleCreationPolicyT::new_instance();
    }

    static value_type* new_instance(sznum sz)
    {
        BIKES_STATIC_ASSERT(TT::Equal<value_type, ArrayCreationPolicyT::value_type>::result);
        return ArrayCreationPolicyT::new_instance(sz);
    }
};
//==============================================================================
} // CreationPolicy
} // Bikes


#endif // <- INCLUDE_BIKES_CREATION_CREATIONPOLICY_H
