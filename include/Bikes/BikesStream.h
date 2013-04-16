#ifndef _BIKES_BIKESSTREAM_H_
#define _BIKES_BIKESSTREAM_H_

#include <Bikes/ObjectSream.h>

namespace Bikes
{
	class Point;
	class Vector;
	class Basis;

	class PointStreamer: public AbstractObjectStreamer<Point>
	{
	public:
		virtual ~PointStreamer(){}
		void read(Point* p);
		void write(const Point* p);
		
		static void read(ByteStream &bstr, Point* p);
		static void write(ByteStream &bstr, const Point* p);
	};

	class VectorStreamer: public AbstractObjectStreamer<Vector>
	{
	public:
		virtual ~VectorStreamer(){}
		void read(Vector* v);
		void write(const Vector* v);

		static void read(ByteStream &bstr, Vector *v);
		static void write(ByteStream &bstr, const Vector *v);

	};

	class BasisStreamer: public AbstractObjectStreamer<Basis>
	{
	public:
		virtual ~BasisStreamer(){}
		void read(Basis* b);
		void write(const Basis* b);

		static void read(ByteStream &bstr, Basis *b);
		static void write(ByteStream &bstr, const Basis *b);
	};


	class BikesStream: 
		public AbstractObjectStream, 
		public PointStreamer, 
		public VectorStreamer,
		public BasisStreamer
	{
	};

} // Bikes

#endif