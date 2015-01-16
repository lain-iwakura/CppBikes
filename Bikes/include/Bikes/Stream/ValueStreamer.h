#ifndef INCLUDE_BIKES_STREAM_VALUESTREAMER_H
#define INCLUDE_BIKES_STREAM_VALUESTREAMER_H

#include <Bikes/Stream/AbstractObjectStreamer.h>

namespace Bikes
{
//==============================================================================
template<class ValueType>
class ValueStreamer : public AbstractObjectStreamer<ValueType>
{
public:

    ValueStreamer(const ValueType * val):
        AbstractObjectStreamer<ValueType>(val)
    {
    }

    ValueStreamer(ValueType * val):
        AbstractObjectStreamer<ValueType>(val)
    {
    }

    void read(ByteStream& bs) const
    { 
        read(bs, this->obj_r); 
    }

    void write(ByteStream& bs) const
    {
        write(bs, this->obj_w); 
    }

    static void read(ByteStream& bs, ValueType *val)
    { 
        bs.readValue(*val); 
    }

    static void write(ByteStream& bs, const ValueType *val)
    {
        bs.writeValue(*val); 
    }
};
//==============================================================================
template<class ValueType>
ValueStreamer<ValueType> valueStreamer(ValueType *val)
{
    return ValueStreamer<ValueType>(val);
}
//==============================================================================
template<class ValueType>
ValueStreamer<ValueType> valueStreamer(const ValueType *val)
{
    return ValueStreamer<ValueType>(val);
}
//==============================================================================
}

#endif // <- INCLUDE_BIKES_STREAM_VALUESTREAMER_H
