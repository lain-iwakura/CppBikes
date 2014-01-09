#ifndef PREBIKES_TYPES_H
#define PREBIKES_TYPES_H
#include <cstddef>

namespace Bikes
{
	typedef double rnum;
    typedef int num;
    typedef unsigned int sznum;
	typedef long long lnum;
	typedef unsigned long long ulnum;
    typedef std::size_t sznum;    

    enum ApproximationMethodType
    {
        ApproxMethod_avg,
        ApproxMethod_max,
        ApproxMethod_min        
    };
}

#endif
