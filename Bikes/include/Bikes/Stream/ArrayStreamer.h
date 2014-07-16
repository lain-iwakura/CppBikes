#ifndef INCLUDE_BIKES_STREAM_ARRAYSTREAMER_H
#define INCLUDE_BIKES_STREAM_ARRAYSTREAMER_H

namespace Bikes
{
//==============================================================================
template<class ElementStreamer, class ArrayClass>
class ArrayStreamer : public AbstractObjectStreamer<ArrayClass>
{
    typedef typename AbstractObjectStreamer<ArrayClass>::StreamerType StreamerType;
public:
    ArrayStreamer(StreamerType *obj): 
	  AbstractObjectStreamer<StreamerType>(obj)
	{
	}

    ArrayStreamer(const StreamerType *obj): 
		AbstractObjectStreamer<StreamerType>(obj)
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

    static void read(ByteStream& bs, StreamerType *obj)
    {
        obj->clear();
        sznum sz;
        bs >> sz;
        typename ElementStreamer::StreamerType el;
        ElementStreamer es(&el);
        for (sznum i = 0; i < sz; i++)
        {
            bs >> es;
            obj->push_back(el);
        }
    }

    static void write(ByteStream& bs, const StreamerType *obj)
    {
        bs.prepareForWrite(obj->size() + sizeof(sznum));
        bs << sznum(obj->size());
        for (sznum i = 0; i < obj->size(); i++)
            bs << ElementStreamer(&((*obj)[i]));
    }

};
//==============================================================================
template<class ElementStreamer, class ArrayClass>
ArrayStreamer<ElementStreamer, ArrayClass> arrayStreamer(ArrayClass *arr)
{
    return ArrayStreamer<ElementStreamer, ArrayClass>(arr);
}
//==============================================================================
template<class ElementStreamer, class ArrayClass>
ArrayStreamer<ElementStreamer, ArrayClass> arrayStreamer(const ArrayClass *arr)
{
    return ArrayStreamer<ElementStreamer, ArrayClass>(arr);
}
//==============================================================================

}


#endif // <- INCLUDE_BIKES_STREAM_ARRAYSTREAMER_H
