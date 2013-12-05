#ifndef _BIKES_RAWARRAY_H_
#define _BIKES_RAWARRAY_H_
#include <vector>

namespace Bikes
{

template<class T>
class RawArray
{
public:

	RawArray():arr(0),s(0),l(0),ds(1)
	{
	}

	RawArray(int sz)
	{
		if(sz>0)
		{	
			arr=new T[sz];
			s=sz;
			l=s;
		}else
		{
			arr=0;
			s=0;
			l=0;
		}
	}

	RawArray(int sz, int cap, int dcap=1)
	{
		if(cap>0)
		{
			s=cap;
			arr=new T[cap];
			if(sz<=cap)
			{
				if(sz>0) l=sz;
				else l=0;
			}else l=cap;
		}else
		{
			arr=0;
			s=0;
			l=0;
		}		
		if(dcap<1) ds=1;
		else ds=dcap;
	}

	RawArray(const RawArray<T>& ra): s(ra.s), l(ra.l), ds(ra.ds)
	{
		if(s>0)
		{		
			arr=new T[s];
			for(int i=0; i<l; i++)
			{
				arr[i]=ra.arr[i];
			}
		}else
		{
			arr=0;
		}
	}

	RawArray(const T* buf, int sz)
	{
		if(sz>0)
		{
			arr=new T[sz];
			for(int i=0; i<sz; i++)
				arr[i]=buf[i];	
			l=sz;
			s=sz;
			ds=1;
		}else
		{
			ds=1;
			arr=0;
			l=0;
			s=0;
		}
	}

	virtual ~RawArray()
	{
		if(arr) delete [] arr;
	}

	void setCapacity(int cap)
	{
		T *narr=0;
		if(cap>0)
		{		
			narr=new T[cap];
			int ms=l;if(ms>cap)ms=cap;
			for(int i=0; i<ms;i++)
				narr[i]=arr[i];
			s=cap;
			l=ms;
		}else
		{
			s=0;
			l=0;
		}
		if(arr) delete [] arr;
		arr=narr;		
	}

	void setCapacityIncrement(int dcap)
	{
		if(dcap<1)ds=1;
		else ds=dcap;
	}

	void setSize(int sz)
	{
		if(sz<0)
		{
			l=0;
		}else
		{		
			if(sz>s) setCapacity((int(sz/ds)+1)*ds);
			l=sz;
		}
	}

	void push_back(const T& val)
	{
		setSize(l+1);
		arr[l-1]=val;
	}

	void pop_back()
	{
		setSize(s-1);
	}
	
	void clear()
	{
		setSize(0);
	}

	int size()const{return l;}
	int capacity()const{return s;}
	T* data(){return arr;}
	const T* data() const{return arr;}

	void takeData(T* d, int sz)
	{
		 if(arr) delete [] arr;
		 arr=d;
		 s=sz;
		 l=s;
	}

	void takeData(RawArray<T>& ra)
	{
		if(arr) delete [] arr;
		arr=ra.arr;
		s=ra.s;
		l=ra.l;
		ra.arr=0;
		ra.s=0;
		ra.l=0;
	}

	T* passData() // unsafe!
	{
		s=0;
		l=0;
		T* r=arr;
		arr=0;
		return r;
	}

	void toVector(std::vector<T>& v)
	{
		for(int i=0; i<l; i++)
			v.push_back(arr[i]);
	}

	T& operator [](int i){return arr[i];}
	const T& operator [](int i) const {return arr[i];}

	//operator T*(){return arr;} //?
	//operator const T*(){return arr;} //?

	T& at(int i){return arr[i];}
	const T& at(int i)const{return arr[i];}


protected:
	T *arr;
	int s;	
	int l;
	int ds;
};

}
#endif