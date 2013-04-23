#include <Bikes/ByteStream.h>



namespace Bikes
{


	ByteStream::ByteStream(RawArray<char>* bytes ):ri(0),wi(0)
	{
		b=bytes;		
	}


	RawArray<char>* ByteStream::byteArray()
	{
		return b;
	}


	void ByteStream::setByteArray( RawArray<char>* bytes )
	{
		b=bytes;
		ri=0;
		wi=bytes->size();
	}

}