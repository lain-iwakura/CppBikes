#ifndef INCLUDE_BIKES_CREATION_CREATIONPOLICY_H
#define INCLUDE_BIKES_CREATION_CREATIONPOLICY_H

#include <Bikes/Types.h>
#include <Bikes/Assert.h>


//==============================================================================
#define CBIKES_NEW_OBJECT_DECLDEF(Policy)                                      \
    static value_type* new_object(){                                           \
        return Policy::new_object();                                           \
    }
//------------------------------------------------------------------------------
#define CBIKES_NEW_ARRAY_DECLDEF(Policy)                                       \
    static value_type* new_array(sznum sz){                                    \
        return Policy::new_array(sz);                                          \
    }
//==============================================================================
namespace Bikes{
namespace Creation{
//==============================================================================
template<class T>
struct ByNew
{
    typedef T value_type;

    static T* new_object()
    {
        return new T;
    }
};
//------------------------------------------------------------------------------
#if 0
template<class T>
struct ByPlacementNew
{
    typedef T value_type;

    static T* new_object()
    {
        T *obj = static_cast<T*>(new(sizeof(T)))
        new (obj) T();
        return obj;
    }
};
#endif
//------------------------------------------------------------------------------
template<class T>
struct Null
{
    typedef T value_type;

    static T* new_object()
    {
        return 0;
    }
};
//==============================================================================
template<class T>
struct ArrayByNew
{
    typedef T value_type;

    static T* new_array(sznum sz)
    {
        return new T[sz];
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayByPlacementNew
{
    typedef T value_type;

    static T* new_array(sznum sz)
    {
        T* arr = static_cast<T*>(new(sizeof(T)*sz));
        for (sznum i = 0; i < sz; i++)
            new (arr + i) T();
        return arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct NullArray
{
    typedef T value_type;

    static T* new_array(sznum sz)
    {
        return 0;
    }
};
//==============================================================================
template<class T>
struct UniounByNew
{
    typedef T value_type;    

    CBIKES_NEW_OBJECT_DECLDEF(ByNew<T>)
    CBIKES_NEW_ARRAY_DECLDEF(ArrayByNew<T>)
};
//------------------------------------------------------------------------------
template<class T>
struct UnionByPlacementNew
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(ByNew<T>)
    CBIKES_NEW_ARRAY_DECLDEF(ArrayByPlacementNew<T>)
};
//------------------------------------------------------------------------------
template<class T>
struct NullUnion
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(Null<T>)
    CBIKES_NEW_ARRAY_DECLDEF(NullArray<T>)
};
//==============================================================================
template<class ObjectCreationPolicyT, class ArrayCreationPolicyT>
struct Union
{
    typedef typename ObjectCreationPolicyT::value_type value_type;

    static value_type* new_object()
    {
        return ObjectCreationPolicyT::new_object();
    }

    static value_type* new_array(sznum sz)
    {
        StaticAssert<TT::Equal<value_type, ArrayCreationPolicyT::value_type>::result>();
        return ArrayCreationPolicyT::new_array(sz);
    }
};
//==============================================================================
} // CreationPolicy
} // Bikes


#endif // <- INCLUDE_BIKES_CREATION_CREATIONPOLICY_H
