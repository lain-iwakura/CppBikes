#ifndef INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H
#define INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H

#include <Bikes/Abstract/Cloner.h>
#include <Bikes/Abstract/Creator.h>
#include <Bikes/Abstract/Deleter.h>

namespace Bikes
{						



template<class TCloner, class TCreator, class TDeleter>
class CreationSupervisor
{
public:
	typedef typename Cloner::value_type value_type;
	typedef TCloner Cloner;
	typedef TCreator Creator;
	typedef TDeleter Deleter;

	static value_type* createCopy(const value_type* obj)
	{
		return Cloner::createCopy(obj);
	}

	static value_type* create()
	{
		return Creator::create();
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

}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H
