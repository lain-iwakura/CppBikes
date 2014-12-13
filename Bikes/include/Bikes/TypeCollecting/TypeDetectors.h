#ifndef INCLUDE_BIKES_TYPECOLLECTING_TYPEDETECTORS_H
#define INCLUDE_BIKES_TYPECOLLECTING_TYPEDETECTORS_H

namespace Bikes
{
//==============================================================================
template<class T>
struct ConstDetector
{
    enum{
        isConst = false
    };
    typedef T NotConst;
};
template<class T>
struct ConstDetector<const T>
{
    enum{
        isConst = true
    };
    typedef T NotConst;
};
//------------------------------------------------------------------------------
template<class T>
struct PointerDetector
{
    enum{
        isPointer = false
    };
    typedef T NotPointer;
};
template<class T>
struct PointerDetector<T*>
{
    enum{
        isPointer = true
    };
    typedef T NotPointer;
};
//------------------------------------------------------------------------------
template<class T>
struct ConstPointerDetector
{
    enum{
        isConstPointer = false
    };

    typedef typename ConstDetector<
        typename PointerDetector<T>::NotPointer
    >::NotConst NotConstPointer;
};
template<class T>
struct ConstPointerDetector<const T*>
{
    enum{
        isConstPointer = true
    };
    typedef T NotConstPointer;
};
//------------------------------------------------------------------------------
template<class T>
struct ReferenceDetector
{
    enum{
        isReference = false
    };
    typedef T NotReference;
};
template<class T>
struct ReferenceDetector<T&>
{
    enum{
        isReference = true
    };
    typedef T NotReference;
};
//------------------------------------------------------------------------------
template<class T>
struct ConstReferenceDetector
{
    enum{
        isConstReference = false
    };

    typedef typename ConstDetector<
        typename ReferenceDetector<T>::NotReference
    >::NotConst NotConstReference;

};
template<class T>
struct ConstReferenceDetector<const T&>
{
    enum{
        isConstReference = true
    };
    typedef T NotConstReference;
};
//==============================================================================
}

#endif // <- INCLUDE_BIKES_TYPECOLLECTING_TYPEDETECTORS_H
