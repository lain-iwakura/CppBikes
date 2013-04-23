#ifndef _BIKES_BIKESSTREAM_H_
#define _BIKES_BIKESSTREAM_H_
#include <Bikes/ObjectStream.h>

namespace Bikes
{

	BIKES_OBJECTSTREAMER_DECL(PointStreamer,	Point)
	BIKES_OBJECTSTREAMER_DECL(VectorStreamer,	Vector)
	BIKES_OBJECTSTREAMER_DECL(BasisStreamer,	Basis)

} // Bikes

#endif