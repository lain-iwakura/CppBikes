#ifndef INCLUDE_BIKES_TYPECOLLECTING_NULLTYPES_H
#define INCLUDE_BIKES_TYPECOLLECTING_NULLTYPES_H

namespace Bikes
{
//==============================================================================
struct NullType;
//------------------------------------------------------------------------------
struct EmptyType{};
//==============================================================================
namespace Inner{
//------------------------------------------------------------------------------
typedef char SmallType;
struct BigType { char c[2]; };
//------------------------------------------------------------------------------
} //Inner
//==============================================================================
} // Bikes
#endif // <- INCLUDE_BIKES_TYPECOLLECTING_NULLTYPES_H
