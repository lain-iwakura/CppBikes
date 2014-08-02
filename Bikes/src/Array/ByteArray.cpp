#include <Bikes/Array/ByteArray.h>
#include <Bikes/Mathem/Tools.h>

namespace Bikes
{

ByteArray::ByteArray(sznum sz/*=0*/, sznum cap/*=1024*/, unum capInc) :RawArrayBase(sz, cap, capInc), ri(0), wi(0)
{
}

ByteArray::ByteArray(const ByteArray& ba) : RawArrayBase(ba), ri(ba.ri), wi(ba.wi)
{
}

ByteArray::ByteArray(const char *bt, sznum btSize) : RawArrayBase(bt, btSize)
{
	this->setMaxCapacityIncrement(Inner::defMaxByteArrayMemoryIncrement);
    ri = 0;
    wi = this->size();
}

ByteArray::ByteArray(const char *bt) :RawArrayBase(bt, strlen(bt) + 1)
{
	this->setMaxCapacityIncrement(Inner::defMaxByteArrayMemoryIncrement);
    ri = 0;
    wi = this->size();
}


void ByteArray::readBytes(char *bt, sznum btSize)
{
    int nr = btSize;

    if (ri + nr > this->size()) 
        nr = this->size() - ri;

	char* arr = this->data();
    for (int i = 0; i<nr; i++, ri++)
        bt[i] = arr[ri];
}

void ByteArray::writeBytes(const char *bt, sznum btSize)
{
	sznum nsz = wi + btSize;
	sznum cap = this->capacity();
	sznum mcap = this->maxCapacityIncrement();

	if (nsz > this->size())
	{
		if (nsz > cap)
		{
			if (mcap + cap > nsz)
				this->setCapacity(inRange<sznum>(2 * cap, nsz, cap + mcap));
			else
				this->setCapacity(nsz);
		}

		this->setSize(wi + btSize);
	}

	char* arr = this->data();
    for (sznum i = 0; i < btSize; i++, wi++)
        arr[wi] = bt[i];
}

sznum ByteArray::writeIndex() const
{
    return wi;
}

sznum ByteArray::readIndex() const
{
    return ri;
}

void ByteArray::setWriteIndex(sznum i)
{
    wi = inRange<sznum>(i, 0, size());
}

void ByteArray::setReadIndex(sznum i)
{
    ri = inRange<sznum>(i, 0, size());
}

void ByteArray::prepareForWrite(sznum byteCapacity)
{
    if (wi + byteCapacity > capacity()) 
        this->setCapacity(wi + byteCapacity);
}

ByteArray& ByteArray::operator=(const char *bt)
{
    setSize(strlen(bt) + 1);

	char* arr = this->data();
    for (sznum i = 0; i < size(); i++) 
        arr[i] = bt[i];

    return *this;
}

ByteArray& ByteArray::operator=(const ByteArray& ba)
{
	RawArrayBase *ra1 = this;
	*ra1 = ba;
	ri = ba.ri;
	wi = ba.wi;
	return *this;
}

bool ByteArray::operator==(const char *str) const
{
    sznum strl = strlen(str);

    if (strl != size() - 1) 
        return false;

	const char* arr = this->data();
    for (sznum i = 0; i < size(); i++)
        if (str[i] != arr[i]) 
            return false;

    return true;
}

bool ByteArray::operator!=(const char *str) const
{
	return !(*this == str);
}

bool ByteArray::operator ==(const ByteArray& ba) const
{
	const RawArrayBase *ra1 = this;
	return *ra1 == ba;
}

bool ByteArray::operator !=(const ByteArray& ba) const
{
	return !(*this == ba);
}
		 

bool ByteArray::atEnd() const
{
    return ri >= size();
}

}