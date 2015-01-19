#ifndef INCLUDE_BIKES_STREAM_ASSERT_H
#define INCLUDE_BIKES_STREAM_ASSERT_H

#include <Bikes/Exception.h>
#include <Bikes/TypeTools/Compare.h>
#include <typeinfo>

namespace Bikes{

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


#define BIKES_CHECK_INSTANCE(instancePtr)                                      \
    ::Bikes::checkInstance(                                                    \
        (instancePtr),                                                         \
        std::string(#instancePtr) + " as instance of " +                       \
        std::string(typeid((instancePtr)).name()),                             \
        __FILE__,                                                              \
        __LINE__                                                               \
        );

#define BIKES_COMPILE_TIME_ASSERT(assertion) ::Bikes::CompileTimeAssert<(assertion)!=0>();

#define BIKES_ASSERT_WITH_EXCEPTION(assertion)                                 \
    ::Bikes::assertWithException(                                              \
        (assertion),                                                           \
        std::string(#assertion) + " is not true",                              \
        __FILE__,                                                              \
        __LINE__                                                               \
        );



#endif // <- INCLUDE_BIKES_STREAM_ASSERT_H
