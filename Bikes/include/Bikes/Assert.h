#ifndef INCLUDE_BIKES_STREAM_ASSERT_H
#define INCLUDE_BIKES_STREAM_ASSERT_H

#include <Bikes/Exception.h>
#include <Bikes/TypeTools/Compare.h>
#include <typeinfo>


#define BIKES_STATIC_ASSERT(assertion)                                         \
    ::Bikes::StaticAssert<(assertion) != 0>();

#define BIKES_ASSERT_WITH_EXCEPTION(assertion)                                 \
    ::Bikes::assertWithException(                                              \
        (assertion),                                                           \
        std::string(#assertion) + " is not true",                              \
        __FILE__,                                                              \
        __LINE__                                                               \
        );

#define BIKES_CHECK_INSTANCE(instancePtr)                                      \
    ::Bikes::checkInstance(                                                    \
        (instancePtr),                                                         \
        std::string(#instancePtr) + " as instance of " +                       \
        std::string(typeid((instancePtr)).name()),                             \
        __FILE__,                                                              \
        __LINE__                                                               \
        );

#define BIKES_ASSERT_NEVER_REACH()                                             \
    ::Bikes::assertWithException(                                              \
        false,                                                                 \
        "never reach assertion failed",                                        \
        __FILE__,                                                              \
        __LINE__                                                               \
        );

namespace Bikes{
namespace Exception{    

class AssertionFailed : public BikesException
{
public:

    AssertionFailed();

    AssertionFailed(
        const std::string& msg, 
        const std::string& atFile = std::string(), 
        int atLine = -1
        );

    const std::string& file() const throw();

    int line() const throw();

protected:

    AssertionFailed(
        const std::string& exceptionName,
        const std::string& msg,
        const std::string& atFile,
        int atLine
        );
        
private:
    std::string _file;
    int _line;
};

#define BIKES_ASSERTEXCEPTION_DECLDEF(ExceptionName, AsertionFaildName)        \
    class ExceptionName : public AsertionFaildName                             \
    {                                                                          \
    public:                                                                    \
        ExceptionName() :                                                      \
        AsertionFaildName(#ExceptionName, std::string(), std::string(), -1)    \
        {}                                                                     \
                                                                               \
        ExceptionName(                                                         \
            const std::string& msg,                                            \
            const std::string& atFile = std::string(),                         \
            int atLine = -1                                                    \
            ) :                                                                \
            AsertionFaildName(#ExceptionName, msg, atFile, atLine)             \
        {}                                                                     \
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
        {}                                                                     \
                                                                               \
    };

BIKES_ASSERTEXCEPTION_DECLDEF(InvalidInstance, AssertionFailed)

} // Exception


namespace Inner{

template<bool boolConversionExists>
struct InstanceChecker
{
    template<class T>
    static bool check(const T& instance)
    {
        return bool(instance);
    }
};

template<>
struct InstanceChecker<false>
{
    template<class T>
    static bool check(const T& instance)
    {
        return 0 != (&(*instance));
    }
};

} // Inner

template<bool>
struct StaticAssert;

template<>
struct StaticAssert<true> {};

inline void assertWithException(
    bool assertion, 
    const std::string& msg = std::string(),
    const std::string& atFile = std::string(),
    int atLine = -1
    )
{
    if(!assertion)
        throw Exception::AssertionFailed(msg,atFile,atLine);
}

template<class T>
void checkInstance(
    const T& instancePtr,
    const std::string& msg = std::string(),
    const std::string& atFile = std::string(),
    int atLine = -1
    )
{
    if (!Inner::InstanceChecker<TT::ConversionExists<T, bool>::result >::check(instancePtr))
        throw Exception::InvalidInstance(msg, atFile, atLine);
}

} // Bikes





#endif // <- INCLUDE_BIKES_STREAM_ASSERT_H
