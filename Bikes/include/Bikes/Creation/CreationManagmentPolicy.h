#ifndef INCLUDE_BIKES_CREATION_CREATIONMANAGMENTPOLICY_H
#define INCLUDE_BIKES_CREATION_CREATIONMANAGMENTPOLICY_H

#include <Bikes/Creation/CreationPolicy.h>
#include <Bikes/Creation/CopyingPolicy.h>
#include <Bikes/Creation/DestructionPolicy.h>

namespace Bikes{
namespace CreationManagment{
//==============================================================================
template<
    class ObjectCreationPolicyT, 
    class ObjectCopyingPolicyT, 
    class ObjectDestructionPolicyT
    >
struct ObjectUnion
{
    typedef typename ObjectCreationPolicyT::value_type value_type;

    static value_type* new_object()
    {
        return ObjectCreationPolicyT::new_object();
    }

    static value_type* new_object(const value_type* otherObject)
    {
        StaticAssert<
            TT::Equal<value_type, typename ObjectCopyingPolicyT::value_type>
            ::result >();

        return ObjectCopyingPolicyT::new_object(otherObject);
    }

    static void delete_object(value_type* object)
    {
        StaticAssert<
            TT::Equal<value_type, typename ObjectDestructionPolicyT::value_type>
            ::result >();

        ObjectDestructionPolicyT::delete_object(object);
    }
};
//==============================================================================
template<class T>
struct SimpleObject
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(Creation::ByNew<T>)
    CBIKES_NEW_OBJECT_CPY_DECLDEF(Copying::ByNew<T>)
    CBIKES_DELETE_OBJECT_DECLDEF(Destruction::ByDelete<T>)
};

template<class T>
struct Null
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(Creation::Null<T>)
    CBIKES_NEW_OBJECT_CPY_DECLDEF(Copying::Null<T>)
    CBIKES_DELETE_OBJECT_DECLDEF(Destruction::Null<T>)
};

template<class T>
struct AbstractObject
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(Creation::Null<T>)
    CBIKES_NEW_OBJECT_CPY_DECLDEF(Copying::BySafetyClone<T>)
    CBIKES_DELETE_OBJECT_DECLDEF(Destruction::BySafetyDelete<T>)
};

template<class T>
struct PolimorphObject
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(Creation::ByNew<T>)
    CBIKES_NEW_OBJECT_CPY_DECLDEF(Copying::ByClone<T>)
    CBIKES_DELETE_OBJECT_DECLDEF(Destruction::ByDelete<T>)
};
//==============================================================================
template<
    class ArrayCreationPolicyT,
    class ArrayCopyingPolicyT,
    class ArrayDestructionPolicyT
>
struct ArrayUnion
{
    typedef typename ArrayCreationPolicyT::value_type value_type;

    static value_type* new_array(sznum sz)
    {
        return ObjectCreationPolicyT::new_array(sz);
    }

    static value_type* new_array(const value_type* otherArray, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayCopyingPolicyT::value_type>
            ::result >();

        return ArrayCreationPolicyT::new_array(otherArray, sz);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayDestructionPolicyT::value_type>
            ::result >();

        ArrayDestructionPolicyT::delete_array(arr, sz);
    }
};
//==============================================================================
template<class T>
struct SimpleArray
{
    typedef T value_type;

    CBIKES_NEW_ARRAY_DECLDEF(Creation::ArrayByNew<T>)
    CBIKES_NEW_ARRAY_CPY_DECLDEF(Copying::ArrayByNew<T>)
    CBIKES_DELETE_ARRAY_DECLDEF(Destruction::ArrayByDelete<T>)
};
//------------------------------------------------------------------------------
template<class T>
struct PlacementArray
{
    typedef T value_type;

    CBIKES_NEW_ARRAY_DECLDEF(Creation::ArrayByPlacementNew<T>)
    CBIKES_NEW_ARRAY_CPY_DECLDEF(Copying::ArrayByPlacementNew<T>)
    CBIKES_DELETE_ARRAY_DECLDEF(Destruction::ArrayByPlacementDelete<T>)
};
//==============================================================================
template<
    class ObjectUnionT, 
    class ArrayUnionT
    >
struct UnionBy2Way
{
    typedef typename ObjectUnionT::value_type value_type;

    static value_type* new_object()
    {
        return ObjectUnionT::new_object();
    }

    static value_type* new_object(const value_type* otherObject)
    {
        return ObjectUnionT::new_object(otherObject);
    }

    static void delete_object(value_type* object)
    {
        ObjectUnionT::delete_object(object);
    }

    static value_type* new_array(sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayUnionT::value_type>
            ::result >();

        return ObjectCreationPolicyT::new_array(sz);
    }

    static value_type* new_array(const value_type* otherArray, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayUnionT::value_type>
            ::result >();

        return ArrayUnionT::new_array(otherArray, sz);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayUnionT::value_type>
            ::result >();

        ArrayUnionT::delete_array(arr, sz);
    }
};
//==============================================================================
template<
    class CreationUnionT, 
    class CopyingUnionT,
    class DestructionUnionT
    >
struct UnionBy3Way
{
    typedef typename CreationUnionT::value_type value_type;

    static value_type* new_object()
    {
        return CreationUnionT::new_object();
    }

    static value_type* new_object(const value_type* otherObject)
    {
        StaticAssert<
            TT::Equal<value_type, typename CopyingUnionT::value_type>
            ::result >();

        return CopyingUnionT::new_object(otherObject);
    }

    static void delete_object(value_type* object)
    {
        StaticAssert<
            TT::Equal<value_type, typename DestructionUnionT::value_type>
            ::result >();

        DestructionUnionT::delete_object(object);
    }

    static value_type* new_array(sznum sz)
    {
        return CreationUnionT::new_array(sz);
    }

    static value_type* new_array(const value_type* otherArray, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename CopyingUnionT::value_type>
            ::result >();

        return CopyingUnionT::new_array(otherArray, sz);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename DestructionUnionT::value_type>
            ::result >();

        DestructionUnionT::delete_array(arr, sz);
    }
};
//==============================================================================
}
} // Bikes


#endif // <- INCLUDE_BIKES_CREATION_CREATIONMANAGMENTPOLICY_H
