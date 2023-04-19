#include "helpers/HullMovingAverage.hpp"

HullMovingAverage::HullMovingAverage(int period) :wma1Input((int)(period/2)), wma2Input(period), combinedWMAs(period)
{
    this->size = period;
}

void HullMovingAverage::input(double value)
{
    this->wma1Input.append(value);
    this->wma2Input.append(value);
    
    this->combinedWMAs.append(2*this->wma1Input.wma() - this->wma2Input.wma());
}

double HullMovingAverage::value()
{
    return this->combinedWMAs.wma();
}

void HullMovingAverage::clear()
{
    this->wma1Input.clear();
    this->wma2Input.clear();
    this->combinedWMAs.clear();
}

void HullMovingAverage::fill(int value)
{
    this->wma1Input.fill(value);
    this->wma2Input.fill(value);
    this->combinedWMAs.fill(value);
}