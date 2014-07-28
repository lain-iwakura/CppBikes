#ifndef PREBIKES_RAWARRAY_H
#define PREBIKES_RAWARRAY_H
#include <Bikes/Types.h>
#include <Bikes/Mathem/Tools.h>
#include <vector>

namespace Bikes
{

template<class T, sznum maxCapacityIncrement_bytes = 1024>
class RawArray
{
public:

	RawArray():_arr(0),_cap(0),_sz(0)
	{
	}

	RawArray(sznum sz)
	{
		if(sz>0)
		{	
			_arr=new T[sz];
			_cap=sz;
			_sz=_cap;
		}else
		{
			_arr=0;
			_cap=0;
			_sz=0;
		}
	}

	RawArray(sznum sz, sznum cap)
	{
		if(cap>0)
		{
			_cap=cap;
			_arr=new T[cap];
			if(sz<=cap)
			{
				if(sz>0) _sz=sz;
				else _sz=0;
			}else _sz=cap;
		}else
		{
			_arr=0;
			_cap=0;
			_sz=0;
		}		
	}

	RawArray(const RawArray<T>& ra): _cap(ra._cap), _sz(ra._sz)
	{
		if(_cap>0)
		{		
			_arr=new T[_cap];
			for(sznum i=0; i<_sz; i++)
			{
				_arr[i]=ra._arr[i];
			}
		}else
		{
			_arr=0;
		}
	}

	RawArray(const T* buf, sznum sz)
	{
		if(sz>0)
		{
			_arr=new T[sz];
			for(sznum i=0; i<sz; i++)
				_arr[i]=buf[i];	
			_sz=sz;
			_cap=sz;
		}else
		{
			_arr=0;
			_sz=0;
			_cap=0;
		}
	}

	virtual ~RawArray()
	{
		if(_arr) 
			delete [] _arr;
	}

	void setCapacity(sznum cap)
	{
		T *narr=0;
		if(cap>0)
		{		
			narr=new T[cap];
			sznum ms=_sz;if(ms>cap)ms=cap;
			for(sznum i=0; i<ms;i++)
				narr[i]=_arr[i];
			_cap=cap;
			_sz=ms;
		}else
		{
			_cap=0;
			_sz=0;
		}
		if(_arr) delete [] _arr;
		_arr=narr;		
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
		{
			setCapacity(_cap + inRange(_cap, 1, maxCapacityIncrement()));
		}
		setSize(_sz+1);
		_arr[_sz-1]=val;
	}

	void pop_back()
	{
		setSize(_cap-1);
	}
	
	void clear()
	{
		setSize(0);
	}

	sznum size() const
	{
		return _sz;
	}

	sznum capacity() const
	{
		return _cap;
	}

	T* data()
	{
		return _arr;
	}

	const T* data() const
	{
		return _arr;
	}

	void takeData(T* d, sznum sz)
	{
		 if(_arr) 
			 delete [] _arr;
		 _arr=d;
		 _cap=sz;
		 _sz=_cap;
	}

	void takeData(RawArray<T>& ra)
	{
		if(_arr) 
			delete [] _arr;
		_arr=ra.arr;
		_cap=ra.s;
		_sz=ra.l;
		ra.arr=0;
		ra.s=0;
		ra.l=0;
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

	
	static sznum maxCapacityIncrement()
	{
		static const sznum inc = 
			inRange<sznum>(
			maxCapacityIncrement_bytes / sizeof(T), 
			1, 
			maxCapacityIncrement_bytes
			);

		return inc;
	}

private:
	T *_arr;
	sznum _cap;	
	sznum _sz;
};


}
#endif