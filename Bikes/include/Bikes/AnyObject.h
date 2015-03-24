#ifndef INCLUDE_BIKES_ARBITARYOBJECT_H
#define INCLUDE_BIKES_ARBITARYOBJECT_H

#include <Bikes/TypeTools/TypeStack.h>
#include <Bikes/TypeTools/ToTypeStack.h>
#include <Bikes/Conversion.h>
#include <Bikes/MacrosBikes.h>
#include <Bikes/Creation/CreationManager.h>

#include <memory>

namespace Bikes{
namespace Inner{
//==============================================================================
class AnyObjectBase
{
public:
    virtual ~AnyObjectBase()
    {}

    virtual AnyObjectBase* clone() const = 0;

    virtual void* getVoid() = 0;

    virtual const void* getVoid() const = 0;
};
//==============================================================================
template<class T>
class AnyObjectInterface
{
public:

    typedef typename T ObjectType;

    virtual ObjectType* get() = 0;

    virtual const ObjectType* get() const = 0;

    virtual ObjectType* cloneObject() const = 0;

    virtual const ObjectCreationManagerInterface<T>* crMng() const
    {
        return 0;
    }
};
//==============================================================================
template<class CrMngT, class HintT = TT::NullType>
class AnyObjectHolder;
//==============================================================================
template<class T, class HintT>
class AnyObjectWrapper : public AnyObjectInterface<HintT>
{
public:

    typedef HintT ObjectType;

    ObjectType* get()
    {
        AnyObjectInterface<T>* p =
            dynamic_cast<AnyObjectInterface<T>*>(this);

        if (p)
            return optimum_cast<ObjectType*>(p->get());
        return 0;
    }

    const ObjectType* get() const
    {
        const AnyObjectInterface<T>* p =
            dynamic_cast<const AnyObjectInterface<T>*>(this);

        if (p)
            return optimum_cast<const ObjectType*>(p->get());
        return 0;
    }

