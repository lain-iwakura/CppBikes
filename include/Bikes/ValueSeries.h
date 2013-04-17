#ifndef MYCPP_VALUESERIES_H
#define MYCPP_VALUESERIES_H

#include <Bikes/List.h>
#include <Bikes/BasicMath.h>

namespace Bikes
{

template<class T>
class ValueSeries
{
public:
	ValueSeries(int maxN=1)
	{
		nSeries=ABS(maxN);
	}
	~ValueSeries(){}

	void operator+= (const T &v)
	{
		if(series.count()>nSeries) series.removeFirst();
		series+=v;
	}

	void setMaxNumber(int maxN)
	{
		nSeries=ABS(maxN);
		while(series.count()>nSeries) series.removeFirst();
	}

	T avg()
	{
		if(series.count()==0) return T();
		T r=series.first();
		for(int i=1; i<series.count(); i++) r+=series[i];
		r/=series.count();
		return r;
	}
	

private:
	int nSeries;
	List<T> series;
};


}
#endif