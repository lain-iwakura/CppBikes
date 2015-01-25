#ifndef INCLUDE_BIKES_CREATION_DELETER_H
#define INCLUDE_BIKES_CREATION_DELETER_H

namespace Bikes
{
//==============================================================================
template<class T>
class SingleDeleterInterface
{
public:

    virtual void destroy(T* obj) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleDeleterInterface)
};
//------------------------------------------------------------------------------	
template<class T>
class ArrayDeleterInterface
{
public:

    virtual void destroy(T* obj, sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayDeleterInterface)
};
//------------------------------------------------------------------------------	
template<class T>
class DeleterInterface:
    public SingleDeleterInterface<T>,
    public ArrayDeleterInterface<T>
{
public:
//  virtual void destroy(T* obj) const = 0;
//  virtual void destroy(T* obj, sznum sz) const = 0;
protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(DeleterInterface)
};
//==============================================================================
template<class SingleDestructionPolicyT>
class SingleDeleter:
    public SingleDeleterInterface<typename SingleDestructionPolicyT::value_type>
{
public:
    typedef typename SingleDestructionPolicyT::value_type value_type;

    static const SingleDeleter& instance()
    {
        static const SingleDeleter i;
        return i;
    }

    void destroy(T* obj) const
    {
        delete_instance(obj);
    }

    static void delete_instance(T* obj)
    {
        SingleDestructionPolicyT::delete_instance(obj);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleDeleter)
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

    void destroy(T* obj, sznum sz) const
    {
        delete_instance(obj, sz);
    }

    static void delete_instance(T* obj,sznum sz)
    {
        ArrayDestructionPolicyT::delete_instance(obj,sz);
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

    void destroy(T* obj) const
    {
        delete_instance(obj);
    }

    void destroy(T* obj, sznum sz) const
    {
        delete_instance(obj, sz);
    }

    static void delete_instance(T* obj)
    {
        ArrayDestructionPolicyT::delete_instance(obj);
    }

    static void delete_instance(T* obj, sznum sz)
    {
        DestructionPolicyT::delete_instance(obj, sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Deleter)
};
//==============================================================================
}



#endif // <- INCLUDE_BIKES_CREATION_DELETER_H
