#ifndef Hopper_h
#define Hopper_h

#include "helpers/QuickQueue.hpp"
#include "api.h"
using namespace pros;

void hopperController(void *);

class Hopper {
public:
    QuickQueue distanceValues;

    Hopper(int distanceValueSize);

    int discs();

    int mostRecentValue;
};

#endif