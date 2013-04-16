#ifndef _CPPBIKES_OBJECTSTREAM_H_
#define _CPPBIKES_OBJECTSTREAM_H_

#include <Bikes/ByteStream.h>

namespace Bikes
{
	template<class T>
	class AbstractObjectStreamer
	{
	public:
		virtual ~AbstractObjectStreamer(){}
		virtual void read(T* obj) = 0;
		virtual void write(const T* obj) = 0;	
	protected:
		virtual ByteStream& byteStream_() = 0;
	};
//=========================================================================
	class AbstractObjectReader;
	class AbstractObjectWrite;

//=========================================================================
	class AbstractObjectReader
	{
	public:
		virtual ~AbstractObjectReader(){}

		template <class T> 
		AbstractObjectReader& operator >> (T& obj)
		{
			read(obj);
			return *this;
		}

		template<class T>
		void read(T& obj)
		{
			if(AbstractObjectStreamer<T>* ostr=dynamic_cast<AbstractObjectStreamer<T>* >(this))
			{
				ostr->read(&obj);
			}else
			{					
				byteStream_().read(obj); // (?)
			}
		}

		template<class T>
		bool isObjectStreamer()
		{
			return dynamic_cast<AbstractObjectStreamer<T>*>(this);
		}
		
	protected:
		virtual ByteStream& byteStream_() = 0;
	};

//=========================================================================
	class AbstractObjectWriter
	{
	public:
		virtual ~AbstractObjectWriter(){}

		template <class T> 
		AbstractObjectWriter& operator << (const T& obj)
		{
			write(obj);
			return *this;
		}

		template<class T>
		void write(const T& obj)
		{
			if(AbstractObjectStreamer<T>* ostr=dynamic_cast<AbstractObjectStreamer<T>* >(this))
			{
				ostr->write(&obj);
			}else
			{					
				byteStream_().write(obj); // (?)
			}
		}

		template<class T>
		bool isObjectStreamer()
		{
			return dynamic_cast<AbstractObjectStreamer<T>*>(this);
		}

	protected:
		virtual ByteStream& byteStream_() = 0;
	};
//=========================================================================
	class AbstractObjectStream: public AbstractObjectReader, public AbstractObjectWriter
	{
	public:
		virtual ~AbstractObjectStream(){}
		
		template<class T>
		bool isObjectStreamer()
		{
			return dynamic_cast<AbstractObjectStreamer<T>*>(this);
		}

		void setByteArray(RawArray<char> *ba){bstr.setByteArray(ba);}


	protected:
		ByteStream& byteStream_() {return bstr;}	
		ByteStream bstr;
	};
//=========================================================================



}

#endif