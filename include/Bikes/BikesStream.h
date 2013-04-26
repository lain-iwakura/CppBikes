#ifndef _BIKES_BIKESSTREAM_H_
#define _BIKES_BIKESSTREAM_H_
#include <Bikes/ObjectStreamer.h>

namespace Bikes
{
	class Point;
	class Vector;
	class Basis;
	
	BIKES_OBJECTSTREAMER_DECL(PointStreamer,	Point)
	BIKES_OBJECTSTREAMER_DECL(VectorStreamer,	Vector)
	BIKES_OBJECTSTREAMER_DECL(BasisStreamer,	Basis)

} // Bikes

#endif