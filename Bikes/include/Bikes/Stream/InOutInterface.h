#ifndef BIKES_INOUTINTERFACE_H
#define BIKES_INOUTINTERFACE_H

#include <Bikes/Types.h>

namespace Bikes
{

class InOutInterface
{
public:

    virtual ~InOutInterface()
    {
    }

    virtual void readBytes(char *bt, sznum btSize) = 0;

    virtual void writeBytes(const char *bt, sznum btSize) = 0;

    virtual void prepareForWrite(sznum byteCapacity)
    {
    }

    virtual bool atEnd() const //?
    {
        return false; 
    }

    //... 
};


}
#endif
