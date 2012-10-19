#pragma once
#ifndef ABSTRACTLINE_H
#define ABSTRACTLINE_H

#include <List>
#include "DestinationArea.h"
#include "DependedObject.h"
#include "AdjacentObject.h"

#define DEFARCPOLY_N 90
//#define AL AbstractLine
class AbstractLine;
// class Line;
// class Arcline;
// class APolyline;
typedef AbstractLine AL;
typedef TransPhantomObject<AbstractLine> TransALine;





template<class T> class QWE
{
public:
	QWE(){}

	T fun(T a, T b);

};


class AbstractLine: public AdjacentObject
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

	enum LinePointsType
	{
		LP_START,
		LP_END,
		LP_MIDDLE,
		LP_CENTER,
		_LP_COUNT
	};

	LineType line_type;
	AbstractLine(LineType lt=LT_NULL, AbstractLine *parentLine=0){line_type=lt;  parent=parentLine; LEN=0; nextLine=0; preLine=0; Level=0; /*debug_marker=0;*/ }
	AbstractLine(const AbstractLine &al):p1(al.p1),p2(al.p2),pM(al.pM),w(al.w),LEN(al.LEN),parent(0){line_type=al.line_type;  nextLine=0; preLine=0; Level=0;/*debug_marker=777;*/}//{ p1=al.p1; p2=al.p2; pM=al.pM; /*LEN=0;*/ /*pC=al.pC;*/}
	virtual AbstractLine* clone() const {return new AbstractLine(*this);}
	virtual ~AbstractLine(){}
	virtual List<Point> toPolyline()  {List<Point> lp; lp+=p1; lp+=pM; lp+=p2; return lp;} 
	virtual List<Point> toPolylineD(TMETRIC d)  {TMETRIC l=length(); return toPolylineN(l/d>1?l/d:1);} 
	virtual List<Point> toPolylineN(int n) {return List<Point>();} 
	virtual TMETRIC length() {return LEN;/*Vector(p1,pM).length()+Vector(pM,p2).length();*/}
	virtual Point* GetLinePoint(LinePointsType lp); //{return 0;}
	virtual void Invert(){Point bp=p1; p1=p2; p2=bp;}
	virtual Point EndPoint() /*const*/ {return p2.Val(p_null);}//{Point *p=GetLinePoint(LP_END); return p?*p:Point(false);}
	virtual Point StartPoint() /*const*/ {return p1.Val(p_null);}//{Point *p=GetLinePoint(LP_START); return p?*p:Point(false);}
	virtual Point MiddlePoint() /*const*/ {return pM.Val(p_null);}//{Point *p=GetLinePoint(LP_MIDDLE); return p?*p:Point(false);}
	virtual Vector OutDirection() { return p2.Val()==pM.Val()?v_null:-Vector(p2,pM).e(); }
	virtual Vector InDirection() { return p1.Val()==pM.Val()?v_null:Vector(p1,pM).e(); }	
	virtual Vector sDirection(TMETRIC s){if(s<0) return Vector(false,InDirection()); if(s>length()) return Vector(false,OutDirection()); Vector r(OutDirection()*s+InDirection()*(length()-s)); r.fulcrum=PointFromSCoordinate(s); return r.e(); }
	virtual Vector MiddleDirection() {if(p1.Val()==p2.Val())return v_null; Vector rp(p1,p2); rp.fulcrum=pM; return rp.e();} 

	virtual Vector sRCurvature(TMETRIC s){return v_null;}
	virtual Vector InRCurvature(){return v_null;}
	virtual Vector OutRCurvature(){return v_null;}

	virtual TMETRIC SCoordinateFromPoint(const Point &p){return p.lx(&OrtoBasis_InXY_ByI(V(p1,p2)));}//p.inBasis(&OrtoBasis_InXY_ByI(V(p1,p2))).x();};
	virtual Point PointFromSCoordinate(TMETRIC s){return Point(s,0,0,&OrtoBasis_InXY_ByI(V(p1,p2)));}; //?
	virtual bool PointBelongToLine(const Point &p) { TMETRIC s=SCoordinateFromPoint(p); if((s<-TMETRIC_O)||(s>(length()+TMETRIC_O))) return false; return p==PointFromSCoordinate(s);}	
	virtual TransALine divideS(TMETRIC s){return TransObject<AbstractLine>();}
	
	static bool isLinesCollapsed(AbstractLine *l1, AbstractLine *l2, TMETRIC epsilon=TMETRIC_O); //?
	
	//PlaneAnalysis ->
	static List<Point> LinesIntersections(AbstractLine *l1, AbstractLine *l2,bool ContinuesMode=true);
	List<TMETRIC> sIntersections(AbstractLine *al, bool ContinuesMode=true);
	// <- PlaneAnalysis

	Point P1() const {return p1.Val(p_null);}
	Point P2() const {return p2.Val(p_null);}
	Point PM() const {return pM.Val(p_null);}

	virtual void SetParentLine(AbstractLine *parentLine){parent=parentLine;}
	virtual AbstractLine* ParentLine(){return parent;}
	virtual int Count() const {return 1;}
	virtual AbstractLine* ChildrenLine(int index){return (index==0)?(this):(0);}

	TMETRIC_CALC w;
	BoolMarkerList markers;
	DependedLength<TMETRIC> LEN;	

	AbstractLine *nextLine;
	AbstractLine *preLine;
	int Level;



