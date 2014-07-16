#include <Bikes/Stream/ByteStream.h>

namespace Bikes
{

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

void ByteStream::readBytes( char *bt, sznum btSize )
{
	io_->readBytes(bt,btSize);
}

void ByteStream::writeBytes(const char *bt, sznum btSize )
{
	io_->writeBytes(bt,btSize);
}

void ByteStream::prepareForWrite( sznum byteCapacity )
{
	io_->prepareForWrite(byteCapacity);
}

void ByteStream::read(bool &val){
    readValue(val);
}

void ByteStream::read(char &val)
{
    readValue(val);
}		  

void ByteStream::read(unsigned char &val)
{
	readValue(val);
}

void ByteStream::read(short &val)
{
    readValue(val);
}

void ByteStream::read(unsigned short &val)
{
    readValue(val);
}

void ByteStream::read(int &val)
{
    readValue(val);
}

void ByteStream::read(unsigned int &val)
{
    readValue(val);
}

void ByteStream::read(long &val)
{
    readValue(val);
}

void ByteStream::read(unsigned long &val)
{
    readValue(val);
}

void ByteStream::read(long long &val)
{
    readValue(val);
}

void ByteStream::read(unsigned long long &val)
{
    readValue(val);
}

void ByteStream::read(float &val)
{
    readValue(val);
}

void ByteStream::read(double &val)
{
    readValue(val);
}

void ByteStream::write(bool val)
{
    writeValue(val);
}

void ByteStream::write(char val)
{
    writeValue(val);
}

void ByteStream::write(short val)
{
    writeValue(val);
}

void ByteStream::write(unsigned short val)
{
    writeValue(val);
}

void ByteStream::write(int val)
{
    writeValue(val);
}

void ByteStream::write(unsigned int val)
{
    writeValue(val);
}

void ByteStream::write(long val)
{
    writeValue(val);
}

void ByteStream::write(unsigned long val)
{
    writeValue(val);
}

void ByteStream::write(long long val)
{
    writeValue(val);
}

void ByteStream::write(unsigned long long val)
{
    writeValue(val);
}

void ByteStream::write(float val)
{
    writeValue(val);
}

void ByteStream::write(double val)
{
    writeValue(val);
}

void ByteStream::write(unsigned char val)
{
	writeValue(val);
}


























	




}