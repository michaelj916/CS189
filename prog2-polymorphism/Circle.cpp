#include <iostream>
#include "Circle.h"

Circle::Circle() { radius = 1; }

// SetArea method for Circle class
void Circle::SetSize(double r)
{
	r = radius;
}

// GetArea method for Circle class
double Circle::GetArea()
{
	return 3.14 * pow(radius, 2.0);
}

Circle::~Circle() {}