#ifndef PREBIKES_DEPENDEDOBJECT_H
#define PREBIKES_DEPENDEDOBJECT_H
#include "PhantomObject.h"


namespace Bikes
{

template<class T> class DependedObject
{
public:
	DependedObject(){changing=false;}	
	DependedObject(const T& obj_):OBJ(obj_){changing=false;}
	DependedObject(const DependedObject<T> &dobj):OBJ(dobj.OBJ){changing=false;}
	~DependedObject()
	{
		if(changing) for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->changingMasters.remove(this);
			slaves[i]->masters.remove(this);
			slaves[i]->beginChanging();
			slaves[i]->masterChanged(phBackupOBJ.val(OBJ),OBJ);
			slaves[i]->masterDeleted(OBJ);	
			slaves[i]->endChanging();
		}else for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->masters.remove(this);
			slaves[i]->beginModify();
			slaves[i]->masterDeleted(OBJ);
			slaves[i]->endModify();
		}
		for(int i=0; i<masters.count(); i++) masters[i]->slaves.remove(this);
	}

	void operator =(const T& obj_)
	{
		if(!changing) modify(OBJ,obj_);
		OBJ=obj_;				
	}
	void operator=(const DependedObject<T> & dobj)
	{
		if(!changing) modify(OBJ,dobj.OBJ);
		OBJ=dobj.OBJ;				
	}

	void beginChanging()
	{
		if(changing) return;
		changing=true;
		for(int i=0; i<slaves.count(); i++) 
		{
			slaves[i]->changingMasters+=this;
			slaves[i]->beginChanging();
		}
		phBackupOBJ.create(OBJ);
	}

	void endChanging()
	{
		if(!changing) return;
		mastersInspection();
		changing=false;
		for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->changingMasters.remove(this);
			modifySlave(slaves[i]);			
		}
		phBackupOBJ.destroy();
	}
		
	T& obj() //?
	{
		mastersInspection();//?
		beginChanging();//?
		return OBJ;
	}

	operator T() const
	{
		mastersInspection();
		return OBJ;
	}

	const T& cObj() const
	{
		mastersInspection();
		return OBJ;
	}
 	const T& cObjC() const //???
 	{
 		return OBJ;
 	}

	bool isChanging() const {return changing;}
	bool isMastersChanging() const {return changingMasters.count();}

	bool mastersInspection() const
	{
		if(changingMasters.count())
		{
			for(int i=0; i<changingMasters.count(); i++){changingMasters[i]->endChanging();}
			return true;
		}
		return false;
	}

	void addMaster(DependedObject<T> &m){addMaster(&m);}
	void addMaster(DependedObject<T> *Master)
	{
		if(!Master->slaves.contains(this))
		{
			masters+=Master;
			Master->slaves+=this;
			masterAdded(Master->OBJ);
		}
	}
	void addSlave(DependedObject<T> &s){addSlave(&s);}
	void addSlave(DependedObject<T> *Slave)
	{
		if(!Slave->masters.contains(this))
		{
			slaves+=Slave;
			Slave->masters+=this;
			Slave->masterAdded(OBJ);
		}
	}
	void removeMaster(DependedObject<T> &m){removeMaster(&m);}
	bool removeMaster(DependedObject<T> *Master)
	{
		if(masters.remove(Master))
		{
			Master->slaves.remove(this);
			masterRemoved(Master->OBJ);
			return true;
		}
		return false;
	}
	void removeSlave(DependedObject<T> &s){removeSlave(&s);}
	bool removeSlave(DependedObject<T> *Slave)
	{
		if(slaves.remove(Slave))
		{
			Slave->masters.remove(this);
			Slave->masterRemoved(OBJ);
			return true;
		}
		return false;
	}
	

protected:

	T OBJ;
	PhantomObject<T> phBackupOBJ;

	virtual void masterChanged(const T& MasterBackup,const T& MasterNow ){} //***
	virtual void masterDeleted(const T& MasterNow){} //***
	virtual void masterAdded(const T& MasterNow){} //***
	virtual void masterRemoved(const T& MasterNow){} //***

	void modifySlave(DependedObject<T> *slave)
	{
			slave->beginModify();
			slave->masterChanged(phBackupOBJ.val(OBJ),OBJ);
			slave->endModify();
	}
	void modifyAllSlaves()
	{
		if(phBackupOBJ.exist())	for(int i=0; i<slaves.count(); i++)
		{			
			slaves[i]->beginModify();
			slaves[i]->masterChanged(phBackupOBJ.obj(),OBJ);
			slaves[i]->endModify();
		}
	}
	void modify(const T& MasterOld, const T& MasterNew)
	{
		for(int i=0; i<slaves.count(); i++)
		{
			slaves[i]->beginModify();
			slaves[i]->masterChanged(MasterOld,MasterNew);
			slaves[i]->endModify();
		}
	}
	void beginModify()
	{
		if(!changing)phBackupOBJ.create(OBJ);
	}
	void endModify()
	{
		if(!changing)
		{
			modifyAllSlaves();
			phBackupOBJ.destroy();
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
    using DependedObject<T>::beginModify;
    using DependedObject<T>::endModify;
   // using DependedObject<T>::OBJ;
    using DependedObject<T>::mastersInspection;
public:
 //   DependedValue(){}
	TEMPLT_DEFALL(DependedValue,DependedObject,T)

	void operator +=(const T& obj_)
	{
		beginModify();
        this->OBJ+=obj_;
		endModify();
	}
	void operator -=(const T& obj_)
	{
		beginModify();
        this->OBJ-=obj_;
		endModify();
	}
	void operator *=(const T& obj_)
	{
		beginModify();
        this->OBJ*=obj_;
		endModify();
	}
	void operator /=(const T& obj_)
	{
		beginModify();
        this->OBJ/=obj_;
		endModify();
	}

	operator T() const
	{
		mastersInspection();
        return this->OBJ;
	}

protected:
	virtual void masterChanged(const T& MasterBackup,const T& MasterNow ){} //***
	virtual void masterDeleted(const T& MasterNow){} //***
	virtual void masterAdded(const T& MasterNow){} //***
	virtual void masterRemoved(const T& MasterNow){} //***
	
};



//////////////////////////////////////////////////////////////////////////

template<class T> class DependedLength: public DependedValue<T>
{
       // using DependedValue<T>::OBJ;        
public:
 //   DependedLength(){}
	TEMPLT_DEFALL(DependedLength,DependedValue,T)
private:
	void masterChanged(const T& MasterBackup,const T& MasterNow )
	{
        this->OBJ+=MasterNow-MasterBackup;
	} 
	void masterDeleted(const T& MasterNow)
	{
        this->OBJ-=MasterNow;
	}
	void masterAdded(const T& MasterNow) //?
	{
        this->OBJ+=MasterNow;
	} 
	void masterRemoved(const T& MasterNow) //?
	{
        this->OBJ-=MasterNow;
	} 
};

}
#endif
