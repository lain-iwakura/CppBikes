#ifndef INCLUDE_BIKES_STREAM_STREAMPOSITIONSAVER_H
#define INCLUDE_BIKES_STREAM_STREAMPOSITIONSAVER_H

#include <Bikes/Types.h>

namespace Bikes{

namespace Exception{
class StreamException;
}

class InOutInterface;

class StreamPositionSaver
{
public:

    StreamPositionSaver(InOutInterface* io);
    
    void save();

    bool tryRestore() const;

    bool tryRestore(Exception::StreamException& strEx) const;

private:
    InOutInterface* _io;
    sznum _spos;
};



}

#endif 