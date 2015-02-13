#ifndef INCLUDE_BIKES_CREATION_CREATOR_H
#define INCLUDE_BIKES_CREATION_CREATOR_H

#include <Bikes/Creation/CreationPolicy.h>
#include <Bikes/MacrosBikes.h>

namespace Bikes
{
//==============================================================================
template<class T>
class ObjectCreatorInterface
{
public:

    virtual T* createObject() const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectCreatorInterface)
};
//==============================================================================
template<class T>
class ArrayCreatorInterface
{
public:

    virtual T* createArray(sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCreatorInterface)
};
//==============================================================================
template<class T>
class CreatorInterface : 
    public ObjectCreatorInterface<T>,
    public ArrayCreatorInterface<T>
{
public: 
//  virtual T* createObject() const = 0;
//  virtual T* createArray(sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreatorInterface)
};
//==============================================================================
template<class ObjectCreationPolicyT>
class ObjectCreator : 
    public ObjectCreatorInterface<typename ObjectCreationPolicyT::value_type>
{
public:
    typedef typename ObjectCreationPolicyT::value_type value_type;

    static const ObjectCreator& instance()
    {
        static const ObjectCreator i;
        return i;
    }

    value_type* createObject() const
    {
        return new_object();
    }

    static value_type* new_object()
    {
        return ObjectCreationPolicyT::new_object();
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectCreator)
};
//==============================================================================
template<class ArrayCreationPolicyT>
class ArrayCreator : 
    public ArrayCreatorInterface<typename ArrayCreationPolicyT::value_type>
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
template<class CreationPolicyT>
class Creator : public CreatorInterface<typename CreationPolicyT::value_type>
{
public:
    typedef typename CreationPolicyT::value_type value_type;

    static const ArrayCreator& instance()
    {
        static const Creator i;
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

    static value_type* new_object()
    {
        return CreationPolicyT::new_object();
    }

    static value_type* new_array(sznum sz)
    {
        return CreationPolicyT::new_array(sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Creator)
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_CREATION_CREATOR_H
