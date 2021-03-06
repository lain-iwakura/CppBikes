#ifndef INCLUDE_BIKES_CREATION_DESTRUCTIONPOLICY_H
#define INCLUDE_BIKES_CREATION_DESTRUCTIONPOLICY_H

//==============================================================================
#define CBIKES_DELETE_OBJECT_DECLDEF(Policy)                                   \
    static void                                                                \
    delete_object(value_type* obj){                                            \
        Policy::delete_object(obj);                                            \
    }
//------------------------------------------------------------------------------
#define CBIKES_DELETE_ARRAY_DECLDEF(Policy)                                    \
    static void                                                                \
    delete_array(value_type* arr, sznum sz){                                   \
        Policy::delete_array(arr,sz);                                          \
    }
//==============================================================================

namespace Bikes{
namespace Destruction{
//==============================================================================
template<class T>
struct ByDelete
{
    typedef T value_type;

    static void delete_object(T* obj)
    {
        delete obj;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct BySafetyDelete
{
    typedef T value_type;

    static void delete_object(T* obj)
    {
        if(obj)
            delete obj;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct Null
{
    typedef T value_type;

    static void delete_object(T* obj)
    {
    }
};
//------------------------------------------------------------------------------
#if 0
template<class T>
struct ByPlacementDelete
{
    typedef T value_type;

    static void delete_object(T* obj)
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

    static void delete_array(T* arr, sznum)
    {
        delete[] arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayBySafetyDelete
{
    typedef T value_type;

    static void delete_array(T* arr, sznum)
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

    static void delete_array(T* arr, sznum sz)
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

    static void delete_array(T* arr, sznum sz)
    {
        if (!arr)
            return;

        for (sznum i = 0; i < sz; i++)
            arr->~T();

        delete[] arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct NullArray
{
    typedef T value_type;

    static void delete_array(T* obj, sznum sz)
    {
    }
};
//==============================================================================
} // DestructionPolicy
} // Bikes
#endif // <- INCLUDE_BIKES_CREATION_DESTRUCTIONPOLICY_H
