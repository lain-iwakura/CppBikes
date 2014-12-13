#ifndef INCLUDE_BIKES_STREAM_BYTESTREAM_H
#define INCLUDE_BIKES_STREAM_BYTESTREAM_H

#include <Bikes/Types.h>
#include <Bikes/Stream/StreamerInterface.h>
#include <Bikes/Stream/InOutInterface.h>

namespace Bikes
{
	class ByteStreamData;
	class ByteArray;
    	
//=========================================================================
	class ByteStream: public InOutInterface
	{
	public:

		~ByteStream();

		ByteStream();

		ByteStream(InOutInterface* io);

		void setIO(InOutInterface* io);		

		InOutInterface* getIO() const;
		

		template<class T>
		ByteStream& operator << (const T& val)
        {
            write(val); 
            return *this;
        }

		template<class T>
		ByteStream& operator >> (T& val)
        {
            read(val);	
            return *this;
        }

		template<class T>
		ByteStream& operator >> (const T& val)
        {
            read(val);	
            return *this;
        }
        	
		template<class T>
		void read(T& val)
		{
			if(StreamerInterface *as=dynamic_cast<StreamerInterface *>(&val))
			{
				as->read(*this);
			}else
			{	
				readValue(val);
				//exception
			}
		}

		template<class T>
		void read(const T& val)
		{
			if(const StreamerInterface *as=dynamic_cast<const StreamerInterface *>(&val))
			{
				as->read(*this);
			}else
			{
				//?
				//exception
			}
		}

		
		template<class T>
		void readValue(T& val)
		{
			readBytes(reinterpret_cast<char*>(&val),sizeof(T));			
		}

	
		template<class T>
		void write(const T& val)
		{			
			if(const StreamerInterface *as=dynamic_cast<const StreamerInterface*>(&val))
			{
				as->write(*this);
			}else
			{
				writeValue(val);
				//exception
			}
		}

		template<class T>
		void writeValue(const T& val)
		{
			writeBytes(reinterpret_cast<const char*>(&val),sizeof(T));
		}

		void readBytes(char *bt, sznum btSize);

		void writeBytes(const char *bt, sznum btSize);

		void prepareForWrite(sznum byteCapacity);


        void read(bool &val);
        void read(char &val);
		void read(unsigned char &val);
        void read(short &val);
        void read(unsigned short &val);
        void read(int &val);
        void read(unsigned int &val);
        void read(long &val);
        void read(unsigned long &val);
        void read(long long  &val);
        void read(unsigned long long &val);
        void read(float &val);
        void read(double &val);

        void write(bool val);
        void write(char val);
		void write(unsigned char val);
        void write(short val);
        void write(unsigned short val);
        void write(int  val);
        void write(unsigned int val);
        void write(long  val);
        void write(unsigned long val);
        void write(long long val);
        void write(unsigned long long val);
        void write(float val);
        void write(double val);

		void readRecurrentData(ByteArray& data);
		void writeRecurrentData(const ByteArray& data);		

	private:
		ByteStreamData *_d;
		InOutInterface *io_;
	};



}

#endif // <- INCLUDE_BIKES_STREAM_BYTESTREAM_H
