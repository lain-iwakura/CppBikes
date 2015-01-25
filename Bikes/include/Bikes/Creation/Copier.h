#ifndef INCLUDE_BIKES_CREATION_COPIER_H
#define INCLUDE_BIKES_CREATION_COPIER_H

#include <Bikes/Creation/ÑopyingPolicy.h>

namespace Bikes
{
//==============================================================================
template<class T>
class SingleCopierInterface
{
public:

    virtual T* copy(const T* otherObject) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleCopierInterface)
};
//------------------------------------------------------------------------------
template<class T>
class ArrayCopierInterface
{
public:
    typedef T value_type;

    virtual T* copy(const T* otherArray, sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ArrayCopierInterface)
};
//------------------------------------------------------------------------------
template<class T>
class CopierInterface :
    public SingleCopierInterface<T>,
    public ArrayCopierInterface<T>
{
public:
//  virtual T* copy(const T* otherObject) const = 0;
//  virtual T* copy(const T* otherArray, sznum sz) const = 0;
protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(CopierInterface)
};
//==============================================================================
template<class SingleCopyingPolicyT>
class SingleCopier :
    public SingleCopierInterface<typename SingleCopyingPolicyT::value_type>
{
public:
    typedef typename SingleCopyingPolicyT::value_type value_type;

    static const SingleCopier& instance()
    {
        static const SingleCopier i;
        return i;
    }

    value_type* copy(const value_type* otherObject) const
    {
        return new_copy(otherObject);
    }

    static value_type* new_copy(const value_type* otherObject)
    {
        return SingleCopyingPolicyT::new_copy(otherObject);
    }
private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(SingleCopier)
};
//==============================================================================
template<class ArrayCopyingPolicyT>
class ArrayCopier :
    public SingleCopierInterface<typename ArrayCopyingPolicyT::value_type>
{
public:
    typedef typename ArrayCopyingPolicyT::value_type value_type;

    static const ArrayCopier& instance()
    {
        static const ArrayCopier i;
        return i;
    }

    value_type* copy(const value_type* otherObject) const
    {
        return new_copy(otherObject);
    }    

    value_type* copy(const value_type* otherObject, sznum sz) const
    {
        return new_copy(otherObject,sz);
    }

    static value_type* new_copy(const value_type* otherObject)
    {
        return CopyingPolicyT::new_copy(otherObject);
    }

    static value_type* new_copy(const value_type* otherObject, sznum sz)
    {
        return ArrayCopyingPolicyT::new_copy(otherObject,sz);
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

    value_type* copy(const value_type* otherObject, sznum sz) const
    {
        return new_copy(otherObject, sz);
    }

    static value_type* new_copy(const value_type* otherObject, sznum sz)
    {
        return CopyingPolicyT::new_copy(otherObject, sz);
    }
private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Copier)
};
//==============================================================================
}


#endif // <- INCLUDE_BIKES_CREATION_COPIER_H
