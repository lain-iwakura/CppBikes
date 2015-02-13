#ifndef INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
#define INCLUDE_BIKES_CREATION_CREATIONMANAGER_H

#include <Bikes/Creation/CreationManagmentPolicy.h>
#include <Bikes/Creation/Creator.h>
#include <Bikes/Creation/Copier.h>
#include <Bikes/Creation/Deleter.h>

namespace Bikes
{

template<class T>
class ObjectCreationManagerInterface :
    public ObjectCreatorInterface<T>,
    public ObjectCopierInterface<T>,
    public ObjectDeleterInterface<T>
{
public:
//     virtual T* createObject() const = 0;
//     virtual T* copyObject(const T* pObj) const = 0;
//     virtual void destroyObject(T* pObj) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectCreationManagerInterface)
};
//==============================================================================
template<class T>
class ArrayCreationManagerInterface: 
    public ArrayCreatorInterface<T>,
    public ArrayCopierInterface<T>,
    public ArrayDeleterInterface<T>
{
public:
//     virtual T* createArray(sznum sz) const = 0;
//     virtual T* copyArray(const T* pObj, sznum sz) const = 0; 
//     virtual void destroyArray(T* pObj, sznum sz) const = 0; 

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCreationManagerInterface)
};
//==============================================================================
template<class T>
class CreationManagerInterface :
    public ObjectCreationManagerInterface<T>,
    public ArrayCreationManagerInterface<T>
{
public:
//     virtual T* createObject() const = 0;
//     virtual T* createArray(sznum sz) const = 0; 
//     virtual T* copyObject(const T* pObj) const = 0;
//     virtual T* copyArray(const T* pObj, sznum sz) const = 0;
//     virtual void destroyObject(const T* pObj) const = 0;
//     virtual void destroyArray(const T* pObj, sznum sz) const = 0;
protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreationManagerInterface)
};
//==============================================================================
template<class ObjectCreationManagmentPolicyT>
class ObjectCreationManager:
    public ObjectCreationManagerInterface<typename ObjectCreationManagmentPolicyT::value_type>
{
public:
    typedef ObjectCreationManagmentPolicyT Policy;
    typedef typename Policy::value_type value_type;
    typedef ObjectCreationManagerInterface<value_type> Interface;

    static const ObjectCreationManager& instance()
    {
        static const ObjectCreationManager i;
        return i;
    }

    value_type* createObject() const
    {
        return new_object();
    }

    value_type* copyObject(const value_type* otherObj) const
    {
        return new_object(otherObj);
    }

    void destroyObject(value_type* pObj) const
    {
        delete_object(pObj);
    }

    static value_type* new_object()
    {
        return Policy::new_object();
    }

    static value_type* new_object(const value_type* otherObj)
    {
        return Policy::new_object(otherObj);
    }

    static void delete_object(value_type* obj)
    {
        Policy::delete_object(obj);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectCreationManager)
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

    value_type* createArray(sznum sz) const
    {
        return new_array(sz);
    }

    value_type* copyArray(const value_type* arr, sznum sz) const
    {
        return new_array(arr, sz);
    }

    void destroyArray(value_type* arr, sznum sz) const
    {
        delete_array(arr, sz);
    }

    static value_type* new_array(sznum sz)
    {
        return Policy::new_array(sz);
    }

    static value_type* new_array(const value_type* arr, sznum sz)
    {
        return Policy::new_array(arr, sz);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        Policy::delete_array(arr, sz);
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

    value_type* createObject() const
    {
        return new_object();
    }

    value_type* createArray(sznum sz) const
    {
        return new_array(sz);
    }

    value_type* copyObject(const value_type* otherObj) const
    {
        return new_object(otherObj);
    }

    value_type* copyArray(const value_type* arr, sznum sz) const
    {
        return new_array(arr, sz);
    }

    void destroyObject(value_type* pObj) const
    {
        delete_object(pObj);
    }

    void destroyArray(value_type* arr, sznum sz) const
    {
        delete_array(arr, sz);
    }

    static value_type* new_object()
    {
        return Policy::new_object();
    }

    static value_type* new_array(sznum sz)
    {
        return Policy::new_array(sz);
    }

    static value_type* new_object(const value_type* otherObj)
    {
        return Policy::new_object(otherObj);
    }

    static value_type* new_array(const value_type* arr, sznum sz)
    {
        return Policy::new_array(arr, sz);
    }

    static void delete_object(value_type* obj)
    {
        Policy::delete_object(obj);
    }

    static void delete_array(value_type* arr, sznum sz)
    {
        Policy::delete_array(arr, sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreationManager)
};
//==============================================================================
}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
