#ifndef INCLUDE_BIKES_CREATION_�OPYINGPOLICY_H
#define INCLUDE_BIKES_CREATION_�OPYINGPOLICY_H

//==============================================================================
#define CBIKES_NEW_OBJECT_CPY_DECLDEF(Policy)                                  \
    static value_type*                                                         \
    new_object(const value_type* other){                                       \
        return Policy::new_object(other);                                      \
    }
//------------------------------------------------------------------------------
#define CBIKES_NEW_ARRAY_CPY_DECLDEF(Policy)                                   \
    static value_type*                                                         \
    new_array(const value_type* other, sznum sz){                              \
        return Policy::new_array(other,sz);                                    \
    }
//==============================================================================
namespace Bikes{
namespace Copying{
//==============================================================================
template<class T>
struct ByNew
{    
    typedef T value_type;

    static T* new_object(const T* otherObject)
    {
        return new T(*otherObject);
    }
};
//------------------------------------------------------------------------------
template<class T>
struct BySafetyNew
{
    typedef T value_type;

    static T* new_object(const T* otherObject)
    {
        if (otherObject)
            return new T(*otherObject);
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct ByClone
{
    typedef T value_type;

    static T* new_object(const T* otherObject)
    {
        return otherObject->clone();
    }
};
//------------------------------------------------------------------------------
template<class T>
struct Null
{
    typedef T value_type;

    static T* new_object(const T* otherObject)
    {
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
struct BySafetyClone
{
    typedef T value_type;

    static T* new_object(const T* otherObject)
    {
        if(otherObject)
            return otherObject->clone();
        return 0;
    }
};
//------------------------------------------------------------------------------
#if 0
template<class T>
struct ByPlacementNew
{
    typedef T value_type;

    static T* new_object(const T* otherObject)
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

    static T* new_array(const T* otherArray, sznum sz)
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

    static T* new_array(const T* otherArray, sznum sz)
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

    static T* new_array(const T* otherArray, sznum sz)
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

    static T* new_array(const T* otherArray, sznum sz)
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
} // CopyingPolicy
} // Bikes

#endif // <- INCLUDE_BIKES_CREATION_�OPYINGPOLICY_H
