#ifndef CIRCLE_H
#define CIRCLE_H
#include "Shape.h"
class Circle :
    public Shape
{
    double radius;
public:
    Circle();
    void SetSize(double);
    double GetArea();
    virtual ~Circle();
};
#endif // CIRCLE_H