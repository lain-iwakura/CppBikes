#ifndef INCLUDEBIKES_SEQUENCEELEMENT_H
#define INCLUDEBIKES_SEQUENCEELEMENT_H


#include <Bikes/Types.h>


namespace Bikes
{

template<class T>
class SequenceElement
{
public:

    SequenceElement() :
        _iEl(0),
        _seq(0)
    {
    }

    virtual ~SequenceElement()
    {
        //?
    }

    sznum getIndex() const
    {
        return _iEl;
    }

    const Sequence<T>* getSequence() const
    {
        return _seq;
    }

    const T* getRight() const
    {
        if (_seq && _iEl < _sec->size() - 1)
            return &((*_seq)[_iEl + 1]);
        return 0;
    }

    const T* getLeft() const
    {
        if (_seq && _iEl > 0)
            return &((*_seq)[_iEl - 1]);
        return 0;
    }


protected:


    virtual void sequenceElementWillBeChanged(const T& el)
    {
    }

    virtual void sequenceElementChanged(const T& el)
    {
    }

    virtual void sequenceElementWillBeAdded(const T& el)
    {
    }

    virtual void sequenceElementAdded(const T& el)
    {
    }

    virtual void sequenceElementWillBeRemoved(const T& el)
    {
    }

    virtual void sequenceElementRemoved(const T& el)
    {
    }


    void willBeChanged()
    {
        _seq->elementWillBeChanged(_iEl);
    }
    
    void changed() 
    {
        _seq->elementChanged(_iEl);
    }

private:
    sznum _iEl;
    const Sequence<T>* _seq;

    friend class BaseSequence;
};

}

#endif