#include "main.h"
#include "helpers/Maths.hpp"


double mean(double val1, double val2) { return ((val1 + val2) / 2); }

double median(double arrOG[], int size)
{
    double arr[size];
    for (int i = 0; i < size; i++) { arr[i] = arrOG[i]; }
    std::sort(arr, arr + size);
    if (size % 2 != 0)
        return (double)arr[size / 2];
    return (double)(arr[(size - 1) / 2] + arr[size / 2]) / 2.0;
}

double clamp(double val, double max, double min) {
  return (std::max(std::min(val, max), min));
}