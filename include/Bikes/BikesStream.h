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

	BIKES_MULTITYPESTREAMER_DECLDEF(BikesMultiTypeStreamer,	
		add<PointStreamer>();
		add<VectorStreamer>();
		add<BasisStreamer>();			
		add<ValueStreamer<bool> >();
		add<ValueStreamer<char> >();
		add<ValueStreamer<short> >();
		add<ValueStreamer<unsigned short> >();
		add<ValueStreamer<int> >();
		add<ValueStreamer<unsigned int> >();
		add<ValueStreamer<long> >();
		add<ValueStreamer<unsigned long> >();
		add<ValueStreamer<unsigned long long> >();
		add<ValueStreamer<float> >();
		add<ValueStreamer<double> >();
	)

} // Bikes

#endif