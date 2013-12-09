#ifndef PREBIKES_BYTESTREAM_H
#define PREBIKES_BYTESTREAM_H
#include <Bikes/RawArray.h>
#include <vector>
#include <Bikes/Types.h>
#include <Bikes/AbstractStreamer.h>

namespace Bikes
{


	//typedef RawArray<char> ByteArray;

	
	class InOutInterface
	{
	public:
		virtual ~InOutInterface(){}
		virtual void readBytes(char *bt, lnum btSize) = 0;
		virtual void writeBytes(const char *bt, lnum btSize) = 0;
		virtual void prepareForWrite(lnum byteCapacity){}
		virtual bool atEnd() const{return false;};
		//... 
	};

	class ByteArray: public InOutInterface, public RawArray<char>
	{
	public:
		ByteArray();
		ByteArray(int cap, int dcap=1, int sz=0);
		ByteArray(const ByteArray& ba);
		ByteArray(const char *bt, lnum btSize);
		ByteArray(const char *str);

		ByteArray& operator=(const ByteArray& ba);
		ByteArray& operator=(const char *str);

		bool operator ==(const ByteArray& ba) const;
		bool operator ==(const char *str) const;


		void readBytes(char *bt, lnum btSize);
		void writeBytes(const char *bt, lnum btSize);
		void prepareForWrite(lnum byteCapacity);
		bool atEnd() const;

		int writeIndex() const;
		int readIndex() const;
		void setWriteIndex(int i);
		void setReadIndex(int i);

	private:
		int ri;
		int wi;		
	};

	


//=========================================================================
// 	class StreamVal
// 	{
// 	public:
// 		StreamVal():bArr(0),s(0){}
// 		template<class T>
// 		StreamVal(T& obj):bArr(reinterpret_cast<char*>(&obj)),s(sizeof(T)){}
// 		StreamVal(const StreamVal& sv):s(sv.s),bArr(sv.bArr){}
// 		void operator = (const StreamVal& sv){bArr=sv.bArr; s=sv.s;}
// 		char *bArr;
// 		int s;
// 	};
// 
// 	class StreamConstVal
// 	{
// 	public:
// 		StreamConstVal():bArr(0),s(0){}		
// 		template<class T>
// 		StreamConstVal(const T& obj):bArr(reinterpret_cast<const char*>(&obj)),s(sizeof(T)){}
// 		StreamConstVal(const StreamConstVal& scv): bArr(scv.bArr), s(scv.s){}
// 		const char *bArr;
// 		int s;
// 	};
	
//=========================================================================


//=========================================================================
	class ByteStream: public InOutInterface
	{
	public:

		ByteStream();
		ByteStream(InOutInterface* io);

		void setIO(InOutInterface* io);		
		InOutInterface* getIO() const;
		

		template<class T>
		ByteStream& operator << (const T& val){write(val); return *this;}

		template<class T>
		ByteStream& operator >> (T& val){read(val);	return *this;}

		template<class T>
		ByteStream& operator >> (const T& val){read(val);	return *this;}

	
		//void read(ByteArray& out_bytes, int n);	

		template<class T>
		void read(T& val)
		{
			if(AbstractStreamer *as=dynamic_cast<AbstractStreamer *>(&val))
			{
				as->read(*this);
			}else
			{	
				readValue(val);
				//TODO: exaption
			}
		}

		template<class T>
		void read(const T& val)
		{
			if(const AbstractStreamer *as=dynamic_cast<const AbstractStreamer *>(&val))
			{
				as->read(*this);
			}else
			{
				//?
				//TODO: exaption
			}
		}

		void read(bool &val)				{readValue(val);}
		void read(char &val)				{readValue(val);}
		void read(short &val)				{readValue(val);}
		void read(unsigned short &val)		{readValue(val);}
		void read(int &val)					{readValue(val);}
		void read(unsigned int &val)		{readValue(val);}
		void read(long &val)				{readValue(val);}
		void read(unsigned long &val)		{readValue(val);}
		void read(long long  &val)			{readValue(val);}
		void read(unsigned long long &val)	{readValue(val);}
		void read(float &val)				{readValue(val);}
		void read(double &val)				{readValue(val);}


		template<class T>
		void readValue(T& val)
		{
			readBytes(reinterpret_cast<char*>(&val),sizeof(T));			
		}

	
		template<class T>
		void write(const T& val)
		{			
			if(const AbstractStreamer *as=dynamic_cast<const AbstractStreamer*>(&val))
			{
				as->write(*this);
			}else
			{
				writeValue(val);
				//TODO: exaption
			}
		}

		void write(bool val)				{writeValue(val);}
		void write(char val)				{writeValue(val);}
		void write(short val)				{writeValue(val);}
		void write(unsigned short val)		{writeValue(val);}
		void write(int  val)				{writeValue(val);}
		void write(unsigned int val)		{writeValue(val);}
		void write(long  val)				{writeValue(val);}
		void write(unsigned long val)		{writeValue(val);}
		void write(long long val)			{writeValue(val);}
		void write(unsigned long long val)	{writeValue(val);}
		void write(float val)				{writeValue(val);}
		void write(double val)				{writeValue(val);}

		template<class T>
		void writeValue(const T& val)
		{
			writeBytes(reinterpret_cast<const char*>(&val),sizeof(T));
		}

		void readBytes(char *bt, lnum btSize);
		void writeBytes(const char *bt, lnum btSize);
		void prepareForWrite(lnum byteCapacity);


	private:
		InOutInterface *io_;
	};



}

#endif
