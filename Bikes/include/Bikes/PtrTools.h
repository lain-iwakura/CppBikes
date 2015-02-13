#ifndef INCLUDE_BIKES_PTRTOOLS_H
#define INCLUDE_BIKES_PTRTOOLS_H

namespace Bikes
{

template<class T>
struct SmartPtr
{

    template<class OtherPtr> 
    static T* get(OtherPtr& p)
    {
        return &(*p);
    }

    static T* get(T* p)
    {
        return p;
    }

    template<class OtherPtr>
    static const T* get(const OtherPtr& p)
    {
        return &(*p);
    }

    static const T* get(const T* p)
    {
        return p;
    }

};

}

#endif // <- INCLUDE_BIKES_PTRTOOLS_H
