#ifndef INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H
#define INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H

#include <Bikes/Creation/Cloner.h>
#include <Bikes/Creation/Creator.h>
#include <Bikes/Creation/Deleter.h>

namespace Bikes
{						



template<class TCloner, class TCreator, class TDeleter>
class CreationSupervisor
{
public:
	typedef TCloner Cloner;
	typedef TCreator Creator;
	typedef TDeleter Deleter;
	typedef typename Cloner::value_type value_type;

	static value_type* createCopy(const value_type* obj)
	{
		return Cloner::createCopy(obj);
	}

	static value_type* create()
	{
		return Creator::create();
	}

	static value_type* createArray(sznum sz)
	{
		return Creator::createArray(sz);
	}

	static void destroy(value_type* obj)
	{			
		Deleter::destroy(obj);
	}
};

template<class T>
class SimpleCopyingSupervisor: 
	public CreationSupervisor<SimpleCopier<T>,SimpleCreator<T>,SimpleDeleter<T> >
{
public:
// 	typedef typename CreationSupervisor<SimpleCopier<T>, SimpleCreator<T>, SimpleDeleter<T> > Base;
// 	typedef typename Base::value_type value_type;
// 	typedef typename Base::Cloner Cloner;
// 	typedef typename Base::Creator Creator;
// 	typedef typename Base::Deleter Deleter;
};

template<class T>
class SimpleCloningSupervisor :
	public CreationSupervisor<SimpleCloner<T>, SimpleCreator<T>, SimpleDeleter<T> >
{
public:
// 	typedef typename CreationSupervisor<SimpleCopier<T>, SimpleCreator<T>, SimpleDeleter<T> > Base;
// 	typedef typename Base::value_type value_type;
// 	typedef typename Base::Cloner Cloner;
// 	typedef typename Base::Creator Creator;
// 	typedef typename Base::Deleter Deleter;
};


template<class T>
class SimpleArraySupervisor :
	public CreationSupervisor<SimpleCopier<T>, SimpleArrayCreator<T>, SimpleArrayDeleter<T> >
{
public:
	// 	typedef typename CreationSupervisor<SimpleCopier<T>, SimpleCreator<T>, SimpleDeleter<T> > Base;
	// 	typedef typename Base::value_type value_type;
	// 	typedef typename Base::Cloner Cloner;
	// 	typedef typename Base::Creator Creator;
	// 	typedef typename Base::Deleter Deleter;
};
}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H
