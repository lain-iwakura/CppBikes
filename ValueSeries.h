#ifndef MYCPP_VALUESERIES_H
#define MYCPP_VALUESERIES_H

#include "ContainerInterface.h"
#include "BasicMath.h"

template<class T>
class ValueSeries
{
public:
	ValueSeries(int maxN=1)
	{
		nSeries=Abs(maxN);
	}
	~ValueSeries(){}

	void operator+= (const T &v)
	{
		if(series.count()>nSeries) series.removeFirst();
		series+=v;
	}

	void setMaxNumber(int maxN)
	{
		nSeries=Abs(maxN);
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



#endif