#include <Bikes/TypeTools/Info.h>

namespace Bikes{
namespace TT{


Bikes::sznum InfoBase::typeCount()
{
    return _typeCount();
}

sznum& InfoBase::_typeCount()
{
    static sznum tc = 0;
    return tc;
}

} // TT
} // Bikes
