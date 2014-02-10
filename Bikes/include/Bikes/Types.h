#ifndef PREBIKES_TYPES_H
#define PREBIKES_TYPES_H

#include <cstddef>

namespace Bikes
{
	typedef double rnum;

    typedef int num;

    typedef unsigned int unum;

	typedef long long lnum;

	typedef unsigned long long ulnum;

    typedef std::size_t sznum;    

	typedef rnum radian;

	typedef rnum degree;

	typedef rnum meter;

	typedef rnum cosnum;

	typedef rnum sinnum;

	typedef rnum tannum;

	enum ApproximationMethodType
	{
		ApproxMethod_avg,
		ApproxMethod_max,
		ApproxMethod_min        
	};

	enum ValSign
	{
		positiveSign,
		negativeSign,
		undefinedSign
	};
}

#endif
