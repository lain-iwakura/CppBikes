#ifndef INCLUDE_BIKES_ARRAY_BYTEARRAY_H
#define INCLUDE_BIKES_ARRAY_BYTEARRAY_H

#include <Bikes/Stream/InOutInterface.h>
#include <Bikes/Array/RawArray.h>

namespace Bikes
{
    
class ByteArray: 
    public InOutInterface, 
    public RawArray<char>
{
public:

    ByteArray();

    ByteArray(sznum cap, sznum dcap = 1, sznum sz = 0);

    ByteArray(const ByteArray& ba);

    ByteArray(const char *bt, sznum btSize);

    ByteArray(const char *str);

    ByteArray& operator=(const ByteArray& ba);

    ByteArray& operator=(const char *str);

    bool operator ==(const ByteArray& ba) const;

    bool operator ==(const char *str) const;

    void readBytes(char *bt, sznum btSize);

    void writeBytes(const char *bt, sznum btSize);

    void prepareForWrite(sznum byteCapacity);

    bool atEnd() const;

    sznum writeIndex() const;

    sznum readIndex() const;

    void setWriteIndex(sznum i);

    void setReadIndex(sznum i);

private:
    sznum ri;
    sznum wi;
};


}

#endif // <- INCLUDE_BIKES_ARRAY_BYTEARRAY_H
