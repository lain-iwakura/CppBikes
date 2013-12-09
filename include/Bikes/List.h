#ifndef PREBIKES_LIST_H
#define PREBIKES_LIST_H
#include <vector>
#include <stdlib.h>

namespace Bikes
{

template<class T> class List //: public std::vector<T*>
{
	std::vector<T*> l_;
public:

	std::vector<T*>& data(){return l_;}

	List(){}	
	List(const List<T>& cnt){append(cnt);}

	~List()
	{
		int c=size();
		for(int i=0; i<c; i++) delete l_[i];
	}
	
	int count() const {return l_.size();}	
	int size() const {return l_.size();}
	bool isEmpty() const {return l_.size()==0;}
		
	const List<T> & operator = (const List<T> & other ) 
	{
		clear();
		append(other);
		return *this;
	}

	T& increase(int di)
	{
		for(int i=0; i<di; i++) l_.push_back(new T());
		return last();
	}

	T& increase()
	{
		l_.push_back(new T());
		return last();
	}

	T& operator ++ () 
	{
		l_.push_back(new T());
		return last();
	}
	
	void operator += (const List<T> & other ){append(other);}
	void operator += (const T & obj ){l_.push_back(new T(obj));}
	void add(const T &obj){l_.push_back(new T(obj));}
	void append ( const T & obj ) {l_.push_back(new T(obj)); /*cnt++;*/}
	void append (const List<T> & other )
	{
		int c=other.size();
		for(int i=0; i<c; i++) push_back(other[i]);
	}

	void push_back(const T& obj)
	{
		l_.push_back(new T(obj));
	}
	
	const T & first () const { return (*this)[0];}
	T & first (){ return (*this)[0]; }
	
	const T & last () const { return (*this)[size()-1]; }
	T & last () { return (*this)[size()-1]; }

	
	const T & afterFirst () const { return (*this)[1];}
	T & afterFirst (){ return (*this)[1]; }

	const T & beforeLast () const { return (*this)[size()-2]; }
	T & beforeLast () { return (*this)[size()-2]; }

	const T& at(int i) const { return *(l_[i]);}
	T& at(int i){ return *(l_[i]); }

	const T& operator[](int i) const { return *(l_[i]);}	
	T& operator[](int i) { return *(l_[i]); }

	T& take(T *pItm)
	{
		l_.push_back(pItm);	
		return *pItm;
	}

	T& take(T *pItm,int i)
	{
		l_.insert(l_.begin()+i,pItm);
		return *pItm;
	}

	void take(List<T>& l)
	{		
		int c=l.size();
		for(int i=0; i<c; i++)l_.push_back(l.l_[i]);
		l.clear();
	}

	T*	pass(int i)
	{
	//	if(i>=size()||i<0)  return 0;
		T* r=l_[i];
		l_.erase(l_.begin()+i);
		return r;
	}

	T* passLast()
	{
		int i=l_.size()-1;
		T* r=l_[i];
		l_.erase(l_.begin()+i);
		return r;
	}

	T* passFirst()
	{
		T* r=l_[0];
		l_.erase(l_.begin());
		return r;
	}


	void removeAt(int i)
	{
		if(i>=0&&i<size())
		{
			delete l_[i];
			l_.erase(l_.begin()+i);
		}
	}

	void remove_i1i2(int i1,int i2)
	{
        if(i1>=0&&i1<size()&&i2>=0&&i2<size()&&i2>=i1)
		{
			for(int i=i1; i<=i2; i++) delete l_[i];
			l_.erase(l_.begin()+i1,l_.begin()+i2);
		}
	}

	bool remove(const T &r)
	{
		int c=size();
		for(int i=0; i<c; i++) if((*this)[i]==r){ removeAt(i); return true;}
		return false;
	}
	bool removeThat(T *r)
	{
		int c=size();
		for(int i=0; i<c; i++) if(l_[i]==r)
		{
			removeAt(i);
			return true;
		}
		return false;
	}
	void removeLast(){if(size()>0) removeAt(size()-1);}
	void removeFirst(){if(size()>0) removeAt(0);}

	void insert(int i,const T &o)
	{
		if(i<0) i=0;
		else if(i>size()) i=size();
		l_.insert(l_.begin()+i,new T(o));
	}

	bool contains(const T& itm) const
	{
		int c=size();
		for(int i=0; i<c; i++) if((*this)[i]==itm){ return true;}
		return false;
	}

	int find(const T &itm) const
	{
		int c=size();
		for(int i=0; i<c; i++) if(*(l_[i])==itm) return i;
		return -1;
	}

	void clear()
	{
		int c=size();
		for(int i=0; i<c; i++) delete l_[i];
		l_.clear();
	}	

	void invert()
	{
		int c=size();
		int c_=c-1;
		int c2=c/2;
		T *buf;
		for(int i=0; i<c2; i++)
		{
			buf=l_[i];
			l_[i]=l_[c_-i];
			l_[c_-i]=buf;
		}
	}


};

}
#endif

