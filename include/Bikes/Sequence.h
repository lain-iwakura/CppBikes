#ifndef INCLUDEBIKES_SEQUENCE_H
#define INCLUDEBIKES_SEQUENCE_H

#include <vector>
#include <Bikes/Types.h>

namespace Bikes
{

class BaseSequenceElement;

class BaseSequence
{
public:
    virtual ~BaseSequence();

protected:

    virtual void elementWillBeChanged(sznum i) const = 0;

    virtual void elementChanged(sznum i) const = 0;      

    friend class BaseSequenceElement;
};


class InnerSequence
{
public:

    virtual ~InnerSequence(){}

protected:

    void call_sequenceElementWillBeChanged(BaseSequenceElement* el, sznum ich) const;

    void call_sequenceElementChanged(BaseSequenceElement* el, sznum ich) const;

    void call_sequenceElementWillBeRemoved(BaseSequenceElement* el, sznum ich) const;

    void call_sequenceElementInserted(BaseSequenceElement* el, sznum ich) const;

    void call_inserted(BaseSequenceElement* el);

    void call_willBeRemoved(BaseSequenceElement* el);


};

#define INNERBIKES_SEQUENCE_ACTION(ACTION, iEl)                                             \
{   for (sznum i = 0; i < (iEl); i++) call_##ACTION(_arr[i], iEl);                          \
    for (sznum i = (iEl)+1; i < _arr.size(); i++) call_##ACTION(_arr[i], iEl);               \
    ACTION(iEl); }


template<class T>
class Sequence : public BaseSequence, private InnerSequence
{
public:

    Sequence()
    {
    }

    Sequence(const Sequence<T>& seq)
    {
        for (sznum i = 0; i < seq._arr.size(); i++)
            take(new T(*seq._arr[i]));
    }

    virtual ~Sequence()
    {        
        for (sznum i = 0; i < _arr.size(); i++)
            delete _arr[i];
    }

    Sequence<T>& operator = (const Sequence<T>& seq)
    {
        clear();
        for (sznum i = 0; i < seq._arr.size(); i++)
            take(new T(*seq._arr[i]));
        return *this;
    }

    Sequence<T>& operator += (const T& el)
    {
        take(new T(el));
        return *this;
    }

    Sequence<T>& operator += (T* el)
    {
        take(el);
        return *this;
    }

    Sequence<T>& operator += (const Sequence<T>& seq)
    {
        for (sznum i = 0; i < seq._arr.size(); i++)
            take(new T(*seq._arr[i]));
        return *this;
    }

    void push_back(const T& el)
    {   
        take(new T(el));
    }

    void insert(const T& el, sznum iEl)
    {
        take(new T(el), iEl);
    }

    void take(T *el)
    {
        if (el)
        {
            if (el->_seq)
                el->_seq->pass(el->_iEl);            

            sznum n = _arr.size();
            el->_seq = this;
            el->_iEl = n;
            _arr.push_back(el);

            call_inserted(el);

            INNERBIKES_SEQUENCE_ACTION(sequenceElementInserted,n)            
        }
    }

    void take(T *el, sznum iEl)
    {
        if (el)
        {
            sznum n = _arr.size();

            if (iEl > n)
                iEl = n;

            if (el->_seq)
                el->_seq->pass(el->_iEl);
           
            el->_seq = this;
            el->_iEl = iEl;

            _arr.insert(_arr.begin()+iEl, el);
                        
            call_inserted(el);

            INNERBIKES_SEQUENCE_ACTION(sequenceElementInserted, iEl)
            
        }
    }

    T* pass(sznum iEl)
    {
        if (iEl < _arr.size())
        {
            T* el = _arr[iEl];           

            INNERBIKES_SEQUENCE_ACTION(sequenceElementWillBeRemoved, iEl)

            call_willBeRemoved(el);
                
            el->_iEl = 0;
            el->_seq = 0;

            _arr.erase(_arr.begin() + iEl);            
        }
        return 0;
    }

    void erase(sznum iEl)
    {
        if (T* el = pass(iEl))
            delete el;
    }

    void clear()
    {
        for (sznum i = 0; i < _arr.size(); i++)
            delete _arr[i];
        _arr.clear();
    }

    sznum size() const
    {
        return _arr.size();
    }

    sznum count() const
    {
        return _arr.size();
    }

    T& operator [](sznum iEl)
    {
        return *_arr[iEl];
    }

    const T& operator [](sznum iEl) const
    {
        return *_arr[iEl];
    }

    T& at(sznum iEl)
    {
        return *_arr[iEl];
    }

    const T& at(sznum iEl) const
    {
        return *_arr[iEl];
    }


    const std::vector<T*>& data() const
    {
        return _arr;
    }



protected:

    virtual void sequenceElementWillBeChanged(sznum ich) const
    {
    }

    virtual void sequenceElementChanged(sznum ich) const
    {
    }

    virtual void sequenceElementWillBeRemoved(sznum ich) const
    {
    }

    virtual void sequenceElementInserted(sznum ich) const
    {
    }

    
private:

    void elementWillBeChanged(sznum ich) const
    {
        if ( ich < _arr.size())
            INNERBIKES_SEQUENCE_ACTION(sequenceElementWillBeChanged, ich)        
    }

    void elementChanged(sznum ich) const
    {
        if (ich < _arr.size())
            INNERBIKES_SEQUENCE_ACTION(sequenceElementChanged, ich)
    }

    std::vector<T*> _arr;
};

}

#endif
