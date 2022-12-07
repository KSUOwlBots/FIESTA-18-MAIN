#include "HMA.hpp"

HMA::HMA(int period) :wma1Input((int)(period/2)), wma2Input(period), combinedWMAs(period)
{
    this->size = period;
}

void HMA::input(double value)
{
    this->wma1Input.append(value);
    this->wma2Input.append(value);
    
    this->combinedWMAs.append(2*this->wma1Input.wma() - this->wma2Input.wma());
}

double HMA::value()
{
    return this->combinedWMAs.wma();
}

void HMA::clear()
{
    this->wma1Input.clear();
    this->wma2Input.clear();
    this->combinedWMAs.clear();
}