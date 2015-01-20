#include <Bikes/Exception.h>



BikesException::BikesException() :
_msg("BikesException : Unknown error")
{
}

BikesException::BikesException(const std::string& exceptionMessage) :
_msg("BikesException : " + exceptionMessage)
{
}

BikesException::BikesException(const std::string& exceptionName, const std::string& exceptionMessage) :
_msg(
"BikesException : " +
(exceptionMessage.empty() ? (exceptionName) : (
exceptionName + " : " + exceptionMessage))
)
{
}

BikesException::~BikesException() throw()
{
}

const char* BikesException::what() const throw()
{
    return _msg.c_str();
}

const std::string& BikesException::whatStr() const throw()
{
    return _msg;
}


