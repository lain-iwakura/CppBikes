#ifndef INCLUDE_BIKES_CREATION_DELETER_H
#define INCLUDE_BIKES_CREATION_DELETER_H

namespace Bikes
{
//==============================================================================
template<class T>
class ObjectDeleterInterface
{
public:

    virtual void destroyObject(T* obj) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectDeleterInterface)
};
//------------------------------------------------------------------------------	
template<class T>
class ArrayDeleterInterface
{
public:

    virtual void destroyArray(T* arr, sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayDeleterInterface)
};
//------------------------------------------------------------------------------	
template<class T>
class DeleterInterface:
    public ObjectDeleterInterface<T>,
    public ArrayDeleterInterface<T>
{
public:
//  virtual void destroyObject(T* obj) const = 0;
//  virtual void destroyArray(T* obj, sznum sz) const = 0;
protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(DeleterInterface)
};
//==============================================================================
template<class ObjectDestructionPolicyT>
class ObjectDeleter:
    public ObjectDeleterInterface<typename ObjectDestructionPolicyT::value_type>
{
public:
    typedef typename ObjectDestructionPolicyT::value_type value_type;

    static const ObjectDeleter& instance()
    {
        static const ObjectDeleter i;
        return i;
    }

    void destroyObject(value_type* obj) const
    {
        delete_object(obj);
    }

    static void delete_object(value_type* obj)
    {
        ObjectDestructionPolicyT::delete_object(obj);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectDeleter)
};
//==============================================================================
template<class ArrayDestructionPolicyT>
class ArrayDeleter :
    public ArrayDeleterInterface<typename ArrayDestructionPolicyT::value_type>
{
public:
    typedef typename ArrayDestructionPolicyT::value_type value_type;

    static const ArrayDeleter& instance()
    {
        static const ArrayDeleter i;
        return i;
    }

    void destroyArray(value_type* arr, sznum sz) const
    {
        delete_array(arr, sz);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        ArrayDestructionPolicyT::delete_array(arr,sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayDeleter)
};
//==============================================================================
template<class DestructionPolicyT>
class Deleter :
    public DeleterInterface<typename DestructionPolicyT::value_type>
{
public:
    typedef typename DestructionPolicyT::value_type value_type;

    static const Deleter& instance()
    {
        static const Deleter i;
        return i;
    }

    void destroyObject(value_type* obj) const
    {
        delete_object(obj);
    }

    void destroyArray(value_type* arr, sznum sz) const
    {
        delete_array(arr, sz);
    }

    static void delete_object(value_type* obj)
    {
        ArrayDestructionPolicyT::delete_object(obj);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        DestructionPolicyT::delete_array(arr, sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Deleter)
};
//==============================================================================
}



#endif // <- INCLUDE_BIKES_CREATION_DELETER_H