    ObjectType* cloneObject() const
    {
        const AnyObjectInterface<T>* p =
            dynamic_cast<const AnyObjectInterface<T>*>(this);
        if (p)
        {
            T *_co = p->cloneObject();
            if (_co)
            {
                if (ObjectType* co = optimum_cast<ObjectType*>(_co))
                    return co;
                else
                {
                    if (p->crMng())
                        p->crMng()->destroyObject(_co);
                    else
                    {
                        BIKES_ASSERT_NEVER_REACH();
                    }
                }
            }
        }
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
class AnyObjectWrapper<T,TT::NullType>
{
public:
};
//==============================================================================
template<class CrMngT, class HintT>
class AnyObjectHolder:
    public AnyObjectHolder<CrMngT, TT::NullType>,
    public AnyObjectInterface<HintT>
{
public:

    typedef AnyObjectHolder<CrMngT, TT::NullType> Base;
    typedef HintT ObjectType;

    AnyObjectHolder(typename CrMngT::value_type *pObj) :
        AnyObjectHolder<CrMngT, TT::NullType>(pObj)
    {}


    virtual ObjectType* get()
    {
        return optimum_cast<ObjectType*>(Base::get());
    }

    virtual const ObjectType* get() const
    {
        return optimum_cast<const ObjectType*>(Base::get());
    }

    ObjectType* cloneObject() const
    {
        return Base::cloneObject();
    }

    const ObjectCreationManagerInterface<typename CrMngT::value_type>* crMng() const
    {
        return Base::crMng();
    }
};
//------------------------------------------------------------------------------
template<class CrMngT>
class AnyObjectHolder<CrMngT, TT::NullType> :
    public AnyObjectBase,
    public AnyObjectInterface<typename CrMngT::value_type>
{
public:

    typedef AnyObjectHolder<CrMngT, TT::NullType> ThisType;

    typedef typename CrMngT::value_type ObjectType;

    AnyObjectHolder(ObjectType* pObj) :
        _obj(pObj)
    {
    }

    AnyObjectHolder(const ThisType& other) :
        _obj((other._obj) ? (CrMngT::new_object(other._obj)) : (0)) //?
    {
    }

    virtual ~AnyObjectHolder()
    {
        if (_obj)
            CrMngT::delete_object(_obj);
    }

    ObjectType* get()
    {
        return _obj;
    }

    const ObjectType* get() const
    {
        return _obj;
    }

    void* getVoid()
    {
        return _obj;
    }

    const void* getVoid() const
    {
        return _obj;
    }

    ObjectType* cloneObject() const
    {
        if (_obj)
            return CrMngT::new_object(_obj);
        return 0;
    }

    const ObjectCreationManagerInterface<typename CrMngT::value_type>* crMng() const
    {
        return &ObjectCreationManager<CrMngT>::instance();
    }

    CBIKES_CLONE_DECLDEF

private:
    ObjectType* _obj;
};
//------------------------------------------------------------------------------
template<class CrMngT, class T1, class T2>
class AnyObjectHolder<CrMngT, TT::TypeStack::Element<T1, T2> > :
    public AnyObjectWrapper<typename CrMngT::value_type, typename TT::TypeStack::Element<T1, T2>::Head>,
    public AnyObjectHolder<CrMngT, typename TT::TypeStack::Element<T1, T2>::Tail>
{
public:

    typedef AnyObjectHolder<CrMngT, TT::TypeStack::Element<T1, T2> > ThisType;

    AnyObjectHolder(typename CrMngT::value_type *pObj) :
        AnyObjectHolder<CrMngT, typename TT::TypeStack::Element<T1, T2>::Tail>(pObj)
    {}

    CBIKES_CLONE_DECLDEF
};
//==============================================================================
template<class T, class HintStack = TT::NullType>
struct AnyCrMngPlc
{
    typedef typename TT::TypeStack::FindMin<HintStack, TT::CompareByHierrarchy >::ResultType HintMin;

    typedef typename TT::MinType<T, HintMin, TT::CompareByHierrarchy>
        ::ResultType MinT;

    typedef typename CreationManagment::ObjectUnion<
        Creation::NullObject<MinT>,
        Copying::ObjectByNew<MinT>,
        Destruction::ObjectByDelete<MinT>
    > CrMngPlc;

    typedef typename CrMngPlc::value_type value_type;

    CBIKES_NEW_OBJECT_DECLDEF(CrMngPlc)
    CBIKES_NEW_OBJECT_CPY_DECLDEF(CrMngPlc)
    CBIKES_DELETE_OBJECT_DECLDEF(CrMngPlc)
};
//------------------------------------------------------------------------------
template<class T>
struct AnyCrMngPlc<T,TT::NullType>
{
    typedef T value_type;

    CBIKES_NEW_OBJECT_DECLDEF(Creation::NullObject<T>)
    CBIKES_NEW_OBJECT_CPY_DECLDEF(Copying::ObjectByNew<T>)
    CBIKES_DELETE_OBJECT_DECLDEF(Destruction::ObjectByDelete<T>)
};
//==============================================================================
}
//==============================================================================
class AnyObject
{
public:

    typedef AnyObject ThisType;

    AnyObject():
        _aObj(0)
    {}

    AnyObject(const AnyObject& anyObj) :
        _aObj(anyObj._aObj ? anyObj._aObj->clone() : 0)
    {}

    template<class T>
    AnyObject(const T& obj):
        _aObj(0)
    {
        set(obj);
    }

    template<class T>
    AnyObject(T* obj) :
        _aObj(0)
    {
        set(obj);
    }

    ~AnyObject()
    {
        if (_aObj)
            delete _aObj;
    }

    template<class T>
    T* get()
    {
        Inner::AnyObjectInterface<T>* p = 
            dynamic_cast<Inner::AnyObjectInterface<T>*>(_aObj);
        if (p)
            return p->get();
        return 0;
    }

    template<class T>
    const T* get() const
    {
        const Inner::AnyObjectInterface<T>* p =
            dynamic_cast<const Inner::AnyObjectInterface<T>*>(_aObj);
        if (p)
            return p->get();
        return 0;
    }   

