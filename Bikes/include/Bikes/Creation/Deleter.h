#ifndef INCLUDE_BIKES_CREATION_DELETER_H
#define INCLUDE_BIKES_CREATION_DELETER_H

namespace Bikes
{
//==============================================================================
template<class T>
class IDeleter
{
public:

    virtual void destroy(T* obj) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(IDeleter)
};
//------------------------------------------------------------------------------	
template<class T>
class IArrayDeleter
{
public:

    virtual void destroyArray(T* arr, sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(IArrayDeleter)
};
//==============================================================================
template<class ObjectDestructionPolicyT>
class Deleter:
    public IDeleter<typename ObjectDestructionPolicyT::value_type>
{
public:
    typedef typename ObjectDestructionPolicyT::value_type value_type;

    static const Deleter& instance()
    {
        static const Deleter i;
        return i;
    }

    void destroy(value_type* obj) const
    {
        delete_object(obj);
    }

    static void delete_object(value_type* obj)
    {
        ObjectDestructionPolicyT::delete_object(obj);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Deleter)
};
//==============================================================================
template<class ArrayDestructionPolicyT>
class ArrayDeleter :
    public IArrayDeleter<typename ArrayDestructionPolicyT::value_type>
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
}



#endif // <- INCLUDE_BIKES_CREATION_DELETER_H
