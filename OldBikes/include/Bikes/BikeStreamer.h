#ifndef PREBIKES_BIKESTREAMER_H
#define PREBIKES_BIKESTREAMER_H
#include <Bikes/ObjectStreamer.h>

namespace Bikes
{
	class Point;
	class Vector;
	class Basis;
	struct PhiLamPoint;
	struct PhiLamHPoint;

	
	BIKES_OBJECTSTREAMER_DECL(PointStreamer,			Point			)
	BIKES_OBJECTSTREAMER_DECL(VectorStreamer,			Vector			)
	BIKES_OBJECTSTREAMER_DECL(BasisStreamer,			Basis			)
	BIKES_OBJECTSTREAMER_DECL(PhiLamPointStreamer,		PhiLamPoint		)
	BIKES_OBJECTSTREAMER_DECL(PhiLamHPointStreamer,		PhiLamHPoint	)

	
 	BIKES_MULTITYPESTREAMER_DECLDEF(MultiValueStreamer,
 						BIKES_MULTITYPESTREAMER_ADDVALUESTREAMER
 						)

 	BIKES_MULTITYPESTREAMER_DECLDEF(MultiBikeStreamer,	
 		add<PointStreamer>();
 		add<VectorStreamer>();
 		add<BasisStreamer>();			
 		BIKES_MULTITYPESTREAMER_ADDVALUESTREAMER
 		)


	



} // Bikes

#endif