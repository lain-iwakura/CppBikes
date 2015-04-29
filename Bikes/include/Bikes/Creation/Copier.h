#ifndef INCLUDE_BIKES_CREATION_COPIER_H
#define INCLUDE_BIKES_CREATION_COPIER_H

#include <Bikes/Creation/CopyingPolicy.h>

namespace Bikes
{
//==============================================================================
template<class T>
class ICopier
{
public:

    virtual T* copy(const T* otherObject) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(ICopier)
};
//------------------------------------------------------------------------------
template<class T>
class IArrayCopier
{
public:
    typedef T value_type;

    virtual T* copyArray(const T* otherArray, sznum sz) const = 0;

protected:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(IArrayCopier)
};
//==============================================================================
template<class ObjectCopyingPolicyT>
class Copier :
    public ICopier<typename ObjectCopyingPolicyT::value_type>
{
public:
    typedef typename ObjectCopyingPolicyT::value_type value_type;

    static const Copier& instance()
    {
        static const Copier i;
        return i;
    }

    value_type* copy(const value_type* otherObject) const
    {
        return new_object(otherObject);
    }

    static value_type* new_object(const value_type* otherObject)
    {
        return ObjectCopyingPolicyT::new_object(otherObject);
    }
private:
    CBIKES_DEFAULTDEFINITIONS_NULL_DECLDEF(Copier)
};
//==============================================================================
template<class ArrayCopyingPolicyT>
class ArrayCopier :
    public IArrayCopier<typename ArrayCopyingPolicyT::value_type>
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
}


#endif // <- INCLUDE_BIKES_CREATION_COPIER_H
