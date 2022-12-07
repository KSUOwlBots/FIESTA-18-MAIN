#pragma once

#include "api.h"
#include "main.h"
#include "QuickQueue.hpp"

class HMA {
public:
    HMA(int period);

    void input(double data);
    double value();
    void clear();
    
    int size;
    QuickQueue wma1Input;
    QuickQueue wma2Input;
    QuickQueue combinedWMAs;
};