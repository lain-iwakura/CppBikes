#ifndef INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H
#define INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H

#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Stream/ObjectStreamerBase.h>
#include <Bikes/Stream/ObjectStreamerMacros.h>
#include <Bikes/Stream/StreamerInterface.h>
#include <vector>
#include <map>
#include <memory>
#include <Bikes/TypeTools/Info.h>


namespace Bikes
{
//==============================================================================
namespace Inner{
//==============================================================================
template<class AbstractType>
class PolymorphicSingleStreamerBase
{
public:
    typedef typename AbstractType StreamType;    

    typedef PolymorphicSingleStreamerBase<AbstractType> ThisType;

    virtual~PolymorphicSingleStreamerBase()
    {
    }

    virtual void read(ByteStream &bs, AbstractType& aobj) const = 0;

    virtual bool tryWrite(ByteStream &bs, const AbstractType& aobj) const = 0;

    virtual AbstractType* newObject() const = 0;

    virtual ThisType* clone() const = 0;

    virtual const ByteArray& typeSignature() const = 0;

    virtual bool operator ==(const ThisType&) const = 0;

    //virtual
};
//==============================================================================
template<
    class AbstractType,
    class ChildTypeStreamer,
    class CreatorT = SimpleCreator<typename ChildTypeStreamer::StreamType>
    >
class PolymorphicSingleStreamer: 
    public PolymorphicSingleStreamerBase<AbstractType>
{
public:

    typedef typename ChildTypeStreamer::StreamType StreamType;
    typedef CreatorT Creator;

    typedef PolymorphicSingleStreamerBase<AbstractType> Base;
    typedef PolymorphicSingleStreamer<AbstractType, ChildTypeStreamer, CreatorT> ThisType;

    void read(ByteStream &bs, AbstractType& aobj) const
    {
        if(StreamType *obj=dynamic_cast<StreamType *>(&aobj))
        {
            ChildTypeStreamer::read(bs,*obj);
        }else
        {
            //exception
        }
    }

    bool tryWrite(ByteStream &bs, const AbstractType& aobj) const
    {
        if(const StreamType *obj=dynamic_cast<const StreamType *>(&aobj))
        {
            ChildTypeStreamer::write(bs,*obj);
            return true;
        }
        return false;
    }

    AbstractType* newObject() const
    {
        return Creator::create();
    }

    ThisType* clone() const
    {
        return new ThisType(/* *this */);
    }

    const ByteArray& typeSignature() const
    {
        return ChildTypeStreamer::typeSignature();
    }
    
    bool operator == (const Base& other) const
    {
        const ByteArray& s1 = ChildTypeStreamer::typeSignature();
        const ByteArray& s2 = other.typeSignature();
        return (&s1 == &s2) || (s1 == s2);
    }
};
//==============================================================================
// template<class AbstractTypeT
// class PolymorphicStreamerHolder
// {
// public:
// 
// };
//==============================================================================
} // Inner
//==============================================================================

template<
    class AbstractTypeT,
    class StremersTypeStackT,
    class AbstractTypePtrT = AbstractTypeT*
    >
class PolymorphicStreamer:
    public ObjectStreamerBase<AbstractTypePtrT>
{
    //typedef Inner::PolymorphicSingleStreamerBase<>
    //typedef TT::ConstObjectsHolder<>

public:

    typedef AbstractTypePtrT StreamType;
    typedef ObjectStreamerBase<AbstractTypePtrT> Base;

    PolymorphicStreamer(AbstractTypePtrT& pObj) :
        Base(pObj)
    {
    }

    PolymorphicStreamer(const AbstractTypePtrT& pObj) :
        Base(pObj)
    {
    }



    void read(ByteStream& bs)
    {
        if (obj_r)
            read(bs, *obj_r);
        else
        { 
            //?
        }
    }

    void write(ByteStream& bs)
    {
        if (obj_w)
            write(bs, *obj_r);
        else
        {
            //?
        }
    }

    static void read(ByteStream& bs, AbstractTypePtrT& pAObj)
    {
    }

    static void write(ByteStream& bs, AbstractTypePtrT& pAObj)
    {
    }
};
/*
template<
    class AbstractTypeT,
    class AbstractTypePtrT = AbstractTypeT*,
    class CollectorT = AbstractTypeT 
    >
class PolymorphicStreamer: 
    public ObjectStreamerBase<AbstractTypePtrT>
{
    static List<
        Inner::PolymorphicSingleStreamerBase, 
        SimpleCloningSupervisor<Inner::PolymorphicSingleStreamerBase>
        > streamers;
public:

    typedef AbstractType* StreamType;

    virtual ~PolymorphicStreamer(){}

    void read(ByteStream& bs) const {read(bs,*this->obj_r);}
    void write(ByteStream& bs) const {write(bs,*this->obj_w);}

    template<
        class ObjectStreamerT,
        class CreatorT = SimpleCreator<typename ObjectStreamerT::StreamType> 
        >
    static void add()
    {        
        typedef typename ObjectStreamerT::StreamType NewStreamType;
        if (Hierrarchy<AbstractTypeT,NewStreamType>::exists)
        {
            Inner::PolymorphicSingleStreamer<ObjectStreamerT> str;
            for (sznum i = 0; i < streamers.size())
            {

            }
        }
        else if (Equal<AbstractTypeT, NewStreamType>::result)
        {
            if (streamers.size() != 0)
            {
                //if (streamers)
            }
        }
        else
        {
            //?
        }
    }

    static void read(ByteStream& bs, AbstractTypePtr& pAObj)
    {
        ByteArray bastr(100,10);
        ByteStream bstr(&bastr);
        char ch;
        while(!bs.getIO()->atEnd())
        {
            bs >> ch;
            bstr << ch;
            if(ch=='\0') break;
        }
        if(ch=='\0')
        {
            const char *str=bastr.data();
                        typename std::map<const char*,typename Ptr<PolymorphicSingleStreamerBase<AbstractType> >::Shared > ::iterator pItr;
            typename Ptr<PolymorphicSingleStreamerBase<AbstractType> >::Shared stre;

            for(pItr=streamers.begin(); pItr!=streamers.end(); pItr++)
                if(bastr==pItr->first)
                {
                    stre=pItr->second;
                    break;
                }

            if(stre.get())
            {
                (*ppAObj)=AbstractTypePtr(stre->newObject());
                stre->read(bs,getP(ppAObj));
            }else
            {
                // TODO: exception
            }
        }else
        {
            // TODO: exception
        }
    }

    static void write(ByteStream& bs, const AbstractTypePtr* ppAObj)
    {

        if(ppAObj&&(getP(ppAObj)))
        {
            ByteArray bastr((*ppAObj)->getTypeName());

                        typename std::map<const char*,typename Ptr<PolymorphicSingleStreamerBase<AbstractType> >::Shared >::iterator pItr;
            typename Ptr<PolymorphicSingleStreamerBase<AbstractType> >::Shared stre;

            for(pItr=streamers.begin(); pItr!=streamers.end(); pItr++)
                if(bastr==pItr->first)
                {
                    stre=pItr->second;
                    break;
                }

            if(stre.get())
            {
                bs.writeBytes(bastr.data(),bastr.size());
                stre->write(bs,getP(ppAObj));
            }else
            {
                //exception
            }
        }else
        {
            //exception
        }
    }

    static int streamersCount(){return streamers.size();}

private:
        
    template<class TPtr>
        static AbstractType * getP(const TPtr* ptr){return Ptr<AbstractType>::get(*ptr);}

//     static std::map<
//         const char*,
//         std::auto_ptr<PolymorphicSingleStreamerBase<AbstractType> >
//         > streamers;
};

// 
// template<class AbstractType, class AbstractTypePtr, class Collector>
// std::map<
//     const char*, 
//     auto_ptr<PolymorphicSingleStreamerBase<AbstractType> >
//     > 
//     PolymorphicStreamer<AbstractType,AbstractTypePtr,Collector>::streamers;

/*

//-------------------------------------------------------------------------

namespace Aux
{
    template<class AbstractTypeStreamerClass, class AddStreamerClass>
    class AbstractTypeStreamerInitor
    {
    public:
        AbstractTypeStreamerInitor()
        {
            static bool i=false;
            if(!i)
            {
                i=true;
                                AbstractTypeStreamerClass::template add<AddStreamerClass>();
            }
        }
    };
}

//==============================================================================

template<class T> class OneTypeStreamerCreator;

class AbstractOneTypeStreamerCreator
{
public:
    virtual~AbstractOneTypeStreamerCreator(){}

    template<class T>
    ObjectStreamerBase<T>* newObjectStreamer(T *obj)
    {
        OneTypeStreamerCreator<T>* ots=dynamic_cast<OneTypeStreamerCreator<T>*>(this);
        if(ots==0){	}
        return ots->newObjectStreamer(obj);
    }

    template<class T>
    ObjectStreamerBase<T>* newObjectStreamer(const T *obj)
    {
        OneTypeStreamerCreator<T>* ots=dynamic_cast<OneTypeStreamerCreator<T>*>(this);
        if(ots==0){	}
        return ots->newObjectStreamer(obj);
    }
};
//-------------------------------------------------------------------------
template<class T>
class OneTypeStreamerCreator: public AbstractOneTypeStreamerCreator
{
public:
    virtual ~OneTypeStreamerCreator(){}
    virtual ObjectStreamerBase<T>* newObjectStreamer(T *obj) = 0;
    virtual ObjectStreamerBase<T>* newObjectStreamer(const T *obj) = 0;
};
//-------------------------------------------------------------------------
template<class ObjectStreamer>
class OneTypeObjectStreamerCreator: public OneTypeStreamerCreator<typename ObjectStreamer::StreamerType>
{
public:
    ObjectStreamerBase<typename ObjectStreamer::StreamerType>* newObjectStreamer(typename ObjectStreamer::StreamerType *obj)
    {
        return new ObjectStreamer(obj);
    }
    ObjectStreamerBase<typename ObjectStreamer::StreamerType>* newObjectStreamer(const typename ObjectStreamer::StreamerType *obj)
    {
        return new ObjectStreamer(obj);
    }
};
//-------------------------------------------------------------------------
// class BaseMultiTypeStreamer
// {
// public:
// 	virtual~BaseMultiTypeStreamer(){}
// };


template<class TypesCollection>
class MultiTypeStreamer: public StreamerInterface
{
public:

    MultiTypeStreamer(){}

    template<class T>
    MultiTypeStreamer(T* obj){setObject(obj);}

    template<class T>
    MultiTypeStreamer(const T* obj){setObject(obj);}


    template<class ObjectStreamer>
    static void add()
    {
                sznum it=TypesCollection::template typeId<typename ObjectStreamer::StreamerType>();
        if(it>=strCreators.size()) strCreators.resize(it+1);
        strCreators[it].reset(new OneTypeObjectStreamerCreator<ObjectStreamer>());
    }

// 	template<class OtherMultiTypeStreamer>
// 	static void addMulti()
// 	{
// 		const std::vector<std::tr1::shared_ptr<AbstractOneTypeStreamerCreator> >&strCr OtherMultiTypeStreamer::streamerCreators();
//
// 		for(int i=0; i<strCr.size(); i++)
// 		{
// 			if(strCr[i])
// 			{
// 				int it=TypesCollection::typeId<ObjectStreamer::StreamerType>();
// 				if(it>=strCreators.size()) strCreators.resize(it+1);
// 				strCreators[it].reset(new OneTypeObjectStreamerCreator<ObjectStreamer>());
// 			}
// 		}
// 	}

    template<class T>
    void setObject(T *obj)
    {
                int it=TypesCollection::template typeId<T>();
        if((it<strCreators.size())&&(strCreators[it].get()))
        {
            curStr.reset(strCreators[it]->newObjectStreamer(obj));
        }else
        {
            //exception
        }
    }

    template<class T>
    void setObject(const T *obj)
    {
                int it=TypesCollection::template typeId<T>();
        if((it<strCreators.size())&&(strCreators[it].get()))
        {
            curStr.reset(strCreators[it]->newObjectStreamer(obj));
        }else
        {
            //exception
        }
    }

    void read(ByteStream &bs) const
    {
        if(curStr.get())
        {
            curStr->read(bs);
        }else
        {
            //exception
        }
    }

    void write(ByteStream &bs) const
    {
        if(curStr.get())
        {
            curStr->write(bs);
        }else
        {
            //exception
        }
    }

private:
    Ptr<StreamerInterface>::Auto curStr;
    static std::vector<Ptr<AbstractOneTypeStreamerCreator>::Shared > strCreators;
};


template<class TypesCollection>
std::vector<Ptr<AbstractOneTypeStreamerCreator>::Shared >    MultiTypeStreamer<TypesCollection>::strCreators(TypesCollection::typeCount());


//==============================================================================
//*/

} // Bikes

#endif // <- INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H
