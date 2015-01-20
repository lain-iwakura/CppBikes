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

    const std::string& whatStr() const throw();

protected:

    BikesException(
        const std::string& exceptionName, 
        const std::string& exceptionMessage
        );

    std::string _msg;
};

#define BIKES_EXCEPTION_DECLDEF(ExceptionName, BeseException)                  \
class ExceptionName : public BeseException                                     \
{                                                                              \
public:                                                                        \
    ExceptionName() :                                                          \
        BeseException(#ExceptionName, std::string()),                          \
    {}                                                                         \
                                                                               \
    ExceptionName(const std::string& exceptionMessage) :                       \
        BeseException(#ExceptionName, exceptionMessage),                       \
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

} // Exception
} // Bikes


#endif // <- INCLUDE_BIKES_BIKESEXCEPTION_H
