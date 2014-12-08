#ifndef INCLUDE_BIKES_ARRAY_LIST_H
#define INCLUDE_BIKES_ARRAY_LIST_H

#include <Bikes/Array/ListIterator.h>

namespace Bikes{
//------------------------------------------------------------------------------
template<
	class T,
	class CreationSupervisorT 
	>
class List: public ListBase<T> 
{
public:
   
    typedef ListBase<T> Base;
    typedef typename Base::value_type value_type;
    typedef typename Base::size_type size_type;
    typedef typename Base::difference_type difference_type;
    typedef typename Base::pointer pointer;
    typedef typename Base::const_pointer const_pointer;
    typedef typename Base::reference reference;
    typedef typename Base::const_reference const_reference;

    typedef typename Base::const_iterator const_iterator;
    typedef typename Base::iterator iterator;

    typedef typename Base::BaseContainer BaseContainer;
    typedef typename Base::BaseConstIterator BaseConstIterator;
    typedef typename Base::BaseIterator BaseIterator;
    typedef List<T, CreationSupervisorT> ThisType;
    typedef CreationSupervisorT CreationSupervisor;

	List()
	{
	}

    template<class OtherCreationSupervisorT>
    List(const List<T, OtherCreationSupervisorT>& other) : _l(other._l.size())
    {
        BaseIterator i = _l.begin();
        BaseConstIterator j = other._l.begin();
        const BaseIterator& iEnd = _l.end();
        for (; i != iEnd ; ++i, ++j)
            *i = _createCopy(*j);
	}

	template<class ArrayT>
    List(const ArrayT& arr) :_l(arr.size())
	{
		sznum sz = objs.size();
		for (sznum i = 0; i < sz; ++i)
            _l[i] = _createCopy(&arr[i]);
	}

    template<class RawArrayT>
    List(const RawArrayT& arr, sznum arrSize) :_l(arrSize)
    {
        for (sznum i = 0; i < arrSize; ++i)
            _l[i] = _createCopy(&arr[i]);
    }

	~List()
	{
        BaseConstIterator i = _l.begin();
        const BaseConstIterator& iEnd = _l.end();
        for (; i != iEnd; ++i)
            _destroy(*i);
	}

//..............................................................................
// std::vector interface ->

//	vector::assign(STL / CLR) // Replaces all elements.
//	x

// 	vector::at(STL / CLR) // Accesses an element at a specified position.
	reference at(size_type i)
	{
		return *_l.at(i);
	}

	const_reference at(size_type i) const
	{
		return *_l.at(i);
	}

// 	vector::back(STL / CLR) // Accesses the last element.
	reference back()
	{
		return *_l.back();
	}

    const_reference back() const
	{
		return *_l.back();
	}

// 	vector::begin(STL / CLR) // Designates the beginning of the controlled sequence.
    iterator begin()
    {
        return iterator(_l.begin());
    }

    const_iterator begin() const
    {
        return const_iterator(_l.begin());
    }

// 	vector::capacity(STL / CLR) // Reports the size of allocated storage for the Container.
	size_type capacity() const
	{
		return _l.capacity();
	}

// 	vector::clear(STL / CLR) // Removes all elements.
	void clear()
	{
        BaseConstIterator i = _l.begin();
        const BaseConstIterator& iEnd = _l.end();
        for (; i != iEnd; ++i)
            _destroy(*i);
        _l.clear();
	}

// 	vector::empty(STL / CLR) // Tests whether no elements are present.
	bool empty() const
	{
		return _l.empty();
	}

// 	vector::end(STL / CLR) // Designates the end of the controlled sequence.
    iterator end()
    {
        return iterator(_l.end());
    }

    const_iterator end() const
    {
        return const_iterator(_l.end());
    }

// 	vector::erase(STL / CLR) // Removes elements at specified positions.
    iterator erase(const_iterator whereItr)
    {
        const const_iterator::BaseIterator& bi = Base::getBaseIterator(whereItr)
        _destroy(*bi);
        return iterator(_l.erase(bi));
    }

