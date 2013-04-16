#include <Bikes/BikesStream.h>
#include <Bikes/BasicGeometry.h>


namespace Bikes
{
	


	void PointStreamer::read(Point* p )
	{
		read(byteStream_(),p);
	}

	void PointStreamer::write(const Point* p )
	{
		write(byteStream_(),p);
	}

	void PointStreamer::read( ByteStream &bstr, Point* p )
	{
		bstr >> p->gx;
		bstr >> p->gy;
		bstr >> p->gz;	
	}

	void PointStreamer::write( ByteStream &bstr, const Point* p )
	{
		bstr << p->gx;
		bstr << p->gy;
		bstr << p->gz;		
	}


	void VectorStreamer::read( Vector* v )
	{
		read(byteStream_(),v);
	}

	void VectorStreamer::read( ByteStream &bstr, Vector *v )
	{
		PointStreamer::read(bstr,&v->anchor);
		bstr >> v->gx;
		bstr >> v->gy;
		bstr >> v->gz;
	}

	void VectorStreamer::write( const Vector* v )
	{
		write(byteStream_(),v);
	}

	void VectorStreamer::write( ByteStream &bstr, const Vector *v )
	{
		PointStreamer::write(bstr,&v->anchor);
		bstr << v->gx;
		bstr << v->gy;
		bstr << v->gz;
	}


	void BasisStreamer::read( Basis* b )
	{
		read(byteStream_(),b);
	}

	void BasisStreamer::read( ByteStream &bstr, Basis *b )
	{
		PointStreamer::read(bstr,&b->O);
		b->i.anchor=b->O;
		b->j.anchor=b->O;
		b->k.anchor=b->O;
		bstr >> b->i.gx;
		bstr >> b->i.gy;
		bstr >> b->i.gz;
		bstr >> b->j.gx;
		bstr >> b->j.gy;
		bstr >> b->j.gz;
		bstr >> b->k.gx;
		bstr >> b->k.gy;
		bstr >> b->k.gz;
	}

	void BasisStreamer::write( const Basis* b )
	{
		write(byteStream_(),b);
	}

	void BasisStreamer::write( ByteStream &bstr, const Basis *b )
	{
		PointStreamer::write(bstr,&b->O);		
		bstr << b->i.gx;
		bstr << b->i.gy;
		bstr << b->i.gz;
		bstr << b->j.gx;
		bstr << b->j.gy;
		bstr << b->j.gz;
		bstr << b->k.gx;
		bstr << b->k.gy;
		bstr << b->k.gz;
	}

} //Bikes