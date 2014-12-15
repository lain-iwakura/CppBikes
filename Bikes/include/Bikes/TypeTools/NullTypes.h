#ifndef INCLUDE_BIKES_TYPETOOLS_NULLTYPES_H
#define INCLUDE_BIKES_TYPETOOLS_NULLTYPES_H

namespace Bikes{
namespace TT{
//==============================================================================
struct NullType;
//------------------------------------------------------------------------------
struct EmptyType{};
//==============================================================================
typedef char SmallType;
//------------------------------------------------------------------------------
struct BigType { char c[2]; };
//==============================================================================
} // TT
} // Bikes
#endif // <- INCLUDE_BIKES_TYPETOOLS_NULLTYPES_H
