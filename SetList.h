#ifndef SETLIST_H
#define SETLIST_H



namespace CppBikes
{

template<class T> class SetList
{    
public:
	SetList(){}
	SetList(const SetList<T> &ml):phObjects(ml.phObjects){}
	void set(int i, const T & val)
	{
		if(i<0) return;
		PhantomObject<T> pht;
		while(i>=phObjects.count()) phObjects+=pht;
		phObjects[i]=val;
	}

	T& operator [] (int i)
	{
		if(i<0) i=0;
		PhantomObject<T> pht;
		while(i>=phObjects.count()){phObjects+=pht;}
		return phObjects[i].Obj();
	}

	bool isSet(int i) const
	{
		if(i<0) return false;
		if(i>=phObjects.count()) return false;
		return phObjects[i].Exist();
	}

	T* at(int i)
	{
		if(i<0) return 0;
		if(i>=phObjects.count()) return 0;
		return phObjects[i].pObj(); 
	}

	T* atFirst()
	{
		if(phObjects.count()) return phObjects[0].pObj();
		return 0;
	}

	T* atLast()
	{
		if(phObjects.count()) return phObjects[phObjects.count()-1].pObj();
		return 0;
	}

	void unset(int i)
	{
		if(i<0) return;
		if(i>phObjects.count()) return;
		phObjects[i].Destroy();
	}


	void removeAt(int i){phObjects.removeAt(i);}
	void removeLast(){phObjects.removeLast();}
	void removeFirst(){phObjects.removeFirst();}
	void insert(int i, const T & obj)
	{
		if(i<0) i=0;
		else if(i>phObjects.count()) i=phObjects.count();
		phObjects.insert(i,PhantomObject<T>());
		phObjects[i].Create(obj);
	}

	int count() const {return phObjects.count();}
	void clear() {phObjects.clear();}	
protected:
    List<PhantomObject<T> > phObjects;
};

class BoolMarkerList: public SetList<bool>
{
public:

	BoolMarkerList():SetList<bool>(){}
	BoolMarkerList(const BoolMarkerList &bml):SetList<bool>(bml){}
	void SetMarker(int i, bool b)
	{
		if(i<0) return;
		PhantomObject<bool> pht; pht.Obj(false);
		while(i>=phObjects.count()){phObjects+=pht;}
		phObjects[i]=b;
	}
	bool& operator [] (int i)
	{
		if(i<0) i=0;		
		PhantomObject<bool> pht; pht.Obj(false);
		while(i>=phObjects.count()){phObjects+=pht;}
		return phObjects[i].Obj(false);
	}
};


}
#endif
