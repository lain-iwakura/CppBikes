#ifndef INCLUDE_BIKES_STREAM_ISTREAMER_H
#define INCLUDE_BIKES_STREAM_ISTREAMER_H

namespace Bikes
{

class ByteStream;

class IStreamer
{
public:

    virtual ~IStreamer()
    {
    }

    virtual void read(ByteStream& bs) const = 0;

    virtual void write(ByteStream& bs) const = 0;
};

}


#endif // <- INCLUDE_BIKES_STREAM_ISTREAMER_H
