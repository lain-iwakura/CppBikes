#include <Bikes/Assert.h>
#include <sstream>

namespace Bikes{
namespace Exception{
    

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

int AssertionFaild::line() const throw()
{
    return _line;
}

const std::string& AssertionFaild::file() const throw()
{
    return _file;
}


}
}