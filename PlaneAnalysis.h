#pragma once
#include "AbstractLine.h"


// Правило заполнения:
//		|***A
//		|***|
//		|***|
//		V***|
//

struct IntersectPoint 	// (Plain analysis)
{
	IntersectPoint(AbstractLine *itAl1=0,AbstractLine *itAl2=0, const Point &itP=p_null, TMETRIC itS1=-1, TMETRIC itS2=-1, bool itRight12=false)
		:al1(itAl1),al2(itAl2),p(itP),s1(itS1),s2(itS2),right12(itRight12)
	{
		al11=0;
		al12=0;
		al21=0;
		al22=0;
	}
	AbstractLine *al1;
	AbstractLine *al2;	

	AbstractLine *al11;
	AbstractLine *al12;
	AbstractLine *al21;
	AbstractLine *al22;

	Point p;
	TMETRIC s1;
	TMETRIC s2;
	bool right12; 

	IntersectPoint Inverted()
	{
		IntersectPoint r(al2,al1,p,s2,s1,!right12);
		r.al11=al21;
		r.al12=al22;
		r.al21=al11;
		r.al22=al12;
		return r;
	}
	
	TMETRIC cS1(AbstractLine *Al1=0) const 
	{
		if(Al1==0||Al1==al1) return s1;
		return s2;	
	}

 	TMETRIC & S1(AbstractLine *Al1=0)
 	{
 		if(Al1==0||Al1==al1) return s1;
 		return s2;	
 	}

	TMETRIC  cS2(AbstractLine *Al1=0) const 
	{
		if(Al1==0||Al1==al1) return s2;
		return s1;	
	}

	TMETRIC & S2(AbstractLine *Al1=0)
	{
		if(Al1==0||Al1==al1) return s2;
		return s1;		
	}

	AbstractLine* AL2(AbstractLine *Al1=0)
	{
		if(Al1==0||Al1==al1) return al2;
		return al1;
	}

	AbstractLine*& AL11(AbstractLine *Al1=0)
	{
		if(Al1==al1||Al1==0) return al11;
		return al21;
	}

	AbstractLine*& AL12(AbstractLine *Al1=0)
	{
		if(Al1==al1||Al1==0) return al12;
		return al22;
	}

	AbstractLine*& AL21(AbstractLine *Al1=0)
	{
		if(Al1==al1||Al1==0) return al21;
		return al11;
	}

	AbstractLine*& AL22(AbstractLine *Al1=0)
	{
		if(Al1==al1||Al1==0) return al22;
		return al12;
	}

	int dLevel(AbstractLine *Al1=0) const 
	{
		if(Al1==0||Al1==al1) return right12?(-1):(1);
		return right12?(1):(-1);
	}

	// Right intersection (right12=true):
	//           1(2)		dLevel=-1;
	//            A  
	//         \\\|		
	//         \\\|
	//   2(2) <---|--- 2(1)
	//         XXX|///
	//         XXX|///	
	//           1(1)
	//
	//
	// Left intersection (right12=false):
	//           1(2)		dLevel=+1;
	//            A  
	//         XXX|///
	//         XXX|///
	//    2(1) ---|---> 2(2)
	//         \\\|
	//         \\\|
	//           1(1)
};

 
List<IntersectPoint> FindIntersectPoints(AbstractLine *al1, AbstractLine *al2);

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

// 	enum LineMarkers
// 	{
// 		LM_TRAVERSE,
// 		LM_DEL,
// 		LM_NOINTERSECTIONS,
// 		_LM_COUNT
// 	};

	struct DebugLineInfo
	{
		DebugLineInfo():Level(-1000),nextLineIndex(-1){}
		int Level;
		//AbstractLine *nextLine;
		int nextLineIndex;
	};

	AlCircuit();
	AlCircuit(const AlCircuit &acirc);
	~AlCircuit();
	void Clear();
 	List< PhantomObject<AlPolylineCircuit> > OutCircuits;
	List< PhantomObject<AlPolylineCircuit> > InCircuits;

	AlPolyline debugPoly;
	ContainerModelMap<DebugLineInfo> dli;



//	List<AlPolylineCircuit> OutCircuits;
//	List<AlPolylineCircuit>> InCircuits;

	void operator +=(const AlPolyline &polycirc);
	void operator -=(AlPolyline &polycirc);
	
	//void OptAdd(const AlPolyline &polycirc);
	
};