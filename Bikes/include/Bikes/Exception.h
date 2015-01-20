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
    const bool _final;
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
    const bool _final;                                                         \
};          



#endif // <- INCLUDE_BIKES_BIKESEXCEPTION_H
