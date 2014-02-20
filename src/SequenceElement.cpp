#include <bikes/SequenceElement.h>


namespace Bikes
{
       


    SequenceElement::SequenceElement() :
        _iEl(0),
        _seq(0)
    {

    }

    SequenceElement::~SequenceElement()
    {
        //?
    }

    Bikes::sznum SequenceElement::getIndex() const
    {
        return _iEl;
    }

    const Sequence* SequenceElement::getSequence() const
    {
        return _seq;
    }

}