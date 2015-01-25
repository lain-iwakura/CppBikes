#ifndef INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
#define INCLUDE_BIKES_CREATION_CREATIONMANAGER_H

#include <Bikes/Creation/CreationManagmentPolicy.h>
#include <Bikes/Creation/Creator.h>
#include <Bikes/Creation/Copier.h>
#include <Bikes/Creation/Deleter.h>

namespace Bikes
{

template<class T>
class SingleCreationManagerInterface :
    public SingleCreatorInterface<T>,
    public SingleCopierInterface<T>,
    public SingleDeleterInterface<T>
{
public:
//     virtual T* create() const = 0;
//     virtual T* copy(const T* pObj) const = 0;
//     virtual void destroy(T* pObj) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleCreationManagerInterface)
};
//==============================================================================
template<class T>
class ArrayCreationManagerInterface: 
    public ArrayCreatorInterface<T>,
    public ArrayCopierInterface<T>,
    public ArrayDeleterInterface<T>
{
public:
//     virtual T* create(sznum sz) const = 0;
//     virtual T* copy(const T* pObj, sznum sz) const = 0; 
//     virtual void destroy(T* pObj, sznum sz) const = 0; 

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCreationManagerInterface)
};
//==============================================================================
template<class T>
class CreationManagerInterface :
    public SingleCreationManagerInterface<T>,
    public ArrayCreationManagerInterface<T>
{
public:
//     virtual T* create() const = 0;
//     virtual T* create(sznum sz) const = 0; 
//     virtual T* copy(const T* pObj) const = 0;
//     virtual T* copy(const T* pObj, sznum sz) const = 0;
//     virtual void destroy(const T* pObj) const = 0;
//     virtual void destroy(const T* pObj, sznum sz) const = 0;
protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreationManagerInterface)
};
//==============================================================================
template<class SingleCreationManagmentPolicyT>
class SingleCreationManager:
    public SingleCreationManagerInterface<typename SingleCreationManagmentPolicyT::value_type>
{
public:
    typedef SingleCreationManagmentPolicyT Policy;
    typedef typename Policy::value_type value_type;
    typedef SingleCreationManagerInterface<value_type> Interface;

    static const SingleCreationManager& instance()
    {
        static const SingleCreationManager i;
        return i;
    }

    value_type* create() const
    {
        return new_instance();
    }

    value_type* copy(const value_type* otherObj) const
    {
        return new_copy(otherObj);
    }

    void destroy(value_type* pObj) const
    {
        delete_instance(pObj);
    }

    static value_type* new_instance()
    {
        return Policy::new_instance();
    }

    static value_type* new_copy(const value_type* otherObj)
    {
        return Policy::new_copy(otherObj);
    }

    static void delete_instance(value_type* obj)
    {
        Policy::delete_instance(obj);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleCreationManager)
};
//==============================================================================
template<class ArrayCreationManagmentPolicyT>
class ArrayCreationManager :
    public ArrayCreationManagerInterface<typename ArrayCreationManagmentPolicyT::value_type>
{
public:
    typedef ArrayCreationManagmentPolicyT Policy;
    typedef typename Policy::value_type value_type;
    typedef ArrayCreationManagerInterface<value_type> Interface;

    static const ArrayCreationManager& instance()
    {
        static const ArrayCreationManager i;
        return i;
    }

    value_type* create(sznum sz) const
    {
        return new_instance(sz);
    }

    value_type* copy(const value_type* otherObj, sznum sz) const
    {
        return new_copy(otherObj,sz);
    }

    void destroy(value_type* pObj, sznum sz) const
    {
        delete_instance(pObj,sz);
    }

    static value_type* new_instance(sznum sz)
    {
        return Policy::new_instance(sz);
    }

    static value_type* new_copy(const value_type* otherObj, sznum sz)
    {
        return Policy::new_copy(otherObj,sz);
    }

    static void delete_instance(value_type* obj, sznum sz)
    {
        Policy::delete_instance(obj,sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCreationManager)
};
//==============================================================================
template<class CreationManagmentPolicyT>
class CreationManager :
    public CreationManagerInterface<typename CreationManagmentPolicyT::value_type>
{
public:
    typedef CreationManagmentPolicyT Policy;
    typedef typename Policy::value_type value_type;
    typedef CreationManagerInterface<value_type> Interface;


    static const CreationManager& instance()
    {
        static const CreationManager i;
        return i;
    }

    value_type* create() const
    {
        return new_instance();
    }

    value_type* create(sznum sz) const
    {
        return new_instance(sz);
    }

    value_type* copy(const value_type* otherObj) const
    {
        return new_copy(otherObj);
    }

    value_type* copy(const value_type* otherObj, sznum sz) const
    {
        return new_copy(otherObj, sz);
    }

    void destroy(value_type* pObj) const
    {
        delete_instance(pObj);
    }

    void destroy(value_type* pObj, sznum sz) const
    {
        delete_instance(pObj, sz);
    }

    static value_type* new_instance()
    {
        return Policy::new_instance();
    }

    static value_type* new_instance(sznum sz)
    {
        return Policy::new_instance(sz);
    }

    static value_type* new_copy(const value_type* otherObj)
    {
        return Policy::new_copy(otherObj);
    }

    static value_type* new_copy(const value_type* otherObj, sznum sz)
    {
        return Policy::new_copy(otherObj, sz);
    }

    static void delete_instance(value_type* obj)
    {
        Policy::delete_instance(obj);
    }

    static void delete_instance(value_type* obj, sznum sz)
    {
        Policy::delete_instance(obj, sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreationManager)
};
//==============================================================================
}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
