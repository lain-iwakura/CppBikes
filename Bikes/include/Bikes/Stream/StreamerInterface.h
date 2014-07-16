#ifndef PREBIKES_STREAMERINTERFACE_H
#define PREBIKES_STREAMERINTERFACE_H

namespace Bikes
{

class ByteStream;

class StreamerInterface
{
public:

    virtual ~StreamerInterface()
    {
    }

    virtual void read(ByteStream& bs) const = 0;

    virtual void write(ByteStream& bs) const = 0;
};

}


#endif
