#ifndef INCLUDE_BIKES_ARRAY_LIST_H
#define INCLUDE_BIKES_ARRAY_LIST_H

#include <Bikes/Types.h>
#include <Bikes/Creation/CreationSupervisor.h>

#include <vector>
#include <algorithm>

namespace Bikes
{

template<class TList>
class ListConstIterator
{
public:

	typedef typename TList::BaseContainer::iterator BaseIterator;
	typedef typename TList::BaseContainer::const_iterator BaseConstIterator;

	typedef typename TList::value_type value_type;
	typedef const value_type* pointer;
	typedef const value_type& reference;

	ListConstIterator()
	{
	}

	const BaseConstIterator& data() const /*no const?*/
	{
		return _it;
	}

	reference operator*() const
	{
		return **_it;
	}

	pointer operator->() const
	{
		return *_it;
	}

	ListConstIterator<TList>& operator++()
	{
		_it++;
		return *this;
	}

protected:
	BaseIterator _it;
};

template<class TList>
class ListIterator: public ListConstIterator<TList>
{
public:

	typedef typename TList::value_type value_type;
	typedef value_type* pointer;
	typedef value_type& reference;

	reference operator*() 
	{
		return **_it;
	}

	pointer operator->() 
	{
		return *_it;
	}
};

	
// template<
// 	class T, 
// 	class TCloner = SimpleCopier<T>, 
// 	class TCreator = SimpleCreator<T>,
// 	class TDeleter = SimpleDeleter<T>
// 	>
template<
	class T,
	class TCreationSupervisor = SimpleCopyingSupervisor<T>
	>
class List:
{
	std::vector<T*> _l;
public:

	typedef std::vector<T*> BaseContainer;

	typedef TCreationSupervisor CreationSupervisor;

	typedef T value_type;
	typedef sznum size_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;



	const BaseContainer& data() /*no const*/
	{
		return _l; 
	}

	List()
	{
	}

	List(const List<T> & objs) : _l(objs._l.size())
	{
		sznum sz = objs.size();
		for (sznum i = 0; i < sz; i++)
			_l[i] = _createCopy(objs._l[i]);
	}

	template<class ArrayT>
	List(const ArrayT& objs) :_l(objs.size())
	{
		sznum sz = objs.size();
		for (sznum i = 0; i < sz; i++)
			_l[i] = _createCopy(&objs[i]);
	}

	~List()
	{
		sznum c = size();
		for (sznum i = 0; i < c; i++)
			_destroy(_l[i]);
	}

//..............................................................................
// std::vector interface ->

//	vector::assign(STL / CLR) // Replaces all elements.
//	x

// 	vector::at(STL / CLR) // Accesses an element at a specified position.
	T& at(sznum i)
	{
		return *_l.at(i);
	}
	const T & at(sznum i) const
	{
		return *_l.at(i);
	}

// 	vector::back(STL / CLR) // Accesses the last element.
	T& back()
	{
		return *_l.back();
	}
	const T& back() const
	{
		return *_l.back();
	}

// 	vector::begin(STL / CLR) // Designates the beginning of the controlled sequence.
//	x

// 	vector::capacity(STL / CLR) // Reports the size of allocated storage for the Container.
	sznum capacity() const
	{
		return _l.capacity();
	}

// 	vector::clear(STL / CLR) // Removes all elements.
	void clear()
	{
		sznum sz = _l.size();
		for (sznum i = 0; i < sz; i++) 
			_destroy(_l[i]);
		_l.clear();
	}

// 	vector::empty(STL / CLR) // Tests whether no elements are present.
	bool empty() const
	{
		return empty();
	}

// 	vector::end(STL / CLR) // Designates the end of the controlled sequence.
//	x

// 	vector::erase(STL / CLR) // Removes elements at specified positions.
	void erase(sznum i)
	{
		Deleter::cleanup(_l[i]);
		_l.erase(_l.begin() + i);
	}

	void erase(sznum iFirst, sznum iLast)
	{
		for (sznum i = iFirst; i < iLast; i++)				
			_destroy(_l[i]);
		_l.erase(_l.begin()+iFirst,_l.begin()+iLast);
	}

//	vector::front(STL / CLR) // Accesses the first element.
	T& front()
	{
		return *_l.front();
	}
	const T& front() const
	{
		return *_l.front();
	}

//  vector::insert(STL / CLR) // Adds elements at a specified position.	
	void	insert(sznum iWhere, const T & obj)
	{
		_l.insert(_l.begin() + iWhere, _createCopy(&obj));
	}

	void insert(sznum iWhere, const List<T>& objs)
	{
		rnum sz1 = _l.size();
		rnum sz2 = objs._l.size();
		_l.insert(_l.begin() + iWhere, sz2, T*(0))
		for (sznum i = 0; i < sz2; i++)
			_l[iWhere + i] = _createCopy(objs._l[i]);
	}
	
