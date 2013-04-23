#include <Bikes/BikesStream.h>
#include <Bikes/BasicGeometry.h>


namespace Bikes
{
	BIKES_OBJECTSTREAMER_DEF(PointStreamer, (p->gx,p->gy,p->gz), () )
	BIKES_OBJECTSTREAMER_DEF(VectorStreamer, (p->gx,p->gy,p->gz), (PointStreamer(&p->anchor)) )
	BIKES_OBJECTSTREAMER_DEF_EXTENDED(BasisStreamer, (p->i.gx,p->i.gy,p->i.gz,p->j.gx,p->j.gy,p->j.gz,p->k.gx,p->k.gy,p->k.gz), (PointStreamer(&p->O)), p->setO(p->O) )

} //Bikes