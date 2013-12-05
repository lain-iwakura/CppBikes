#include <Bikes/ByteStream.h>
#include <Bikes/BasicMath.h>
#include <string.h>


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

	ByteArray::ByteArray(const char *bt ):RawArray<char>(bt,strlen(bt)+1)
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

	ByteArray& ByteArray::operator=( const ByteArray& ba )
	{
		setCapacity(ba.capacity());
		setSize(ba.size());
		for(int i=0; i<size(); i++) arr[i]=ba[i];
		return *this;
	}

	ByteArray& ByteArray::operator=( const char *bt )
	{
		setSize(strlen(bt)+1);
		for(int i=0; i<size(); i++) arr[i]=bt[i];
		return *this;
	}

	bool ByteArray::operator==( const ByteArray& ba ) const
	{
		if(ba.size()!=size()) return false;
		for(int i=0; i<size(); i++)
			if(arr[i]!=ba[i]) return false;
		return true;
	}

	bool ByteArray::operator==( const char *str ) const
	{
		int strl=strlen(str);
		if(strl!=size()-1) return false;
		for(int i=0;i<size();i++)
			if(str[i]!=arr[i]) return false;
		return true;
	}

	bool ByteArray::atEnd() const
	{
		return ri>=size();
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