#include <Bikes/Array/ByteArray.h>
#include <Bikes/Mathem/Tools.h>

namespace Bikes
{

ByteArray::ByteArray() : ri(0), wi(0)
{
}

ByteArray::ByteArray(sznum cap, sznum dcap/*=1*/, sznum sz/*=0*/) : RawArray<char>(sz, cap, dcap), ri(0), wi(0)
{
}

ByteArray::ByteArray(const ByteArray& ba) : RawArray<char>(ba), ri(ba.ri), wi(ba.wi)
{
}

ByteArray::ByteArray(const char *bt, sznum btSize) : RawArray<char>(bt, btSize)
{
    ri = 0;
    wi = l;
}

ByteArray::ByteArray(const char *bt) :RawArray<char>(bt, strlen(bt) + 1)
{
    ri = 0;
    wi = l;
}


void ByteArray::readBytes(char *bt, sznum btSize)
{
    int nr = btSize;

    if (ri + nr > l) 
        nr = l - ri;

    for (int i = 0; i<nr; i++, ri++)
        bt[i] = arr[ri];
}

void ByteArray::writeBytes(const char *bt, sznum btSize)
{
    if (wi + btSize>l) 
        setSize(wi + btSize);

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
    if (wi + byteCapacity > s) 
        this->setCapacity(wi + byteCapacity);
}

ByteArray& ByteArray::operator=(const ByteArray& ba)
{
    setCapacity(ba.capacity());
    setSize(ba.size());

    for (sznum i = 0; i < size(); i++) 
        arr[i] = ba[i];

    return *this;
}

ByteArray& ByteArray::operator=(const char *bt)
{
    setSize(strlen(bt) + 1);

    for (sznum i = 0; i < size(); i++) 
        arr[i] = bt[i];

    return *this;
}

bool ByteArray::operator==(const ByteArray& ba) const
{
    if (ba.size() != size()) 
        return false;

    for (sznum i = 0; i < size(); i++)
        if (arr[i] != ba[i]) 
            return false;

    return true;
}

bool ByteArray::operator==(const char *str) const
{
    sznum strl = strlen(str);

    if (strl != size() - 1) 
        return false;

    for (sznum i = 0; i < size(); i++)
        if (str[i] != arr[i]) 
            return false;

    return true;
}

bool ByteArray::atEnd() const
{
    return ri >= size();
}

}