    const void* getVoid() const
    {
        if (_aObj)
            return _aObj->getVoid();
        return 0;
    }

    void* getVoid() 
    {
        if (_aObj)
            return _aObj->getVoid();
        return 0;
    }

    bool empty() const
    {
        if (_aObj)
            return _aObj->getVoid() == 0;
        return true;
    }

    template<class T>
    T value() const
    {
        T* val = get<T>();
        if (val)
            return *val;
        return T();
    }

    template<class T>
    T value(const T& defaultValue)
    {
        T* val = get<T>();
        if (val)
            return *val;
        return defaultValue;
    }


    template< 
        class T, 
        class Hint1 = TT::NullType, class Hint2 = TT::NullType, class Hint3 = TT::NullType, 
        class Hint4 = TT::NullType, class Hint5 = TT::NullType, class Hint6 = TT::NullType,
        class Hint7 = TT::NullType, class Hint8 = TT::NullType, class Hint9 = TT::NullType
        >
    void set(const T& obj)
    {
        setWithPolicy<Inner::AnyCrMngPlc<T>,
            Hint1, Hint2, Hint3, Hint4, Hint5, Hint6, Hint7, Hint8, Hint9
            >(obj);
    }

    // void set(const T& obj, const ObjectCreationManagerInterface<T>* crMng ) 

    template<
        class CrMngPolicy,
        class Hint1 = TT::NullType, class Hint2 = TT::NullType, class Hint3 = TT::NullType,
        class Hint4 = TT::NullType, class Hint5 = TT::NullType, class Hint6 = TT::NullType,
        class Hint7 = TT::NullType, class Hint8 = TT::NullType, class Hint9 = TT::NullType
    >
    void setWithPolicy(typename CrMngPolicy::value_type const& obj)
    {
        takeWithPolicy<CrMngPolicy,
            Hint1, Hint2, Hint3, Hint4, Hint5, Hint6, Hint7, Hint8, Hint9
        >(CrMngPolicy::new_object(&obj));
    }

    template< 
        class T, 
        class Hint1 = TT::NullType, class Hint2 = TT::NullType, class Hint3 = TT::NullType, 
        class Hint4 = TT::NullType, class Hint5 = TT::NullType, class Hint6 = TT::NullType,
        class Hint7 = TT::NullType, class Hint8 = TT::NullType, class Hint9 = TT::NullType
        >
    void take(T* obj)
    {
        takeWithPolicy<Inner::AnyCrMngPlc<T>,
            Hint1, Hint2, Hint3, Hint4, Hint5, Hint6, Hint7, Hint8, Hint9
            >(obj);
    }

    template<
        class CrMngPolicy,
        class Hint1 = TT::NullType, class Hint2 = TT::NullType, class Hint3 = TT::NullType, 
        class Hint4 = TT::NullType, class Hint5 = TT::NullType, class Hint6 = TT::NullType,
        class Hint7 = TT::NullType, class Hint8 = TT::NullType, class Hint9 = TT::NullType
        >
    void takeWithPolicy(typename CrMngPolicy::value_type* obj)
    {
        typedef typename TT::ToTypeStack<
            Hint1, Hint2, Hint3, Hint4, Hint5, Hint6, Hint7, Hint8, Hint9
        >::ResultStack HintStack;

        if (_aObj)
            delete _aObj;

        if (obj)
        {
            _aObj = new Inner::AnyObjectHolder<CrMngPolicy, HintStack>(obj);
        }
        else
        {
            _aObj = 0; //?
        }
    }
        
    template<class T>
    AnyObject& operator = (const T& obj)
    {
        set(obj);
        return *this;
    }

    template<class T>
    AnyObject& operator = (T* obj)
    {
        set(obj);
        return *this;
    }

private:
    Inner::AnyObjectBase* _aObj;
};
//==============================================================================
} // Bikes

#endif // <- INCLUDE_BIKES_ARBITARYOBJECT_H
