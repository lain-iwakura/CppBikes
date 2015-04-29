#ifndef INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
#define INCLUDE_BIKES_CREATION_CREATIONMANAGER_H

#include <Bikes/Creation/CreationManagmentPolicy.h>
#include <Bikes/Creation/Creator.h>
#include <Bikes/Creation/Copier.h>
#include <Bikes/Creation/Deleter.h>

namespace Bikes
{

template<class T>
class ICreationManager :
    public ICreator<T>,
    public ICopier<T>,
    public IDeleter<T>
{
public:
//     virtual T* create() const = 0;
//     virtual T* copy(const T* pObj) const = 0;
//     virtual void destroy(T* pObj) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ICreationManager)
};
//==============================================================================
template<class T>
class IArrayCreationManager: 
    public IArrayCreator<T>,
    public IArrayCopier<T>,
    public IArrayDeleter<T>
{
public:
//     virtual T* createArray(sznum sz) const = 0;
//     virtual T* copyArray(const T* pObj, sznum sz) const = 0; 
//     virtual void destroyArray(T* pObj, sznum sz) const = 0; 

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(IArrayCreationManager)
};
//==============================================================================
template<class ObjectCreationManagmentPolicyT>
class CreationManager:
    public ICreationManager<typename ObjectCreationManagmentPolicyT::value_type>
{
public:
    typedef ObjectCreationManagmentPolicyT Policy;
    typedef typename Policy::value_type value_type;
    typedef ICreationManager<value_type> Interface;

    static const CreationManager& instance()
    {
        static const CreationManager i;
        return i;
    }

    value_type* create() const
    {
        return new_object();
    }

    value_type* copy(const value_type* otherObj) const
    {
        return new_object(otherObj);
    }

    void destroy(value_type* pObj) const
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
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreationManager)
};
//==============================================================================
template<
    class FromType, 
    class ToType,
    class EmergencyPolicyT = CreationManagment::Union<
        Creation::Null<ToType>,
        Copying::Null<ToType>,
        Destruction::BySafetyDelete<ToType>
        > 
    >
class CreationManagerWrapper:
    public ICreationManager<ToType>
{
public:

    typedef ToType value_type;
    typedef ICreationManager<value_type> Interface;

    CreationManagerWrapper(const ICreationManager<FromType>* creationManager):
        _cm(creationManager)
    {
        StaticAssert<TT::Equal<EmergencyPolicyT::value_type, value_type>::result>();
    }
        
    value_type* create() const
    {
        if (_cm)
        {
            FromType* obj = _cm->create();
            ToType* robj = optimum_cast<ToType*>(obj);
            if (robj)
                return robj;
            else if (obj)
                _cm->destroy(obj);
        }
        return EmergencyPolicyT::new_object();
    }

    value_type* copy(const value_type* otherObject) const
    {
        if (_cm)
        {
            if (const FromType* cobj = optimum_cast<const FromType*>(otherObject))
            {
                FromType* obj = _cm->copy(cobj);
                ToType* robj = optimum_cast<ToType*>(obj);
                if (robj)
                    return robj;
                else if (obj)
                    _cm->destroy(obj);
            }
        }
        return EmergencyPolicyT::new_object(otherObject);
    }

    void destroy(value_type* object) const
    {
        if (_cm)
        {            
            FromType* obj = optimum_cast<FromType*>(object);
            if (obj)
            {
                _cm->destroy(obj);
                return;
            }             
        }
        EmergencyPolicyT::delete_object(object);
    }
    
private:
    const ICreationManager<FromType> *_cm;
};
//==============================================================================
template<class ArrayCreationManagmentPolicyT>
class ArrayCreationManager :
    public IArrayCreationManager<typename ArrayCreationManagmentPolicyT::value_type>
{
public:
    typedef ArrayCreationManagmentPolicyT Policy;
    typedef typename Policy::value_type value_type;
    typedef IArrayCreationManager<value_type> Interface;

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
}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
