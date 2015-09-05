#ifndef INCLUDE_BIKES_TESTING_H
#define INCLUDE_BIKES_TESTING_H
#include <ctime>
#include <iostream>

#define BIKES_TIMETEST_START(REPEATS)                                          \
    {                                                                          \
        unsigned long long BIKES_TIMETEST_ITER = 0;                            \
        unsigned long long BIKES_TIMETEST_REPEATS = (REPEATS);                 \
        unsigned long long BIKES_TIMETEST_TIME = std::clock();                 \
        for (                                                                  \
            ;                                                                  \
            BIKES_TIMETEST_ITER < BIKES_TIMETEST_REPEATS;                      \
            ++BIKES_TIMETEST_ITER                                              \
            )                                                                  \
        {

#define BIKES_TIMETEST_FINISH(AVG_TIME_REFERENCE)                              \
        }                                                                      \
        (AVG_TIME_REFERENCE) = double(std::clock() - BIKES_TIMETEST_TIME)      \
                               / (double(BIKES_TIMETEST_REPEATS)*1000.0);      \
    }

#define BIKES_COUT_VAR(VAR)                                                    \
    std::cout << #VAR << " = " << (VAR) << std::endl << std::endl;

#define BIKES_COUT_TYPE(T)                                                    \
    std::cout << #T << " = " << typeid(T()).name() << std::endl << std::endl;

	
#endif // <- INCLUDE_BIKES_TESTING_H
