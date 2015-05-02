#include <Bikes/Stream/ByteStream.h>
#include <Bikes/Array/List.h>
#include <Bikes/Array/ByteArray.h>


using namespace std;

namespace Bikes
{


class AbstractUnsignedValueStreamer
{
public:
	virtual ~AbstractUnsignedValueStreamer(){}
	virtual sznum maxNumber() const = 0;
	virtual void read(ByteStream& bs, sznum& rval) const = 0;
	virtual void write(ByteStream& bs, sznum wval) const = 0;
};

template<typename T>
class UnsignedValueStreamer : public AbstractUnsignedValueStreamer
{
public:

	sznum maxNumber() const	{		
        return std::numeric_limits<T>::max();
	}

	void read(ByteStream& bs, sznum& rval) const{
		T r;
		bs >> r;
		rval = sznum(r);
	}

	void write(ByteStream& bs, sznum wval) const{
		bs << T(wval);
	}
};

struct UnsignedValueStreamerCollection
{
	UnsignedValueStreamerCollection(){
		streamers.push_back(new UnsignedValueStreamer<unsigned char>());
		streamers.push_back(new UnsignedValueStreamer<unsigned short>());
		streamers.push_back(new UnsignedValueStreamer<unsigned long>());
		streamers.push_back(new UnsignedValueStreamer<unsigned long long>());
	}
	~UnsignedValueStreamerCollection()
	{	
		for (sznum i = 0; i < streamers.size(); i++)
			delete streamers[i];
	}
	std::vector< AbstractUnsignedValueStreamer*> streamers;
};




AbstractUnsignedValueStreamer* uvalStreamerFor(sznum val)
{
	static const UnsignedValueStreamerCollection uvStreamers;
	for (int i = 0; i < uvStreamers.streamers.size(); i++)
	{
		if (val <= uvStreamers.streamers[i]->maxNumber())
			return uvStreamers.streamers[i];
	}
	return 0;
}



class ByteStreamData
{
public:
	ByteStreamData(InputOutput* _io=0) :io(_io)
	{
	}

	sznum getIndexOfRecurrentData(const ByteArray& data);

	void takeRecurrentData(ByteArray* data);


	InputOutput *io;
	List<ByteArray> recData;
	List< vector<sznum> > indexMap;
};

sznum ByteStreamData::getIndexOfRecurrentData(const ByteArray& data)
{		
	sznum dtsz = data.size();
	if (dtsz < indexMap.size())
	{
		vector<sznum>& indexes = indexMap[dtsz];		
		for (vector<sznum>::const_iterator ind = indexes.begin(); ind != indexes.end(); ++ind)
		{
			if (recData[*ind] == data)
				return *ind;
		}
		sznum ind = recData.size();
		recData.push_back(data);
		indexes.push_back(ind);
		return ind;
	}
	else
	{
		sznum ind = recData.size();
		recData.push_back(data);
		indexMap.resize(dtsz + 1);
		indexMap[dtsz].push_back(ind);
		return ind;
	}
}

void ByteStreamData::takeRecurrentData(ByteArray* data)
{		
	sznum dtsz = data->size();

	if (dtsz >= indexMap.size())
		indexMap.resize(dtsz + 1);

	indexMap[dtsz].push_back(recData.size());
	recData.take_back(data);
}



ByteStream::~ByteStream()
{
	delete _d;
}


ByteStream::ByteStream():
_d(new ByteStreamData)
{
}


ByteStream::ByteStream( InputOutput* io ):
_d(new ByteStreamData(io))
{
}


void ByteStream::setIO( InputOutput* io)
{		
	_d->io=io;
	_d->recData.clear();
	_d->indexMap.clear();
}

InputOutput* ByteStream::getIO() const
{
	return _d->io;
}


void ByteStream::read(bool &val){
    readValue(val);
}

void ByteStream::read(char &val)
{
    readValue(val);
}		  

void ByteStream::read(unsigned char &val)
{
	readValue(val);
}

void ByteStream::read(short &val)
{
    readValue(val);
}

void ByteStream::read(unsigned short &val)
{
    readValue(val);
}

void ByteStream::read(int &val)
{
    readValue(val);
}

void ByteStream::read(unsigned int &val)
{
    readValue(val);
}

void ByteStream::read(long &val)
{
    readValue(val);
}

void ByteStream::read(unsigned long &val)
{
    readValue(val);
}

void ByteStream::read(long long &val)
{
    readValue(val);
}

void ByteStream::read(unsigned long long &val)
{
    readValue(val);
}

void ByteStream::read(float &val)
{
    readValue(val);
}

void ByteStream::read(double &val)
{
    readValue(val);
}


void ByteStream::write(bool val)
{
    writeValue(val);
}

void ByteStream::write(char val)
{
    writeValue(val);
}

void ByteStream::write(short val)
{
    writeValue(val);
}

void ByteStream::write(unsigned short val)
{
    writeValue(val);
}

void ByteStream::write(int val)
{
    writeValue(val);
}

void ByteStream::write(unsigned int val)
{
    writeValue(val);
}

void ByteStream::write(long val)
{
    writeValue(val);
}

void ByteStream::write(unsigned long val)
{
    writeValue(val);
}

void ByteStream::write(long long val)
{
    writeValue(val);
}

void ByteStream::write(unsigned long long val)
{
    writeValue(val);
}

void ByteStream::write(float val)
{
    writeValue(val);
}

void ByteStream::write(double val)
{
    writeValue(val);
}

void ByteStream::write(unsigned char val)
{
	writeValue(val);
}






void ByteStream::readRecurrentData(ByteArray& data)
{
	sznum rdsz = _d->recData.size();
	AbstractUnsignedValueStreamer* uvs = uvalStreamerFor(rdsz);
	sznum ind;
	uvs->read(*this, ind);
	if (ind >= rdsz)
	{
		sznum dtsz;
		read(dtsz);
		ByteArray *ba = new ByteArray(dtsz,dtsz);
		readBytes(ba->data(), dtsz);
		_d->takeRecurrentData(ba);
	}
	data = _d->recData[ind];
}

void ByteStream::writeRecurrentData(const ByteArray& data)
{								
	sznum rdsz = _d->recData.size();
	AbstractUnsignedValueStreamer* uvs = uvalStreamerFor(rdsz);	
	sznum ind = _d->getIndexOfRecurrentData(data);
	uvs->write(*this, ind);
	if (ind == rdsz)
	{
		write(data.size());
		writeBytes(data.data(), data.size());
	}
}

void ByteStream::readBytes(char *bt, sznum btSize)
{
    _d->io->readBytes(bt, btSize);
}

void ByteStream::writeBytes(const char *bt, sznum btSize)
{
    _d->io->writeBytes(bt, btSize);
}

void ByteStream::prepareForWrite(sznum byteCapacity)
{
    _d->io->prepareForWrite(byteCapacity);
}

bool ByteStream::atEnd() const
{
    return _d->io->atEnd();
}

bool ByteStream::isRandomAccess() const
{
    return _d->io->isRandomAccess();
}

bool ByteStream::setPosition(sznum pos)
{
    return _d->io->setPosition(pos);
}

Bikes::sznum ByteStream::getPosition() const
{
    return _d->io->getPosition();
}

} //Bikes
