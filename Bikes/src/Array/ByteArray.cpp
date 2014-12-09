#include <Bikes/Array/ByteArray.h>
#include <Bikes/Mathem/Tools.h>

namespace Bikes
{

ByteArray::ByteArray(sznum sz/*=0*/, sznum cap/*=1024*/, unum capInc) 
:RawArrayBase(sz, cap, capInc), 
_ri(0), 
_wi(0)
{
}

ByteArray::ByteArray(const ByteArray& ba) : 
RawArrayBase(ba), 
_ri(ba._ri), 
_wi(ba._wi)
{
}

ByteArray::ByteArray(const char *bt, sznum btSize) : RawArrayBase(bt, btSize)
{
	this->setMaxCapacityIncrement(Inner::defMaxByteArrayMemoryIncrement);
    _ri = 0;
    _wi = this->size();
}

ByteArray::ByteArray(const char *bt) :RawArrayBase(bt, strlen(bt) + 1)
{
	this->setMaxCapacityIncrement(Inner::defMaxByteArrayMemoryIncrement);
    _ri = 0;
    _wi = this->size();
}


void ByteArray::readBytes(char *bt, sznum btSize)
{
    int nr = btSize;

    if (_ri + nr > this->size()) 
        nr = this->size() - _ri;

	char* arr = this->data();
    for (int i = 0; i<nr; i++, _ri++)
        bt[i] = arr[_ri];
}

void ByteArray::writeBytes(const char *bt, sznum btSize)
{
	sznum nsz = _wi + btSize;
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

		this->setSize(_wi + btSize);
	}

	char* arr = this->data();
    for (sznum i = 0; i < btSize; i++, _wi++)
        arr[_wi] = bt[i];
}

sznum ByteArray::writeIndex() const
{
    return _wi;
}

sznum ByteArray::readIndex() const
{
    return _ri;
}

void ByteArray::setWriteIndex(sznum i)
{
    _wi = inRange<sznum>(i, 0, size());
}

void ByteArray::setReadIndex(sznum i)
{
    _ri = inRange<sznum>(i, 0, size());
}

void ByteArray::prepareForWrite(sznum byteCapacity)
{
    if (_wi + byteCapacity > capacity()) 
        this->setCapacity(_wi + byteCapacity);
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
	_ri = ba._ri;
	_wi = ba._wi;
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
    return _ri >= size();
}

}