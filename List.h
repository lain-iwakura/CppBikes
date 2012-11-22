#ifndef CPPBIKES_LIST_H
#define CPPBIKES_LIST_H
#include <vector>
#include <stdlib.h>

namespace CppBikes
{

template<class T> class List : public std::vector<T*>
{
	
public:

	typedef std::vector<T*> Container;
	using Container::begin;

	List(){}	
	List(const List<T>& cnt){append(cnt);}

	~List()
	{
		int c=size();
		for(int i=0; i<c; i++) delete Container::operator [](i);
	}
	
	int count() const {return size();}
	using Container::size;
	bool isEmpty() const {return empty();}
	using Container::empty;
	
	const List<T> & operator = (const List<T> & other ) 
	{
		clear();
		append(other);
		return *this;
	}

	T& increase(int di)
	{
		for(int i=0; i<di; i++) Container::push_back(new T());
		return last();
	}

	T& increase()
	{
		Container::push_back(new T());
		return last();
	}

	T& operator ++ () 
	{
		Container::push_back(new T());
		return last();
	}
	
	void operator += (const List<T> & other ){append(other);}
	void operator += (const T & obj ){Container::push_back(new T(obj));}
	void add(const T &a){Container::push_back(new T(obj));}
	void append ( const T & obj ) { Container::push_back(new T(obj)); /*cnt++;*/}
	void append (const List<T> & other )
	{
		int c=other.size();
		for(int i=0; i<c; i++) 	push_back(other[i]);
	}

	void push_back(const T& obj)
	{
		Container::push_back(new T(obj));
	}
	
	const T & first () const { return (*this)[0];}
	T & first (){ return (*this)[0]; }
	
	const T & last () const { return (*this)[size()-1]; }
	T & last () { return (*this)[size()-1]; }

	
	const T & afterFirst () const { return (*this)[1];}
	T & afterFirst (){ return (*this)[1]; }

	const T & beforeLast () const { return (*this)[size()-2]; }
	T & beforeLast () { return (*this)[size()-2]; }

	const T& at(int i) const { return *(Container::operator[](i));}
	T& at(int i){ return *(Container::operator[](i)); }

	const T& operator[](int i) const { return *(Container::operator[](i));}	
	T& operator[](int i) { return *(Container::operator[](i)); }

	T& Take(T *pItm)
	{
		Container::push_back(pItm);	
		return *pItm;
	}

	T& Take(T *pItm,int i)
	{
		Container::insert(begin()+i,pItm);
		return *pItm;
	}

	T*	Pass(int i)
	{
	//	if(i>=size()||i<0)  return 0;
		T* r=Container::operator[](i);
		erase(begin()+i);
		return r;
	}


	const T& circElement(int i) const {return circElement(i);}
	T& circElement(int i)
	{
		int c=size();
		//if(c==0) return T();
        if(abs(i)%c==0) return *Container::operator[](0);
		else if(i<0)
		{			
			return *Container::operator[]( c-((-i)%c) );
		}else
		{
			return *Container::operator[]( i%c );
		}
		//return 0;
	}

	void removeAt(int i)
	{
		if(i>=0&&i<size())
		{
			delete Container::operator [](i);
			erase(begin()+i);
		}
	}

	void remove_i1i2(int i1,int i2)
	{
        if(i1>=0&&i1<size()&&i2>=0&&i2<size()&&i2>=i1)
		{
			for(int i=i1; i<=i2; i++) delete Container::operator [](i);
			erase(begin()+i1,begin()+i2);
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
		for(int i=0; i<c; i++) if(Container::operator [](i)==r)
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
		Container::insert(begin()+i,new T(o));
	}

	bool contains(const T& obj) const
	{
		int c=size();
		for(int i=0; i<c; i++) if((*this)[i]==obj){ return true;}
		return false;
	}

	void clear()
	{
		int c=size();
		for(int i=0; i<c; i++) delete Container::operator [](i);
		Container::clear();
	}	

	void Invert()
	{
		int c=size();
		int c_=c-1;
		int c2=c/2;
		T *buf;
		for(int i=0; i<c2; i++)
		{
			buf=Container::operator [](i);
			Container::operator [](i)=Container::operator [](c_-i);
			Container::operator [](c_-i)=buf;
		}
	}

///////////////////////////
	

};

}
#endif

