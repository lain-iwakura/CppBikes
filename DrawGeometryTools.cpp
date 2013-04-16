#include "DrawGeometryTools.h"

namespace Bikes
{



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




inline bool PointInScreenRect(const ScreenPoint &p, const ScreenRect &scr)
{
	return (p.x>=scr.x1)&&(p.x<=scr.x2)&&(p.y>=scr.y1)&&(p.y<=scr.y2);
}

ScreenZone ScreenZoneOfPoint(const ScreenPoint &p, const ScreenRect &scr )
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
	
	rnum dx=p2.x-p1.x;

	 if(p1z.v==1) 
	 {
		 if(p2z.h==1)
		 {		 
			 // 11 ->
			 rnum dy=-p2.y+p1.y;
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
			rnum dy=p2.y-p1.y;
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
		rnum dy=p2.y-p1.y;
		return (dx*(scr.y1-p1.y) < (scr.x2-p1.x)*dy);
	}
	 // <- 13
	 
	 // 33 ->
	/*(p1z.h==3&&p2z.v==3)*/
	rnum dy=-p2.y+p1.y;
	 //...
	 return  dy*(scr.x2-p1.x) > (p1.y-scr.y2)*dx;
	 // <- 33


}

bool LineSegmentCrossScreenRect( const ScreenPoint &p1, const ScreenZone &p1z, const ScreenPoint &p2, const ScreenZone &p2z, const ScreenRect &scr )
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

bool LineSegmentCrossScreenRect( const ScreenPoint &p1, const ScreenPoint &p2, const ScreenRect &scr )
{
	return LineSegmentCrossScreenRect(p1,ScreenZoneOfPoint(p1,scr),p2,ScreenZoneOfPoint(p2,scr),scr);
}

ScreenPoint findCrossH(const ScreenPoint &p1, const ScreenPoint &p2, rnum hy)
{
	return ScreenPoint( ((hy-p1.y)*p2.x+(p2.y-hy)*p1.x)/not0(p2.y-p1.y) , hy );
}

ScreenPoint findCrossV(const ScreenPoint &p1, const ScreenPoint &p2, rnum hx)
{
	return ScreenPoint( hx , ((hx-p1.x)*p2.y+(p2.x-hx)*p1.y)/not0(p2.x-p1.x) );
}

bool LineSegmentCrossScreenRect(	const ScreenPoint &p1, 
									  const ScreenPoint &p2,
									  const ScreenRect &scr, 
									  List<ScreenPoint> &crossPoints)
{
	return LineSegmentCrossScreenRect(p1,ScreenZoneOfPoint(p1,scr),p2,ScreenZoneOfPoint(p2,scr),scr,crossPoints);
}



bool LineSegmentCrossScreenRect(	const ScreenPoint &p1,  
									  const ScreenZone &p1z, 
									  const ScreenPoint &p2,  
									  const ScreenZone &p2z, 
									  const ScreenRect &scr, 
									 List<ScreenPoint> &crossPoints)
{	

	if(p1z.v!=p2z.v)
	{
		if(p1z.v==1||p2z.v==1)
		{		
			const ScreenPoint &cp=findCrossV(p1,p2,scr.x1);
			if(cp.y>scr.y1&&cp.y<scr.y2)
			{
				crossPoints+=cp;
			}
		}

		if(p1z.v==3||p2z.v==3)
		{		
			const ScreenPoint &cp=findCrossV(p1,p2,scr.x2);
			if(cp.y>scr.y1&&cp.y<scr.y2)
			{
				crossPoints+=cp;				
			}
		}
	}
	
	if(crossPoints.count()<2)
	{
		if(p1z.h!=p2z.h)
		{	
			if(p1z.h==1||p2z.h==1)
			{			
				const ScreenPoint &cp=findCrossH(p1,p2,scr.y1);
				if(cp.x>scr.x1&&cp.x<scr.x2)
				{
					crossPoints+=cp;
				}
			}

			if(crossPoints.count()<2)
			{
				if(p1z.h==3||p2z.h==3)
				{			
					const ScreenPoint &cp=findCrossH(p1,p2,scr.y2);
					if(cp.x>scr.x1&&cp.x<scr.x2)
					{
						crossPoints+=cp;
					}
				}
			}
		}
	}
	
	if(crossPoints.count()==2)
	{
		if(crossPoints[0].x!=crossPoints[1].x)
		{
			if( (crossPoints[0].x<crossPoints[1].x) != (p1.x<p2.x) )
			{
				crossPoints.invert();
			}
		}else
		{
			if( (crossPoints[0].y<crossPoints[1].y) != (p1.y<p2.y) )
			{
				crossPoints.invert();
			}
		}
	}

	return crossPoints.count();

// 	if(p1.x>p2.x)
// 	{
// 		//TODO: перевернуть
// 	}

	/*
	int cpi=0;
	if(p1z.v!=p2z.v)
	{
		if(p1z.v==1||p2z.v==1)
		{		
			const ScreenPoint &cp=findCrossV(p1,p2,scr.x1);
			if(cp.y>scr.y1&&cp.y<scr.y2)
			{
				CrossPoints+=cp; cpi++;
			}
		}

		if(p2z.v==3||p1z.v==3)
		{		
			const ScreenPoint &cp=findCrossV(p1,p2,scr.x2);
			if(cp.y>scr.y1&&cp.y<scr.y2)
			{
				CrossPoints+=cp; cpi++;
				if(cpi>1) return;
			}
		}
	}

	if(p1z.h!=p2z.h)
	{
		if(p1z.h==1||p2z.h==1)
		{
			const ScreenPoint &cp=findCrossH(p1,p2,scr.y1);
			if(cp.x>scr.x1&&cp.x<scr.x2)
			{
				CrossPoints+=cp;cpi++;
				if(cpi>1) return;
			}
		}

		if(p1z.h==3||p2z.h==3)
		{
			const ScreenPoint &cp=findCrossH(p1,p2,scr.y2);
			if(cp.x>scr.x1&&cp.x<scr.x2)
			{
				CrossPoints+=cp;
			}
		}
	}
//*/
/*
	if(p1z.v==p2z.v) // в одной вертикале 
	{
		if(p1z.v==2) // в центральной вертикале
		{
// 			if(p1z.h==p2z.h&&p1z.h!=2)  // в периферийных горизонталях 
// 			{
// 				return false;
// 			}else //
			if(p1z.h!=p2z.h) // в разных горизонталях
			{
				// TODO: ищем пересечения
				if(p1z.h==1||p2z.h==1)
				{
					CrossPoints+=findCrossH(p1,p2,scr.y1);				
				}				
				if(p1z.h==3||p2z.h==3)
				{					
					CrossPoints+=findCrossH(p1,p2,scr.y2);
				}				
				return true;
			}else 
			{
				return p1z.h==2;
			}
		}
		return false; // в периферийных вертикалях
	}

	if(p1z.h==p2z.h) // в одной горизонтале 
	{
		//return (p1z.h==2); // в видимой области | в периферии		
		if(p1z.h==2)
		{
			if(p1z.v==1||p2z.v==1)
			{
				CrossPoints+=findCrossV(p1,p2,scr.x1);
			}
			if(p1z.v==3||p2z.v==3)
			{
				CrossPoints+=findCrossV(p1,p2,scr.x2);
			}
			return true;
		}else
		{
			return false;
		}
	}

	if((p1z.h==2&&p1z.v==2)||(p2z.h==2&&p2z.v==2)) return true; // в диагонале (в видимой области)


	// * * * * * * * * * * * * * * * * * * * * 

	// в неоднозначных областях (редкий случай) ->
//*/
//	return false;
}

}

