#ifndef INCLUDE_BIKES_ENUMSTRUCT_H
#define INCLUDE_BIKES_ENUMSTRUCT_H


#define BIKES_ENUMSTRUCT(NAME, ...)                                             \
struct NAME                                                                     \
{                                                                               \
enum EType                                                                      \
    {                                                                           \
        __VA_ARGS__                                                             \
    };                                                                          \
    EType val;                                                                  \
    NAME(const EType& _val) :val(_val){}                                        \
    operator NAME::EType() const{ return val; }                                 \
    bool operator == (const NAME& other) const { return val == other.val; }     \
    bool operator != (const NAME& other) const { return val != other.val; }     \
    bool operator == (const NAME::EType& other) const { return val == other; }  \
    bool operator != (const NAME::EType& other) const { return val != other; }  \
};

#endif