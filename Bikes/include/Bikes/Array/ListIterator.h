#ifndef INCLUDE_BIKES_ARRAY_LISTITERATOR_H
#define INCLUDE_BIKES_ARRAY_LISTITERATOR_H
#include <Bikes/Array/ListBase.h>

namespace Bikes{
//------------------------------------------------------------------------------
template<class T>
class ListConstIterator
{
public:

    typedef typename ListBase<T>::BaseContainer BaseContainer;
    typedef typename ListBase<T>::BaseConstIterator BaseIterator;

    typedef typename ListBase<T>::value_type value_type;
    typedef typename ListBase<T>::const_pointer pointer;
    typedef typename ListBase<T>::const_reference reference;
    typedef typename ListBase<T>::difference_type difference_type;

    typedef typename ListConstIterator<T> ThisType;

    ListConstIterator()
    {
    }

    ListConstIterator(const BaseIterator& baseIter) : _it(baseIter)
    {
    }

    reference operator*() const
    {
        return *(*_it);
    }

    pointer operator->() const
    {
        return *_it;
    }

    ThisType& operator++()
    {
        ++_it;
        return *this;
    }

    ThisType operator++(int)
    {
        ThisType tmp(*this);
        ++_it;
        return tmp;
    }

    ThisType& operator--()
    {
        --_it;
        return *this;
    }

    ThisType operator--(int)
    {
        ThisType tmp(*this);
        --_it;
        return tmp;
    }

    ThisType& operator += (difference_type di)
    {
        _it += di;
        return *this;
    }

    ThisType& operator -= (difference_type di)
    {
        _it -= di;
        return *this;
    }

    ThisType operator + (difference_type di) const
    {
        ThisType tmp(*this);
        return tmp += di;
    }

    ThisType operator - (difference_type di) const
    {
        ThisType tmp(*this);
        return tmp -= di;
    }

    difference_type operator - (const ThisType& itr) const
    {
        return _it - itr._it;
    }

    reference operator [] (difference_type di) const
    {
        return *_it[di];
    }

    bool operator == (const ThisType& right) const
    {
        return _it == right._it;
    }

    bool operator != (const ThisType& right) const
    {
        return !(*this == right);
    }

    bool operator > (const ThisType& right) const
    {
        return _it > right._it;
    }

    bool operator < (const ThisType& right) const
    {
        return _it < right._it;
    }

    bool operator >= (const ThisType& right) const
    {
        return _it >= right._it;
    }

    bool operator <= (const ThisType& right) const
    {
        return _it <= right._it;
    }

protected:
    BaseIterator _it;

    friend class ListBase<T>;
};
//------------------------------------------------------------------------------
template<class T>
typename ListBase<T>::const_iterator::BaseIterator const&
    ListBase<T>::getBaseIterator(
    const typename ListBase<T>::const_iterator& itr
    )
{
        return itr._it;
    }

template<class T>
typename ListBase<T>::const_iterator::BaseIterator&
    ListBase<T>::getBaseIterator(
    typename ListBase<T>::const_iterator& itr
    )
{
        return itr._it;
    }
//------------------------------------------------------------------------------
template<class T>
class ListIterator : public ListConstIterator<T>
{
public:

    typedef typename ListBase<T>::BaseContainer BaseContainer;
    typedef typename ListBase<T>::BaseConstIterator BaseIterator;

    typedef typename ListBase<T>::value_type value_type;
    typedef typename ListBase<T>::pointer pointer;
    typedef typename ListBase<T>::reference reference;
    typedef typename ListBase<T>::difference_type difference_type;

    typedef typename ListIterator<T> ThisType;

    ListIterator()
    {
    }

    ListIterator(const BaseIterator& baseIter) : _it(baseIter)
    {
    }

    reference operator [] (difference_type di) const
    {
        return *_it[di];
    }

    reference operator*() const
    {
        return *(*_it);
    }

    pointer operator->() const
    {
        return *_it;
    }

    ThisType& operator++()
    {
        ++_it;
        return *this;
    }

    ThisType operator++(int)
    {
        ThisType tmp(*this);
        ++_it;
        return tmp;
    }

    ThisType& operator--()
    {
        --_it;
        return *this;
    }

    ThisType operator--(int)
    {
        ThisType tmp(*this);
        --_it;
        return tmp;
    }

    ThisType& operator += (difference_type di)
    {
        _it += di;
        return *this;
    }

    ThisType& operator -= (difference_type di)
    {
        _it -= di;
        return *this;
    }

    ThisType operator + (difference_type di) const
    {
        ThisType tmp(*this);
        return tmp += di;
    }

    ThisType operator - (difference_type di) const
    {
        ThisType tmp(*this);
        return tmp -= di;
    }


    /*
    difference_type operator - (const ThisType& itr) const
    {
    return _it - itr._it;
    }
    //*/

    /*
    bool operator == (const ThisType& right) const
    {
    return _it == right._it;
    }

    bool operator != (const ThisType& right) const
    {
    return !(*this == right);
    }

    bool operator > (const ThisType& right) const
    {
    return _it > right._it;
    }

    bool operator < (const ThisType& right) const
    {
    return _it < right._it;
    }

    bool operator >= (const ThisType& right) const
    {
    return _it >= right._it;
    }

    bool operator <= (const ThisType& right) const
    {
    return _it <= right._it;
    }
    //    */
};
//------------------------------------------------------------------------------
}
#endif // <- INCLUDE_BIKES_ARRAY_LISTITERATOR_H