protected:
	PhantomObject<Point> p1; 
	PhantomObject<Point> p2;
	PhantomObject<Point> pM;

	AbstractLine *parent;
	//TMETRIC_CALC LEN;

//friend class APolyline;
};

List<Point> AbstractLinesIntersections(AbstractLine *l1, AbstractLine *l2);	
List<Point> invertPointList(List<Point> &pl);
List<AbstractLine *> invertAbstractLineList(List<AbstractLine *> &al);

class AlPoint: public AbstractLine //?
{
	public:
		void Set(Point p){p1=p; p2=p; pM=p; /*pC=p;*/}
		AlPoint(Point p=Point()):AbstractLine(LT_LPOINT){Set(p);}
		AlPoint(AlPoint &lp):AbstractLine(LT_LPOINT){Set(lp.p1);}
		AlPoint *clone(){return new AlPoint(*this);}
		List<Point> toPolyline(){List<Point> lp; lp+=p1; return lp;}
		List<Point> toPolylineN(int n){ return toPolyline();}
		List<Point> toPolylineD(TMETRIC d){ return toPolyline();}
		TMETRIC length() {return 0;}
		Vector OutDirection(){return Vector(false);}
		Vector InDirection(){return Vector(false);}
		Vector MiddleDirection(){return Vector(false);}
};

class AlLine: public AbstractLine
{
public:
	void Set(const Point &pStart,const Point &pEnd, TMETRIC width=0);
	AlLine(const Point &lp1=Point(),const Point &lp2=Point(), TMETRIC  width=0);
	AlLine(const AlLine &l);
	AlLine* clone() const {return new AlLine(*this);}
	List<Point> toPolyline() ;
	List<Point> toPolylineN(int n);
	TMETRIC length() ;
//	Point* GetLinePoint(LinePointsType lp);
	void Invert();
	//AlLine* divideS(TMETRIC s);
	TransALine divideS(TMETRIC s);
	Vector sDirection(TMETRIC s);
};


class AlArcline : public AbstractLine
{
public:

	void Set(const Basis &abas, TMETRIC ar, TAMETRIC aa, TMETRIC  width=0);

	TAMETRIC angle;
	TAMETRIC XYangle0;	

	AlArcline(const Basis &abas=Basis(), TMETRIC ar=0, TAMETRIC aa=0, TMETRIC  width=0);
	AlArcline(const AlArcline &al);//:AbstractLine(LT_ARCLINE){arcbas=al.arcbas; angle=al.angle; XYangle0=al.XYangle0; r=al.r;}
	AlArcline* clone() const {return new AlArcline(*this);}

	void ArcConjugationBy2LinesAndRadius(AlLine &l1, AlLine &l2, TMETRIC arc_r, LinePointsType l1p=LP_END, bool RedefineLines=true, bool prolongation_l1=true);
	void ArcConjugationBy2LinesAndRadiusOpt(AlLine &l1, AlLine &l2, TMETRIC arc_r, bool RedefineLines=true);
	AlLine ArcTurnToPoint(AlLine l, Point p, TMETRIC arc_r, LinePointsType lp=LP_END ); //?
	List<Point> toPolyline();
	List<Point> toPolylineN(int n);
	TMETRIC length();
	Point* GetLinePoint(LinePointsType lp);
	void Invert();

	TMETRIC SCoordinateFromPoint(const Point &p) ;
	Point PointFromSCoordinate(TMETRIC s) ;

	Vector InDirection() ;
	Vector OutDirection() ;
	Vector MiddleDirection() ;
	Vector sDirection(TMETRIC s);

	Vector sRCurvature(TMETRIC s);
	Vector InRCurvature();
	Vector OutRCurvature();

