#ifndef INCLUDE_BIKES_BIKESEXCEPTION_H
#define INCLUDE_BIKES_BIKESEXCEPTION_H

#include <stdexcept>
#include <string>


namespace Bikes{
namespace Exception{

class Base: public std::exception
{
public:

    Base():
        _queue(0)
    {}
     
    Base(const std::string& exceptionMessage):
        _msg(exceptionMessage),
        _queue(0)
    {}

    
    virtual ~Base() throw()    
    {
        if (_queue)
            delete _queue;
    }

    const char* what() const throw();

    const std::string& whatStr() const throw();

    template<class ExceptionT>
    const ExceptionT* find() const
    {
        if (const ExceptionT* e = dynamic_cast<const ExceptionT*>(this))
            return e;
        if (_queue)
            return _queue->find<ExceptionT>();
        return 0;
    }

    template<class ExceptionT>
    ExceptionT* find()
    {
        if (ExceptionT* e = dynamic_cast<ExceptionT*>(this))
            return e;
        if (_queue)
            return _queue->find<ExceptionT>();
        return 0;
    }

    void addGeneratedException()
    {
    }

protected:

    Base(
        const std::string& exceptionName, 
        const std::string& exceptionMessage
        );

    std::string _msg;

private:
    Base *_queue;
};

}
}

class BikesException: public std::exception
{
public:

    BikesException();

    BikesException(const std::string& exceptionMessage);
    
    virtual ~BikesException() throw();

    const char* what() const throw();

    const std::string& whatStr() const throw();

protected:

    BikesException(
        const std::string& exceptionName, 
        const std::string& exceptionMessage
        );

    std::string _msg;
};

#define BIKES_EXCEPTION_DECLDEF(ExceptionName,BeseException)                   \
class ExceptionName : public BeseException                                     \
{                                                                              \
public:                                                                        \
    ExceptionName() :                                                          \
        BeseException(#ExceptionName, std::string())                           \
    {}                                                                         \
                                                                               \
    ExceptionName(const std::string& exceptionMessage) :                       \
        BeseException(#ExceptionName, exceptionMessage)                        \
    {}                                                                         \
                                                                               \
protected:                                                                     \
    ExceptionName(                                                             \
        const std::string& exceptionName,                                      \
        const std::string& exceptionMessage                                    \
        ) :                                                                    \
        BeseException(                                                         \
            std::string(#ExceptionName) + " : " + exceptionName,               \
            exceptionMessage                                                   \
            )                                                                  \
    {}                                                                         \
};          

namespace Bikes{
namespace Exception{
    BIKES_EXCEPTION_DECLDEF(ProhibitedAction, BikesException);
} // Exception
} // Bikes


#endif // <- INCLUDE_BIKES_BIKESEXCEPTION_H
