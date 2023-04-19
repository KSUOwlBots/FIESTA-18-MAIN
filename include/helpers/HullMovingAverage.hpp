#ifndef HullMovingAverage_h
#define HullMovingAverage_h

#include "api.h"
#include "helpers/QuickQueue.hpp"

class HullMovingAverage {
public:
    HullMovingAverage(int period);

    void input(double data);
    double value();
    void clear();
    void fill(int value);
    
    int size;
    QuickQueue wma1Input;
    QuickQueue wma2Input;
    QuickQueue combinedWMAs;
};

#endif