#ifndef _BIKES_BYTESTREAM_H_
#define _BIKES_BYTESTREAM_H_
#include <Bikes/RawArray.h>


namespace Bikes
{
	class ByteStream
	{
	public:

		ByteStream():b(0){}
		ByteStream(RawArray<char>* bytes);

		void setByteArray(RawArray<char>* bytes);
		RawArray<char>* byteArray();

		char* data() const;

		template<class T>
		ByteStream& operator << (const T& val){write(val);	return *this; }

		template<class T>
		ByteStream& operator >> (T& val){read(val);	return *this; }

		int size() const;
		int remainderReadSize() const;

		int readPosition() const;
		int writePosition() const;
		

		//void read(RawArray<char>& out_bytes, int n);	

		template<class T>
		void read(T& val)
		{
			char ch[sizeof(T)];
			T *v=reinterpret_cast<T*>(ch);
			for(int i=0; (i<sizeof(T))&&(ri<b->size()); i++, ri++)
				ch[i]=(*b)[ri];
			val=*v;
		}
	
//		void write(RawArray<char>& in_bytes);

		template<class T>
		void write(const T& val)
		{
			int s0=b->size();
			int ds=sizeof(T);
			if(wi+ds>s0) b->setSize(wi+ds);
			
			const char* ch=reinterpret_cast<const char*>(&val);
			for(int i=0; i<ds; i++,wi++)
			{
				b->at(wi)=ch[i];
			}
		}
		 			

	private:
		RawArray<char> *b;
		int ri;
		int wi;
	};
}

#endif