#include <Bikes/SequenceElement.h>
#include <Bikes/Sequence.h>

namespace Bikes
{
    
BaseSequenceElement::~BaseSequenceElement()
{
}

void BaseSequenceElement::startChanging()
{
    if (const BaseSequence* seq = getSequence())
    {
        seq->elementWillBeChanged(getIndex());
    }
}

void BaseSequenceElement::endChanging()
{
    if (const BaseSequence* seq = getSequence())
    {
        seq->elementChanged(getIndex());
    }
}

}