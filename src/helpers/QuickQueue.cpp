#include "helpers/QuickQueue.hpp"
#include "api.h"

QuickQueue::QuickQueue(int givenSize)
{
    this->data = new double[givenSize];
    this->size = givenSize;
    this->clear();
}

void QuickQueue::pop()
{
    for (int i = 0; i < this->size-1; i++) { this->data[i] = this->data[i + 1]; }
}

void QuickQueue::append(double value)
{
    this->pop();
    this->data[this->size - 1] = value;
}

void QuickQueue::clear()
{
    for (int i = 0; i < this->size; i++) { this->data[i] = 0; }
}

void QuickQueue::fill(int value)
{
    for (int i = 0; i < this->size; i++) { this->data[i] = value; }
}

double QuickQueue::top()
{ return this->data[this->size - 1]; }

double QuickQueue::sum()
{
    double sum = 0;
    for (int i = 0; i < this->size; i++)
    { sum += this->data[i]; }
    return sum;
}

double QuickQueue::sumError(double target, int errorSize)
{
    double sum = 0;
    for (int i = (this->size-1); i >this->size-(errorSize+1); i--)
    { sum += abs(target - this->data[i]); }
    return sum;
}

double QuickQueue::mean()
{
    return (this->sum() / this->size);
}

double QuickQueue::wma()
{
    double top = 0;
    for (int i = 0; i < this->size; i++)
    { top += this->data[i]*(i+1); }
    return top / (   (this->size* (this->size+1))/2   );
}