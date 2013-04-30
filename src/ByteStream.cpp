#include <Bikes/ByteStream.h>
#include <Bikes/BasicMath.h>


namespace Bikes
{





//=========================================================================

	ByteArray::ByteArray(): ri(0),wi(0)
	{
	}

	ByteArray::ByteArray( int cap, int dcap/*=1*/, int sz/*=0*/ ):RawArray<char>(sz,cap,dcap),ri(0),wi(0)
	{		
	}

	ByteArray::ByteArray(const ByteArray& ba ):RawArray<char>(ba),ri(ba.ri),wi(ba.wi)
	{
	}

	ByteArray::ByteArray( const char *bt, llnum btSize ):RawArray<char>(bt,btSize)
	{
		ri=0;
		wi=l;
	}


	void ByteArray::readBytes( char *bt, llnum btSize )
	{
		int nr=btSize;
		if(ri+nr>l) nr=l-ri;
		
		for(int i=0; i<nr; i++, ri++)
			bt[i]=arr[ri];
	}

	void ByteArray::writeBytes(const char *bt, llnum btSize )
	{
		if(wi+btSize>l) setSize(wi+btSize);
		for(int i=0; i<btSize; i++, wi++)
			arr[wi]=bt[i];
	}

	int ByteArray::writeIndex() const
	{
		return wi;
	}

	int ByteArray::readIndex() const
	{
		return ri;
	}

	void ByteArray::setWriteIndex( int i )
	{
		wi=inRange<int>(i,0,size());
	}

	void ByteArray::setReadIndex( int i )
	{
		ri=inRange<int>(i,0,size());
	}

	void ByteArray::prepareForWrite( llnum byteCapacity )
	{
		if(wi+byteCapacity>s) this->setCapacity(wi+byteCapacity);
	}

//=========================================================================


	ByteStream::ByteStream():io_(0)
	{
	}


	ByteStream::ByteStream( InOutInterface* io ):io_(io)
	{
	}


	void ByteStream::setIO( InOutInterface* io)
	{		
		io_=io;
	}

	InOutInterface* ByteStream::getIO() const
	{
		return io_;
	}

	void ByteStream::readBytes( char *bt, llnum btSize )
	{
		io_->readBytes(bt,btSize);
	}

	void ByteStream::writeBytes(const char *bt, llnum btSize )
	{
		io_->writeBytes(bt,btSize);
	}

	void ByteStream::prepareForWrite( llnum byteCapacity )
	{
		io_->prepareForWrite(byteCapacity);
	}

	




}