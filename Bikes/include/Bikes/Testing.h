#ifndef INCLUDE_BIKES_TESTING_H
#define INCLUDE_BIKES_TESTING_H
#include <Bikes/Types.h>
#include <ctime>



#define BIKES_TIMETEST_START(REPEATS)                                          \
    {                                                                          \
        Bikes::sznum BIKES_TIMETEST_ITER = 0;                                  \
        Bikes::sznum BIKES_TIMETEST_REPEATS = REPEATS;                         \
        Bikes::sznum BIKES_TIMETEST_TIME = std::clock();                       \
        for (                                                                  \
            ;                                                                  \
            BIKES_TIMETEST_ITER < BIKES_TIMETEST_REPEATS;                      \
            ++BIKES_TIMETEST_ITER                                              \
            )                                                                  \
		{

#define BIKES_TIMETEST_FINISH(AVG_TIME_REFERENCE)                              \
        }                                                                      \
        AVG_TIME_REFERENCE = (Bikes::rnum(std::clock() - BIKES_TIMETEST_TIME) / Bikes::rnum(BIKES_TIMETEST_REPEATS)) / 1000.0;\
    }


namespace Bikes
{
}	
#endif // <- INCLUDE_BIKES_TESTING_H
