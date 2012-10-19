#ifndef DEPENDEDOBJECT_H
#define DEPENDEDOBJECT_H
#include "PhantomObject.h"


namespace CppBikes
{

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

	operator T() const
	{
		MastersInspection();
		return OBJ;
	}

	const T& cObj() const
	{
		MastersInspection();
		return OBJ;
	}
 	const T& cObjC() const //???
 	{
 		return OBJ;
 	}

	bool isChanging() const {return changing;}
	bool isMastersChanging() const {return changingMasters.count();}

	bool MastersInspection() const
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
	virtual void MasterRemoved(const T& MasterNow){} //***

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
    using DependedObject<T>::BeginModify;
    using DependedObject<T>::EndModify;
   // using DependedObject<T>::OBJ;
    using DependedObject<T>::MastersInspection;
public:
 //   DependedValue(){}
	TEMPLT_DEFALL(DependedValue,DependedObject,T)

	void operator +=(const T& obj)
	{
		BeginModify();
        this->OBJ+=obj;
		EndModify();
	}
	void operator -=(const T& obj)
	{
		BeginModify();
        this->OBJ-=obj;
		EndModify();
	}
	void operator *=(const T& obj)
	{
		BeginModify();
        this->OBJ*=obj;
		EndModify();
	}
	void operator /=(const T& obj)
	{
		BeginModify();
        this->OBJ/=obj;
		EndModify();
	}

	operator T() const
	{
		MastersInspection();
        return this->OBJ;
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
       // using DependedValue<T>::OBJ;        
public:
 //   DependedLength(){}
	TEMPLT_DEFALL(DependedLength,DependedValue,T)
private:
	void MasterChanged(const T& MasterBackup,const T& MasterNow )
	{
        this->OBJ+=MasterNow-MasterBackup;
	} 
	void MasterDeleted(const T& MasterNow)
	{
        this->OBJ-=MasterNow;
	}
	void MasterAdded(const T& MasterNow) //?
	{
        this->OBJ+=MasterNow;
	} 
	void MasterRemoved(const T& MasterNow) //?
	{
        this->OBJ-=MasterNow;
	} 
};

}
#endif
