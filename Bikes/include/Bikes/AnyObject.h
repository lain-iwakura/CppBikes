#ifndef INCLUDE_BIKES_ARBITARYOBJECT_H
#define INCLUDE_BIKES_ARBITARYOBJECT_H

#include <Bikes/TypeTools/TypeStack.h>
#include <Bikes/TypeTools/ToTypeStack.h>
#include <Bikes/Conversion.h>
#include <Bikes/MacrosBikes.h>

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

    virtual ~AnyObjectInterface()
    {}

    virtual ObjectType* get() = 0;

    virtual const ObjectType* get() const = 0;
};
//==============================================================================
template<class T, class HintT = NullType>
class AnyObjectWrapper : public AnyObjectInterface<HintT>
{
public:
    virtual ~AnyObjectWrapper()
    {}

    typedef HintT ObjectType;

    ObjectType* get()
    {
        AnyObjectWrapper<T>* p = 
            dynamic_cast<AnyObjectWrapper<T>*>(this);

        if (p)
            return optimum_cast<ObjectType*>(p->get());
        return 0;
    }

    const ObjectType* get() const
    {
        const AnyObjectWrapper<T>* p = 
            dynamic_cast<const AnyObjectWrapper<T>*>(this);

        if (p)
            return optimum_cast<const ObjectType*>(p->get());
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
class AnyObjectWrapper<T,TT::NullType> :
    public AnyObjectBase,
    public AnyObjectInterface<T>
{
public:

    typedef AnyObjectWrapper<T, TT::NullType> ThisType;

    AnyObjectWrapper(T* pObj):
        _obj(pObj)
    {
    }

    AnyObjectWrapper(const ThisType& other) :
        _obj( (other._obj) ? (new T(_obj)) : (0) ) //?
    {
    }

    virtual ~AnyObjectWrapper()
    {
        if (_obj)
            delete _obj;
    }

    typedef T ObjectType;

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

    CBIKES_CLONE_DECLDEF

private:
    T* _obj;
};
//------------------------------------------------------------------------------
template<class T, class T1, class T2>
class AnyObjectWrapper<T, TT::TypeStack::Element<T1,T2> > :
    public TT::Select<
        TT::IsNullType<typename TT::TypeStack::Element<T1, T2>::Head>::result,
        TT::EmptyType,
        AnyObjectWrapper<T, typename TT::TypeStack::Element<T1, T2>::Head>
        >::ResultType,
    public AnyObjectWrapper<T, typename TT::TypeStack::Element<T1,T2>::Tail>
{
public:

    typedef AnyObjectWrapper<T, TT::TypeStack::Element<T1, T2> > ThisType;

    AnyObjectWrapper(T *pObj):
        AnyObjectWrapper<T, typename TT::TypeStack::Element<T1, T2>::Tail>(pObj)
    {}

    CBIKES_CLONE_DECLDEF
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


    template< 
        class T, 
        class Hint1 = TT::NullType, class Hint2 = TT::NullType, class Hint3 = TT::NullType, 
        class Hint4 = TT::NullType, class Hint5 = TT::NullType, class Hint6 = TT::NullType,
        class Hint7 = TT::NullType, class Hint8 = TT::NullType, class Hint9 = TT::NullType
        >
    void set(const T& obj)
    {
        if (_aObj)
            delete _aObj;

        _aObj = new Inner::AnyObjectWrapper<
            T, 
            typename TT::ToTypeStack<
                Hint1,Hint2,Hint3,Hint4,Hint5,Hint6,Hint7,Hint8,Hint9
                >::ResultStack 
            >(new T(obj));
    }

    template< 
        class T, 
        class Hint1 = TT::NullType, class Hint2 = TT::NullType, class Hint3 = TT::NullType, 
        class Hint4 = TT::NullType, class Hint5 = TT::NullType, class Hint6 = TT::NullType,
        class Hint7 = TT::NullType, class Hint8 = TT::NullType, class Hint9 = TT::NullType
        >
    void set(T* obj)
    {
        if (_aObj)
            delete _aObj;

        if(obj)
        {
            _aObj = new Inner::AnyObjectWrapper<
                T, 
                typename TT::ToTypeStack<
                    Hint1,Hint2,Hint3,Hint4,Hint5,Hint6,Hint7,Hint8,Hint9
                    >::ResultStack 
                >(obj);
        }
        else
        {
            _aObj = 0;
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

    CBIKES_CLONE_DECLDEF

private:
    Inner::AnyObjectBase* _aObj;
};
//==============================================================================
} // Bikes

#endif // <- INCLUDE_BIKES_ARBITARYOBJECT_H
