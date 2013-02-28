#include "DrawGeometryTools.h"

using namespace CppBikes;



ScreenZone& ScreenZone::operator = (char hv_)
{
	//hv=hv_;
	h=hv_/10;
	v=hv_%10;
	return *this;
}


ScreenZone& ScreenZone::operator = (const ScreenZone&  sz)
{
	h=sz.h;
	v=sz.v;
	//hv=sz.hv;
	return *this;
}

bool ScreenZone::operator == (char hv) const
{
	return (h==hv/10)&&(v==hv%10);
}

void ScreenZone::set( char h_, char v_ )
{
	h=h_;
	v=v_;
	//hv=h_*10+v_;
}




inline bool CppBikes::PointInScreenRect(const ScreenPoint &p, const ScreenRect &scr)
{
	return (p.x>=scr.x1)&&(p.x<=scr.x2)&&(p.y>=scr.y1)&&(p.y<=scr.y2);
}

ScreenZone CppBikes::ScreenZoneOfPoint(const ScreenPoint &p, const ScreenRect &scr )
{
	char v=2;
	char h=2;
	if(p.x<scr.x1) v=1;
	else if(p.x>scr.x2) v=3;	

	if(p.y<scr.y1) h=1;
	else if(p.y>scr.y2) h=3;

	return ScreenZone(h,v);
}


bool LineSegmentCrossScreenRect_ambiguous( const ScreenPoint &p1, const ScreenZone &p1z, const ScreenPoint &p2, const ScreenZone &p2z, const ScreenRect &scr )
{
	
	
	if(p1.x>p2.x) return LineSegmentCrossScreenRect_ambiguous(p2,p2z,p1,p1z,scr);
	
	// реализация только для направления  (p1)>-->(p2)
	
	RNUM dx=p2.x-p1.x;

	 if(p1z.v==1) 
	 {
		 if(p2z.h==1)
		 {		 
			 // 11 ->
			 RNUM dy=-p2.y+p1.y;
			 if(dy*(scr.x1-p1.x) > (-scr.y1+p1.y)*dx) return false;
			 if(p1z.h==3&&p2z.v==3)
			 {
				 return (dy*(scr.x2-p1.x) > (-scr.y2+p1.y)*dx );			 
			 }
			 return true;
			 // <- 11
		 }
		// 31 ->
		// ...
		if(p2z.h==3)
		{
			RNUM dy=p2.y-p1.y;
			if(dx*(scr.y2-p1.y) < (scr.x1-p1.x)*dy ) return false;
			if(p1z.h==1&&p2z.v==3)
			{
				return dx*(scr.y1-p1.y) < (scr.x2-p1.x)*dy;
			}
			return true;
		}
		// <- 31
	 }	 
	 
	 // 13 ->
	if(p1z.h==1) 
	{
		/*p2z.v==3*/
		RNUM dy=p2.y-p1.y;
		return (dx*(scr.y1-p1.y) < (scr.x2-p1.x)*dy);
	}
	 // <- 13
	 
	 // 33 ->
	/*(p1z.h==3&&p2z.v==3)*/
	RNUM dy=-p2.y+p1.y;
	 //...
	 return  dy*(scr.x2-p1.x) > (p1.y-scr.y2)*dx;
	 // <- 33


}

bool CppBikes::LineSegmentCrossScreenRect( const ScreenPoint &p1, const ScreenZone &p1z, const ScreenPoint &p2, const ScreenZone &p2z, const ScreenRect &scr )
{
	if(p1z.v==p2z.v) // в одной вертикале 
	{
		if(p1z.v==2) // в центральной вертикале
		{
			return !(p1z.h==p2z.h&&p1z.h!=2);  // в периферийных горизонталях | в видимой области			
		}
		return false; // в периферийных вертикалях
	}

	if(p1z.h==p2z.h) // в одной горизонтале 
	{
		return (p1z.h==2); // в видимой области | в периферии		
	}

	if((p1z.h==2&&p1z.v==2)||(p2z.h==2&&p2z.v==2)) return true; // в диагонале (в видимой области)


	// * * * * * * * * * * * * * * * * * * * * 
	 
	// в неоднозначных областях (редкий случай) ->


	return LineSegmentCrossScreenRect_ambiguous(p1,p1z,p2,p2z,scr);

}

bool CppBikes::LineSegmentCrossScreenRect( const ScreenPoint &p1, const ScreenPoint &p2, const ScreenRect &scr )
{
	return LineSegmentCrossScreenRect(p1,ScreenZoneOfPoint(p1,scr),p2,ScreenZoneOfPoint(p2,scr),scr);
}

