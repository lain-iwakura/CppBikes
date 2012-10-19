#pragma once
#ifndef ABSTRACTLINE_H
#define ABSTRACTLINE_H

#include "BasicGeometry.h"
//#include <List>
//#include "DestinationArea.h"
#include "DependedObject.h"
#include "AdjacentObject.h"
#include "SetList.h"
#include "AbstractContainer.h"

#define DEFARCPOLY_N 90
class AbstractLine;
typedef AbstractLine AL;
typedef TransPhantomObject<AbstractLine> TransALine;




//////////////////////////////////////////////////////////////////////////////////
////////////////////////// AbstractLine //////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class AbstractLine: public AdjacentObject, public AbstractContainer
{
public:
	ADJACENTOBJECT_DEFFUNC(AbstractLine)
	
	enum LineType
	{
		LT_NULL,
		LT_LINE,
		LT_ARCLINE,
		LT_POLYLINE,
		LT_LPOINT,
		LT_CIRCUIT,
		_LT_COUNT
	};

	LineType line_type;
	DependedLength<TMETRIC> LEN;	

	AbstractLine(LineType lt=LT_NULL, AbstractLine *parentLine=0);
	AbstractLine(const AbstractLine &al);
	virtual ~AbstractLine(){}

	virtual AbstractLine* clone() const;

	virtual List<Point> toPolyline()const; 
	virtual List<Point> toPolylineD(TMETRIC d)const; 
	virtual List<Point> toPolylineN(int n)const; 

	virtual TMETRIC length() const;

	virtual Point EndPoint() const;
	virtual Point StartPoint() const;
	virtual Point MiddlePoint() const;

	virtual Vector OutDirection()const;
	virtual Vector InDirection()const;	
	virtual Vector MiddleDirection()const; 
	virtual Vector sDirection(TMETRIC s)const;
	
	virtual Vector InRCurvature()const;
	virtual Vector OutRCurvature()const;
	virtual Vector MiddleRCurvature() const;
	virtual Vector sRCurvature(TMETRIC s)const;
	
	virtual TAMETRIC DirectionTurn()const;

	virtual TMETRIC SCoordinateFromPoint(const Point &p)const;
	virtual Point PointFromSCoordinate(TMETRIC s) const; //?
	virtual bool PointBelongToLine(const Point &p)const;	
	
	virtual TransALine divideS(TMETRIC s);
	virtual void Invert();
	
	
	//PlaneAnalysis (?) {
	static bool isLinesCollapsed(AbstractLine *l1, AbstractLine *l2, TMETRIC epsilon=TMETRIC_O); //?
	static List<Point> LinesIntersections(AbstractLine *l1, AbstractLine *l2, bool ContinuesMode=true);
	List<TMETRIC> sIntersections(AbstractLine *al, bool ContinuesMode=true);
	// } PlaneAnalysis


	virtual void SetParentLine(AbstractLine *parentLine); //(?)
	virtual AbstractLine* ParentLine(); //(?)
	virtual int Count() const; //(?)
	virtual AbstractLine* ChildrenLine(int index); // (?)
	

////////////
//// TRASH {			
	enum LinePointsType //(X)(?)
	{
		LP_START,
		LP_END,
		LP_MIDDLE,
		LP_CENTER,
		_LP_COUNT
	};
	const Point& P1() const {return p1;} // (X)
	const Point& P2() const {return p2;} // (X)
	const Point& PM() const {return pM;} // (X)
//// } TRASH;
/////////////


protected:// (?)

	Point p1;
	Point p2;
	Point pM;

	AbstractLine *parent; // (?)	
};


List<Point> AbstractLinesIntersections(AbstractLine *l1, AbstractLine *l2);	
List<Point> invertPointList(List<Point> &pl);
List<AbstractLine *> invertAbstractLineList(List<AbstractLine *> &al);




//////////////////////////////////////////////////////////////////////////////////
////////////////////////// AlPoint ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class AlPoint: public AbstractLine // (?)
{
	public:
		Vector direct;
		Vector curv;
		void Set(Point p,Vector Direct=Vector(false),Vector Curv=Vector(false));
		AlPoint(Point p=Point());
		AlPoint(AlPoint &lp);
		AlPoint *clone();
		
		List<Point> toPolyline()const;
		List<Point> toPolylineN(int n) const;
		List<Point> toPolylineD(TMETRIC d) const;

		TMETRIC length() const;
		Vector OutDirection()const;
		Vector InDirection()const;
		Vector MiddleDirection()const;

		Vector OutRCurvature() const;
		Vector InRCurvature() const;
		Vector MiddleRCurvature() const;
		Vector sRCurvature() const;
};





//////////////////////////////////////////////////////////////////////////////////
////////////////////////// AlLine ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class AlLine: public AbstractLine
{
public:
	void Set(const Point &pStart,const Point &pEnd);
	AlLine(const Point &lp1=Point(),const Point &lp2=Point());
	AlLine(const AlLine &l);
	AlLine* clone() const;
	List<Point> toPolyline() const;
	List<Point> toPolylineN(int n) const;
	void Invert();	
	TransALine divideS(TMETRIC s);
	Vector sDirection(TMETRIC s) const;
};




