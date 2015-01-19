#include <Bikes/Exception.h>
#include <sstream>


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


namespace Bikes{
namespace Exception{
    
int AssertionFaild::line() const throw()
{
    return _line;
}

const std::string& AssertionFaild::file() const throw()
{
    return _file;
}

bool AssertionFaild::isFinal() const throw()
{
    return _final;
}

AssertionFaild::AssertionFaild(
    const std::string& msg, 
    const std::string& atFile /*= std::string()*/, 
    int atLine /*= -1 */
    ) :
    BikesException("AssertionFaild",msg),
    _file(atFile),
    _line(atLine)
{
    if(!atFile.empty())
    {
        _msg.append(", at file \"" + atFile +"\"");
    }
    if(atLine >= 0)
    {
        _msg.append(", at line ");
        std::ostringstream str;
        str << atLine;
        _msg.append(str.str());
    }
}

AssertionFaild::AssertionFaild() :
    BikesException("AssertionFaild", std::string()),
    _line(-1)
{
}


AssertionFaild::AssertionFaild(
    const std::string& exceptionName,
    const std::string& msg,
    const std::string& atFile,
    int atLine
    ):
    BikesException("AssertionFaild : " + exceptionName, msg)
{
    if (!atFile.empty())
    {
        _msg.append(", at file \"" + atFile + "\"");
    }
    if (atLine >= 0)
    {
        _msg.append(", at line ");
        std::ostringstream str;
        str << atLine;
        _msg.append(str.str());
    }
}

}
}