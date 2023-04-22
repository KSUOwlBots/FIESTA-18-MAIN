#ifndef QuickQueue_h
#define QuickQueue_h

class QuickQueue {
public:
    QuickQueue(int givenSize);

    void pop();
    void append(double value);
    void clear();
    void fill(int value);
    void print();
    double sum();
    double mean();
    double wma();
    double sumError(double target, int errorSize);
    double top();
    
    double * data;
    int size;
};

#endif