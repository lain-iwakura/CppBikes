#ifndef INCLUDE_BIKES_TYPES_H
#define INCLUDE_BIKES_TYPES_H

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

	typedef rnum kmeter;

	typedef rnum cosnum;

	typedef rnum sinnum;

	typedef rnum tannum;

	enum ValSign
	{
		positiveSign,
		negativeSign,
		undefinedSign
	};
}

#endif // <- INCLUDE_BIKES_TYPES_H
