#ifndef _BIKES_BYTESTREAM_H_
#define _BIKES_BYTESTREAM_H_
#include <Bikes/RawArray.h>
#include <vector>

namespace Bikes
{


	typedef RawArray<char> ByteArray;

	

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
	class ByteStream
	{
	public:

		ByteStream():b(0){}
		ByteStream(ByteArray* bytes);

		void setByteArray(ByteArray* bytes);
		ByteArray* byteArray();

		char* data() const;

		template<class T>
		ByteStream& operator << (const T& val){write(val); return *this;}

		template<class T>
		ByteStream& operator >> (T& val){read(val);	return *this;}

		template<class T>
		ByteStream& operator >> (const T& val){read(val);	return *this;}

		int size() const;
		int remainderReadSize() const;

		int readPosition() const;
		int writePosition() const;
		

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
			char *ch=reinterpret_cast<char*>(&val);			
			for(int i=0; (i<sizeof(T))&&(ri<b->size()); i++, ri++)
				ch[i]=b->at(ri);			
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
		void writeValue(T val)
		{
			int s0=b->size();
			int ds=sizeof(T);
			if(wi+ds>s0) b->setSize(wi+ds);

			const char* ch=reinterpret_cast<const char*>(&val);
			for(int i=0; i<ds; i++,wi++)			
				b->at(wi)=ch[i];			
		}

//-------------------------------------------------------------------------

// 		void read(std::vector<StreamVal>& valArr) //?
// 		{
// 			for(int i=0; (i<valArr.size())&&(ri<b->size()); i++)
// 			{
// 				for(int j=0; (j<valArr[i].s)&&(ri<b->size()); j++, ri++)
// 					valArr[i].bArr[j]=b->at(ri);
// 			}
// 		}
// 
// 		void write(const std::vector<StreamConstVal>& valArr) //?
// 		{
// 			int s0=b->size();
// 			int ds=0;
// 			for(int i=0; i<valArr.size(); i++)
// 				ds+=valArr[i].s;
// 			if(wi+ds>s0) b->setSize(wi+ds);  
// 
// 			for(int i=0; i<valArr.size(); i++)
// 			{
// 				for(int j=0; j<valArr[i].s; j++, wi++)
// 					b->at(wi)=valArr[i].bArr[j];
// 			}
// 		}

		//void write(const ByteArray &bArr); 

//-------------------------------------------------------------------------
	private:
		ByteArray *b;
		int ri;
		int wi;
	};



}

#endif