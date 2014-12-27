#ifndef INCLUDE_BIKES_TYPETOOLS_TYPESTACKHOLDER_H
#define INCLUDE_BIKES_TYPETOOLS_TYPESTACKHOLDER_H

#include <Bikes/TypeTools/TypeStack.h>

namespace Bikes{
namespace TT{
//==============================================================================
template<
    class StackT,
    class ObjectBaseT = typename TT::TypeStack::FindMax<StackT, CompareByHierrarchy>::ResultType,
    template<class> class CreationSupervisorT = SafetyCloningSupervisor,
    class BaseCreationSupervisorT = 
        CreationManager<
            SafetyCloner<ObjectBaseT>,
            NullCreator<ObjectBaseT>,
            SafetyDeleter<ObjectBaseT>
            >
    >
class ConstObjectsHolder
{
public:
    typedef List<ObjectBaseT,BaseCreationSupervisorT> Container;
    typedef BaseCreationSupervisorT BaseCreationSupervisor;

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
        static const sznum _i = i;
        objects.retake(_i,CreationSupervisorT<CurType>::create());
    }

    template<num i>
    void deinitialize()
    {
        typedef typename TT::TypeStack::TypeAt<StackT, i>::ResultType CurType;
        static const sznum _i = i;
        CreationSupervisorT<CurType>::destroy(static_cast<CurType*>(objects.pass(_i)));
    }

private:
    Container objects;
};
//==============================================================================
template<
    class StackT,
    class ObjectBaseT = typename TT::TypeStack::FindMax<StackT, CompareByHierrarchy>::ResultType,
    template<class> class CreationSupervisorT = SafetyCloningSupervisor,
    class BaseCreationSupervisorT =
        CreationManager<
            SafetyCloner<ObjectBaseT>,
            NullCreator<ObjectBaseT>,
            SafetyDeleter<ObjectBaseT>
            >
    >
class ObjectsHolder
{
public:
    typedef List<ObjectBaseT, BaseCreationSupervisorT> Container;
    typedef BaseCreationSupervisorT BaseCreationSupervisor;

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
        const sznum _i = i;
        objects.retake(CreationSupervisorT<CurType>::create());
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
    typedef typename Inner::TypeStackHolder<
        StackT,
        TT::TypeStack::Count<StackT>::result - 1,
        HolderBaseT
        >
        InnerStackHolder;

    static typename HolderBaseT::HeldType& get()
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
} // TT
} // Bikes

#endif
