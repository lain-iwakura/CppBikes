#ifndef INCLUDE_BIKES_CREATION_DESTRUCTIONPOLICY_H
#define INCLUDE_BIKES_CREATION_DESTRUCTIONPOLICY_H

namespace Bikes{
namespace DestructionPolicy{
//==============================================================================
template<class T>
struct ObjectByDelete
{
    typedef T value_type;

    static void delete_instance(T* obj)
    {
        delete obj;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ObjectBySafetyDelete
{
    typedef T value_type;

    static void delete_instance(T* obj)
    {
        if(obj)
            delete obj;
    }
};
//------------------------------------------------------------------------------
#if 0
template<class T>
struct ObjectByPlacementDelete
{
    typedef T value_type;

    static void delete_instance(T* obj)
    {
        obj->~T();
        delete obj;
    }
};
#endif
//==============================================================================
template<class T>
struct ArrayByDelete
{
    typedef T value_type;

    static void delete_instance(T* arr, sznum)
    {
        delete[] arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayBySafetyDelete
{
    typedef T value_type;

    static void delete_instance(T* arr, sznum)
    {
        if(arr)
            delete[] arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayByPlacementDelete
{
    typedef T value_type;

    static void delete_instance(T* arr, sznum sz)
    {
        for (sznum i = 0; i < sz; i++)
            arr->~T();

        delete[] arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayBySafetyPlacementDelete
{
    typedef T value_type;

    static void delete_instance(T* arr, sznum sz)
    {
        if (!arr)
            return;

        for (sznum i = 0; i < sz; i++)
            arr->~T();

        delete[] arr;
    }
};
//==============================================================================
template<class T>
struct ByDelete
{
    typedef T value_type;

    static void delete_instance(T* obj)
    {
        ObjectByDelete::delete_instance(obj);
    }

    static void delete_instance(T* obj, sznum sz)
    {
        ArrayByDelete::delete_instance(obj,sz);
    }
};
//==============================================================================
template<class SingleDestructionPolicyT, class ArrayDestructionPolicyT>
struct Union
{
    typedef typename SingleDestructionPolicyT::value_type value_type;

    static void delete_instance(T* obj)
    {
        SingleDestructionPolicyT::delete_instance(obj);
    }

    static void delete_instance(T* obj, sznum sz)
    {
        StaticAssert<TT::Equal<value_type, typename ArrayDestructionPolicyT::value_type>::result>()
        SingleDestructionPolicyT::delete_instance(obj, sz);
    }
};
//==============================================================================
} // DestructionPolicy
} // Bikes



#endif // <- INCLUDE_BIKES_CREATION_DESTRUCTIONPOLICY_H