	void erase(size_type i)
	{
        const BaseConstIterator& itr = _l.begin() + i;
        _destroy(*itr);
		_l.erase(itr);
	}

    iterator erase(const_iterator itrFirst, const_iterator itrLast)
    {
        const_iterator::BaseIterator i = Base::getBaseIterator(itrFirst);
        const const_iterator::BaseIterator& iEnd = Base::getBaseIterator(itrLast)
        for (; i != iEnd; ++i)
            _destroy(*i);
        return _l.erase(Base::getBaseIterator(itrFirst), iEnd);
    }

    void erase(size_type iFirst, size_type iLast)
	{
		for (sznum i = iFirst; i < iLast; ++i)				
			_destroy(_l[i]);
		_l.erase(_l.begin()+iFirst,_l.begin()+iLast);
	}

//	vector::front(STL / CLR) // Accesses the first element.
	reference front()
	{
		return *_l.front();
	}

	const_reference front() const
	{
		return *_l.front();
	}

//  vector::insert(STL / CLR) // Adds elements at a specified position.	
    void insert(const_iterator iWhere, const_reference obj)
    {
        _l.insert(Base::getBaseIterator(iWhere), _createCopy(&obj));
    }

	void insert(size_type iWhere, const_reference obj)
	{
		_l.insert(_l.begin() + iWhere, _createCopy(&obj));
	}

    template<class OtherCreationSupervisorT>
    void insert(const const_iterator& iWhere, const List<T, OtherCreationSupervisorT>& arr)
	{
        const_iterator::BaseIterator i = Base::getBaseIterator(iWhere);
        i = _l.insert(i, arr.size(), pointer(0));
        const const_iterator::BaseIterator& jEnd = arr._l.end();
        const_iterator::BaseIterator j = arr._l.begin();
        for (; j != jEnd; ++i, ++j)
            *i = _createCopy(*j);
	}
	
	template<class ArrayT>
	void insert(size_type iWhere, const ArrayT& arr)
	{
		size_type sz1 = _l.size();
		sznum sz2 = arr.size();
		_l.insert(_l.begin() + iWhere, sz2, pointer(0))
		for (sznum i = 0; i < sz2; ++i)
			_l[iWhere + i] = _createCopy(&arr[i]);
	}

//	vector::pop_back(STL / CLR) // Removes the last element.
	void pop_back()
	{
		_destroy(_l.back());
		_l.pop_back();
	}

	void pop_front()
	{
		_destroy(_l.front());
		_l.erase(_l.begin());
	}


//	vector::push_back(STL / CLR) // Adds a new last element.	
	void push_back(const_reference obj)
	{
		_l.push_back(_createCopy(&obj));
	}

    template<class ArrayT>
	void push_back(const ArrayT& arr)
	{		
        sznum sz1 = _l.size();
		sznum sz2 = arr.size();
		_l.resize(sz1 + sz2);

        for (sznum i = 0; i < sz2; ++i)
			_l[sz1 + i] = _createCopy(arr[i]);
	}

	void push_front(const_reference obj)
	{
		_l.insert(_l.begin(), _createCopy(&obj));
	}

	template<class ArrayT>
	void push_front(const ArrayT& arr)
	{
        sznum sz2 = arr.size();
		_l.insert(_l.begin(), sz2, pointer(0))
		for (sznum i = 0; i < sz2; ++i)
            _l[i] = _createCopy(&arr[i]);
	}

//	vector::rbegin(STL / CLR) //Designates the beginning of the reversed controlled sequence.
//	x

//	vector::rend(STL / CLR) // Designates the end of the reversed controlled sequence.
//	x

//	vector::reserve(STL / CLR) // Ensures a minimum growth capacity for the Container.
	void reserve(size_type cpct)
	{
		_l.reserve(cpct);
	}

//	vector::resize(STL / CLR) // Changes the number of elements.
	void resize(size_type sz, const_reference def)
	{
		size_type csz = _l.size();
		for (size_type i = sz; i < csz; ++i)
			_destroy(_l[i]);
		_l.resize(sz);
		for (size_type i = csz; i < sz; ++i)
			_l[i] = _createCopy(def);
	}

