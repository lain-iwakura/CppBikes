#ifndef INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
#define INCLUDE_BIKES_CREATION_CREATIONMANAGER_H

#include <Bikes/Creation/Creator.h>
#include <Bikes/Creation/Copier.h>
#include <Bikes/Creation/Deleter.h>

namespace Bikes
{						
//==============================================================================
template<class T>
class CreationManagerInterface: 
    public CreatorInterface<T>,
    public CopierInterface<T>,
    public DeleterInterface<T>
{
public:
    virtual T* create() const = 0;
    virtual T* create(sznum sz) const = 0; // create array
    virtual T* copy(const T* pObj) const = 0;
    virtual T* copy(const T* pObj, sznum sz) const = 0; // create array
    virtual void destroy(const T* pObj) const = 0;
    virtual void destroy(const T* pObj, sznum sz) const = 0; // destroy array

protected:
    virtual ~CreationManagerInterface() {}
private:
    CreationManagerInterface& operator = (const CreationManagerInterface&) { return *this; }
};
//==============================================================================



}	

#endif // <- INCLUDE_BIKES_CREATION_CREATIONMANAGER_H
