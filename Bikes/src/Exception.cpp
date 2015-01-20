#include <Bikes/Exception.h>



BikesException::BikesException() :
_msg("BikesException : Unknown error"),
_final(true)
{
}

BikesException::BikesException(const std::string& exceptionMessage) :
_msg("BikesException : " + exceptionMessage),
_final(true)
{
}

BikesException::BikesException(const std::string& exceptionName, const std::string& exceptionMessage) :
_msg(
"BikesException : " +
(exceptionMessage.empty() ? (exceptionName) : (
exceptionName + " : " + exceptionMessage))
),
_final(false)
{
}

BikesException::~BikesException() throw()
{
}

const char* BikesException::what() const throw()
{
    return _msg.c_str();
}

const std::string& BikesException::messageString() const throw()
{
    return _msg;
}

bool BikesException::isFinal() const throw()
{
    return _final;
}

