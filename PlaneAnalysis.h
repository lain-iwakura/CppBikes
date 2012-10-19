#pragma once
#include "AbstractLine.h"



bool PointInCircuit(Point p, AlPolyline *circuit, bool closed=true); // -
bool PointInCircuit(Point p, List<Point> *circuit, bool closed=true); // +
List<int> MaxCircuit_i(List<Point> *ps); // -
List<Point> MaxCircuit(List<Point> *ps); // ?

TMETRIC CircuitArea(List<Point> &ps); // +
TMETRIC CircuitAreaABS(List<Point> &ps); // +
TMETRIC APolylineCircuitArea(AlPolyline &pl); // +
TMETRIC APolylineCircuitAreaABS(AlPolyline &pl); // +


class AlPolylineCircuit: public AlPolyline
{
public:
	AlPolylineCircuit():AlPolyline(){iline=0;}
	AlPolylineCircuit(const AlPolylineCircuit &alpc):AlPolyline(alpc){iline=0;}
	AlPolylineCircuit(const AlPolyline &pl):AlPolyline(pl){iline=0;}
	AbstractLine * currentLine(){return At(iline);}
	AbstractLine * nextLine(){return At(iRelative(1));}
	AbstractLine * relativeLine(int di){return At(iRelative(di));}
	AbstractLine * relativeLine(int i, int di){return At(iRelative(i,di));}
	AbstractLine * relativeLine(AbstractLine *al, int di){return At(iRelative(iLine(al),di));}
	
	void setCurrent(int i)
	{
		if(Count()==0) {iline=0; return;}
		while(i>=Count()) i-=Count();
		while(i<0) i+=Count();
		iline=i;
	}
	bool setCurrent(AbstractLine *al)
	{
		for(int i=0; i<Count(); i++) if(At(i)==al) {iline=i; return true;}
		return false;
	}

	int iRelative(int di){return iRelative(iline,di);}
	int iRelative(int i, int di)
	{
		if(Count()==0) return -1;
		int ri=i+di;
		while(ri>=Count()) ri-=Count();
		while(ri<0) ri+=Count();
		return ri;
	}
	int iLine(AbstractLine *al)
	{
		if(Count()==0) return -1;
		for(int i=0; i<Count(); i++) if(At(i)==al) return i;	
		return -1;
	}
private:
	int iline;
};


class AlCircuit: public AbstractLine
{
public:

	enum LineMarkers
	{
		LM_TRAVERSE,
		LM_DEL,
		LM_NOINTERSECTIONS,
		_LM_COUNT
	};

	AlCircuit();
	AlCircuit(const AlCircuit &acirc);
	~AlCircuit();
	void Clear();
	List<PhantomObject<AlPolylineCircuit>> OutCircuits;
	List<PhantomObject<AlPolylineCircuit>> InCircuits;
	void operator +=(const AlPolyline &polycirc);
	void operator -=(AlPolyline &polycirc);
	
	//void OptAdd(const AlPolyline &polycirc);
	
};