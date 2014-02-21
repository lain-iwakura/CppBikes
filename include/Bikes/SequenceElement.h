#ifndef INCLUDEBIKES_SEQUENCEELEMENT_H
#define INCLUDEBIKES_SEQUENCEELEMENT_H


#include <Bikes/Types.h>


namespace Bikes
{

class BaseSequence;

template<class T>
class Sequence;

class BaseSequenceElement
{
public:

    virtual ~BaseSequenceElement();

    virtual sznum getIndex() const = 0;

    virtual const BaseSequence* getSequence() const = 0;
    
protected:

    virtual void sequenceElementWillBeChanged(sznum iEl)
    {
    }

    virtual void sequenceElementChanged(sznum iEl)
    {
    }

    virtual void sequenceElementAdded(sznum iEl)
    {
    }

    virtual void sequenceElementWillBeRemoved(sznum iEl)
    {
    }

    virtual void inserted()
    {
    }

    virtual void willBePassed()
    {
    }

    void willBeChanged();

    void changed();

    friend class InnerSequence;
};


template<class T>
class SequenceElement : public BaseSequenceElement
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

//     const BaseSequence* getBaseSequence() const
//     {
//         return _seq;
//     }

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



private:
    Sequence<T>* _seq;
    sznum _iEl;    
    
    friend class Sequence<T>;

    
};

}

#endif