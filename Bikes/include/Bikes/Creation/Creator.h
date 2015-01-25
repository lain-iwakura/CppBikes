#ifndef INCLUDE_BIKES_CREATION_CREATOR_H
#define INCLUDE_BIKES_CREATION_CREATOR_H

#include <Bikes/Creation/CreationPolicy.h>
#include <Bikes/MacrosBikes.h>

namespace Bikes
{
//==============================================================================
template<class T>
class SingleCreatorInterface
{
public:

    virtual T* create() const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleCreatorInterface)
};
//==============================================================================
template<class T>
class ArrayCreatorInterface
{
public:

    virtual T* create(sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCreatorInterface)
};
//==============================================================================
template<class T>
class CreatorInterface : 
    public SingleCreatorInterface<T>,
    public ArrayCreatorInterface<T>
{
public: 
//  virtual T* create() const = 0;
//  virtual T* create(sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CreatorInterface)
};
//==============================================================================
template<class SingleCreationPolicyT>
class SingleCreator : 
    public SingleCreatorInterface<typename SingleCreationPolicyT::value_type>
{
public:
    typedef typename SingleCreationPolicyT::value_type value_type;

    static const SingleCreator& instance()
    {
        static const SingleCreator i;
        return i;
    }

    value_type* create() const
    {
        return new_instance();
    }

    static value_type* new_instance()
    {
        return SingleCreationPolicyT::new_instance();
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleCreator)
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

    value_type* create(sznum sz) const
    {
        return new_instance(sz);
    }

    static value_type* new_instance(sznum sz)
    {
        return ArrayCreationPolicyT::new_instance(sz);
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
    
    value_type* create() const
    {        
        return new_instance();
    }

    value_type* create(sznum sz) const
    {
        return new_instance(sz);
    }

    static value_type* new_instance()
    {
        return CreationPolicyT::new_instance();
    }

    static value_type* new_instance(sznum sz)
    {
        return CreationPolicyT::new_instance(sz);
    }

private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Creator)
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_CREATION_CREATOR_H
