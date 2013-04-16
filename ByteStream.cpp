#include "ByteStream.h"



namespace CppBikes
{



/*
	ByteStream::ByteStream( std::vector<char>* bytes )
	{
		b=bytes;
		bi=0;
	}

	void ByteStream::setByteArray( std::vector<char> *bytes )
	{
		b=bytes;
		bi=0;
	}

	std::vector<char>* ByteStream::byteArray()
	{
		return b;
	}

	void ByteStream::read( std::vector<char> &out_bytes, int n )
	{
		int s=bi+n;
		if(s>b->size())s=b->size();
		int i=out_bytes.size();
		out_bytes.resize(i+n);
		for(;bi<s;bi++,i++)
			out_bytes[i]=(*b)[bi];
	}

	void ByteStream::write(const std::vector<char> &in_bytes )
	{
		int j=b->size();
		b->resize(j+in_bytes.size());
		for(int i=0; i<in_bytes.size(); i++,j++)
		{
			(*b)[j]=in_bytes[i];
		}
	}

	void ByteStream::skipRead( int n )
	{
		bi+=n;
		if(bi>b->size()) bi=b->size();
	}


	int ByteStream::remainderSize()
	{
		return b->size()-bi;
	}

	int ByteStream::size()
	{
		return b->size();
	}
//*/


	void ByteStream::setByteArray( RawArray<char>* bytes )
	{
		b=bytes;
		ri=0;
		wi=bytes->size();
	}

}