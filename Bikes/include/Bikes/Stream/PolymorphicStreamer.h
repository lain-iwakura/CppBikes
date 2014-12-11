#ifndef INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H
#define INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H

#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Stream/AbstractObjectStreamer.h>
#include <Bikes/Stream/ObjectStreamerMacros.h>
#include <Bikes/SmartPtr.h>
#include <Bikes/Stream/StreamerInterface.h>
#include <Bikes/TypeInfo.h>
#include <vector>
#include <map>


namespace Bikes
{
//==============================================================================
namespace Inner{
//==============================================================================
template<class AbstractType>
class PolymorphicSingleStreamerBase
{
public:
    typedef typename AbstractType StreamTy                                                                               \pe;

    virtual~TypeAbstractStreamer()
    {
    }

    virtual void read(ByteStream &bs, AbstractType* aobj) const = 0;

    virtual void write(ByteStream &bs, const AbstractType* aobj) const = 0;

    virtual AbstractType* newObject() const = 0;
};
//==============================================================================
template<
    class AbstractType,
    class ChildTypeStreamer,
    class CreatorT = SimpleCreator<ChildTypeStreamer::StreamType>
    >
class PolymorphicSingleStreamer: 
    public PolymorphicSingleStreamerBase<AbstractType>
{
public:

    typedef typename ChildTypeStreamer::StreamType StreamType;
    typedef CreatorT Creator;

    void read(ByteStream &bs, AbstractType* aobj) const
    {
        if(StreamType *obj=dynamic_cast<StreamType *>(aobj))
        {
            ChildTypeStreamer::read(bs,obj);
        }else
        {
            //exception
        }
    }

    void write(ByteStream &bs,const AbstractType* aobj) const
    {
        if(const StreamerType *obj=dynamic_cast<const StreamerType *>(aobj))
        {
            ChildTypeStreamer::write(bs,obj);
        }else
        {
            //exception
        }
    }

    AbstractType* newObject() const
    {
        return Creator::create();
    }
};
//==============================================================================
} // Inner
//==============================================================================
template<
    class AbstractRegistrableType,
    class AbstractRegistrableTypePtr = AbstractRegistrableType*,
    class Collector = AbstractRegistrableType 
    >
class PolymorphicStreamer: 
    public ObjectStreamerBase<AbstractRegistrableTypePtr>
{
public:

    virtual ~PolymorphicStreamer(){}

        void read(ByteStream& bs) const{read(bs,this->obj_r);}
        void write(ByteStream& bs) const{write(bs,this->obj_w);}

    template<class ObjectStreamer>
    static void add()
    {
        streamers[ObjectStreamer::StreamerType::typeName()].reset(new PolymorphicSingleStreamer<AbstractRegistrableType,ObjectStreamer>());
    }

    static void read(ByteStream& bs, AbstractRegistrableTypePtr * ppAObj)
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
                        typename std::map<const char*,typename Ptr<PolymorphicSingleStreamerBase<AbstractRegistrableType> >::Shared > ::iterator pItr;
            typename Ptr<PolymorphicSingleStreamerBase<AbstractRegistrableType> >::Shared stre;

            for(pItr=streamers.begin(); pItr!=streamers.end(); pItr++)
                if(bastr==pItr->first)
                {
                    stre=pItr->second;
                    break;
                }

            if(stre.get())
            {
                (*ppAObj)=AbstractRegistrableTypePtr(stre->newObject());
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

    static void write(ByteStream& bs, const AbstractRegistrableTypePtr* ppAObj)
    {

        if(ppAObj&&(getP(ppAObj)))
        {
            ByteArray bastr((*ppAObj)->getTypeName());

                        typename std::map<const char*,typename Ptr<PolymorphicSingleStreamerBase<AbstractRegistrableType> >::Shared >::iterator pItr;
            typename Ptr<PolymorphicSingleStreamerBase<AbstractRegistrableType> >::Shared stre;

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
        typedef AbstractRegistrableType* AbstractRegistrableTypeP;

    template<class TPtr>
        static AbstractRegistrableType * getP(const TPtr* ptr){return Ptr<AbstractRegistrableType>::get(*ptr);}

    static std::map<const char*,typename Ptr<PolymorphicSingleStreamerBase<AbstractRegistrableType> >::Shared > streamers;
};

//template<class AbstractRegistrableType, class AbstractRegistrableTypePtr, class Collector>
//template<>
//AbstractRegistrableType *AbstractTypeStreamer<AbstractRegistrableType,AbstractRegistrableTypePtr,Collector>::getP<>( AbstractRegistrableType *const *ptr)
//{return *ptr;}

template<class AbstractRegistrableType, class AbstractRegistrableTypePtr, class Collector>
std::map<const char*, typename Ptr<PolymorphicSingleStreamerBase<AbstractRegistrableType> >::Shared > PolymorphicStreamer<AbstractRegistrableType,AbstractRegistrableTypePtr,Collector>::streamers;

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
        if(ots==0){	/*TODO: exaption*/	}
        return ots->newObjectStreamer(obj);
    }

    template<class T>
    ObjectStreamerBase<T>* newObjectStreamer(const T *obj)
    {
        OneTypeStreamerCreator<T>* ots=dynamic_cast<OneTypeStreamerCreator<T>*>(this);
        if(ots==0){	/*TODO: exaption*/ }
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


} // Bikes

#endif // <- INCLUDE_BIKES_STREAM_POLYMORPHICSTREAMER_H
