#include <Bikes/BikeStreamer.h>
#include <Bikes/BasicGeometry.h>


namespace Bikes
{
	BIKES_OBJECTSTREAMER_DEF(PointStreamer, 
							add(p->gx);
							add(p->gy);
							add(p->gz);
							)

	BIKES_OBJECTSTREAMER_DEF(VectorStreamer,
							add(p->gx);
							add(p->gy);
							add(p->gz);
							add(PointStreamer(&p->anchor))
							)

	BIKES_OBJECTSTREAMER_DEF_EXTENDED(BasisStreamer,
									add(p->i.gx);
									add(p->i.gy);
									add(p->i.gz);
									add(p->j.gx);
									add(p->j.gy);
									add(p->j.gz);
									add(p->k.gx);
									add(p->k.gy);
									add(p->k.gz);
									add(PointStreamer(&p->O)),
									p->setO(p->O) )

} //Bikes
