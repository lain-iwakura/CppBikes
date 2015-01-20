#ifndef INCLUDE_BIKES_STREAM_STREAMEXCEPTION_H
#define INCLUDE_BIKES_STREAM_STREAMEXCEPTION_H

#include <Bikes/Exception.h>

namespace Bikes{

class StreamPositionSaver;

namespace Exception{
    
class StreamException : public BikesException
{
public:

    StreamException();

    StreamException(
        const std::string& exceptionMessage,

        bool _positionRestored
        );
        
    bool isFinal() const throw();

    bool positionRestored() const throw();

protected:

    StreamException(
        const std::string& exceptionName,
        const std::string& exceptionMessage,
        bool _positionRestored
        );

    bool _posRest;

private:
    const bool _final;
    friend class StreamPositionSaver;
};

#define BIKES_STREAMEXCEPTION_DECLDEF(EsceptionName,BaseException)             \
class ExceptionName : public BaseException                                     \
{                                                                              \
public:                                                                        \
                                                                               \
    ExceptionName():                                                           \
        BaseException("ExceptionName","",false),                               \
        _final(true)                                                           \
    {}                                                                         \
                                                                               \
    ExceptionName(                                                             \
        const std::string& exceptionMessage,                                   \
        bool _positionRestored                                                 \
        ):                                                                     \
        BaseException("ExceptionName", exceptionMessage, _positionRestored),   \
        _final(true)                                                           \
    {}                                                                         \
                                                                               \
    bool isFinal() const throw()                                               \
    {                                                                          \
        return _final;                                                         \
    }                                                                          \
                                                                               \
protected:                                                                     \
                                                                               \
    ExceptionName(                                                             \
        const std::string& exceptionName,                                      \
        const std::string& exceptionMessage,                                   \
        bool _positionRestored                                                 \
        ):                                                                     \
        BaseException(                                                         \
            "ExceptionName : " + exceptionName,                                \
            exceptionMessage,                                                  \
            _positionRestored                                                  \
            ),                                                                 \
            _final(false)                                                      \
    {}                                                                         \
                                                                               \
private:                                                                       \
    const bool _final;                                                         \
};


BIKES_STREAMEXCEPTION_DECLDEF(UnexpectedStreamType, StreamException)

} //Exception

namespace Inner{

template<class StreamType, class StreamerT>
void throwUnexpectedStreamType(
    const StreamType& obj, 
    const StreamerT& str, 
    bool posRestored
    )
{
    throw UnexpectedStreamType(
        std::string(typeid(obj).name()) +
        " for " +
        std::string(typeid(str).name()),
        posRestored
        );
}

} // Inner
} // Bikes

#endif
