#ifndef INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H
#define INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H

#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Stream/ObjectStreamer.h>
#include <Bikes/Stream/ObjectStreamerMacros.h>
#include <Bikes/Stream/IStreamer.h>
#include <Bikes/TypeTools/Info.h>
#include <Bikes/TypeTools/ToTypeStack.h>
#include <Bikes/TypeTools/TypeStackHolder.h>
#include <Bikes/Conversion.h>

#include <vector>
#include <map>
//#include <memory>


namespace Bikes
{
//==============================================================================
namespace Inner{
//==============================================================================
template<class AbstractTypeT>
struct ToPolymorphicSingleStreamer
{
    typedef ObjectStreamer < AbstractTypeT, CreationManagment::Abstract<AbstractTypeT> >
        BaseObjectStreamer;

    template<class StreamerTypeT>
    struct Converter
    {    
        typedef ObjectStreamerAdapter<
            BaseObjectStreamer,
            StreamerTypeT
            > ResultType;
    };
};
//------------------------------------------------------------------------------
template<class AbstractTypeT, class StreamersTypeStackT>
class ToPolymorphicStreamerStack
{
public:
    typedef TT::TypeStackToTypeStack<
        StreamersTypeStackT, 
        typename ToPolymorphicSingleStreamer<AbstractTypeT>::template Converter
        > ResultStack;
};
//==============================================================================
} // Inner
//==============================================================================

template<
    class AbstractTypeT,
    class StremersTypeStackT,
    class AbstractTypePtrT = AbstractTypeT*
    >
class PolymorphicStreamer:
    public ObjectStreamer<AbstractTypePtrT>
{
    typedef typename  Inner::ToPolymorphicStreamerStack<AbstractTypeT,StremersTypeStackT>
        ::ResultStack PolymorphicStreamerStack;

    typedef TT::ConstObjectsHolder<
        PolymorphicStreamerStack,
        ObjectStreamer<AbstractTypeT>
        > 
        PolymorphicStreamerHolderBase;

    typedef TT::TypeStackHolder<
        PolymorphicStreamerStack,
        PolymorphicStreamerHolderBase
        > 
        PolymorphicStreamerHolder;

    typedef typename PolymorphicStreamerHolder::HeldType PolymorphicStreamerArray;

public:

    typedef AbstractTypeT AbstractType;
    typedef AbstractTypePtrT StreamType;

    typedef ObjectStreamer<AbstractTypePtrT> Base;

    PolymorphicStreamer(AbstractTypePtrT& pObj) :
        Base(pObj)
    {
    }

    PolymorphicStreamer(const AbstractTypePtrT& pObj) :
        Base(pObj)
    {
    }

    void read(ByteStream& bs, AbstractTypePtrT& pAObj) const
    {
        StreamPositionSaver sp0(&bs);

        PolymorphicStreamerArray& pstr = PolymorphicStreamerHolder::get();

        ByteArray typeSign;
        bs.readRecurrentData(typeSign);
        StreamPositionSaver sp1(&bs);

        for (PolymorphicStreamerArray::iterator s = pstr.begin(); s != pstr.end(); ++s)
        {
            if(s->signature() == typeSign)
            {
                try
                {
                    pAObj = AbstractTypePtrT(s->readAndCreate(bs));
                    return;
                }
                catch (Exception::StreamException& e)
                {
                    if ((!e.positionRestored()) && (!sp1.tryRestore(e)))
                        throw;
                }
                catch (std::exception& e)
                {
                    if (!sp1.tryRestore())
                        throw;
                }
            }
        }

        throw UnexpectedStreamType(
            std::string(typeSign.data()),
            sp0.tryRestore();
            );
    }

    void write(ByteStream& bs, const AbstractTypePtrT& ptrObj) const
    {
        PolymorphicStreamerArray& pstr = PolymorphicStreamerHolder::get();

        const AbstractType* pObj = getPtr<const AbstractType*>(ptrObj);

        BIKES_CHECK_INSTANCE(pObj);

        StreamPositionSaver sp(&bs);

        for (PolymorphicStreamerArray::iterator s = pstr.begin(); s != pstr.end(); ++s)
        {
            try
            {
                s->writeWhithSign(bs, *pObj);
                return;
            }
            catch(Exception::StreamException& e)
            {
                 if ( (!e.positionRestored()) &&  (!sp.tryRestore(e)) )
                     throw;
            }
            catch (std::exception& e)
            {
                if (!sp.tryRestore())
                    throw;
            }
        }        
        Inner::throwUnexpectedStreamType(*pObj, *this, true);
    }


private:
};

} // Bikes

#endif // <- INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H
