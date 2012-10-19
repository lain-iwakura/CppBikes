#ifndef CONTAINERINTERFACE_H
#define CONTAINERINTERFACE_H
#include <vector>
#include <stdlib.h>

template<class T> class List : public std::vector<T*>
{
	typedef std::vector<T*> Container;
    using Container::begin;
public:

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

	void operator += (const List<T> & other ){append(other);}
	void operator += (const T & obj ){append(obj);}
	void add(const T &a){append(a);}
	void append ( const T & obj ) { push_back(obj); /*cnt++;*/}
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

	const T& at(int i) const { return (*this)[i];}
	T& at(int i){ return (*this)[i]; }

	const T& operator[](int i) const { return *(Container::operator[](i));}	
	T& operator[](int i) { return *(Container::operator[](i)); }

	void Take(T *pItm)
	{
		//if(pItm) 
		Container::push_back(pItm);	
	}

	void Take(T *pItm,int i)
	{
		//if(pItm==0) return;
		//if(i<0) i=0;
		//else if(i>size()) i=size();
		Container::insert(begin()+i,pItm);
	}

	T*	Pass(int i)
	{
		if(i>=size()||i<0)  return 0;
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

	//void Take
	
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


#endif



// 
// 
// template<class T> class List : public std::vector<T>//CONTAINER<T>
// {
// public:
// 	List():CONTAINER<T>(){/*cnt=0;*/*}	
// 	List(const List<T>& cnt):CONTAINER<T>(cnt){}
// 
// 	void Add(T &a){append(a);}
// 	int count() const {return size();}
// 
// 
// 	void operator+= ( List<T> & other ){append(other);}
// 	void operator+= ( const T & value ){append(value);}
// 	// 
// 	void append ( const T & value ) { push_back(value); /*cnt++;*/}
// 	void append ( List<T> & value )
// 	{
// 		for(int i=0; i<value.count(); i++ /*cnt++*/) 	push_back(value[i]);
// 	}
// 
// 	T & first ()
// 	{
// 		return (*this)[0]; 
// 		//return T();
// 	}
// 	T & last () 
// 	{
// 		//if(count()) 
// 		return (*this)[count()-1]; 
// 		//return T();
// 	}
// 	//const T & first () const {if(count()) return (*this)[0]; return T();}
// 	//const T & last () const {if(count()) return (*this)[count()-1]; return T();}
// 	void removeAt(int i){if(i>=0&&i<count()){erase(begin()+i);/*cnt--;*/}}
// 	void remove_i1i2(int i1,int i2){if(i1>=0&&i1<count()&&i2=>0&&i2<count()&&i2=>i1){erase(v.begin()+i1,begin()+i2);/*c-=i2-i1;*/}}
// 	bool remove(const T &r)
// 	{
// 		for(int i=0; i<count(); i++) if((*this)[i]==r){ removeAt(i); return true;}
// 		return false;
// 	}
// 	void removeLast(){if(count()>0) removeAt(count()-1);}
// 	void removeFirst(){if(count()>0) removeAt(0);}
// 
// 	void Insert(int i,const T &o)
// 	{
// 		if(i<0) i=0;
// 		else if(i>count()) i=count();
// 		insert(begin()+i,o);
// 	}
// 
// 	bool contains(const T& c) const
// 	{
// 		for(int i=0; i<count(); i++) if((*this)[i]==c){ return true;}
// 		return false;
// 	}
// 
// 	bool isEmpty() const {return empty();}
// 
// 	// 	const T & at ( int i ) const
// 	// 	{
// 	// 
// 	// 	}
// 	//	std::vector <int>::iterator Iter;
// 
// 	//	void insert ( int i, const T & value ){};
// 	//	void clear () {v.clear(); cnt=0;};
// 	// 	int removeAll ( const T & value );
// 	// 	void removeAt ( int i );
// 	// 	void removeFirst ();
// 	// 	void removeLast ();
// 	// 	bool removeOne ( const T & value );
// 	// 
// 	//	T & operator[] ( int i ){return v[i];}
// 	//	std::vector<T> v;
// 	//	int cnt;
// };
// 

//*/
