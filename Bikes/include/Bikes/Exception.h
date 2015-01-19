#ifndef INCLUDE_BIKES_BIKESEXCEPTION_H
#define INCLUDE_BIKES_BIKESEXCEPTION_H

#include <stdexcept>
#include <string>


class BikesException: public std::exception
{
public:

    BikesException();

    BikesException(const std::string& exceptionMessage);
    
    virtual ~BikesException() throw();

    const char* what() const throw();

    const std::string& messageString() const throw();

    bool isFinal() const throw();

protected:

    BikesException(
        const std::string& exceptionName, 
        const std::string& exceptionMessage
        );

    std::string _msg;

private:
    bool _final;
};

#define BIKES_EXCEPTION_DECLDEF(ExceptionName, BeseException)                  \
class ExceptionName : public BeseException                                     \
{                                                                              \
public:                                                                        \
    ExceptionName() :                                                          \
        BeseException(#ExceptionName, std::string()),                          \
        _final(true)                                                           \
    {}                                                                         \
                                                                               \
    ExceptionName(const std::string& exceptionMessage) :                       \
        BeseException(#ExceptionName, exceptionMessage),                       \
        _final(true)                                                           \
    {}                                                                         \
                                                                               \
    bool isFinal() const throw()                                               \
    {                                                                          \
        return _final;                                                         \
    }                                                                          \
                                                                               \
protected:                                                                     \
    ExceptionName(                                                             \
        const std::string& exceptionName,                                      \
        const std::string& exceptionMessage                                    \
        ) :                                                                    \
        BeseException(                                                         \
            std::string(#ExceptionName) + " : " + exceptionName,               \
            exceptionMessage                                                   \
            ),                                                                 \
        _final(false)                                                          \
    {}                                                                         \
                                                                               \
private:                                                                       \
    bool _final;                                                               \
};          

       

namespace Bikes {
namespace Exception{

    class AssertionFaild : public BikesException
    {
    public:

        AssertionFaild();

        AssertionFaild(
            const std::string& msg, 
            const std::string& atFile = std::string(), 
            int atLine = -1
            );

        bool isFinal() const throw();

        const std::string& file() const throw();

        int line() const throw();

    protected:

        AssertionFaild(
            const std::string& exceptionName,
            const std::string& msg,
            const std::string& atFile,
            int atLine
            );
        
    private:
        std::string _file;
        int _line;
        bool _final;
    };

#define BIKES_EXCEPTION_ASSERTIONFAILD_DECLDEF(ExceptionName, AsertionFaildName)\
    class ExceptionName : public AsertionFaildName                             \
    {                                                                          \
    public:                                                                    \
        ExceptionName() :                                                      \
        AsertionFaildName(#ExceptionName, std::string(), std::string(), -1),   \
            _final(true)                                                       \
        {}                                                                     \
                                                                               \
        ExceptionName(                                                         \
            const std::string& msg,                                            \
            const std::string& atFile = std::string(),                         \
            int atLine = -1                                                    \
            ) :                                                                \
            AsertionFaildName(#ExceptionName, msg, atFile, atLine),            \
            _final(true)                                                       \
        {}                                                                     \
                                                                               \
        bool isFinal() const throw()                                           \
        {                                                                      \
            return _final;                                                     \
        }                                                                      \
                                                                               \
    protected:                                                                 \
        ExceptionName(                                                         \
            const std::string& exceptionName,                                  \
            const std::string& msg,                                            \
            const std::string& atFile,                                         \
            int atLine                                                         \
            ) :                                                                \
            AsertionFaildName(                                                 \
                std::string(#ExceptionName) + " : " + exceptionName,           \
                msg, atFile, atLine                                            \
                )                                                              \
            ,                                                                  \
            _final(false)                                                      \
        {}                                                                     \
                                                                               \
    private:                                                                   \
        bool _final;                                                           \
    };


    BIKES_EXCEPTION_ASSERTIONFAILD_DECLDEF(InvalidInstance, AssertionFaild)

// Stream Exception ->

    BIKES_EXCEPTION_DECLDEF(StreamException, BikesException)

    BIKES_EXCEPTION_DECLDEF(UnexpectedStreamType, StreamException)

// <- Stream Exception 

} // Exception

namespace Inner{
template<class StreamType, class StreamerT>
void throwUnexpectedStreamType(const StreamType& obj, const StreamerT& str)
{
    throw UnexpectedStreamType(
        std::string(typeid(obj).name()) +
        " for " +
        std::string(typeid(str).name())
        );
}
} // Inner
} // Bikes

#endif // <- INCLUDE_BIKES_BIKESEXCEPTION_H
