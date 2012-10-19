#include "AbstractLine.h"


////////////////////////////////////////////////////////////////////////
//////////////////////// ABSTRACT LINE /////////////////////////////////
////////////////////////////////////////////////////////////////////////

Point* AbstractLine::GetLinePoint(LinePointsType lp)
{
	switch(lp)
	{
		case LP_START: return &p1.Obj(); 
		case LP_END: return &p2.Obj();
		case LP_MIDDLE: return &pM.Obj();
//		case LP_CENTER: return &pC;	
	}
	return 0;
}


List<Point> invertPointList(List<Point> &pl)
{
	List<Point> rpl;
	for(int i=pl.count()-1; i>=0; i--) rpl+=pl[i];
	return rpl;
}

List<AbstractLine *> invertAbstractLineList(List<AbstractLine *> &al)
{
	List<AbstractLine *> ral;
	for(int i=al.count()-1; i>=0; i--) ral+=al[i];
	return ral;
}


List<Point>  AbstractLinesIntersections(AbstractLine *l1, AbstractLine *l2)
{
	return  AbstractLine::LinesIntersections(l1, l2);
}



// void AbstractLine::SetParent(AbstractLine *parentLine)
// {
// // 	if(parent)
// // 	{
// // 		if(parent->LEN.Exist()) LEN
// // 	}
// 	parent
// }



