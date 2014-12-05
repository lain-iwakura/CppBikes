#ifndef INCLUDE_BIKES_ARRAY_LISTINNER_H
#define INCLUDE_BIKES_ARRAY_LISTINNER_H

namespace Bikes{
//------------------------------------------------------------------------------
namespace Inner{
//------------------------------------------------------------------------------
template<class IterTypes>
class ListIteratorPattern
{
public:

    typedef typename IterTypes::BaseContainer BaseContainer;
    typedef typename IterTypes::BaseIterator BaseIterator;

    typedef typename IterTypes::value_type value_type;
    typedef typename IterTypes::pointer pointer;
    typedef typename IterTypes::reference reference;
    typedef typename IterTypes::difference_type difference_type;

    typedef typename ListIteratorPattern<IterTypes> ThisType;

    ListIteratorPattern()
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

    difference_type operator - (const ThisType& itr)
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

    const BaseIterator& data() const /*no const?*/
    {
        return _it;
    }
private:
    BaseIterator _it;
};
//------------------------------------------------------------------------------
} // Inner
//------------------------------------------------------------------------------
} // Bikes
#endif // <- INCLUDE_BIKES_ARRAY_LISTINNER_H
