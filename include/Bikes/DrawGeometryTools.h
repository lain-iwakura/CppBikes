#ifndef PREBIKES_DRAWGEOMETRYTOOLS_H
#define PREBIKES_DRAWGEOMETRYTOOLS_H

#include <Bikes/BasicMath.h>
#include <Bikes/BasicGeometry.h>

/**********************************************************************************************//**
 
	схема зон экрана (22 - видимая область)

	v=1   v=2   v=3
	11 |  12  | 13	h=1			|--> x
y1	---|------|---				|
	21 |  22  | 23	h=2			V 
y2	---|------|---				y
	31 |  32  | 33	h=3
	   x1     x2

 **************************************************************************************************/

namespace Bikes
{	
	struct ScreenPoint
	{
		ScreenPoint(rnum x_=0, rnum y_=0):x(x_),y(y_){}
		rnum x;
		rnum y;
	}; 

	struct ScreenRect
	{
		ScreenRect(rnum x1_=0,rnum x2_=0, rnum y1_=0, rnum y2_=0):x1(x1_),y1(y1_),x2(x2_),y2(y2_){}
		rnum x1; // левая граница
		rnum x2; // правая граница
		rnum y1; // верхняя граница 
		rnum y2; // нижняя граница 
		// x2 > x1
		// y2 > y1
	};

	struct ScreenZone
	{
		ScreenZone (char h_=0, char v_=0):h(h_),v(v_)/*,hv(h_*10+v_)*/{}
		char h;
		char v;
		//char hv;	
		void set(char h_, char v_);
		bool operator == (char hv) const;
		ScreenZone& operator = (char hv);
		ScreenZone& operator = (const ScreenZone&  scrz);

	};

	inline bool PointInScreenRect(const ScreenPoint &p, const ScreenRect &scr);

	ScreenZone ScreenZoneOfPoint(const ScreenPoint &p, const ScreenRect &scr);

	bool LineSegmentCrossScreenRect(const ScreenPoint &p1, const ScreenZone &p1_zone, const ScreenPoint &p2, const ScreenZone &p2_zone, const ScreenRect &scrRect);

	bool LineSegmentCrossScreenRect(const ScreenPoint &p1, const ScreenPoint &p2, const ScreenRect &scr);



// (?) ->

	bool LineSegmentCrossScreenRect(	const ScreenPoint &p1, 
										const ScreenPoint &p2,
										const ScreenRect &scr, 
								List<ScreenPoint> &crossPoints);

	bool LineSegmentCrossScreenRect(	const ScreenPoint &p1,  
										const ScreenZone &p1z, 
										const ScreenPoint &p2,  
										const ScreenZone &p2z, 
										const ScreenRect &scr, 
										List<ScreenPoint> &crossPoints);
// <- (?)
	
//	List<ScreenPoint> FindLineSegmentCrossScreenRect( const ScreenPoint &p1, const ScreenZone &p1z, const ScreenPoint &p2, const ScreenZone &p2z, const ScreenRect &scr );
	
}
#endif