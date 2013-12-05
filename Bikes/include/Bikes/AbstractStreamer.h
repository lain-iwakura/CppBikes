#ifndef BIKES_ABSTRACTSTREAMER_H
#define BIKES_ABSTRACTSTREAMER_H

namespace Bikes
{

class ByteStream;

class AbstractStreamer
{
public:
    virtual ~AbstractStreamer(){}
    virtual void read(ByteStream& bs) const = 0;
    virtual void write(ByteStream& bs) const = 0;
};

}


#endif
