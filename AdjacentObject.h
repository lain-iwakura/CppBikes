#ifndef ADJACENTOBJECT_H
#define ADJACENTOBJECT_H
//#include "ContainerInterface.h"

#define ADJACENTOBJECT_DEFFUNC(C_this) C_this * next(){return (C_this*)AdjacentObject::next();} C_this * previous(){return (C_this*) AdjacentObject::previous();} C_this * nextN(int n){return (C_this*)AdjacentObject::nextN(n);} C_this * previousN(int n){return (C_this*)AdjacentObject::previousN(n);}


class AdjacentObject
{
public:
	AdjacentObject(AdjacentObject *prv=0, AdjacentObject *nxt=0):_previous(prv),_next(nxt)
	{
		if(prv)
		{	
			if(prv->_next) prv->_next->_previous=0;
			prv->_next=this;
		}
		if(nxt)
		{
			if(nxt->_previous) nxt->_previous->_next=0;
			nxt->_previous=this;
		}
	}
	AdjacentObject(const AdjacentObject &aobj):_previous(0),_next(0){}
	~AdjacentObject(){detach();}

	void operator =(const AdjacentObject &aobj){}

	void setNext(AdjacentObject &Next){setNext(&Next);}
	void setNext(AdjacentObject *Next)
	{
		if(_next) _next->_previous=0;
		_next=Next;
		if(Next) 
		{
			if(Next->_previous) Next->_previous->_next=0;
			Next->_previous=this;
		}
	}

	void setPrevious(AdjacentObject &Previous){setPrevious(&Previous);}
	void setPrevious(AdjacentObject *Previous)
	{
		if(_previous) _previous->_next=0;
		_previous=Previous;
		if(Previous) 
		{
			if(Previous->_next) Previous->_next->_previous=0;
			Previous->_next=this;
		}
	}

	void insertAsNext(AdjacentObject &Previous)
	{
		setNext(Previous._next);
		setPrevious(&Previous);		
	}

	void insertAsPrevious(AdjacentObject &Next)
	{
		setPrevious(Next._previous);
		setNext(&Next);		
	}

	void detachJ()
	{
		if(_next!=0&&_previous!=0) _previous->setNext(_next);
		else detach();
	}
	void detach()
	{
		if(_next){_next->_previous=0;_next=0;}
		if(_previous){_previous->_next=0;_previous=0;}
	}

	void SimpleInvert() 
	{
		AdjacentObject* b=_next;
		_next=_previous;
		_previous=b;
	}

	void operator &=( AdjacentObject &aobj) {setNext(aobj);}

	AdjacentObject* next(){return _next;}
	AdjacentObject* previous(){return _previous;}

	AdjacentObject* nextN(int n)
	{
		if(n<0) return previousN(-n);
		AdjacentObject *r=this;
		for(int i=0; i<n; i++)
		{		
			if(r) r=r->_next;
			else  break;
		}
		return r;
	}

	AdjacentObject* previousN(int n)
	{
		if(n<0) return nextN(-n);
		AdjacentObject *r=this;
		for(int i=0; i<n; i++)
		{		
			if(r) r=r->_previous;
			else  break;
		}
		return r;
	}

private:
	AdjacentObject *_next;
	AdjacentObject *_previous;
};


// class AdjacentContainer: public List<AdjacentObject*>
// {
//  	AdjacentContainer():List<AdjacentObject*>(){}
// 	
// };


#endif