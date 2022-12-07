#pragma once

#include "api.h"
#include "main.h"

class QuickQueue {
public:
    QuickQueue(int givenSize);

    void pop();
    void append(double value);
    void clear();
    void print();
    double sum();
    double mean();
    double wma();
    
    double * data;
    int size;
};