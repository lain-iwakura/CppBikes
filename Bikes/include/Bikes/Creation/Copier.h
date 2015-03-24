#ifndef INCLUDE_BIKES_CREATION_COPIER_H
#define INCLUDE_BIKES_CREATION_COPIER_H

#include <Bikes/Creation/CopyingPolicy.h>

namespace Bikes
{
//==============================================================================
template<class T>
class ObjectCopierInterface
{
public:

    virtual T* copyObject(const T* otherObject) const = 0;

protected:

//    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectCopierInterface)
};
//------------------------------------------------------------------------------
template<class T>
class ArrayCopierInterface
{
public:
    typedef T value_type;

    virtual T* copyArray(const T* otherArray, sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCopierInterface)
};
//------------------------------------------------------------------------------
template<class T>
class CopierInterface :
    public ObjectCopierInterface<T>,
    public ArrayCopierInterface<T>
{
public:
//  virtual T* copyObject(const T* otherObject) const = 0;
//  virtual T* copyArray(const T* otherArray, sznum sz) const = 0;
protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CopierInterface)
};
//==============================================================================
template<class ObjectCopyingPolicyT>
class ObjectCopier :
    public ObjectCopierInterface<typename ObjectCopyingPolicyT::value_type>
{
public:
    typedef typename ObjectCopyingPolicyT::value_type value_type;

    static const ObjectCopier& instance()
    {
        static const ObjectCopier i;
        return i;
    }

    value_type* copyObject(const value_type* otherObject) const
    {
        return new_object(otherObject);
    }

    static value_type* new_object(const value_type* otherObject)
    {
        return ObjectCopyingPolicyT::new_object(otherObject);
    }
private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ObjectCopier)
};
//==============================================================================
template<class ArrayCopyingPolicyT>
class ArrayCopier :
    public ObjectCopierInterface<typename ArrayCopyingPolicyT::value_type>
{
public:
    typedef typename ArrayCopyingPolicyT::value_type value_type;

    static const ArrayCopier& instance()
    {
        static const ArrayCopier i;
        return i;
    }

    value_type* copyArray(const value_type* otherArray, sznum sz) const
    {
        return new_array(otherArray, sz);
    }    

    static value_type* new_array(const value_type* otherArray, sznum sz)
    {
        return ArrayCopyingPolicyT::new_array(otherArray,sz);
    }
private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCopier)
};
//==============================================================================
template<class CopyingPolicyT>
class Copier :
    public CopierInterface<typename CopyingPolicyT::value_type>
{
public:
    typedef typename CopyingPolicyT::value_type value_type;

    static const Copier& instance()
    {
        static const Copier i;
        return i;
    }

    value_type* copyObject(const value_type* otherObject) const
    {
        return new_object(otherObject);
    }

    value_type* copyArray(const value_type* otherArray, sznum sz) const
    {
        return new_array(otherArray, sz);
    }

    static value_type* new_object(const value_type* otherObject)
    {
        return CopyingPolicyT::new_object(otherObject);
    }

    static value_type* new_array(const value_type* otherArray, sznum sz)
    {
        return CopyingPolicyT::new_array(otherArray, sz);
    }
private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Copier)
};
//==============================================================================
}


#endif // <- INCLUDE_BIKES_CREATION_COPIER_H
