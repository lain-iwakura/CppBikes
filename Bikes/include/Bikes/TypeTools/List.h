#ifndef INCLUDE_BIKES_TYPETOOLS_LIST_H
#define INCLUDE_BIKES_TYPETOOLS_LIST_H

#include <Bikes/TypeTools/NullTypes.h>
#include <Bikes/MacrosBikes.h>
#include <Bikes/TypeTools/Stack.h>


namespace Bikes{
namespace TT{

template<MACROSBIKES_CT9_DEFTYPE(NullType)>
struct TypeList;




template<MACROSBIKES_CT9>
struct TypeList
{
    typedef MACROSBIKES_TYPESTACK_T9 Stack;

    enum{
        count = TypeStack::Length<Stack>::result
    };
};

// 
// template<class T, MACROSBIKES_CT9>
// struct TypeStackElement<TypeList<MACROSBIKES_TT9>, T >
// {
//     typedef typename T HeadType;
//     typedef typename TypeList<MACROSBIKES_TT9>::TypeStack TailType;
// };
} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_LIST_H
