#ifndef INCLUDE_BIKES_ARRAY_BYTEARRAY_H
#define INCLUDE_BIKES_ARRAY_BYTEARRAY_H

#include <Bikes/Stream/InputOutput.h>
#include <Bikes/Array/RawArray.h>

namespace Bikes
{

	namespace Inner
	{
		const unum defMaxByteArrayMemoryIncrement = 1024 * 1024;
	}
    
class ByteArray: 
    public InputOutput, 
    public RawArray<char>
{	
public:

	typedef RawArray<char> RawArrayBase;

	ByteArray(
        sznum sz = 0,
        sznum cap = 1024,
        unum maxCapInc = Inner::defMaxByteArrayMemoryIncrement
        );

    ByteArray(const ByteArray& ba);

    ByteArray(const char *bt, sznum btSize);

    ByteArray(const char *str);

    ByteArray& operator=(const ByteArray& ba);

    ByteArray& operator=(const char *str);

    bool operator ==(const ByteArray& ba) const;

	bool operator !=(const ByteArray& ba) const;

    bool operator ==(const char *str) const;

	bool operator !=(const char *str) const;

    void readBytes(char *bt, sznum btSize);

    void writeBytes(const char *bt, sznum btSize);

    void prepareForWrite(sznum byteCapacity);

    bool atEnd() const;

    sznum writeIndex() const;

    sznum readIndex() const;

    void setWriteIndex(sznum i);

    void setReadIndex(sznum i);

private:
    sznum _ri;
    sznum _wi;
};


}

#endif // <- INCLUDE_BIKES_ARRAY_BYTEARRAY_H