	void resize(size_type sz)
	{
		size_type csz = size();
		for (size_type i = sz; i < csz; ++i)
			_destroy(_l[i]);
		_l.resize(sz);
		for (size_type i = csz; i < sz; ++i)
			_l[i] = _create();
	}

//	vector::size(STL / CLR) // Counts the number of elements.
	size_type size() const
	{
		return _l.size();
	}

// 	vector::swap(STL / CLR) // Swaps the contents of two Containers.
	void swap(ThisType& other)
	{
		_l.swap(other._l);
	}


// <- std::vector interface	

	
//..............................................................................

// QList interface ->

		void append(const T & obj)
		{
			push_back(obj);
		}

		template<class ArrayT>
		void append(const ArrayT & objs)
		{
			push_back(objs);			
		}

// 		iterator	begin()
// 		const_iterator	begin() const
// 		const_iterator	cbegin() const
// 		const_iterator	cend() const
// 		const_iterator	constBegin() const
// 		const_iterator	constEnd() const
// 		iterator	end()
// 		const_iterator	end() const
// 		iterator	erase(iterator pos)
// 		iterator	erase(iterator begin, iterator end)
		
		bool contains(const T & obj) const
		{
			sznum s = _l.size();
			for (sznum i = 0; i < s; i++)
			{
				if (*_l[i] == obj)
					return true;
			}
			return false;
		}
		
		lnum count(const T & obj) const
		{
			sznum s = _l.size();
			int c = 0;
			for (sznum i = 0; i < s; i++)
			{
				if (*_l[i] == obj)
					c++;
			}
			return c;
		}

		lnum count() const
		{
			return lnum(_l.size());
		}


// 		bool	endsWith(const T & value) const


		T& first()
		{
			return *_l.front();
		}

		const T& first() const
		{
			return *_l.front();
		}

		lnum indexOf(const T & obj, sznum from = 0) const
		{
			sznum sz = _l.size();
			for (sznum i = from; i < sz; i++)
			{
				if (_l[i] == obj)
					return i;
			}
			return -1;
		}
				
		bool isEmpty() const
		{
			return _l.empty();
		}

		T &	last()
		{
			return *_l.back()
		}

		const T & last() const
		{
			return *_l.back();
		}

// 		int	lastIndexOf(const T & value, int from = -1) const

        lnum length() const
        {
            return count();
        }

// 		QList<T>	mid(int pos, int length = -1) const
// 		void	move(int from, int to)

		void prepend(const T & obj)
		{
			push_front(obj);
		}


		void prependArray(const T & obj)
		{
			push_front_array(obj);
		}


		sznum removeAll(const T & obj)
		{
			sznum sz = _l.size();
			sznum c = 0;
			for (sznum i = 0; i < sz; i++)
			{
				if (*_l[i] == obj)
				{
					_destroy(_l[i]);
					_l.erase(_l.begin() + i);
					i--;
					sz--;
					c++;
				}
			}
			return c;
		}

		void removeAt(sznum i)
		{
			erase(i);
		}

		void removeFirst()
		{
			pop_front();
		}

		void removeLast()
		{
			pop_back();
		}

		bool removeOne(const T & obj)
		{
			sznum sz = _l.size();
			for (sznum i = 0; i < sz; i++)
			{
				if (_l[i] == obj)
				{
					_destroy(_l[i]);
					_l.erase(_l.begin() + i);
					return true;
				}
			}
			return false;
		}

		void replace(sznum i, const T & obj)
		{
			_destroy(_l[i]);
			_l[i] = _createCopy(&obj);
		}

// 		bool	startsWith(const T & value) const
		void swap(sznum i, sznum j)
		{
			const T * buf = _l[i];
			_l[i] = _l[j];
			_l[j] = buf;
		}

// 		T	value(int i) const
// 		T	value(int i, const T & defaultValue) const

// <- QList interface
	
//..............................................................................

