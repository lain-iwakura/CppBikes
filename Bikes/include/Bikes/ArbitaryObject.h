#ifndef INCLUDE_BIKES_ARBITARYOBJECT_H
#define INCLUDE_BIKES_ARBITARYOBJECT_H

#include <Bikes/TypeTools/TypeStack.h>
#include <Bikes/TypeTools/ToTypeStack.h>
#include <Bikes/Conversion.h>
#include <Bikes/MacrosBikes.h>

#include <memory>

namespace Bikes{
namespace Inner{

template<class T>
class ArbitaryObjectInterface
{
public:

    typedef typename T ObjectType;

    virtual ~ArbitaryObjectInterface()
    {}

    virtual ObjectType* get() = 0;

    virtual const ObjectType* get() const = 0;
};
//==============================================================================
class ArbitaryObjectBase
{
public:
    virtual ~ArbitaryObjectBase()
    {}

    virtual void* getVoid() = 0;

    virtual const void* getVoid() const = 0;
};
//==============================================================================
template<class T, class HintT = NullType>
class ArbitaryObjectWrapper : public ArbitaryObjectInterface<HintT>
{
public:
    virtual ~ArbitaryObjectWrapper()
    {}

    typedef HintT ObjectType;

    ObjectType* get()
    {
        ArbitaryObjectWrapper<T>* p = 
            dynamic_cast<ArbitaryObjectWrapper<T>*>(this);

        if (p)
            return optimum_cast<ObjectType*>(p->get());
        return 0;
    }

    const ObjectType* get() const
    {
        const ArbitaryObjectWrapper<T>* p = 
            dynamic_cast<const ArbitaryObjectWrapper<T>*>(this);

        if (p)
            return optimum_cast<const ObjectType*>(p->get());
        return 0;
    }
};
//------------------------------------------------------------------------------
template<class T>
class ArbitaryObjectWrapper<T,TT::NullType> :
    public ArbitaryObjectBase,
    public ArbitaryObjectInterface<T>
{
public:

    ArbitaryObjectWrapper(T* pObj):
        _obj(pObj)
    {
    }

    virtual ~ArbitaryObjectWrapper()
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

private:
    T* _obj;
};
//------------------------------------------------------------------------------
template<class T, class T1, class T2>
class ArbitaryObjectWrapper<T, TT::TypeStack::Element<T1,T2> > :
    public TT::Select<
        TT::IsNullType<typename TT::TypeStack::Element<T1, T2>::Head>::result,
        TT::EmptyType,
        ArbitaryObjectWrapper<T, typename TT::TypeStack::Element<T1, T2>::Head>
        >::ResultType,
    public ArbitaryObjectWrapper<T, typename TT::TypeStack::Element<T1,T2>::Tail>
{
public:
    ArbitaryObjectWrapper(T *pObj):
        ArbitaryObjectWrapper<T, typename TT::TypeStack::Element<T1, T2>::Tail>(pObj)
    {}
};
//==============================================================================
}

class ArbitaryObject
{
public:

    ArbitaryObject():
        _aObj(0)
    {}

    template<class T>
    ArbitaryObject(const T& obj):
        _aObj(0)
    {
        set(obj);
    }

    template<class T>
    ArbitaryObject(T* obj) :
        _aObj(0)
    {
        set(obj);
    }

    ~ArbitaryObject()
    {
        if (_aObj)
            delete _aObj;
    }

    template<class T>
    T* get()
    {
        Inner::ArbitaryObjectInterface<T>* p = 
            dynamic_cast<Inner::ArbitaryObjectInterface<T>*>(_aObj);
        if (p)
            return p->get();
        return 0;
    }

    template<class T>
    const T* get() const
    {
        const Inner::ArbitaryObjectInterface<T>* p =
            dynamic_cast<const Inner::ArbitaryObjectInterface<T>*>(_aObj);
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

        _aObj = new Inner::ArbitaryObjectWrapper<
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
            _aObj = new Inner::ArbitaryObjectWrapper<
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

private:
    Inner::ArbitaryObjectBase* _aObj;
};


} // Bikes

#endif // <- INCLUDE_BIKES_ARBITARYOBJECT_H