bool AbstractLine::isLinesCollapsed(AbstractLine *l1, AbstractLine *l2, TMETRIC epsilon/* =TMETRIC_O */)
{
	if(l1==l2) return true; // maybe false?

	if(l1->line_type==LT_LINE&&l2->line_type==LT_LINE)
	{
		Vector v1(l1->StartPoint(),l1->EndPoint());
		Vector v2(l2->StartPoint(),l2->StartPoint());
		if(v1||v2)
		{			
			if(Vector::ParallelDistance(v1,v2)<epsilon)
			{
				TMETRIC pr1=(l1->StartPoint()&&l2->StartPoint())&v1;
				TMETRIC pr2=(l1->StartPoint()&&l2->EndPoint())&v1;
				if(pr1<=0&&pr2<=0) return false;;
				if(pr1>=l1->length()&&pr2>=l1->length()) return false;
				return true;
			}else return false;
		}else return false;
	}else if(l1->line_type==LT_ARCLINE&&l2->line_type==LT_ARCLINE)
	{
		AlArcline *arc1=(AlArcline*)l1;
		AlArcline *arc2=(AlArcline*)l2;
		if(arc1->arcbas.O==arc2->arcbas.O)
		{		
			if(isEqual(arc1->r,arc2->r,epsilon))
			{
				CylCoord a2p1=ToCylCoord_Arc(arc2->StartPoint()[arc1->arcbas]);
				CylCoord a2p2=ToCylCoord_Arc(arc2->EndPoint()[arc1->arcbas]);
				if(a2p1.a>=arc1->angle&&a2p2.a>=arc1->angle&&a2p2.a>=a2p1.a) return false;
				return true;
			} else return false;
		} else return false;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////
/////////////////////// LINE ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

void AlLine::Set(const Point &pStart, const Point &pEnd, TMETRIC width)
{
//	if(parent) if(parent->LEN.Exist()) parent->LEN-=length();
	//LEN.Clear();
	
	//pStart.SetGlobalBasis(); pEnd.SetGlobalBasis();
	p1=pStart;
	p2=pEnd;
	p1.Obj().SetGlobalBasis();
	p2.Obj().SetGlobalBasis();
	pM=((p1.Obj().v()+p2.Obj().v())/2).destination();
	if(width) w=width; else w.Clear();
	LEN=Vector(p1,p2).length();
//	if(parent) if(parent->LEN.Exist()) parent->LEN+=length();
}

AlLine::AlLine(const Point &lp1,const Point &lp2, TMETRIC width): AbstractLine(LT_LINE){Set(lp1,lp2,width);}
AlLine::AlLine(const AlLine &l):AbstractLine(l)
{	
}
void AlLine::Invert()
{
	INTERCHANGET(Point,p1,p2);
}
TMETRIC AlLine::length() 
{
// 	if(LEN.cObj().Exist()) return LEN;
// 	LEN=Vector(p1,p2).length();	
	return LEN;
}

List<Point> AlLine::toPolyline() 
{
	List<Point> lp;
	lp+=p1; lp+=p2;
	return lp;
}

List<Point> AlLine::toPolylineN(int n)
{
	List<Point> lp;lp+=p1;
	Vector v(p1,p2);
	for(int i=1; i<=n; i++)
	{
		lp+=(v*(TMETRIC)i/(TMETRIC)n).destination();
	}
	return lp;
}

TransALine AlLine::divideS(TMETRIC s)
{
	Point rp1(StartPoint());
	Point rp2(PointFromSCoordinate(s));
	Set(rp2,EndPoint());
	return new AlLine(rp1,rp2);
}

Vector AlLine::sDirection(TMETRIC s)
{
	Vector v=InDirection();
	v.fulcrum=PointFromSCoordinate(s);
	return v;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////
/////////////////////// ARCLINE /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void AlArcline::Set(const Basis &abas, TMETRIC ar, TAMETRIC aa, TMETRIC width)
{
//	LEN.Clear();
//	if(parent) if(parent->LEN.Exist()) parent->LEN+=-angle*r+aa*ar;
	arcbas=abas;
	angle=aa;
	XYangle0=Vector::Angle(abas.i,Vector(1,0,0));
	if(abas.i.y()<0) XYangle0=PI*2-XYangle0;
	r=ar;
	Vector vpen(r,0,0,Point(0,0,0,&arcbas),&arcbas);
	p1=vpen.destination().inGlobalBasis();
	vpen.rotate_Z(angle/2);
	pM=vpen.destination().inGlobalBasis();
	vpen.rotate_Z(angle/2);
	p2=vpen.destination().inGlobalBasis();
	pC=arcbas.O;
	if(width) w=width; else w.Clear();
	LEN=r*angle;
}
Vector AlArcline::InDirection() 
{
	Vector v=arcbas.j; v.fulcrum=p1;
	return v.e();
}
Vector AlArcline::OutDirection() 
{
	Vector v=arcbas.k*Vector(arcbas.O,p2); v.fulcrum=p2;
	return v.e();
}
Vector AlArcline::MiddleDirection() 
{
	Vector v=InDirection()+OutDirection()*(-1); v.fulcrum=pM;
	return v.e();
}
Vector AlArcline::sDirection(TMETRIC s)
{
	Point p(PointFromSCoordinate(s));
	Vector v((p&&arcbas.O)*arcbas.k);
	v.fulcrum=p;
	return v.e();
}
AlArcline::AlArcline(const AlArcline &al):AbstractLine(al),
arcbas(al.arcbas),angle(al.angle),r(al.r),pC(al.pC),XYangle0(al.XYangle0)
{/*Set(al.arcbas,al.r,al.angle,al.w);*/}

void AlArcline::Invert()
{
	arcbas.SetOrtoBasis_ByOXY(pC,p2,pM);
	INTERCHANGET(Point,p1,p2);
	XYangle0=Vector::Angle(arcbas.i,Vector(1,0,0));
	if(arcbas.i.y()<0) XYangle0=PI*2-XYangle0;
}


AlArcline::AlArcline(const Basis &abas, TMETRIC ar, TAMETRIC aa, TMETRIC width) :
AbstractLine(LT_ARCLINE)
{
	Set(abas,ar,aa,width);
}
TMETRIC AlArcline::length() {return LEN;}

List<Point> AlArcline::toPolylineN(int n) 
{
	List<Point> lp;
	Basis ab=arcbas;
	Vector vpen(r,0,0,Point(0,0,0,&ab),&ab);
	for(int i=0; i<=n; i++)
	{
		lp+=vpen.inGlobalBasis().destination();
		vpen.rotate_Z(angle/n);		
	}
	return lp;
}

List<Point> AlArcline::toPolyline() 
{
	int n=angle/(PI*2)*DEFARCPOLY_N;
	if(n<1) n=1;
	return toPolylineN(n);
}

TransALine AlArcline::divideS(TMETRIC s)
{
	if(s<=0) return TransALine();
	if(s>=length()) return TransALine();
	AlArcline *ra=new AlArcline(arcbas,r,s/r,w);
	Vector i=arcbas.O&&(ra->EndPoint());
	Set(OrtoBasis_ByIJ(i,arcbas.k*i),r,(length()-s)/r,w);	
	return TransALine(ra);
}

void AlArcline::ArcConjugationBy2LinesAndRadius(AlLine &l1, AlLine &l2, TMETRIC arc_r, LinePointsType l1p, /*int l2p=LP_START,*/ bool RedefineLines, bool prolongation_l1)
{
	r=arc_r;

	Vector v1(l1.P1(),l1.P2());
	Vector v2(l2.P1(),l2.P2());
	if(Vector::isParallel(v1,v2)) return;
	Point lpc=(l1.GetLinePoint(l1p))->inBasis(0);

	TAMETRIC av=Vector::Angle(v1,v2);
	av=abs(av);
	if(av>PI/2){ v2.invert(); av=PI-av;}
	TMETRIC xLong=r/tan(av/2);
	TMETRIC xShort=r/tan((PI-av)/2);
	Point cl=v1.Intersection(v2);
	v1.fulcrum=cl; 
	v2.fulcrum=cl;
	Vector v1e=v1.e();
	Vector v2e=v2.e();
	
	Point pc=(v1e*xLong).destination(); angle=PI-av;
	Point cpc=(v1e*(-xLong)).destination();
	if(Vector(cpc,lpc).length()<Vector(pc,lpc).length()){ pc=cpc; angle=PI-av;}
	cpc=(v1e*(xShort)).destination();
	if(Vector(cpc,lpc).length()<Vector(pc,lpc).length()){ pc=cpc; angle=av;}
	cpc=(v1e*(-xShort)).destination();
	if(Vector(cpc,lpc).length()<Vector(pc,lpc).length()){ pc=cpc; angle=av;}

	if(angle<PI/2) v2*=-1;
	Vector vmO=(v1e+v2e);	
	Vector vrO=(v1e*v2e)*v1e;
	vrO.fulcrum=pc;
	Point O=vmO.Intersection(vrO);
	Vector Opc(O,pc);
	Vector clpc(cl,pc);
	arcbas.SetOrtoBasis_ByIJ(Opc,v1);
	if(prolongation_l1) angle=PI*2-angle;
	else
	{
		arcbas.j*=-1;
		arcbas.k*=-1;
	}
	if(Vector(l1.P2(),O).length()<Vector(l1.P1(),O).length()) angle=PI*2-angle;

	Set(arcbas,r,angle);

	if(RedefineLines)
	{
		Point *pl1=l1.GetLinePoint(l1p);
		*pl1=pc;
		if(Vector(p2,l2.P1()).length()>Vector(p2,l2.P1()).length()) l2.Set(p2,l2.P2());//.p1=p2;
		else l2.Set(l2.P1(),p2);// p2=p2;
	}

}


void AlArcline::ArcConjugationBy2LinesAndRadiusOpt(AlLine &l1, AlLine &l2, TMETRIC arc_r, bool RedefineLinese)
{
 	r=arc_r; 
 	Vector v1(l1.P1(),l1.P2()); 
 	Vector v2(l2.P1(),l2.P2()); 
 	if(Vector::isParallel(v1,v2)) return;
 
 	Point cl=v1.Intersection(v2); 
	v1=Vector(cl,*l1.GetLinePoint(LP_MIDDLE)).e();
	v2=Vector(cl,*l2.GetLinePoint(LP_MIDDLE)).e();
	Vector vm=(v1+v2).e(); 
 	TAMETRIC a=Vector::Angle(v1,v2); 
	TMETRIC h=r/tan(a/2);
	Point crl1=(v1*h).destination();
	Point crl2=(v2*h).destination();
	angle=PI-a;
	Vector or=(v2*v1)*v1; or.fulcrum=crl1;
	Point O=vm.Intersection(or); or.fulcrum=O;
	arcbas.SetOrtoBasis_ByIJ(or,v1*(-1));	

	Set(arcbas,r,angle);

	if(RedefineLinese)
	{
		Point *sp1=l1.GetLinePoint(LP_START);
		Point *sp2=l2.GetLinePoint(LP_START);
		if(Vector(*sp1,crl1).length()>Vector(crl1,*l1.GetLinePoint(LP_END)).length()) sp1=l1.GetLinePoint(LP_END);
		if(Vector(*sp2,crl2).length()>Vector(crl2,*l2.GetLinePoint(LP_END)).length()) sp2=l2.GetLinePoint(LP_END);
		*sp1=crl1;
		*sp2=crl2;
	}
}

AlLine AlArcline::ArcTurnToPoint(AlLine l, Point p, TMETRIC arc_r, LinePointsType lp)
{
	r=arc_r;
	Point pl_1;
	Point pl_2;		
	if(lp==LP_END) {pl_1=*l.GetLinePoint(LP_END); pl_2=*l.GetLinePoint(LP_START);}
	else{pl_1=*l.GetLinePoint(LP_START); pl_2=*l.GetLinePoint(LP_END);}
	Vector v12(pl_1,pl_2);
	Vector v1p(pl_1,p);
	Vector vW=(v1p*v12).e();
	Vector vO1=(v12*vW).e()*r;
	Point O=vO1.destination();
	Vector vOp(O,p); if(vOp.length()<=r) return AlLine();
	vO1.invert();
	arcbas.SetOrtoBasis_ByIJ(vO1,Vector(pl_2,pl_1));	
	TAMETRIC aO1Op=Vector::Angle(vO1,vOp);
	p.SetBasis(&arcbas);
	if(p.y()<0) aO1Op=2*PI-aO1Op;
	TAMETRIC a_=arccos(r/vOp.length());
	angle=aO1Op-a_;
//////////////////////////////////////////////////////////////////////////
	Set(arcbas,r,angle);
	return AlLine(*this->GetLinePoint(LP_END),p);
}


Point* AlArcline::GetLinePoint(LinePointsType lp)
{	
	Point *rp=0;
	switch(lp)
	{
		case LP_CENTER: rp=&arcbas.i.fulcrum;break;
		case LP_START: rp=&p1.Obj();break;
		case LP_END: rp=&p2.Obj(); break;	
		case LP_MIDDLE: rp=&pM.Obj();break;
		default: rp=0;
	}
	return rp;
}


TMETRIC AlArcline::SCoordinateFromPoint(const Point &p) 
{
	return ToCylCoord_Arc(p[arcbas]).a*r;
}

Point AlArcline::PointFromSCoordinate(TMETRIC s) 
{
	return FromCylCoord_Arc(NormAngle_0_2PI(s/r),r,0,&arcbas);
}



Vector AlArcline::sRCurvature(TMETRIC s)
{
	return PointFromSCoordinate(s)&&arcbas.O;
}

Vector AlArcline::InRCurvature()
{	
	return StartPoint()&&arcbas.O;
}

Vector AlArcline::OutRCurvature()
{	
	return EndPoint()&&arcbas.O;
}


//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
//////////////////////// POLYLINE ////////////////////////////////////
//////////////////////////////////////////////////////////////////////
AlPolyline::AlPolyline(PolylineType plt):AbstractLine(LT_POLYLINE){pltype=plt; /*ccngtype=cngt;*/}
AlPolyline::AlPolyline(List<Point> &ps):AbstractLine(LT_POLYLINE)
{	
	pltype=POLY_AUTOJOINING;
	for(int i=0; i<ps.count()-1; i++) Add(&AlLine(ps[i],ps[i+1]));
}

void AlPolyline::Set(const AlPolyline &pl)
{
	//if(parent) if(parent->LEN.Exist()) parent->LEN-=length(); //in Clear();
	Clear();
	pltype=pl.pltype;
	for(int i=0; i<pl.lines.count(); i++) Add(pl.lines.at(i));
	//if(parent) if(parent->LEN.Exist()) parent->LEN+=length();
}
AlPolyline::AlPolyline(const AlPolyline &pl): AbstractLine(LT_POLYLINE)
{
	Set(pl);
}
AlPolyline::~AlPolyline()
{
// 	if(debug_marker==1||debug_marker==2)
// 	{
// 		debug_marker*=1;
// 	}
	for(int i=0; i<lines.count(); i++)
		delete lines[i];
}


TMETRIC AlPolyline::length()
{
// 	if(LEN.Exist()) return LEN;
// 	LEN=0;
// 	//TMETRIC rl=0;
// 	for(int i=0; i<lines.count(); i++)	LEN+=lines[i]->length();
	return LEN;
}

TMETRIC AlPolyline::SCoordinateFromPoint(const Point &p) 
{
	TMETRIC shmin=-TMETRIC_O;
	TMETRIC hmin=TRNUM_INFINITY;
	TMETRIC h=0;
	TMETRIC s=0;
	TMETRIC sl=0;
	TMETRIC l=0;
	Point sp;
	for(int i=0; i<Count(); i++)
	{
		s=At(i)->SCoordinateFromPoint(p);
		l=At(i)->length(); sl+=l;
		if(s<0) continue;
		if(s>l) continue;
		sp=At(i)->PointFromSCoordinate(s);
		if(sp.isNull()) continue;
		h=V(p,sp).length();
		if(h<TMETRIC_O) return sl-l+s;
		if(h<hmin){hmin=h; shmin=sl-l+s;}
	}
	return shmin;
}

Point AlPolyline::PointFromSCoordinate(TMETRIC s) 
{
	if(Count()==0) return p_null;
	if(s<0) return Point(false,StartPoint());
	if(s>length()) return Point(false,EndPoint());
	TMETRIC l=0;
	int i=0;
	for(i=0; i<Count(); i++)
	{
		l+=At(i)->length();
		if(l>=s) break;
	}
	return At(i)->PointFromSCoordinate(s-l+At(i)->length());
}

TransALine AlPolyline::divideS(TMETRIC s)
{
	if(s<=0) return 0;	
	AlPolyline *rpoly=new AlPolyline(pltype);
	TMETRIC len=0;//rpoly->LEN.Obj(0);
	TMETRIC l=0;
	while(Count())
	{
		l=First()->length();
		len+=l;		
		if(s>len)
		{
			rpoly->lines+=First();
			RemoveFirst();			
		}else if(s<len)
		{
			len-=l;
			rpoly->lines+=First()->divideS(s-len).PassObj();
			//len+=rpoly->Last()->length();			
			break;
		}else
		{
			rpoly->lines+=First();
			RemoveFirst();	
			break;
		}
	}
//  if(LEN.Exist()) LEN-=len;
//	if(parent) if(parent->LEN.Exist()) parent->LEN-=length();
	return rpoly;
}


void AlPolyline::intersectS(TMETRIC s)
{
	if(s<0||s>length()) return;
	TMETRIC len=0;
	TMETRIC l=0;
	for(int i=0; i<Count(); i++)
	{
		l=At(i)->length();
		len+=l;
		if(s<len)
		{
			AbstractLine *al=At(i)->divideS(s-len+l).PassObj();
			TakeLine(i,al);
			break;
		}
		if(s==len) break;
	}
}

void AlPolyline::intersectS(int il,TMETRIC s,bool direct)
{
	if(Count()==0) return;
	if(il<0||il>=Count()) return;
	if(s<=0||s>=At(il)->length()) return;
	AbstractLine *al=At(il)->divideS(s).PassObj();
	if(direct)TakeLine(il,al);	
	else TakeLine(il+1,al);
}

void AlPolyline::Clear()
{	
//	if(parent) if(parent->LEN.Exist()) parent->LEN-=length();
	//LEN.Clear();
	for(int i=0; i<lines.count(); i++) delete lines[i];
	lines.clear();
}

void AlPolyline::Invert()
{
	for(int i=0; i<lines.count(); i++)
	{
		lines[i]->Invert();
		lines[i]->SimpleInvert();
//		AdjacentObject* nl lines[i]->next;
//		lines[i]->next=lines[i]->previous;
//		lines[i]->previous=nl;		
	}
	lines=invertAbstractLineList(lines);	
	p1=lines.first()->StartPoint();
	p2=lines.last()->EndPoint();
}

Vector AlPolyline::InDirection()  {if(lines.isEmpty()) return Vector(false); return lines.first()->InDirection();}
Vector AlPolyline::OutDirection()  {if(lines.isEmpty()) return Vector(false); return lines.last()->OutDirection();}
Vector AlPolyline::sDirection(TMETRIC s)
{
	if(s<0) return Vector(false,InDirection());
	if(s>length()) return Vector(false,OutDirection());
	TMETRIC len=0;
	TMETRIC l=0;
	for(int i=0; i<Count(); i++)
	{
		l=At(i)->length();
		len+=l;
		if(s<=len)
		{
			return At(i)->sDirection(s-len+l);			
		}		
	}
	return Vector(false);
}

void AlPolyline::operator +=(AlPolyline pl)
{
	for(int i=0; i<pl.Count(); i++) Add(pl[i]);
}

void AlPolyline::operator +=(AbstractLine *al)
{
	//	if(Line *lal(dynamic_cast<Line *>(al)))
	//	nal = new Line(*lal);
	if(al==0) return;
	if(al->StartPoint()==p_gO&&al->length()==0) return;
	AbstractLine *nal=al->clone();	

	if(pltype==POLY_AUTOJOINING)
		if(lines.count())
		{
			TMETRIC dinv=Vector(Last()->EndPoint(),nal->StartPoint()).length()-Vector(Last()->EndPoint(),nal->EndPoint()).length();
			if(abs(dinv)<TMETRIC_O)
			{
				if((Last()->OutDirection()&nal->InDirection())<(Last()->OutDirection()&(nal->OutDirection()*(-1))))
					nal->Invert();
			}
			else if(dinv>0)	
				nal->Invert();
	//		nal->SetPrevious(lines.last());			
		}
	
	TakeLine(nal);
//	LEN.AddMaster(nal->LEN);	

	p1=First()->StartPoint();
	p2=Last()->EndPoint();
//	//if(LEN.Exist()) LEN+=al->length();
//	//if(parent)if(parent->LEN.Exist()) parent->LEN+=al->length();
//	//pM=*lines[(int)(lines.count()/2)]->GetLinePoint(LP_MIDDLE);
}

AbstractLine * AlPolyline::operator [](int i) 
{
	if((i<0)||(i>=Count())) return 0;		
	return lines[i];
}

void AlPolyline::Insert(int i, AbstractLine *al)
{
	AbstractLine *nal=al->clone();
	if(pltype==POLY_AUTOJOINING)
	{		
		if(i<0) i=0; if(i>Count()) i=Count();
		if(Count()>0)
		{
			if(i==0){ if(Vector(At(0)->StartPoint(),al->StartPoint()).length()<Vector(At(0)->StartPoint(),al->EndPoint()).length()) nal->Invert();}
			else if(i==Count()){if(Vector(Last()->StartPoint(),al->EndPoint()).length()>Vector(Last()->StartPoint(),al->StartPoint()).length()) nal->Invert();}
			else {if(Vector(At(i-1)->EndPoint(),al->StartPoint()).length()+Vector(At(i)->StartPoint(),al->EndPoint()).length()>Vector(At(i-1)->EndPoint(),al->EndPoint()).length()+Vector(At(i)->StartPoint(),al->StartPoint()).length()) nal->Invert();}

	//		nal->InsertAsPrevious(At(i));
		}
	}
	
	TakeLine(i,nal);
	//lines.Insert(i,nal);
	//LEN.AddMaster(nal->LEN);
	//if(LEN.Exist())LEN+=al->length();
//	if(parent)if(parent->LEN.Exist()) parent->LEN+=al->length();
}

void AlPolyline::Remove(int index, int len)
{

	if(index>Count()||index<0||Count()==0) return;
	if(index+len>Count())len=Count()-index;
	if(index>0) lines[index-1]->setNext(lines[index+len-1]->next());
	for(int i=index; i<index+len; i++ )
	{		
		delete lines[i];
	}

//	if(parent)if(parent->LEN.Exist()) LEN+=al->length();
	//if(LEN.Exist()) for(int i=index; i<index+len; i++ ) LEN-=lines[i]->length();
	

	for(int i=0; i<len; i++) lines.removeAt(index);
}
void AlPolyline::RemoveFirst() {Remove(0);}
void AlPolyline::RemoveLast(){Remove(Count()-1);}
void AlPolyline::Add(AbstractLine *al){*this+=al;}



List<Point> AlPolyline::toPolyline() 
{
	List<Point> rlp;
	List<Point> blp;
	int lc=lines.count();

	for(int i=0; i<lc; i++)
	{
		blp=lines[i]->toPolyline();
		if(!blp.isEmpty())
		{
			if(!rlp.isEmpty()) if(rlp.last()==blp.first()) blp.removeFirst();
			rlp+=blp;
		}
	}

	return rlp;

///////////////////////////////////////////////
	switch(pltype)
	{
		case POLY_CONTINUOUS:
			for(int i=0; i<lc; i++)
			{
				blp=lines[i]->toPolyline(); 
				if(i!=lc-1) blp.removeLast();
				rlp+=blp;
			}
		break;

		case POLY_DISCONTINUOUS:
			for(int i=0; i<lc; i++)
			{
				blp=lines[i]->toPolyline();
				rlp+=blp;
			}
		break;

		case POLY_AUTOJOINING:
			for(int i=0; i<lc; i++)
			{
				blp=lines[i]->toPolyline();
				if(i==1)
				{
					TMETRIC l1l2=Vector(rlp.last(),blp.first()).length();
					TMETRIC bl1l2;
					bool pl1_first=false;
					bool pl2_first=true;					
					bl1l2=Vector(rlp.first(),blp.first()).length();
					if(bl1l2<l1l2) {l1l2=bl1l2; pl1_first=true;}
					bl1l2=Vector(rlp.first(),blp.last()).length();
					if(bl1l2<l1l2) {l1l2=bl1l2; pl1_first=true; pl2_first=false;}
					bl1l2=Vector(rlp.last(),blp.last()).length();
					if(bl1l2<l1l2) {l1l2=bl1l2; pl1_first=false; pl2_first=false;}

					if(pl1_first) rlp=invertPointList(rlp);
					if(!pl2_first) blp=invertPointList(blp);

				}
				if(i>1)
				{				
					if(Vector(rlp.last(),blp.first()).length()>Vector(rlp.last(),blp.last()).length()) blp=invertPointList(blp);
					rlp.removeLast();
				}
				rlp+=blp;
			}
		break;
	}
	return rlp;
}

List<Point> AlPolyline::toPolylineD(TMETRIC d) //POLY_AUTOJOINING - ???
{
	List<Point> rlp;
	List<Point> blp;
	int lc=lines.count();

	for(int i=0; i<lc; i++)
		{
			blp=lines[i]->toPolylineD(d);
			if(rlp.count())if(rlp.last()==blp.first()) blp.removeFirst();
			rlp+=blp;
		}
	return rlp;
////////////////////////////////////////////
	switch(pltype)
	{
	case POLY_CONTINUOUS:
		for(int i=0; i<lc; i++)
		{
			blp=lines[i]->toPolylineD(d); 
			if(i!=lc-1) blp.removeLast();
			rlp+=blp;
		}
		break;

	case POLY_DISCONTINUOUS:
		for(int i=0; i<lc; i++)
		{
			blp=lines[i]->toPolylineD(d);
			rlp+=blp;
		}
		break;
	}
	return rlp;
}

List<Point> AlPolyline::toPolylineN(int n)
{return toPolylineD(length()/n);}


TransObject<AlPolyline> AlPolyline::SelectedPolyline(TMETRIC s1, TMETRIC s2)
{
	TransObject<AlPolyline> r;
	if(isEqual(s1,s2,TMETRIC_O)||Count()==0) return r;
	TMETRIC l=0;
	if(s2<s1) INTERCHANGE(s1,s2);	

	bool zone=false;
	for(int i=0; i<Count(); i++)
	{
		l+=At(i)->length();
		if(!zone)
		{
			if(l>s1)
			{
				zone=true;		
				AbstractLine *al=At(i)->clone();
				al->divideS(At(i)->length()-(l-s1));
				r.Obj()+=al;
				delete al;
			}
		}else
		{
			if(l<s2)
			{
				r.Obj()+=At(i);
			}else
			{
				AbstractLine *al=At(i)->clone();
				r.Obj().TakeLine(r.Obj().Count(),al->divideS(At(i)->length()-(l-s2)).PassObj());				
				delete al;
				break;
			}
		}
	}
	return r;
}


Point* AlPolyline::GetLinePoint(LinePointsType lp)
{
	Point *rp=0;
	switch(lp)
	{
		case LP_START: rp=&p1.Obj(); break;
		case LP_END: rp=&p2.Obj(); break;
		default: rp=0;
	}
	return rp;
}


Vector AlPolyline::InRCurvature()
{
	if(!Count()) return v_null;
	return First()->InRCurvature();
}

Vector AlPolyline::OutRCurvature()
{
	if(!Count()) return v_null;
	return Last()->OutRCurvature();
}

Vector AlPolyline::sRCurvature(TMETRIC s)
{
	AbstractLine *al=sLine(s);
	if(al==0) return v_null;
	return al->sRCurvature(s);
}

AbstractLine * AlPolyline::sLine(TMETRIC &s)
{
	if(!Count()) return 0;
	if(s>length())  return Last();
	if(s<=0) return First();
	TMETRIC l=0;
	for(int i=0; i<Count(); i++)
	{
		l+=lines[i]->length();
		if(s<=l)
		{
			s=lines[i]->length()-l+s;
			return lines[i];
		}
	}
	return Last();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void AlPolyline::AbstractConjugation(AbstractLine *al1, AbstractLine *al2, TMETRIC r)
{
	TurnFromDirectionToDirection(al1->OutDirection(),al2->InDirection(),r);
}
void AlPolyline::AbstractConjugationLong(AbstractLine *al1, AbstractLine *al2, TMETRIC r)
{
	TurnFromDirectionToDirection(al1->OutDirection(),al2->InDirection(),r);
}

void AlPolyline::TurnFromDirectionToDirectionAlt(Vector dir1,Vector dir2, TMETRIC r)
{
	Clear();
	Point T1=dir1.fulcrum;
	Point T2=dir2.fulcrum;
	Basis bd1; bd1.SetOrtoBasis_ByIJ(dir1,dir2);
	Basis bd2; bd2.SetOrtoBasis_ByIJ(dir2,dir1*(-1));
	Point O1(0,r,0,&bd1);
	Point O2(0,r,0,&bd2);
	Basis barc1; //!
	Basis barc2; //!
	Basis b12;
	barc1.SetOrtoBasis_ByIJ(Vector(O1,T1),dir1);
	barc2.SetOrtoBasis_ByIJ(Vector(O2,T2),dir2*(-1));
	b12.SetOrtoBasis_ByIJ(Vector(O1,O2),dir1);
	TMETRIC lo1o2=Vector(O1,O2).length();
	Point O_(lo1o2/2,sqrt(4*r*r-(lo1o2*lo1o2)/4),0,&b12);
	Basis b_; b_.SetOrtoBasis_ByIJ(Vector(O_,O1),Vector(O_,O2)*(-1));
	TAMETRIC fi=arccos((lo1o2/2)/(2*r));
	TAMETRIC a1=fi-Vector(O1,T1).Angle(Vector(O1,O2))*signum(T1.inBasis(&b12).y());
	TAMETRIC a2=fi-Vector(O2,T2).Angle(Vector(O2,O1))*signum(T2.inBasis(&b12).y());
	TAMETRIC a_=PI+2*fi;
	AlArcline al1(barc1,r,a1);
	AlArcline al2(barc2,r,a2);
	AlArcline al_(b_,r,a_);
	Add(&al1);
	Add(&al_);
	Add(&al2);
}

void AlPolyline::TurnFromDirectionToDirection(Vector dir1,Vector dir2, TMETRIC r)
{
	//bool isShortCNG=!lCNG;
	Clear();
	Point T1=dir1.fulcrum;
	Point T2=dir2.fulcrum;

	if(Vector(T1,T2).length()<TMETRIC_O){TurnFromDirectionToDirectionAlt(dir1,dir2,r); return;}
	Basis bd1; bd1.SetOrtoBasis_ByIJ(dir1,Vector(T1,T2));
	Basis bd2; bd2.SetOrtoBasis_ByIJ(dir2,Vector(T2,T1));
	Basis barc1; //!
	Basis barc2; //!
	TAMETRIC a1=0; //!
	TAMETRIC a2=0; //!
	Basis bprearc1;
	Basis bprearc2;
	TAMETRIC prea1=0;
	TAMETRIC prea2=0;
	TAMETRIC be=PI/2;

	Point O1(0,r,0,&bd1);
	Point O2(0,r,0,&bd2);
	Point preO1(0,-r,0,&bd1);
	Point preO2(0,-r,0,&bd2);
	bprearc1.SetOrtoBasis_ByIJ(Vector(preO1,T1),dir1);
	bprearc2.SetOrtoBasis_ByIJ(Vector(preO2,T2),dir2*(-1));

	bool crossed=((Vector(O1,T1)*dir1)&(Vector(O2,T2)*(dir2*(-1))))>0?true:false;

	if(!crossed)
	{
		O2.SetGlobalBasis();
		O2.SetBasis(&bd1);
		//TMETRIC  x1=O2.y-r;
	//	TMETRIC x2=O1.inBasis(&bd2).y-r;

		barc1.SetOrtoBasis_ByIJ(Vector(O1,T1),dir1);
		a1=PI/2-Vector::Angle(barc1.i,Vector(O2,O1))*signum(O2.inBasis(&barc1).y());
		AlArcline al1(barc1,r,a1); 

		if(((O2.inBasis(&bd1).y()<=r)&&((Vector(O1,O2)&dir1)>0))||((O1.inBasis(&bd2).y()<=r)&&((Vector(O1,O2)&dir2)>0)))
		//if((al1.OutDirection()&Vector(O1,O2))<0)
		{
			if(Vector(preO1,preO2).length()<r*2){TurnFromDirectionToDirectionAlt(dir1,dir2,r); return;}
		//	isShortCNG=false;
			TMETRIC h=Vector(preO1,preO2).length();
			TAMETRIC prea=(h>4*r)?0:arccos((h/2)/(2*r));
			prea1=abs(prea+(PI/2-Vector::Angle(Vector(preO1,preO2),bprearc1.j)));
			prea2=abs(prea+(PI/2-Vector::Angle(Vector(preO2,preO1),bprearc2.j)));
			dir1=AlArcline(bprearc1,r,prea1).OutDirection();
			dir2=AlArcline(bprearc2,r,prea2).OutDirection()*(-1);
			T1=dir1.fulcrum;
			T2=dir2.fulcrum;
			O1=(Vector(preO1,T1)*2).destination();
			O2=(Vector(preO2,T2)*2).destination();					
		}	
		be=PI/2;		
	}
	else
	{
		if(Vector(O1,O2).length()<=2*r)
		{
	//		isShortCNG=false;
			TMETRIC h=Vector(preO1,preO2).length();
			if(h<=2*r) {TurnFromDirectionToDirectionAlt(dir1,dir2,r); return;}
			TAMETRIC prea=arccos((h*h/4+3*r*r)/(2*h*r));
			prea1=abs(prea+(PI/2-Vector::Angle(Vector(preO1,preO2),bprearc1.j)));
			prea2=abs(prea+(PI/2-Vector::Angle(Vector(preO2,preO1),bprearc2.j)));
			dir1=AlArcline(bprearc1,r,prea1).OutDirection();
			dir2=AlArcline(bprearc2,r,prea2).OutDirection()*(-1);
			T1=dir1.fulcrum;
			T2=dir2.fulcrum;
			O1=(Vector(preO1,T1)*2).destination();
			O2=(Vector(preO2,T2)*2).destination();
		}		
		be=PI-arccos(r/(Vector(O1,O2).length()/2));
	}	

		barc1.SetOrtoBasis_ByIJ(Vector(O1,T1),dir1);
		barc2.SetOrtoBasis_ByIJ(Vector(O2,T2),dir2*(-1));

		if(O1==O2)
		{
			a1=PI+Vector::Angle(dir1,dir2*(-1));
			a2=0;
		}else
		{
			a1=be-Vector::Angle(barc1.i,Vector(O2,O1))*signum(O2.inBasis(&barc1).y());
			a2=be-Vector::Angle(barc2.i,Vector(O1,O2))*signum(O1.inBasis(&barc2).y());
			if(a1<0)a1=2*be-a1;
			if(a2<0)a1=2*be-a1;
			//a1=be-Vector::Angle(barc1.i,Vector(preO2,preO1))*signum(O2.inBasis(&barc1).y);
			//a2=be-Vector::Angle(barc2.i,Vector(preO1,preO2))*signum(O1.inBasis(&barc2).y);		
		}

		//a1=be-Vector::Angle(barc1.i,O1==O2?Vector(preO2,preO1):Vector(O2,O1))*signum(O2.inBasis(&barc1).y);
		//a2=be-Vector::Angle(barc2.i,O1==O2?Vector(preO1,preO2):Vector(O1,O2))*signum(O1.inBasis(&barc2).y);
		AlArcline al1(barc1,r,a1); 
		AlArcline al2(barc2,r,a2);
		AlLine l(al1.EndPoint(),al2.EndPoint());
	
	//	if(a1<0||a2<0||prea1<0||prea2<0){TurnFromDirectionToDirectionAlt(dir1,dir2,r); return isShortCNG;}

	AlArcline preal1(bprearc1,r,prea1); 
	AlArcline preal2(bprearc2,r,prea2);

	if(preal1.length()>TMETRIC_O) Add(&preal1);
	if(al1.length()>TMETRIC_O)	Add(&al1);
	if(l.length()>TMETRIC_O) Add(&l);
	if(al2.length()>TMETRIC_O)	Add(&al2);
	if(preal2.length()>TMETRIC_O) Add(&preal2);

}



void AlPolyline::TurnFromDirectionToPoint( Vector dir,  Point p, TMETRIC r)
{
	TurnFromPointToDirection(dir*(-1),p,r);
	Invert();
}

void AlPolyline::TurnFromPointToDirection( Vector dir,  Point p, TMETRIC r)
{
	Clear();
	Basis b;	
	b.SetOrtoBasis_ByIJ(dir,Vector(dir.fulcrum,p));
	if(Vector(p,Point(0,r,0,&b)).length()>r)
	{
		Basis arcbas;
		TAMETRIC angle;
		Point pl_1=dir.fulcrum;
		Point pl_2=dir.destination();		
		Vector v12(pl_1,pl_2);
		Vector v1p(pl_1,p);
		Vector vW=(v1p*v12).e();
		Vector vO1=(v12*vW).e()*r;
		Point O=vO1.destination();
		Vector vOp(O,p); if(vOp.length()<=r) return;
		vO1.invert();
		arcbas.SetOrtoBasis_ByIJ(vO1,Vector(pl_2,pl_1));	
		TAMETRIC aO1Op=Vector::Angle(vO1,vOp);
		p.SetBasis(&arcbas);
		if(p.y()<0) aO1Op=2*PI-aO1Op;
		TAMETRIC a_=arccos(r/vOp.length());
		angle=aO1Op-a_;
		//////////////////////////////////////////////////////////////////////////
		AlArcline al(arcbas,r,angle);
		Add(&AlLine(p,al.EndPoint()));
		Add(&al);
	}
	else
	{		
		Point O1(0,-r,0,&b);
		p.SetBasis(&b);
		Vector vO1p(O1,p);
		TMETRIC d=vO1p.length();
		TAMETRIC a=arccos((d*d+3*r*r)/(4*d*r));
		TAMETRIC a1=Vector::Angle(Vector(O1,dir.fulcrum),vO1p);
		TAMETRIC al1_a=a+a1*(p.x()>0?-1:1);		
		vO1p.SetBasis(&b);
		vO1p.rotate_Z(a); vO1p.fulcrum=O1;
		Point O2=(vO1p.e()*2*r).destination();
		TAMETRIC al2_a=2*PI-Vector::Angle(Vector(O2,p),Vector(O2,O1));
		Basis al1_b; al1_b.SetOrtoBasis_ByIJ(Vector(O1,dir.fulcrum),dir*(-1));
		Basis al2_b; al2_b.SetOrtoBasis_ByIJ(Vector(O2,O1),Vector(O2,p)*(-1));
		AlArcline al1(al1_b,r,al1_a);		
		AlArcline al2(al2_b,r,al2_a);
		Add(&al1);
		Add(&al2);
	}
}


// AlPolyline AlPolyline::ClearSelfIntersections()
// {
// 	AlPolyline ret;
// 	for(int i=0; i<Count()-1; i++)
// 	{
// 		Point crosp(false);
// 		int cros_i1=i;
// 		int cros_i2=-1;
// 		for(int j=i+1; j<Count(); j++)
// 		{
// 			List<Point> intr=LinesIntersections(At(i),At(j));
// 			if(intr.count())
// 			{
// 				if(crosp.isNull()) {crosp=intr.first(); cros_i2=j;}			
// 			}
// 		}
// 	}
// 	return ret;
// }


// void AlPolyline::ClearSelfIntersections_NeighborsOnly()
// {
// 	for(int i=0; i<Count()-1; i++)
// 	{
// 		if(At(i)->line_type==LT_POLYLINE) ((AlPolyline*)At(i))->ClearSelfIntersections_NeighborsOnly();
// 		if(At(i+1)->line_type==LT_POLYLINE) ((AlPolyline*)At(i+1))->ClearSelfIntersections_NeighborsOnly();
// 		List<Point> inte=LinesIntersections(At(i),At(i+1));		
// 		if(inte.count())
// 		{
// 			if(inte.first()==At(i)->EndPoint()) continue;
// 			LEN.RemoveMaster(At(i)->LEN);
// 			AbstractLine *al=At(i)->divideS(At(i)->SCoordinateFromPoint(inte.first())).PassObj();
// 			LEN.AddMaster(al->LEN);
// 			Remove(i);
// 			lines.Insert(i,al);			
// 			/*PhantomObject<AbstractLine> delAL=*/
// 			At(i+1)->divideS(At(i+1)->SCoordinateFromPoint(inte.first()));
// 		}
// 	}
// }


void AlPolyline::ConvertToSimplePolyline()
{
	for(int i=0; i<Count(); i++)
	{
		if(At(i)->line_type==LT_POLYLINE)
		{
			AlPolyline *inpoly=(AlPolyline*)At(i);
			lines.removeAt(i); LEN.RemoveMaster(inpoly->LEN);
			inpoly->ConvertToSimplePolyline();			
			for(int j=0; j<inpoly->Count(); j++)
			{				
				lines.Insert(i+j,inpoly->At(j));
				LEN.AddMaster(inpoly->At(j)->LEN);
				inpoly->At(j)->SetParentLine(this);
			}
			i+=inpoly->Count()-1;
			inpoly->lines.clear();
			delete inpoly;				
		}
	}
}


void AlPolyline::ConvertToSimplePolyline(AlPolyline &al)
{
	for(int i=0; i<Count(); i++)
	{
		if(At(i)->line_type==LT_POLYLINE)
		{
			((AlPolyline*)At(i))->ConvertToSimplePolyline(al);				
		}else
		{
			al+=At(i);
		}
	}
}


TransALine AlPolyline::PassLine(int index)
{
	if(index<0||index>Count()) return TransALine();
	TransALine tal(At(index));
	LEN.RemoveMaster(tal.Obj().LEN);	
	lines.removeAt(index);
	tal.Obj().detachJ();	
	tal.Obj().SetParentLine(0);
	return tal;
}


void AlPolyline::TakeLine(AbstractLine * al)
{
	if(al==0) return;
	LEN.AddMaster(al->LEN);
	if(lines.count()) al->insertAsNext(*lines.last()); //lines.last()->insertAsNext(*al);
	lines+=al;
	al->SetParentLine(this);
}

void AlPolyline::TakeLine(int index, AbstractLine *al)
{
	if(al==0) return;
	LEN.AddMaster(al->LEN);
	al->insertAsPrevious(*lines[index]);
	lines.Insert(index,al);
	al->SetParentLine(this);
}










//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////// TRASH ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////



void AlPolyline::ArcConjugation2ParallelLines(AlLine &l1, AlLine &l2, TMETRIC r, bool l1p_end)
{
	Clear();
	pltype=POLY_AUTOJOINING;
	Point l1p1;
	Point l1p2;
	Point l2p1;
	Point l2p2;
	if(l1p_end){ l1p1=l1.EndPoint(); l1p2=l1.StartPoint();}
	else{ l1p1=l1.StartPoint(); l1p2=l1.EndPoint();}
	l2p1=l2.EndPoint();
	l2p2=l2.StartPoint();
	if(Vector(l2p1,l1p1).length()>Vector(l2p2,l1p1).length()){Point bp=l2p1; l2p1=l2p2; l2p2=bp; }
	Vector v1(l1p1,l1p2);	
	Basis b; b.SetOrtoBasis_ByIJ(v1,Vector(v1.fulcrum,l2p1));
	Vector v2(l2p1,l2p2);
	l2p1.SetBasis(&b);
	l2p1.SetLocalX(0);
	TMETRIC h=Vector(l1p1,l2p1).length();

	if(h>2*r)
	{
		Point l3p1(-r,r,0,&b); l3p1.SetGlobalBasis();
		Point l3p2(-r,l2p1.y()-r,0,&b); l3p2.SetGlobalBasis();//l2p1.SetGlobalBasis();
		AlLine l3(l3p1,l3p2);
		Basis bal; bal.SetOrtoBasis_ByOXY(Point(0,r,0,&b),Point(0,0,0,&b),Point(-r,0,0,&b));
		AlArcline al1(bal,r,PI/2);
		bal.SetOrtoBasis_ByOXY(Point(0,h-r,0,&b),Point(0,h,0,&b),Point(-r,h-r,0,&b));
		AlArcline al2(bal,r,PI/2); 
		Add(&al1); Add(&l3); Add(&al2);
	}
	else if(h<2*r)
	{
		Point al1_O(0,-r,0,&b);
		Point al2_O(0,r+h,0,&b);
		Point al3_O(-sqrt(3*r*r-r*h-h*h/4),h/2,0,&b);
		Basis al1_b; al1_b.SetOrtoBasis_ByOXY(al1_O,l1p1,al3_O);
		Basis al2_b; al2_b.SetOrtoBasis_ByOXY(al2_O,l2p1,al3_O);
		Basis al3_b; al3_b.SetOrtoBasis_ByIJ(Vector(al3_O,al1_O),Vector(al2_O,al3_O));
		TAMETRIC al1_a=Vector::Angle(Vector(al1_O,l1p1),Vector(al1_O,al3_O));
		TAMETRIC al2_a=Vector::Angle(Vector(al2_O,l2p1),Vector(al2_O,al3_O));
		TAMETRIC al3_a=2*PI-Vector::Angle(Vector(al3_O,al1_O),Vector(al3_O,al2_O));
		AlArcline al1(al1_b,r,al1_a);
		AlArcline al2(al2_b,r,al2_a);
		AlArcline al3(al3_b,r,al3_a);
		Add(&al1);
		Add(&al3);
		Add(&al2);
	} else if(h==2*r)
	{
		Point al_O(0,r,0,&b);
		Basis al_b; al_b.SetOrtoBasis_ByIJ(Vector(al_O,l1p1),Vector(l1p2,l1p1));
		AlArcline al(al_b,r,PI);
		Add(&al);
	}
}


/*
void AlPolyline::ArcTurnToPoint(AlLine l, Point p, TMETRIC r,  bool lp_end )
{
	Clear();
	Point lp1;
	Point lp2;
	lp1=*l.GetLinePoint(lp_end?LP_END:LP_START);
	lp2=*l.GetLinePoint(lp_end?LP_START:LP_END);
	Basis b;
	b.SetOrtoBasis_ByOXY(lp1,lp2,p);

	if(Vector(p,Point(0,r,0,&b)).length()>r)
	{
		AlArcline al;
		AlLine ll=al.ArcTurnToPoint(l,p,r,lp_end?LP_END:LP_START);
		Add(&al);
		Add(&ll);
	}
	else
	{		
		Point O1(0,-r,0,&b);
		p.SetBasis(&b);
		Vector vO1p(O1,p);
		TMETRIC d=vO1p.length();
		TAMETRIC a=arccos((d*d+3*r*r)/(4*d*r));
		TAMETRIC a1=Vector::Angle(Vector(O1,lp1),vO1p);
		TAMETRIC al1_a=a+a1*(p.x()>0?-1:1);		
		vO1p.SetBasis(&b);
		vO1p.rotate_Z(a); vO1p.fulcrum=O1;
		Point O2=(vO1p.e()*2*r).destination();
		TAMETRIC al2_a=2*PI-Vector::Angle(Vector(O2,p),Vector(O2,O1));
		Basis al1_b; al1_b.SetOrtoBasis_ByIJ(Vector(O1,lp1),Vector(lp2,lp1));
		Basis al2_b; al2_b.SetOrtoBasis_ByIJ(Vector(O2,O1),Vector(O2,p)*(-1));
		AlArcline al1(al1_b,r,al1_a);		
		AlArcline al2(al2_b,r,al2_a);
		Add(&al1);
		Add(&al2);
	}

	QWE<int> abc;
	int a=abc.fun(3,5);
}

*/
