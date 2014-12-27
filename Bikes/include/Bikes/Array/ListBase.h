#ifndef INCLUDE_BIKES_ARRAY_LISTBASE_H
#define INCLUDE_BIKES_ARRAY_LISTBASE_H

#include <Bikes/Creation/CreationManager.h>
#include <vector>

namespace Bikes{
//------------------------------------------------------------------------------
template<class T> class ListConstIterator;
template<class T> class ListIterator;
template<class T, class CreationSupervisorT = SimpleCopyingSupervisor<T> > class List;
//------------------------------------------------------------------------------
template<class T>
class ListBase
{
public:
    typedef std::vector<T*> BaseContainer;
    typedef typename BaseContainer::iterator BaseIterator;
    typedef typename BaseContainer::const_iterator BaseConstIterator;

    typedef  T value_type;
    typedef  T* pointer;
    typedef const T* const_pointer;
    typedef T&  reference;
    typedef const T& const_reference;
    typedef typename BaseContainer::size_type size_type;
    typedef typename BaseContainer::difference_type difference_type;

    typedef ListConstIterator<T> const_iterator;
    typedef ListIterator<T> iterator;
protected:
    static typename const_iterator::BaseIterator const& getBaseIterator(const const_iterator& itr);
    static typename const_iterator::BaseIterator& getBaseIterator(const_iterator& itr);
};
//------------------------------------------------------------------------------
}
#endif // <- INCLUDE_BIKES_ARRAY_LISTBASE_H
