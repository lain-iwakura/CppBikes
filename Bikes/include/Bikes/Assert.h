#ifndef INCLUDE_BIKES_STREAM_ASSERT_H
#define INCLUDE_BIKES_STREAM_ASSERT_H

#include <Bikes/Exception.h>
#include <Bikes/TypeTools/Compare.h>
#include <typeinfo>


#define BIKES_COMPILE_TIME_ASSERT(assertion)                                   \
    ::Bikes::CompileTimeAssert<(assertion)!=0>();

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


namespace Bikes{
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
    const bool _final;
};

#define BIKES_ASSERTEXCEPTION_DECLDEF(ExceptionName, AsertionFaildName)\
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
        const bool _final;                                                     \
    };

BIKES_ASSERTEXCEPTION_DECLDEF(InvalidInstance, AssertionFaild)

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
struct CompileTimeAssert;

template<>
struct CompileTimeAssert<true> {};

inline void assertWithException(
    bool assertion, 
    const std::string& msg = std::string(),
    const std::string& atFile = std::string(),
    int atLine = -1
    )
{
    if(!assertion)
        throw Exception::AssertionFaild(msg,atFile,atLine);
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
