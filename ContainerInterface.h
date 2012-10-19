#ifndef CONTAINERINTERFACE_H
#define CONTAINERINTERFACE_H
#include <vector>

#define CONTAINER std::vector 

#define List ContainerInterface



template<class T> class ContainerInterface : public CONTAINER<T>
{
public:
	ContainerInterface():CONTAINER<T>(){/*cnt=0;*/}	
	ContainerInterface(const ContainerInterface<T>& cnt):CONTAINER<T>(cnt){}

	void Add(T &a){append(a);}
	int count() const {return size();}


	void operator+= ( ContainerInterface<T> & other ){append(other);}
	void operator+= ( const T & value ){append(value);}
	// 
	void append ( const T & value ) { push_back(value); /*cnt++;*/}
	void append ( ContainerInterface<T> & value )
	{
		for(int i=0; i<value.count(); i++ /*cnt++*/) 	push_back(value[i]);
	}

	T & first ()
	{
		return (*this)[0]; 
		//return T();
	}
	T & last () 
	{
		//if(count()) 
			return (*this)[count()-1]; 
			//return T();
	}
	//const T & first () const {if(count()) return (*this)[0]; return T();}
	//const T & last () const {if(count()) return (*this)[count()-1]; return T();}
	void removeAt(int i){if(i>=0&&i<count()){erase(begin()+i);/*cnt--;*/}}
	void remove_i1i2(int i1,int i2){if(i1>=0&&i1<count()&&i2=>0&&i2<count()&&i2=>i1){erase(v.begin()+i1,begin()+i2);/*c-=i2-i1;*/}}
	bool remove(const T &r)
	{
		for(int i=0; i<count(); i++) if((*this)[i]==r){ removeAt(i); return true;}
		return false;
	}
	void removeLast(){if(count()>0) removeAt(count()-1);}
	void removeFirst(){if(count()>0) removeAt(0);}
	
	void Insert(int i,const T &o)
	{
		if(i<0) i=0;
		else if(i>count()) i=count();
		insert(begin()+i,o);
	}

	bool contains(const T& c) const
	{
		for(int i=0; i<count(); i++) if((*this)[i]==c){ return true;}
		return false;
	}

	bool isEmpty() const {return empty();}
	
// 	const T & at ( int i ) const
// 	{
// 
// 	}
//	std::vector <int>::iterator Iter;

	//	void insert ( int i, const T & value ){};
	//	void clear () {v.clear(); cnt=0;};
	// 	int removeAll ( const T & value );
	// 	void removeAt ( int i );
	// 	void removeFirst ();
	// 	void removeLast ();
	// 	bool removeOne ( const T & value );
	// 
//	T & operator[] ( int i ){return v[i];}
//	std::vector<T> v;
//	int cnt;
};


#endif