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

	static void destroyArray(value_type* obj)
	{
		Deleter::destroyArray(obj);
	}
};


template<class T>
struct SimpleCreationSupervisor
{
    typedef CreationSupervisor<
        Bikes::SimpleCopier<T>, 
        Bikes::SimpleCreator<T>, 
        Bikes::SimpleDeleter<T>
        > Copier;

    typedef CreationSupervisor<
        Bikes::SimpleCloner<T>, 
        Bikes::SimpleCreator<T>, 
        Bikes::SimpleDeleter<T>
        > Cloner;

    typedef CreationSupervisor<
        Bikes::SafetyCopier<T>, 
        Bikes::SimpleCreator<T>, 
        Bikes::SafetyDeleter<T>
        > SafetyCopier;

    typedef CreationSupervisor<
        Bikes::SafetyCloner<T>, 
        Bikes::SimpleCreator<T>,
        Bikes::SafetyDeleter<T>
        > SafetyCloner;

    typedef CreationSupervisor<
        Bikes::SafetyCopier<T>, 
        Bikes::NullCreator<T>, 
        Bikes::SafetyDeleter<T>
        > NullCopier;

    typedef CreationSupervisor<
        Bikes::SafetyCloner<T>, 
        Bikes::NullCreator<T>, 
        Bikes::SafetyDeleter<T>
        > NullCloner;
    
    typedef CreationSupervisor<
        Bikes::NullCloner<T>, 
        Bikes::NullCreator<T>, 
        Bikes::SafetyDeleter<T>
        > NullDeleter;

    typedef CreationSupervisor<
        Bikes::NullCloner<T>, 
        Bikes::NullCreator<T>, 
        Bikes::NullDeleter<T>
        > Null;

};

template<class T>
class SimpleCopyingSupervisor: 
	public CreationSupervisor<SimpleCopier<T>,SimpleCreator<T>,SimpleDeleter<T> >
{
};

template<class T>
class SafetyCopyingSupervisor:
    public CreationSupervisor<SafetyCopier<T>, SimpleCreator<T>, SafetyDeleter<T> >
{
};

template<class T>
class SimpleCloningSupervisor :
	public CreationSupervisor<SimpleCloner<T>, SimpleCreator<T>, SimpleDeleter<T> >
{
};

template<class T>
class SafetyCloningSupervisor :
    public CreationSupervisor<SafetyCloner<T>, SimpleCreator<T>, SafetyDeleter<T> >
{
};


template<class T>
class NullCloningSupervisor :
    public CreationSupervisor<SafetyCloner<T>, NullCreator<T>, SafetyDeleter<T> >
{
};




}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONSUPERVISOR_H
