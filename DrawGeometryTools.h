#ifndef BIKES_DRAWGEOMETRYTOOLS_H
#define BIKES_DRAWGEOMETRYTOOLS_H

#include <CppBikes/BasicMath.h>
#include <CppBikes/BasicGeometry.h>

/**********************************************************************************************//**
 
	схема зон экрана (22 - видима€ область)

	v=1   v=2   v=3
	11 |  12  | 13	h=1			|--> x
y1	---|------|---				|
	21 |  22  | 23	h=2			V 
y2	---|------|---				y
	31 |  32  | 33	h=3
	   x1     x2

 **************************************************************************************************/

namespace CppBikes
{	
	struct ScreenPoint
	{
		ScreenPoint(RNUM x_=0, RNUM y_=0):x(x_),y(y_){}
		RNUM x;
		RNUM y;
	};

	struct ScreenRect
	{
		ScreenRect(RNUM x1_=0,RNUM x2_=0, RNUM y1_=0, RNUM y2_=0):x1(x1_),y1(y1_),x2(x2_),y2(y2_){}
		RNUM x1; // лева€ граница
		RNUM x2; // права€ граница
		RNUM y1; // верхн€€ граница 
		RNUM y2; // нижн€€ граница 
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
	
}
#endif