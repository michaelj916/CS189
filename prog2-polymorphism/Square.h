#ifndef SQUARE_H
#define SQUARE_H
#include "Shape.h"
class Square :
    public Shape
{
    double edge;
public:
    Square();
    virtual void SetSize(double);
    virtual double GetArea();
    virtual ~Square();
};
#endif // SQUARE_H