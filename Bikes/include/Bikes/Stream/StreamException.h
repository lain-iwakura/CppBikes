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

    bool positionRestored() const throw();

protected:

    StreamException(
        const std::string& exceptionName,
        const std::string& exceptionMessage,
        bool _positionRestored
        );

    bool _posRest;

private:
    friend class StreamPositionSaver;
};

#define BIKES_STREAMEXCEPTION_DECLDEF(EsceptionName,BaseException)             \
class ExceptionName : public BaseException                                     \
{                                                                              \
public:                                                                        \
                                                                               \
    ExceptionName():                                                           \
        BaseException("ExceptionName","",false)                                \
    {}                                                                         \
                                                                               \
    ExceptionName(                                                             \
        const std::string& exceptionMessage,                                   \
        bool _positionRestored                                                 \
        ):                                                                     \
        BaseException("ExceptionName", exceptionMessage, _positionRestored)    \
    {}                                                                         \
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
            )                                                                  \
    {}                                                                         \
                                                                               \
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
