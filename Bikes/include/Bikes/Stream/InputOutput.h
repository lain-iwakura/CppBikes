#ifndef INCLUDE_BIKES_STREAM_INPUTOUTPUT_H
#define INCLUDE_BIKES_STREAM_INPUTOUTPUT_H

#include <Bikes/Types.h>

namespace Bikes
{

class InputOutput
{
public:

    virtual ~InputOutput()
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

    virtual bool setPosition(sznum pos)
    {
        return false;
    }

    virtual sznum getPosition() const
    {
        return 0;
    }

    //... 
};


}
#endif // <- INCLUDE_BIKES_STREAM_INPUTOUTPUT_H
