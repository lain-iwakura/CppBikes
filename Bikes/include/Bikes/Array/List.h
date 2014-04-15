#ifndef INCLUDE_BIKES_ARRAY_LIST_H
#define INCLUDE_BIKES_ARRAY_LIST_H

#include <Bikes/Types.h>
#include <Bikes/Abstract/Cloner.h>
#include <Bikes/Abstract/Creator.h>
#include <Bikes/Abstract/Deleter.h>

#include <vector>



namespace Bikes
{


	
template<
	class T, 
	class Cloner = SimpleCopier<T>, 
	class Creator = SimpleCreator<T>,
	class Deleter = SimpleDeleter<T>
	>
class List 
{
	std::vector<T*> _l;
public:

	const std::vector<T*>& data() const { return _l; }

	List()
	{
	}

	List(const List<T> & cnt) : _l(cnt.size(), T*(0))
	{
		sznum c = cnt.size();
		for (sznum i = 0; i < c; i++)
			_l[i] = Cloner::createCopy(cnt._l[i]);
	}

	~List()
	{
		sznum c = size();
		for (sznum i = 0; i < c; i++)
			Deleter::cleanup(_l[i]);
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

// 	vector::capacity(STL / CLR) // Reports the size of allocated storage for the container.
	sznum capacity() const
	{
		return _l.capacity();
	}

// 	vector::clear(STL / CLR) // Removes all elements.
	void clear()
	{
		sznum sz = _l.size();
		for (sznum i = 0; i < sz; i++) 
			Deleter::cleanup(_l[i]);
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
			Deleter::cleanup(_l[i]);
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
	void	insert(sznum i, const T & obj)
	{
		_l.insert(_l.begin() + i, Cloner::createCopy(&obj));
	}

//	vector::pop_back(STL / CLR) // Removes the last element.
	void pop_back()
	{
		Deleter::cleanup(_l.back());
		_l.pop_back();
	}

	void pop_front()
	{
		Deleter::cleanup(_l.front());
		_l.erase(_l.begin());
	}


//	vector::push_back(STL / CLR) // Adds a new last element.
	void push_back(const T& obj)
	{
		_l.push_back(Cloner::createCopy(&obj));
	}

	void push_back(const List<T> & objs)
	{		
		rnum sz1 = _l.size();
		rnum sz2 = objs._l.size();
		_l.resize(sz1 + sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[sz1 + i] = Cloner::createCopy(objs._l[i]);
	}

	void push_front(const T & obj)
	{
		_l.insert(_l.begin(), Cloner::createCopy(&obj));
	}

	void push_front(const List<T> & objs)
	{
		rnum sz1 = _l.size();
		rnum sz2 = objs._l.size();	
		_l.insert(_l.begin(),sz2,T*(0))
		for (sznum i = 0; i < sz2; i++)		
			_l[i] = Cloner::createCopy(objs._l[i]);	
	}

//	vector::rbegin(STL / CLR) //Designates the beginning of the reversed controlled sequence.
//	x

//	vector::rend(STL / CLR) // Designates the end of the reversed controlled sequence.
//	x

//	vector::reserve(STL / CLR) // Ensures a minimum growth capacity for the container.
	void reserve(sznum cpct)
	{
		_l.reserve(cpct);
	}

//	vector::resize(STL / CLR) // Changes the number of elements.
	void resize(sznum sz, const T& def)
	{
		sznum csz = size();
		for (sznum i = sz; i < csz; i++)
			Deleter::cleanup(_l[i]);
		_l.resize(sz);
		for (sznum i = csz; i < sz; i++)
			_l[i] = Cloner::createCopy(def);
	}

	void resize(sznum sz)
	{
		sznum csz = size();
		for (sznum i = sz; i < csz; i++)
			Deleter::cleanup(_l[i]);
		_l.resize(sz);
		for (sznum i = csz; i < sz; i++)
			_l[i] = Creator::create();
	}

//	vector::size(STL / CLR) // Counts the number of elements.
	sznum size() const
	{
		return _l.size();
	}

// 	vector::swap(STL / CLR) // Swaps the contents of two containers.
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

		void	append(const List<T> & objs)
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

		const T &	first() const
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
				
		bool	isEmpty() const
		{
			return _l.empty();
		}

		T &	last()
		{
			return *_l.back()
		}

		const T &	last() const
		{
			return *_l.back();
		}

// 		int	lastIndexOf(const T & value, int from = -1) const

//		int	length() const	

// 		QList<T>	mid(int pos, int length = -1) const
// 		void	move(int from, int to)

		void	prepend(const T & obj)
		{
			push_front(obj);
		}



		sznum	removeAll(const T & obj)
		{
			sznum sz = _l.size();
			sznum c = 0;
			for (sznum i = 0; i < sz; i++)
			{
				if (*_l[i] == obj)
				{
					Deleter::cleanup(_l[i]);
					_l.erase(_l.begin() + i);
					i--;
					sz--;
					c++;
				}
			}
			return c;
		}

		void	removeAt(sznum i)
		{
			erase(i);
		}

		void	removeFirst()
		{
			pop_front();
		}

		void	removeLast()
		{
			pop_back();
		}

		bool	removeOne(const T & obj)
		{
			sznum sz = _l.size();
			for (sznum i = 0; i < sz; i++)
			{
				if (_l[i] == obj)
				{
					Deleter::cleanup(_l[i]);
					_l.erase(_l.begin() + i);
					return true;
				}
			}
			return false;
		}

		void	replace(sznum i, const T & obj)
		{
			Deleter::cleanup(_l[i]);
			_l[i] = Cloner::createCopy(&obj);
		}

// 		bool	startsWith(const T & value) const
		void	swap(sznum i, sznum j)
		{
			const T * buf = _l[i];
			_l[i] = _l[j];
			_l[j] = buf;
		}

// 		T	takeAt(int i)
		T* passAt(sznum i) // unsafe
		{
			T* buf = _l[i];
			_l.erase(_l.begin() + i);
			return buf;
		}

// 		T	takeFirst()
		T* passFirst() // unsafe
		{
			T* buf = _l.front();
			_l.erase(_l.begin());
			return buf;
		}

// 		T	takeLast()
		T* passLast() // unsafe
		{
			T* buf = _l.back();
			_l.erase(_l.begin());
			return buf;
		}

// 		std::list<T>	toStdList() const
// 		QVector<T>	toVector() const

		std::vector<T> toStdVector()
		{
			std::vector<T> r;
			sznum sz = _l.size();			
			r.reserve(sz);
			for (sznum i = 0; i < sz; i++)
				r.push_back(*_l[i]);
			return r;
		}

		void fromStdVector(const std::vector<T>& objs)
		{
			sznum sz1 = _l.size();
			sznum sz2 = objs.size();
			for (sznum i = 0; i < sz1; i++)
				Deleter::cleanup(_l[i]);
			_l.resize(sz2);
			for (sznum i = 0; i < sz2; i++)
				_l[i] = Cloner::createCopy(&objs[i]);
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
			Deleter::cleanup(_l[i]);
		_l.resize(sz2);
		for (sznum i = 0; i < sz2; i++)
			_l[i] = Cloner::createCopy(objs._l[i]);
		return *this;
	}

//..............................................................................
		
	const List<T> & operator = (const List<T> & other ) 
	{
		clear();
		append(other);
		return *this;
	}

	T& increase(sznum di)
	{
		for(sznum i=0; i<di; i++) _l.push_back(new T());
		return last();
	}

	T& increase()
	{
		_l.push_back(new T());
		return last();
	}

	T& operator ++ () 
	{
		_l.push_back(new T());
		return last();
	}
	
	void operator += (const List<T> & other ){append(other);}
	void operator += (const T & obj ){_l.push_back(new T(obj));}
	void add(const T &obj){_l.push_back(new T(obj));}
	void append ( const T & obj ) {_l.push_back(new T(obj)); /*cnt++;*/}
	void append (const List<T> & other )
	{
		sznum c=other.size();
		for(sznum i=0; i<c; i++) push_back(other[i]);
	}


	
	const T & first () const { return (*this)[0];}
	T & first (){ return (*this)[0]; }
	
	const T & last () const { return (*this)[size()-1]; }
	T & last () { return (*this)[size()-1]; }
	
	const T & afterFirst () const { return (*this)[1];}
	T & afterFirst (){ return (*this)[1]; }

	const T & beforeLast () const { return (*this)[size()-2]; }
	T & beforeLast () { return (*this)[size()-2]; }

	const T& operator[](int i) const { return *(_l[i]);}	
	T& operator[](int i) { return *(_l[i]); }

	T& take(T *pItm)
	{
		_l.push_back(pItm);	
		return *pItm;
	}

	T& take(T *pItm,sznum i)
	{
		_l.insert(_l.begin()+i,pItm);
		return *pItm;
	}

	void take(List<T>& l)
	{		
		sznum c=l.size();
		for(sznum i=0; i<c; i++)_l.push_back(l._l[i]);
		l._l.clear();
	}

	T*	pass(sznum i)
	{
	//	if(i>=size()||i<0)  return 0;
		T* r=_l[i];
		_l.erase(_l.begin()+i);
		return r;
	}

	T* passLast()
	{
		sznum i=_l.size()-1;
		T* r=_l[i];
		_l.erase(_l.begin()+i);
		return r;
	}

	T* passFirst()
	{
		T* r=_l[0];
		_l.erase(_l.begin());
		return r;
	}


	void removeAt(sznum i)
	{
		if(i<size())
		{
			delete _l[i];
			_l.erase(_l.begin()+i);
		}
	}

	void remove_i1i2(sznum i1,sznum i2)
	{
        if(i1<size()&&i2<size()&&i2>=i1)
		{
			for(int i=i1; i<=i2; i++) delete _l[i];
			_l.erase(_l.begin()+i1,_l.begin()+i2);
		}
	}

	bool remove(const T &r)
	{
		sznum c=size();
		for(sznum i=0; i<c; i++) if((*this)[i]==r){ removeAt(i); return true;}
		return false;
	}
	bool removeThat(T *r)
	{
		sznum c=size();
		for(sznum i=0; i<c; i++) if(_l[i]==r)
		{
			removeAt(i);
			return true;
		}
		return false;
	}
	void removeLast(){if(size()>0) removeAt(size()-1);}
	void removeFirst(){if(size()>0) removeAt(0);}

	void insert(sznum i,const T &o)
	{
		if(i<0) i=0;
		else if(i>size()) i=size();
		_l.insert(_l.begin()+i,new T(o));
	}

	bool contains(const T& itm) const
	{
		sznum c=size();
		for(sznum i=0; i<c; i++) if((*this)[i]==itm){ return true;}
		return false;
	}

	int find(const T &itm) const
	{
		sznum c=size();
		for(sznum i=0; i<c; i++) if(*(_l[i])==itm) return i;
		return -1;
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

};

}
#endif // <- INCLUDE_BIKES_ARRAY_LIST_H
