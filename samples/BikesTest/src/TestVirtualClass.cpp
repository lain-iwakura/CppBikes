#include "Tests.h"
#include <Bikes/Geom/Vector.h>
#include <Bikes/Geom/Point.h>
#include <Bikes/Testing.h>
#include <iostream>

using namespace Bikes;

struct Str3x8
{
    double d1;
    double d2;
    double d3;
};

void test_virtualclass()
{
    BIKES_COUT_VAR(sizeof(Vector));
    BIKES_COUT_VAR(sizeof(Point));
    BIKES_COUT_VAR(sizeof(Str3x8));
}