	T& operator [] (sznum i)
	{
		return *_l[i];
	}

	const T& operator [] (sznum i) const
	{
		return *_l[i];
	}

	ThisType& operator += (const T& obj)
	{
		push_back(obj);
		return *this;
	}
		
    template<class ArrayT>
	ThisType& operator += (const ArrayT& arr)
	{
        push_back(arr);
		return *this;
	}

	template<class ArrayT>
	ThisType& operator = (const ArrayT& objs)
	{
		from_array(objs);
		return *this;
	}

//..............................................................................


	T* pass(sznum i) // unsafe
	{
		T* buf = _l[i];
		_l.erase(_l.begin() + i);
		return buf;
	}

	T* pass_back() // unsafe
	{
		T* buf = _l.back();
		_l.pop_back();
		return buf;
	}

	T* pass_front() //unsafe
	{
		T* buf = _l.front();
		_l.erase(_l.begin());
		return buf;
	}

	T* pass() // unsafe
	{
		return pass_back();
	}

	void take_back(T* obj)
	{
        _l.push_back(obj);
	}


	void take_back(ThisType& arr)
	{		
		sznum sz1 = _l.size();
        sznum sz2 = arr._l.size();
		_l.resize(sz1 + sz2);
		for (sznum i = 0; i < sz2; i++)
            _l[sz1 + i] = arr._l[i];
        arr._l.clear();
	}

	void take_front(T* obj)
	{
		_l.insert(_l.begin(), obj);
	}

	void take_front(ThisType& arr)
	{		
        sznum sz2 = arr._l.size();
		_l.insert(_l.begin(), sz2, pointer(0));
		for (sznum i = 0; i < sz2; i++)
			_l[i] = arr._l[i];
		arr._l.clear();
	}

	void take(T* obj, sznum i)
	{
		_l.insert(_l.begin()+i,obj);
	}

	void take(T* obj)
	{
		take_back(obj);
	}
	

	// 		std::list<T>	toStdList() const
	// 		QVector<T>	toVector() const

	std::vector<T> to_std_vector()
	{
		std::vector<T> r;
        to_std_vector(r);
		return r;
	}

    void to_std_vector(std::vector<T>& v)
    {
        sznum sz = _l.size();
        v.reserve(sz);
        for (sznum i = 0; i < sz; i++)
            v.push_back(*_l[i]);
    }

	template<class ArrayT>
	void from_array(const ArrayT& arr)
	{
		sznum sz1 = _l.size();
        sznum sz2 = arr.size();
		for (sznum i = 0; i < sz1; i++)
			_destroy(_l[i]);
		_l.resize(sz2);
		for (sznum i = 0; i < sz2; i++)
            _l[i] = _createCopy(&arr[i]);
	}
		
	T& increase()
	{
		_l.push_back(_create());
		return *_l.back();
	}

	ThisType& operator ++() 
	{		
        _l.push_back(_create());
		return *this;
	}

	const T & beforeLast () const 
	{
		return *_l[_l.size()-2]; 
	}

	T & beforeLast () 
	{ 
		return *_l[_l.size()-2]; 
	}

	void invert()
	{		
		sznum c_ = _l.size() - 1;
		sznum c2 = _l.size() / 2;
		T *buf;
		for(sznum i=0; i<c2; i++)
		{
			buf=_l[i];
			_l[i]=_l[c_-i];
			_l[c_-i]=buf;
		}
	}

    const BaseContainer& data() /* not const (!) */
    {
        return _l;
    }

private:

	BaseContainer _l;

	static T* _createCopy(const T* obj)
	{
		//return Cloner::createCopy(obj);
		return CreationSupervisor::createCopy(obj);
	}

	static T* _create()
	{
		//return Creator::create();
		return CreationSupervisor::create();
	}

	static void _destroy(T* obj)
	{
		//Deleter::destroy(obj);
		return CreationSupervisor::destroy(obj);
	}

};
}
#endif // <- INCLUDE_BIKES_ARRAY_LIST_H