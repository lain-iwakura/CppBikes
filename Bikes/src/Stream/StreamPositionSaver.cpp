#include <Bikes/Stream/StreamPositionSaver.h>
#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Stream/StreamException.h>

namespace Bikes
{

StreamPositionSaver::StreamPositionSaver(InputOutput* io) :
    _io(io),
    _spos(io->getPosition())
{
//     while (ByteStream* bs = dynamic_cast<ByteStream*>(_io))
//         _io = bs->getIO();
}

bool StreamPositionSaver::tryRestore(Exception::StreamException& strEx) const
{
    return strEx._posRest = tryRestore();
}

bool StreamPositionSaver::tryRestore() const
{
    return _io->isRandomAccess() &&
        ((_spos == _io->getPosition()) || _io->setPosition(_spos));
}

void StreamPositionSaver::save()
{
    _spos = _io->getPosition();
}

}