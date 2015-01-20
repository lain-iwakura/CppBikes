#include <Bikes/Stream/StreamException.h>

namespace Bikes{
namespace Exception{


StreamException::StreamException():
    BikesException("StreamException",""),
    _posRest(false)
{
}

StreamException::StreamException(
    const std::string& exceptionMessage, 
    bool _positionRestored):
    BikesException("StreamException", exceptionMessage),
    _posRest(_positionRestored)
{
}

StreamException::StreamException(
    const std::string& exceptionName, 
    const std::string& exceptionMessage, 
    bool _positionRestored):
    BikesException("StreamException : " + exceptionName, exceptionMessage),
    _posRest(_positionRestored)
{
}

bool StreamException::positionRestored() const throw()
{
    return _posRest;
}

}
}