//////////////////////////////////////////////////////////////////////////////////
////////////////////////// AlArcline /////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class AlArcline : public AbstractLine
{
public:

	void Set(const Basis &abas, TMETRIC ar, TAMETRIC aa);
	AlArcline(const Basis &abas=Basis(), TMETRIC ar=0, TAMETRIC aa=0);
	AlArcline(const AlArcline &al);
	AlArcline* clone() const {return new AlArcline(*this);}

	List<Point> toPolyline() const;
	List<Point> toPolylineN(int n) const;

	void Invert();

	TMETRIC SCoordinateFromPoint(const Point &p) const;
	Point PointFromSCoordinate(TMETRIC s) const;

	Vector InDirection() const;
	Vector OutDirection() const;
	Vector MiddleDirection() const;
	Vector sDirection(TMETRIC s) const;

	TAMETRIC DirectionTurn() const;

	Vector sRCurvature(TMETRIC s) const;
	Vector InRCurvature() const;
	Vector OutRCurvature() const;

	TransALine divideS(TMETRIC s);



//////////////
	void ArcConjugationBy2LinesAndRadius(AlLine &l1, AlLine &l2, TMETRIC arc_r, LinePointsType l1p=LP_END, bool RedefineLines=true, bool prolongation_l1=true);
	void ArcConjugationBy2LinesAndRadiusOpt(AlLine &l1, AlLine &l2, TMETRIC arc_r, bool RedefineLines=true);
	AlLine ArcTurnToPoint(AlLine l, Point p, TMETRIC arc_r, LinePointsType lp=LP_END ); //?

public:
	Basis arcbas;
	TAMETRIC angle;
	TAMETRIC XYangle0;		
	TMETRIC r;
	Point & pC();
};



//////////////////////////////////////////////////////////////////////////////////
////////////////////////// AlPolyline ////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

class AlPolyline : public AbstractLine
{
public:

	enum PolylineType // (?)
	{
		POLY_CONTINUOUS,
		POLY_DISCONTINUOUS,
		POLY_AUTOJOINING,
		_POLY_COUNT
	};

	void Set(const AlPolyline &pl);	
	
	AlPolyline(PolylineType plt=POLY_AUTOJOINING);
	AlPolyline(const AlPolyline &);	
	AlPolyline(List<Point> &ps);
	AlPolyline* clone() const;
	~AlPolyline();
	
	AbstractLine* ChildrenLine(int index);
	
	List<Point> toPolyline() const;
	List<Point> toPolylineN(int n) const;
	List<Point> toPolylineD(TMETRIC d) const;
	
	Vector InDirection() const;
	Vector OutDirection() const;
	Vector MiddleDirection() const;
	Vector sDirection(TMETRIC s) const;

	Point MiddlePoint() const;
	Point StartPoint() const;
	Point EndPoint() const;

	Vector sRCurvature(TMETRIC s) const;
	Vector InRCurvature() const;
	Vector OutRCurvature() const;

	TMETRIC SCoordinateFromPoint(const Point &p) const;
	Point PointFromSCoordinate(TMETRIC s) const;

	TAMETRIC DirectionTurn() const;	

	void Invert();	
	TransALine divideS(TMETRIC s);

////////////////////
	void operator =(const AlPolyline &pl);
	void Clear();
    void operator +=(const AbstractLine* al);
    void operator +=(const AbstractLine &al);
	void operator +=(AlPolyline pl);
	AbstractLine * operator [](int i) ;
    const AbstractLine * operator [](int i) const;
	AbstractLine * First();
	AbstractLine * Last();
    const AbstractLine * First() const;
    const AbstractLine * Last() const;
	int Count() const;
	AbstractLine * At(int index);
    void Add(const AbstractLine* al);
    void Add(const AbstractLine& al);
	void Insert(int index, AbstractLine *al);
	void Remove(int index, int len=1);
	void RemoveFirst();
	void RemoveLast();
	TransALine PassLine(int index);
	void TakeLine(int index, AbstractLine * al);
	void TakeLine(AbstractLine * al);
	AbstractLine * sLine(TMETRIC &s) const;

	TransObject<AlPolyline> SelectedPolyline(TMETRIC s1, TMETRIC s2) const;
	void ArcConjugation2ParallelLines(AlLine &l1, AlLine &l2, TMETRIC r, bool l1p_end=true);	
	void TurnFromDirectionToDirection(Vector dir1, Vector dir2, TMETRIC r); 
	void TurnFromDirectionToDirectionAlt(Vector dir1, Vector dir2, TMETRIC r);
	void AbstractConjugation(AbstractLine *al1, AbstractLine *al2, TMETRIC r);
	void AbstractConjugationLong(AbstractLine *al1, AbstractLine *al2, TMETRIC r);
	void TurnFromDirectionToPoint(Vector dir,Point p, TMETRIC r);
	void TurnFromPointToDirection( Vector dir, Point p, TMETRIC r);
	void TurnFromDirectionToDirection2(const Vector &dir1, const Vector &dir2, TMETRIC r);
	void SetCircuitMode(bool on=true); //(?)
	
	void intersectS(TMETRIC s);
	void intersectS(int iL, TMETRIC s, bool direct=true);
	
	AlPolyline ClearSelfIntersections();
	void ClearSelfIntersections_NeighborsOnly();
	void ConvertToSimplePolyline();
	void ConvertToSimplePolyline(AlPolyline &poly);

private:
	PolylineType pltype;
	List <AbstractLine*> lines;
	bool circuitMode;
};




#endif
