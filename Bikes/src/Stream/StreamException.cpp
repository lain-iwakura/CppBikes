#include <Bikes/Stream/StreamException.h>

namespace Bikes{
namespace Exception{


StreamException::StreamException():
    BikesException("StreamException",""),
    _posRest(false),
    _final(true)
{
}

StreamException::StreamException(
    const std::string& exceptionMessage, 
    bool _positionRestored):
    BikesException("StreamException", exceptionMessage),
    _posRest(_positionRestored),
    _final(true)
{
}

StreamException::StreamException(
    const std::string& exceptionName, 
    const std::string& exceptionMessage, 
    bool _positionRestored):
    BikesException("StreamException : " + exceptionName, exceptionMessage),
    _posRest(_positionRestored),
    _final(false)
{
}

bool StreamException::isFinal() const throw()
{
    return _final;
}

bool StreamException::positionRestored() const throw()
{
    return _posRest;
}

}
}