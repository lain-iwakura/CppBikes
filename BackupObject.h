#ifndef BACKUPOBJECT_H
#define BACKUPOBJECT_H


template<class T> class BackupObject
{
public:
	BackupObject(int maxBackupNumber=1)
	{maxBackups=maxBackupNumber;}
	BackupObject(const T &obj, int maxBackupNumber=1):OBJ(obj)
	{maxBackups=maxBackupNumber;}
	BackupObject(const BackupObject<T> & bobj):OBJ(bobj.OBJ),backups(bobj.backups)
	{maxBackups=bobj.maxBackups;}

	virtual void operator =(const T& obj){OBJ=obj;}
	virtual void operator =(const BackupObject<T> &bobj){OBJ=bobj.OBJ;}
	operator T(){/*if(autobackup)MakeBackup();*/ return OBJ;}
	void MakeBackup()
	{
		backups+=OBJ;
		if(backups.count()>maxBackups) backups.removeFirst();
	}

	void SetBackupsLimitNumber(int maxBackupNumber){maxBackups=maxBackupNumber;}
	void RemoveAllBackups(){backups.clear();}
	int BackupsNumber() const {return backups.count();}
	int BackupsLimitNumber() const {return maxBackups;}
	const T & FirstBackup() const {if(backups.count()) return backups.at(0); return OBJ;}
	const T & LastBackup()const {if(backups.count()) return backups.at(backups.count()-1); return OBJ;}
	const T & Backup()const{if(backups.count()) return backups.at(0); return OBJ;}
	const T & Backup(int i)const
	{
		int c=backups.count();
		if(c)
		{
			if(i<0) i=0;
			else if(i>c) i=c;
			return backups.at(i);
		}
		return OBJ;
	}	
	virtual T& Obj(){ return OBJ;}	
	const T & cObj() const { return OBJ;}

protected:
	T OBJ;
	int maxBackups;	
	List<T> backups;
};


template<class T> class AutoBackupObject: public BackupObject<T>
{
public:
	AutoBackupObject(int maxBackupNumber=1, bool autobackupOn=true):BackupObject<T>(maxBackupNumber){autobackup=autobackupOn;}
	AutoBackupObject(const T &obj,int maxBackupNumber=1, bool autobackupOn=true):BackupObject<T>(obj,maxBackupNumber){autobackup=autobackupOn;}
	AutoBackupObject(const AutoBackupObject<T> &abobj):OBJ(abobj.OBJ),backups(abobj.backups)
	{
		maxBackups=abobj.maxBackups;
		autobackup=abobj.autobackup;
	}	
	void operator =(const T &obj){if(autobackup)MakeBackup(); OBJ=obj;}

	T & Obj(){if(autobackup)MakeBackup(); return OBJ;}

	bool isAutobackup() const {return autobackup;}
	void SetAutobackupOn(bool on=true){autobackup=on;}
	void SetAutobackupOff(bool off=true){autobackup=!off;}

protected:
	bool autobackup;
};


template<class T> class AutoBackupValue: public AutoBackupObject<T>
{
public:
	AutoBackupValue(int maxBackupNumber=1, bool autobackupOn=true):AutoBackupObject<T>(maxBackupNumber,autobackupOn){}
	AutoBackupValue(const T &val,int maxBackupNumber=1, bool autobackupOn=true):AutoBackupObject<T>(val,maxBackupNumber,autobackupOn){}
	AutoBackupValue(const AutoBackupObject<T> &abval):OBJ(abobj.OBJ),backups(abobj.backups)
	{
		maxBackups=abobj.maxBackups;
		autobackup=abobj.autobackup;
	}
	void operator +=(const T &val){if(autobackup)MakeBackup(); OBJ+=val;}
	void operator -=(const T &val){if(autobackup)MakeBackup(); OBJ-=val;}
	void operator *=(const T &val){if(autobackup)MakeBackup(); OBJ*=val;}
	void operator /=(const T &val){if(autobackup)MakeBackup(); OBJ/=val;}
};


#endif