#ifndef INCLUDE_BIKES_CREATION_ÑOPYINGPOLICY_H
#define INCLUDE_BIKES_CREATION_ÑOPYINGPOLICY_H

namespace Bikes{
namespace CopyingPolicy{
//==============================================================================
template<class T>
struct ObjectByNew
{    
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return new T(*otherObject);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ObjectBySafetyNew
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        if (otherObject)
            return new T(*otherObject);
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ObjectByClone
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return otherObject->clone();
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ObjectBySafetyClone
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        if(otherObject)
            return otherObject->clone();
        return 0;
    }
};
//------------------------------------------------------------------------------
#if 0
template<class T>
struct ObjectByPlacementNew
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        T * obj = static_cast<T*>(new(sizeof(T)));
        return new T(*otherObject);
    }
};
#endif
//==============================================================================
template<class T>
struct ArrayByNew // copying with T::operator=()
{
    typedef T value_type;

    static T* new_copy(const T* otherArray, sznum sz)
    {
        T* arr = new T[sz];
        for (sznum i = 0; i < sz; i++)
            arr[i] = otherArray[i];
        return arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayBySafetyNew // copying with T::operator=()
{
    typedef T value_type;

    static T* new_copy(const T* otherArray, sznum sz)
    {
        if (otherArray == 0)
            return 0;

        T* arr = new T[sz];
        for (sznum i = 0; i < sz; i++)
            arr[i] = otherArray[i];
        return arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayByPlacementNew // copying with T()
{
    typedef T value_type;

    static T* new_copy(const T* otherArray, sznum sz)
    {
        T* arr = static_cast<T*>( new(sizeof(T)*sz) );
        for (sznum i = 0; i < sz; i++)
            new(arr+i) T(otherArray[i]);
        return arr;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ArrayBySafetyPlacementNew // copying with T()
{
    typedef T value_type;

    static T* new_copy(const T* otherArray, sznum sz)
    {
        if (otherArray == 0)
            return 0;

        T* arr = static_cast<T*>(new(sizeof(T)*sz));
        for (sznum i = 0; i < sz; i++)
            new(arr + i) T(otherArray[i]);
        return arr;
    }
};
//==============================================================================
template<class T>
struct ByNew
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {        
        return ObjectByNew<T>::new_copy(otherObject);
    }

    static T* new_copy(const T* otherArray, sznum sz)
    {        
        return ArrayByNew<T>::new_copy(otherArray, sz);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct BySafetyNew
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return ObjectBySafetyNew<T>::new_copy(otherObject);
    }

    static T* new_copy(const T* otherArray, sznum sz)
    {
        return ArrayBySafetyNew<T>::new_copy(otherArray, sz);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ByPlacementNew
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return ObjectByNew<T>::new_copy(otherObject); // (?) (!)
    }

    static T* new_copy(const T* otherArray, sznum sz)
    {
        return ArrayByPlacementNew<T>::new_copy(otherArray, sz);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct BySafetyPlacementNew
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return ObjectBySafetyNew<T>::new_copy(otherObject); // (?) (!)
    }

    static T* new_copy(const T* otherArray, sznum sz)
    {
        return ArrayBySafetyPlacementNew<T>::new_copy(otherArray, sz);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ByClone
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return ObjectByClone<T>::new_copy(otherObject); 
    }

    static T* new_copy(const T* otherArray, sznum sz)
    {
        throw Exception::ProhibitedAction(
            std::string("ByClone<T>::new_copy() with T = ") + typeid(T).name()
            );

        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct BySafetyClone
{
    typedef T value_type;

    static T* new_copy(const T* otherObject)
    {
        return ObjectBySafetyClone<T>::new_copy(otherObject);
    }

    static T* new_copy(const T* otherArray, sznum sz)
    {
        if (otherArray != 0)
            throw Exception::ProhibitedAction(
                std::string("BySafetyClone<T>::new_copy() with T = ") + typeid(T).name()
                );

        return 0;
    }
};
//==============================================================================
template<class SingleCopyingPolicyT, class ArrayCopyingPolicyT>
struct Union
{
    typedef typename SingleCopyingPolicyT::value_type value_type;

    static value_type* new_copy(const value_type* otherObject)
    {
        return SingleCopyingPolicyT::new_copy(otherObject);
    }

    static value_type* new_copy(const value_type* otherArray, sznum sz)
    {
        StaticAssert<TT::Equal<value_type, ArrayCopyingPolicyT::value_type>::result>();
        return ArrayCopyingPolicyT::new_copy(otherArray,sz);
    }
};
//==============================================================================
} // CopyingPolicy
} // Bikes

#endif // <- INCLUDE_BIKES_CREATION_ÑOPYINGPOLICY_H
