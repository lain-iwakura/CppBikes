#include <Bikes/SequenceElement.h>
#include <Bikes/Sequence.h>

namespace Bikes
{
    
BaseSequenceElement::~BaseSequenceElement()
{
}

void BaseSequenceElement::willBeChanged()
{
    if (const BaseSequence* seq = getSequence())
    {
        seq->elementWillBeChanged(getIndex());
    }
}

void BaseSequenceElement::changed()
{
    if (const BaseSequence* seq = getSequence())
    {
        seq->elementChanged(getIndex());
    }
}

}