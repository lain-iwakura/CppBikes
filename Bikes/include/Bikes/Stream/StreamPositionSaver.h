#ifndef INCLUDE_BIKES_STREAM_STREAMPOSITIONSAVER_H
#define INCLUDE_BIKES_STREAM_STREAMPOSITIONSAVER_H

#include <Bikes/Types.h>

namespace Bikes{

namespace Exception{
class StreamException;
}

class InputOutput;

class StreamPositionSaver
{
public:

    StreamPositionSaver(InputOutput* io);
    
    void save();

    bool tryRestore() const;

    bool tryRestore(Exception::StreamException& strEx) const;

private:
    InputOutput* _io;
    sznum _spos;
};



}

#endif 