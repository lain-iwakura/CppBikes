#include "TypeInfo.h"

namespace Bikes{



Bikes::sznum TypeInfoBase::typeCount()
{
    return _typeCount();
}

sznum& TypeInfoBase::_typeCount()
{
    static sznum tc = 0;
}

}
