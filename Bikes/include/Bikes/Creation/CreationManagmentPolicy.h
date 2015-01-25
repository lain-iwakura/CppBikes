#ifndef INCLUDE_BIKES_CREATION_CREATIONMANAGMENTPOLICY_H
#define INCLUDE_BIKES_CREATION_CREATIONMANAGMENTPOLICY_H

namespace Bikes{
namespace CreationManagmentPolicy{
//==============================================================================
template<
    class SignleCreationPolicyT, 
    class SingleCopyingPolicyT, 
    class SingleDestructionPolicyT
    >
struct ObjectUnion
{
    template typename SignleCreationPolicyT::value_type value_type;

    static value_type* new_instance()
    {
        return SignleCreationPolicyT::new_instance();
    }

    static value_type* new_copy(const value_type* otherObject)
    {
        StaticAssert<
            TT::Equal<value_type, typename SingleCopyingPolicyT::value_type>
            ::result >();

        return SingleCopyingPolicyT::new_copy(otherObject);
    }

    static void delete_instance(value_type* object)
    {
        StaticAssert<
            TT::Equal<value_type, typename SingleDestructionPolicyT::value_type>
            ::result >();

        SingleDestructionPolicyT::delete_instance(object);
    }
};
//==============================================================================
template<
    class ArrayCreationPolicyT,
    class ArrayCopyingPolicyT,
    class ArrayDestructionPolicyT
>
struct ArrayUnion
{
    template typename ArrayCreationPolicyT::value_type value_type;

    static value_type* new_instance(sznum sz)
    {
        return SignleCreationPolicyT::new_instance(sz);
    }

    static value_type* new_copy(const value_type* otherArray, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayCopyingPolicyT::value_type>
            ::result >();

        return ArrayCreationPolicyT::new_copy(otherArray, sz);
    }

    static void delete_instance(value_type* arr, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayDestructionPolicyT::value_type>
            ::result >();

        ArrayDestructionPolicyT::delete_instance(arr, sz);
    }
};
//==============================================================================
template<class ObjectUnionT, class ArrayUnionT>
struct UnionBy2Way
{
    typedef typename ObjectUnionT::value_type value_type;

    static value_type* new_instance()
    {
        return ObjectUnionT::new_instance();
    }

    static value_type* new_copy(const value_type* otherObject)
    {
        return ObjectUnionT::new_copy(otherObject);
    }

    static void delete_instance(value_type* object)
    {
        ObjectUnionT::delete_instance(object);
    }

    static value_type* new_instance(sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayUnionT::value_type>
            ::result >();

        return SignleCreationPolicyT::new_instance(sz);
    }

    static value_type* new_copy(const value_type* otherArray, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayUnionT::value_type>
            ::result >();

        return ArrayUnionT::new_copy(otherArray, sz);
    }

    static void delete_instance(value_type* arr, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename ArrayUnionT::value_type>
            ::result >();

        ArrayUnionT::delete_instance(arr, sz);
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

    static value_type* new_instance()
    {
        return CreationUnionT::new_instance();
    }

    static value_type* new_copy(const value_type* otherObject)
    {
        StaticAssert<
            TT::Equal<value_type, typename CopyingUnionT::value_type>
            ::result >();

        return CopyingUnionT::new_copy(otherObject);
    }

    static void delete_instance(value_type* object)
    {
        StaticAssert<
            TT::Equal<value_type, typename DestructionUnionT::value_type>
            ::result >();

        DestructionUnionT::delete_instance(object);
    }

    static value_type* new_instance(sznum sz)
    {
        return CreationUnionT::new_instance(sz);
    }

    static value_type* new_copy(const value_type* otherArray, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename CopyingUnionT::value_type>
            ::result >();

        return CopyingUnionT::new_copy(otherArray, sz);
    }

    static void delete_instance(value_type* arr, sznum sz)
    {
        StaticAssert<
            TT::Equal<value_type, typename DestructionUnionT::value_type>
            ::result >();

        DestructionUnionT::delete_instance(arr, sz);
    }
};
//==============================================================================
}
} // Bikes


#endif // <- INCLUDE_BIKES_CREATION_CREATIONMANAGMENTPOLICY_H
