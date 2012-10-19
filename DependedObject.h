#ifndef DEPENDEDOBJECT_H
#define DEPENDEDOBJECT_H
#include "PhantomObject.h"

template<class T> class DependedObject
{
public:
	DependedObject(){changing=false;}	
	DependedObject(const T& obj):OBJ(obj){changing=false;}
	DependedObject(const DependedObject<T> &dobj):OBJ(dobj.OBJ){changing=false;}
	~DependedObject()
	{
		if(changing) for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->changingMasters.remove(this);
			slaves[i]->masters.remove(this);
			slaves[i]->BeginChanging();
			slaves[i]->MasterChanged(phBackupOBJ.Val(OBJ),OBJ);
			slaves[i]->MasterDeleted(OBJ);	
			slaves[i]->EndChanging();
		}else for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->masters.remove(this);
			slaves[i]->BeginModify();
			slaves[i]->MasterDeleted(OBJ);
			slaves[i]->EndModify();
		}
		for(int i=0; i<masters.count(); i++) masters[i]->slaves.remove(this);
	}

	void operator =(const T& obj)
	{
		if(!changing) Modify(OBJ,obj);
		OBJ=obj;				
	}
	void operator=(const DependedObject<T> & dobj)
	{
		if(!changing) Modify(OBJ,dobj.OBJ);
		OBJ=dobj.OBJ;				
	}

	void BeginChanging()
	{
		if(changing) return;
		changing=true;
		for(int i=0; i<slaves.count(); i++) 
		{
			slaves[i]->changingMasters+=this;
			slaves[i]->BeginChanging();
		}
		phBackupOBJ.Create(OBJ);
	}

	void EndChanging()
	{
		if(!changing) return;
		MastersInspection();
		changing=false;
		for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->changingMasters.remove(this);
			ModifySlave(slaves[i]);			
		}
		phBackupOBJ.Destroy();
	}
		
	T& Obj() //?
	{
		MastersInspection();//?
		BeginChanging();//?
		return OBJ;
	}

	operator T() 
	{
		MastersInspection();
		return OBJ;
	}

	const T& cObj() 
	{
		MastersInspection();
		return OBJ;
	}
	const T& cObjC() const
	{
		return OBJ;
	}

	bool isChanging() const {return changing;}
	bool isMastersChanging() const {return changingMasters.count();}

	bool MastersInspection()
	{
		if(changingMasters.count())
		{
			for(int i=0; i<changingMasters.count(); i++){changingMasters[i]->EndChanging();}
			return true;
		}
		return false;
	}

	void AddMaster(DependedObject<T> &m){AddMaster(&m);}
	void AddMaster(DependedObject<T> *Master)
	{
		if(!Master->slaves.contains(this))
		{
			masters+=Master;
			Master->slaves+=this;
			MasterAdded(Master->OBJ);
		}
	}
	void AddSlave(DependedObject<T> &s){AddSlave(&s);}
	void AddSlave(DependedObject<T> *Slave)
	{
		if(!Slave->masters.contains(this))
		{
			slaves+=Slave;
			Slave->masters+=this;
			Slave->MasterAdded(OBJ);
		}
	}
	void RemoveMaster(DependedObject<T> &m){RemoveMaster(&m);}
	bool RemoveMaster(DependedObject<T> *Master)
	{
		if(masters.remove(Master))
		{
			Master->slaves.remove(this);
			MasterRemoved(Master->OBJ);
			return true;
		}
		return false;
	}
	void RemoveSlave(DependedObject<T> &s){RemoveSlave(&s);}
	bool RemoveSlave(DependedObject<T> *Slave)
	{
		if(slaves.remove(Slave))
		{
			Slave->masters.remove(this);
			Slave->MasterRemoved(OBJ);
			return true;
		}
		return false;
	}
	

protected:

	T OBJ;
	PhantomObject<T> phBackupOBJ;

	virtual void MasterChanged(const T& MasterBackup,const T& MasterNow ){} //***
	virtual void MasterDeleted(const T& MasterNow){} //***
	virtual void MasterAdded(const T& MasterNow){} //***
	virtual void MasterRemoved(const T& MasterNow) {} //***

	void ModifySlave(DependedObject<T> *slave)
	{
			slave->BeginModify();
			slave->MasterChanged(phBackupOBJ.Val(OBJ),OBJ);
			slave->EndModify();
	}
	void ModifyAllSlaves()
	{
		if(phBackupOBJ.Exist())	for(int i=0; i<slaves.count(); i++)
		{			
			slaves[i]->BeginModify();
			slaves[i]->MasterChanged(phBackupOBJ.Obj(),OBJ);
			slaves[i]->EndModify();
		}
	}
	void Modify(const T& MasterOld, const T& MasterNew)
	{
		for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->BeginModify();
			slaves[i]->MasterChanged(MasterOld,MasterNew);
			slaves[i]->EndModify();
		}
	}
	void BeginModify()
	{
		if(!changing)phBackupOBJ.Create(OBJ);
	}
	void EndModify()
	{
		if(!changing)
		{
			ModifyAllSlaves();
			phBackupOBJ.Destroy();
		}
	}

private:
	bool changing;
	List<DependedObject<T> *> slaves;
	List<DependedObject<T> *> masters;
	List<DependedObject<T> *> changingMasters;//?
};


template<class T> class DependedValue: public DependedObject<T>
{	
public:
	TEMPLT_DEFALL(DependedValue,DependedObject,T)

	void operator +=(const T& obj)
	{
		BeginModify();
		OBJ+=obj;	
		EndModify();
	}
	void operator -=(const T& obj)
	{
		BeginModify();
		OBJ-=obj;
		EndModify();
	}
	void operator *=(const T& obj)
	{
		BeginModify();
		OBJ*=obj;
		EndModify();
	}
	void operator /=(const T& obj)
	{
		BeginModify();
		OBJ/=obj;
		EndModify();
	}

	operator T()
	{
		MastersInspection();
		return OBJ;
	}

protected:
	virtual void MasterChanged(const T& MasterBackup,const T& MasterNow ){} //***
	virtual void MasterDeleted(const T& MasterNow){} //***
	virtual void MasterAdded(const T& MasterNow){} //***
	virtual void MasterRemoved(const T& MasterNow){} //***
	
};



//////////////////////////////////////////////////////////////////////////

template<class T> class DependedLength: public DependedValue<T>
{
public:
	TEMPLT_DEFALL(DependedLength,DependedValue,T)
private:
	void MasterChanged(const T& MasterBackup,const T& MasterNow )
	{
		OBJ+=MasterNow-MasterBackup;
	} 
	void MasterDeleted(const T& MasterNow)
	{
		OBJ-=MasterNow;
	}
	void MasterAdded(const T& MasterNow) //?
	{
		OBJ+=MasterNow;
	} 
	void MasterRemoved(const T& MasterNow) //?
	{
		OBJ-=MasterNow;
	} 
};



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
		phObjects.Insert(i,PhantomObject<T>());
		phObjects[i].Create(obj);
	}

	int count() const {return phObjects.count();}
	void clear() {phObjects.clear();}	
protected:
	List<PhantomObject<T>> phObjects;
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

#endif