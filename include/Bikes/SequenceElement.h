#ifndef INCLUDEBIKES_SEQUENCEELEMENT_H
#define INCLUDEBIKES_SEQUENCEELEMENT_H


#include <Bikes/Types.h>
#include <Bikes/Sequence.h>


namespace Bikes
{


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

    virtual void sequenceElementInserted(sznum iEl)
    {
    }

    virtual void sequenceElementWillBeRemoved(sznum iEl)
    {
    }

    virtual void inserted()
    {
    }

    virtual void willBeRemoved()
    {
    }

    void startChanging();

    void endChanging();

    friend class InnerSequence;
};


template<class T>
class AbstractSequenceElement : public BaseSequenceElement
{
public:

    typedef Sequence<T> MySequence;

    AbstractSequenceElement():
        _iEl(0),
        _seq(0)
    {
    }

    virtual ~AbstractSequenceElement()
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

    const T* getAt(sznum iEl) const
    {
        if (_seq && iEl < _seq->size())
            return &(_seq->at(iEl));
        return 0;
    }
    
    virtual T* clone() const = 0;

private:
    Sequence<T>* _seq;
    sznum _iEl;    
    
    friend class Sequence<T>;    
};

template<class T>
class SequenceElement : public AbstractSequenceElement<T>
{
public:

    virtual ~SequenceElement()
    {
    }

    virtual T* clone() const
    {
        if (const T* el = dynamic_cast<const T*>(this))
            return new T(*el);
        return 0;
    }
};


}

#endif