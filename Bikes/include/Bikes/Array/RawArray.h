#ifndef PREBIKES_RAWARRAY_H
#define PREBIKES_RAWARRAY_H
#include <Bikes/Types.h>
#include <Bikes/Mathem/Tools.h>
#include <Bikes/Creation/CreationManager.h>
#include <vector>

namespace Bikes
{

namespace Inner{

const unum defMaxMemoryIncrement = 64*1024;

template<typename T>
const unum defMaxCapacityIncrement()
{
	static const unum inc = noLess<unum>(defMaxMemoryIncrement / sizeof(T), 1);
	return inc;
}

}

template<
	class T,
	class CreationSupervisorT = SimpleCopyingSupervisor<T>
	>
class RawArray
{
public:

    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef const T* const_pointer;
    typedef const T& const_reference;
    typedef sznum size_type;
    typedef lnum difference_type;
    typedef pointer iterator;
    typedef const_pointer const_iterator;

	typedef CreationSupervisorT CreationSupervisor;
    typedef RawArray<T, CreationSupervisorT> ThisType;
	
	RawArray() :
		_arr(0), 
		_cap(0), 
		_sz(0), 
		_maxInc(Inner::defMaxCapacityIncrement<T>())
	{
	}

	RawArray(sznum sz):
		_arr(0),
		_cap(sz),
		_sz(sz),
		_maxInc(Inner::defMaxCapacityIncrement<T>())
	{
		if(sz>0)
			_arr = _createArray(sz);
	}

	RawArray(sznum sz, sznum cap):
		_arr(_createArray(cap)),
		_cap(cap),
		_sz(noGreater<sznum>(sz,cap)),
		_maxInc(Inner::defMaxCapacityIncrement<T>())
	{
	}

	RawArray(sznum sz, sznum cap, sznum maxCapInc) :
		_arr(_createArray(cap)),
		_cap(cap),
		_sz(noGreater<sznum>(sz, cap)),
		_maxInc(maxCapInc)
	{
	}

    RawArray(const ThisType& ra) :
		_arr(_createArrayCopy(ra._arr,ra._cap,ra._sz)),
		_cap(ra._cap), 
		_sz(ra._sz),
		_maxInc(ra._maxInc)
	{
	}

	RawArray(const T* arr, sznum sz):
		_arr(_createArrayCopy(arr,sz,sz)),
		_cap(sz),
		_sz(sz),
		_maxInc(Inner::defMaxCapacityIncrement<T>())
	{
	}

    ThisType& operator=(const ThisType& ra)
    {
        _arr = _createArrayCopy(ra._arr, ra._cap, ra._sz);
        _cap = ra._cap;
        _sz = ra._sz;
        _maxInc = ra._maxInc;
        return *this;
    }

	virtual ~RawArray()
	{
		_destroyArray(_arr);
	}

	void setCapacity(sznum cap)
	{
		_cap = cap;
		if (_sz > cap)
			_sz = cap;
		T *narr=_createArrayCopy(_arr,cap,_sz);
		_destroyArray(_arr);
		_arr = narr;
	}

	void setSize(sznum sz)
	{	
		if (sz > _cap)
			setCapacity(sz);
		_sz = sz;
	}

	void push_back(const T& val)
	{
		if (_cap == _sz)
			setCapacity(_cap + inRange<sznum>(_cap, 1, _maxInc));
		_sz+=1;
		_arr[_sz-1]=val;
	}

	void pop_back()
	{
		if (sz!=0)
			_sz--;
	}
	
	void clear()
	{
		_sz=0;
		if (_cap > _maxInc)
			setCapacity(_maxInc);
	}

	sznum size() const
	{
		return _sz;
	}

	sznum capacity() const
	{
		return _cap;
	}

    iterator begin()
    {
        return _arr;
    }

    const_iterator begin() const
    {
        return _arr;
    }

    iterator end()
    {
        return _arr + _sz;
    }

    const_iterator end() const
    {
        return _arr + _sz;
    }


	T* data()
	{
		return _arr;
	}

	const T* data() const
	{
		return _arr;
	}

	void take(T* d, sznum sz)
	{
		_destroyArray(_arr);
		 _arr=d;
		 _cap=sz;
		 _sz=_cap;
	}

    void take(ThisType& ra)
	{
		_destroyArray(_arr);
		_arr=ra.arr;
		_cap=ra._cap;
		_sz=ra._sz;
		ra.arr=0; 
		ra._sz=0;
		ra._cap=0;
	}

	T* passData() // unsafe!
	{
		_cap=0;
		_sz=0;
		T* r=_arr;
		_arr=0;
		return r;
	}

	void toStdVector(std::vector<T>& v)
	{
		v.clear();
		for(sznum i=0; i<_sz; i++)
			v.push_back(_arr[i]);
	}

	T& operator [](sznum i)
	{
		return _arr[i];
	}

	const T& operator [](sznum i) const
	{
		return _arr[i];
	}

	//operator T*(){return arr;} //?
	//operator const T*(){return arr;} //?

	T& at(sznum i)
	{
		return _arr[i];
	}

	const T& at(sznum i) const
	{
		return _arr[i];
	}

	
	unum maxCapacityIncrement() const
	{
		return _maxInc;
	}

	unum maxMemoryIncrement() const
	{
		return _maxInc*sizeof(T);
	}

	void setMaxCapacityIncrement(unum inc_size)
	{
		_maxInc = noLess<unum>(inc_size, 1);
	}

	void setMaxMemoryIncrement(unum inc_bytes)
	{
		_maxInc = setMaxCapacityIncrement(inc_bytes / sizeof(T));
	}

	bool operator == (const RawArray& other) const
	{
		if (other._sz != _sz)
			return false;
		for (sznum i = 0; i < _sz; i++)
		{
			if (other[i] != _arr[i])
				return false;
		}
		return true;
	}

	bool operator !=(const RawArray& other) const
	{
		return !(*this == other);
	}



protected:

	static T* _createArray(sznum sz)
	{
		if (sz == 0)
			return 0;
		return CreationSupervisor::createArray(sz);
	}

	static T* _createArrayCopy(const T* arr, sznum cap, sznum sz)
	{
		if (cap == 0)
			return 0;
		T* carr = CreationSupervisor::createArray(cap);
		if (arr)
		{
			for (sznum i = 0; i < sz; i++)
				carr[i] = arr[i];
		}
		return carr;
	}

	static void _destroyArray(T* arr)
	{
		if (arr)
			CreationSupervisor::destroyArray(arr);
	}

	T *_arr;
	sznum _cap;	
	sznum _sz;
	unum _maxInc;
};


}
#endif