	template<class ArrayT>
	void insert(sznum iWhere, const ArrayT& objs)
	{
		rnum sz1 = _l.size();
		rnum sz2 = objs.size();
		_l.insert(_l.begin() + iWhere, sz2, T*(0))
		for (sznum i = 0; i < sz2; i++)
			_l[iWhere + i] = _createCopy(&objs[i]);
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
	void push_back(const T& obj)
	{
		_l.push_back(_createCopy(&obj));
	}

	void push_back(const List<T> & objs)
	{		
		rnum sz1 = _l.size();
		rnum sz2 = objs._l.size();
		_l.resize(sz1 + sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[sz1 + i] = _createCopy(objs._l[i]);
	}

	template<class ArrayT>
	void push_back_array(const ArrayT& objs)
	{
		rnum sz1 = _l.size();
		rnum sz2 = objs.size();
		_l.resize(sz1 + sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[sz1 + i] = _createCopy(&objs[i]);
	}

	void push_front(const T& obj)
	{
		_l.insert(_l.begin(), _createCopy(&obj));
	}

	void push_front(const List<T>& objs)
	{
		rnum sz1 = _l.size();
		rnum sz2 = objs._l.size();	
		_l.insert(_l.begin(),sz2,T*(0))
		for (sznum i = 0; i < sz2; i++)		
			_l[i] = _createCopy(objs._l[i]);	
	}

	template<class ArrayT>
	void push_front_array(const ArrayT& objs)
	{
		rnum sz1 = _l.size();
		rnum sz2 = objs.size();
		_l.insert(_l.begin(), sz2, T*(0))
		for (sznum i = 0; i < sz2; i++)
			_l[i] = _createCopy(&objs[i]);
	}

//	vector::rbegin(STL / CLR) //Designates the beginning of the reversed controlled sequence.
//	x

//	vector::rend(STL / CLR) // Designates the end of the reversed controlled sequence.
//	x

//	vector::reserve(STL / CLR) // Ensures a minimum growth capacity for the Container.
	void reserve(sznum cpct)
	{
		_l.reserve(cpct);
	}

//	vector::resize(STL / CLR) // Changes the number of elements.
	void resize(sznum sz, const T& def)
	{
		sznum csz = size();
		for (sznum i = sz; i < csz; i++)
			_destroy(_l[i]);
		_l.resize(sz);
		for (sznum i = csz; i < sz; i++)
			_l[i] = _createCopy(def);
	}

	void resize(sznum sz)
	{
		sznum csz = size();
		for (sznum i = sz; i < csz; i++)
			_destroy(_l[i]);
		_l.resize(sz);
		for (sznum i = csz; i < sz; i++)
			_l[i] = _create();
	}

//	vector::size(STL / CLR) // Counts the number of elements.
	sznum size() const
	{
		return _l.size();
	}

// 	vector::swap(STL / CLR) // Swaps the contents of two Containers.
	void swap(List<T>& other)
	{
		_l.swap(other._l);
	}


// 	vector::to_array(STL / CLR) // Copies the controlled sequence to a new array.
//	x


// <- std::vector interface	

	
//..............................................................................

// QList interface ->

		void	append(const T & obj)
		{
			push_back(obj);
		}

		template<class ArrayT>
		void	appendArray(const ArrayT & objs)
		{
			push_back_array(objs);			
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
		
		num	count(const T & obj) const
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

		num	count() const
		{
			return num(_l.size());
		}


// 		bool	endsWith(const T & value) const


		T &	first()
		{
			return *_l.front();
		}

		const T & first() const
		{
			return *_l.front();
		}

		num	indexOf(const T & obj, sznum from = 0) const
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

//		int	length() const	

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

	List<T>& operator += (const T& obj)
	{
		push_back(obj);
		return *this;
	}
		
	List<T>& operator = (const List<T>& objs)
	{
		sznum sz1 = _l.size();
		sznum sz2 = objs._l.size();
		for (sznum i = 0; i < sz1; i++)
			_destroy(_l[i]);
		_l.resize(sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[i] = _createCopy(objs._l[i]);
		return *this;
	}

	template<class ArrayT>
	List<T>& operator = (const ArrayT& objs)
	{
		fromArray(objs);
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

	void take_back(List<T>& objs)
	{		
		sznum sz1 = _l.size();
		sznum sz2 = objs._l.size();
		_l.resize(sz1 + sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[sz1 + i] = objs._l[i];
		objs._l.clear();
	}

	void take_front(T* obj)
	{
		_l.insert(_l.begin(), obj);
	}

	void take_front(List<T>& objs)
	{		
		sznum sz2 = objs._l.size();
		_l.insert(_l.begin(), sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[i] = objs._l[i];
		objs._l.clear();
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
		sznum sz = _l.size();
		r.reserve(sz);
		for (sznum i = 0; i < sz; i++)
			r.push_back(*_l[i]);
		return r;
	}

	template<class ArrayT>
	void from_array(const ArrayT& objs)
	{
		sznum sz1 = _l.size();
		sznum sz2 = objs.size();
		for (sznum i = 0; i < sz1; i++)
			_destroy(_l[i]);
		_l.resize(sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[i] = _createCopy(&objs[i]);
	}
		
	T& increase()
	{
		_l.push_back(_create());
		return *_l.back();
	}

	T& operator ++ () 
	{		
		return increase();
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