	TransALine divideS(TMETRIC s);


public:
	Basis arcbas;
	TMETRIC r;
	Point pC;
};


class AlPolyline : public AbstractLine
{
public:

	enum PolylineType
	{
		POLY_CONTINUOUS,
		POLY_DISCONTINUOUS,
		POLY_AUTOJOINING,
		_POLY_COUNT
	};

	enum ConjugationType
	{
		CNG_NO,
		CNG_DIRTODIR,
		CNG_LINESOPT,
		_CNG_COUNT
	};
	
	void Set(const AlPolyline &pl);
	PolylineType pltype;
	//ConjugationType cngtype;
	AlPolyline(PolylineType plt=POLY_AUTOJOINING/*,ConjugationType cngt=CNG_NO*/);
	AlPolyline(const AlPolyline &);
	void operator =(const AlPolyline &pl){Set(pl);}
	AlPolyline(List<Point> &ps);
	AlPolyline* clone() const {return new AlPolyline(*this);}
	~AlPolyline();
	void Clear();
	void operator +=(AbstractLine* al);
	void operator +=(AlPolyline pl);
	AbstractLine * operator [](int i) ;
	AbstractLine * First()  {if(!Count()) return 0; return lines.first();}
	AbstractLine * Last()  {if(!Count()) return 0; return lines.last();}
	int Count() const {return lines.count();}
	AbstractLine* ChildrenLine(int index){return (*this)[index];}
	AbstractLine * At(int index) {return (*this)[index];}
	void Add(AbstractLine* al);
	void Insert(int index, AbstractLine *al);
	//void Remove(int index);
	void Remove(int index, int len=1);
	void RemoveFirst();
	void RemoveLast();
	List<Point> toPolyline() ;
	List<Point> toPolylineN(int n);
	List<Point> toPolylineD(TMETRIC d);
	TransObject<AlPolyline> SelectedPolyline(TMETRIC s1, TMETRIC s2);
	TMETRIC length();
	Point* GetLinePoint(LinePointsType lp);
	void ArcConjugation2ParallelLines(AlLine &l1, AlLine &l2, TMETRIC r, bool l1p_end=true);
	//void ArcTurnToPoint(AlLine l, Point p, TMETRIC arc_r, bool lp_end=true );
	void TurnFromDirectionToDirection(Vector dir1, Vector dir2, TMETRIC r); // return isShortCNG;
	void TurnFromDirectionToDirectionAlt(Vector dir1, Vector dir2, TMETRIC r);
	void AbstractConjugation(AbstractLine *al1, AbstractLine *al2, TMETRIC r);
	void AbstractConjugationLong(AbstractLine *al1, AbstractLine *al2, TMETRIC r);
	void TurnFromDirectionToPoint(Vector dir,Point p, TMETRIC r);
	void TurnFromPointToDirection( Vector dir, Point p, TMETRIC r);

	TMETRIC SCoordinateFromPoint(const Point &p) ;//{return p.lx(&OrtoBasis_InXY_ByI(V(p1,p2)));}//p.inBasis(&OrtoBasis_InXY_ByI(V(p1,p2))).x();};
	Point PointFromSCoordinate(TMETRIC s) ;//{return Point(s,0,0,&OrtoBasis_InXY_ByI(V(p1,p2)));}; //?
	void Invert();
	//AlPolyline *divideS(TMETRIC s);
	TransALine divideS(TMETRIC s);
	void intersectS(TMETRIC s);
	void intersectS(int iL,TMETRIC s, bool direct=true);
	
	AlPolyline ClearSelfIntersections();
	void ClearSelfIntersections_NeighborsOnly();
	void ConvertToSimplePolyline();
	void ConvertToSimplePolyline(AlPolyline &poly);

	TransALine PassLine(int index);
	void TakeLine(int index, AbstractLine * al);
	void TakeLine(AbstractLine * al);
	AbstractLine * sLine(TMETRIC &s);

	Vector sRCurvature(TMETRIC s);
	Vector InRCurvature();
	Vector OutRCurvature();

	Vector InDirection();
	Vector OutDirection();
	Vector MiddleDirection(){return sDirection(length()/2);}
	Vector sDirection(TMETRIC s);
	Point MiddlePoint(){return PointFromSCoordinate(length()/2);}
	Point StartPoint() {return First()->StartPoint();}
	Point EndPoint() {return Last()->EndPoint();}

	void SetCircuitMode(bool on=true);

private:
	List <AbstractLine*> lines;
	bool circuitMode;
};





#endif