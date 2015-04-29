#ifndef INCLUDE_BIKES_CREATION_CREATOR_H
#define INCLUDE_BIKES_CREATION_CREATOR_H

#include <Bikes/Creation/CreationPolicy.h>
#include <Bikes/MacrosBikes.h>

namespace Bikes
{
//==============================================================================
template<class T>
class ICreator
{
public:

    virtual T* create() const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ICreator)
};
//==============================================================================
template<class T>
class IArrayCreator
{
public:

    virtual T* createArray(sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(IArrayCreator)
};
//==============================================================================
template<class ObjectCreationPolicyT>
class Creator : 
    public ICreator<typename ObjectCreationPolicyT::value_type>
{
public:
    typedef typename ObjectCreationPolicyT::value_type value_type;

    static const Creator& instance()
    {
        static const Creator i;
        return i;
    }

    value_type* create() const
    {
        return new_object();
    }

    static value_type* new_object()
    {
        return ObjectCreationPolicyT::new_object();
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Creator)
};
//==============================================================================
template<class ArrayCreationPolicyT>
class ArrayCreator : 
    public IArrayCreator<typename ArrayCreationPolicyT::value_type>
{
public:
    typedef typename ArrayCreationPolicyT::value_type value_type;

    static const ArrayCreator& instance()
    {
        static const ArrayCreator i;
        return i;
    }

    value_type* createArray(sznum sz) const
    {
        return new_array(sz);
    }

    static value_type* new_array(sznum sz)
    {
        return ArrayCreationPolicyT::new_array(sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCreator)
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_CREATION_CREATOR_H
