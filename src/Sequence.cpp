#include <Bikes/Sequence.h>
#include <Bikes/SequenceElement.h>

namespace Bikes
{


BaseSequence::~BaseSequence()
{

}

void InnerSequence::call_sequenceElementWillBeChanged(BaseSequenceElement* el, sznum ich) const
{
    el->sequenceElementWillBeChanged(ich);
}

void InnerSequence::call_sequenceElementChanged(BaseSequenceElement* el, sznum ich) const
{
    el->sequenceElementChanged(ich);
}

void InnerSequence::call_sequenceElementWillBeRemoved(BaseSequenceElement* el, sznum ich) const
{
    el->sequenceElementWillBeRemoved(ich);
}

void InnerSequence::call_sequenceElementInserted(BaseSequenceElement* el, sznum ich) const
{
    el->sequenceElementInserted(ich);
}

void InnerSequence::call_inserted(BaseSequenceElement* el)
{
    el->inserted();
}

void InnerSequence::call_willBeRemoved(BaseSequenceElement* el)
{
    el->willBeRemoved();
}


}