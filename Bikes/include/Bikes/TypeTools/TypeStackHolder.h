#ifndef INCLUDE_BIKES_TYPETOOLS_TYPESTACKHOLDER_H
#define INCLUDE_BIKES_TYPETOOLS_TYPESTACKHOLDER_H

#include <Bikes/TypeTools/TypeStack.h>
#include <Bikes/Array/List.h>

namespace Bikes{
namespace TT{
//==============================================================================
template<
    class StackT,
    class ObjectBaseT = typename TT::TypeStack::FindMax<StackT, CompareByHierrarchy>::ResultType,
    template<class> class ChildCreationManagmentT = CreationManagment::PolimorphObject,
    class BaseCreationManagmentT = CreationManagment::AbstractObject<ObjectBaseT>
    >
class ConstObjectsHolder
{
public:
    typedef List<ObjectBaseT, BaseCreationManagmentT> Container;
    typedef BaseCreationManagmentT BaseCreationManagment;

    typedef StackT TypeStack;

    typedef const Container HeldType;

    ConstObjectsHolder() :
        objects(Container::size_type(TT::TypeStack::Count<StackT>::result))
    {
    }

    virtual ~ConstObjectsHolder()
    {
    }

    HeldType& get() const
    {
        return objects;
    }


protected:

    template<num i>
    void initialize()
    {
        typedef typename TT::TypeStack::TypeAt<StackT, i>::ResultType CurType;
        objects.retake(sznum(i), ChildCreationManagmentT<CurType>::new_object());
    }

    template<num i>
    void deinitialize()
    {
        typedef typename TT::TypeStack::TypeAt<StackT, i>::ResultType CurType;
        ChildCreationManagmentT<CurType>::delete_object(static_cast<CurType*>(objects.pass(sznum(i))));
    }

private:
    Container objects;
};
//==============================================================================
template<
    class StackT,
    class ObjectBaseT = typename TT::TypeStack::FindMax<StackT, CompareByHierrarchy>::ResultType,
    template<class> class ChildCreationManagmentT = CreationManagment::PolimorphObject,
    class BaseCreationManagmentT = CreationManagment::AbstractObject<ObjectBaseT>
    >
class ObjectsHolder
{
public:
    typedef List<ObjectBaseT, BaseCreationManagmentT> Container;
    typedef BaseCreationManagmentT BaseCreationManagment;

    typedef StackT TypeStack;

    typedef Container HeldType;

    ObjectsHolder() :
        objects(TT::TypeStack::Count<StackT>::result)
    {
    }

    virtual ~ObjectsHolder()
    {
    }

    HeldType& get()
    {
        return objects;
    }

    
protected:

    template<num i>
    void initialize()
    {
        typedef typename TT::TypeStack::TypeAt<StackT, i>::ResultType CurType;
        objects.retake(sznum(i), ChildCreationManagmentT<CurType>::create());
    }

    template<num i>
    void deinitialize()
    {      
    }

private:
    Container objects;
};
//==============================================================================
namespace Inner{
template<class StackT, num i, class HolderBaseT >
class TypeStackHolder:
    public Inner::TypeStackHolder<StackT, i - 1, HolderBaseT>
{
public:
    TypeStackHolder()
    {
        HolderBaseT::template initialize<i>();
    }

    virtual ~TypeStackHolder()
    {
        HolderBaseT:: template deinitialize<i>();
    }
};
//------------------------------------------------------------------------------
template<class StackT, class HolderBaseT >
class TypeStackHolder<StackT, 0, HolderBaseT>:
    public HolderBaseT
{
public:
    TypeStackHolder()
    {
        HolderBaseT:: template initialize<0>();
    }

    virtual ~TypeStackHolder()
    {
        HolderBaseT:: template deinitialize<0>();
    }
};
//------------------------------------------------------------------------------
template<class StackT, class HolderBaseT >
class TypeStackHolder<StackT, -1, HolderBaseT>:
    public HolderBaseT
{
public:
    TypeStackHolder()
    {
    }

    virtual ~TypeStackHolder()
    {
    }
};
} // Inner
//==============================================================================
template<class StackT, class HolderBaseT = ConstObjectsHolder<StackT> >
class TypeStackHolder
{
public:

    typedef typename HolderBaseT::HeldType HeldType;

    typedef typename Inner::TypeStackHolder<
        StackT,
        TT::TypeStack::Count<StackT>::result - 1,
        HolderBaseT
        >
        InnerStackHolder;

    static HeldType& get()
    {
        return _holder.get();
    }

private:
    static InnerStackHolder _holder;
};
//------------------------------------------------------------------------------
template<class StackT, class HolderBaseT >
typename TypeStackHolder<StackT, HolderBaseT>::InnerStackHolder
TypeStackHolder<StackT, HolderBaseT>::_holder;
//==============================================================================
template<class T = NullType>
struct MultiType : public T, public MultiType<>
{
    typedef T Base;
    typedef MultiType<> MultiBase;

    virtual ~MultiType()
    {}
};
//------------------------------------------------------------------------------
template<class T1, class T2>
struct MultiType<TypeStack::Element<T1,T2> > :
    public TypeStack::Element<T1, T2>::Head,
    public MultiType<typename TypeStack::Element<T1, T2>::Tail>
{
    typedef typename TypeStack::Element<T1, T2>::Head Base;
    typedef typename MultiType<typename TypeStack::Element<T1, T2>::Tail> MultiBase;

    virtual ~MultiType()
    {}
};
//------------------------------------------------------------------------------
template<>
struct MultiType<NullType>
{
    typedef NullType Base;
    typedef NullType MultiBase;

    virtual ~MultiType()
    {}
};
//==============================================================================
} // TT
} // Bikes

#endif
