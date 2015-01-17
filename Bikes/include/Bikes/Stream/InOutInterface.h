#ifndef INCLUDE_BIKES_STREAM_INOUTINTERFACE_H
#define INCLUDE_BIKES_STREAM_INOUTINTERFACE_H

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

    virtual bool isRandomAccess() const
    {
        return false;
    }

    bool isSequential() const
    {
        return !isRandomAccess();
    }

    virtual bool setAccessPosition(sznum pos)
    {
        return false;
    }

    virtual sznum getAccessPosition() const
    {
        return 0;
    }

    //... 
};


}
#endif // <- INCLUDE_BIKES_STREAM_INOUTINTERFACE_H
