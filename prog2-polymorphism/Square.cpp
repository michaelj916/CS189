#include <iostream>
#include "Square.h"

// default constructor
Square::Square() { edge = 2; }

// SetSize method for square class
void Square::SetSize(double e)
{
	e = edge;
}

// GetArea method for square class
double Square::GetArea()
{
	return edge * edge;
}

// destructor
Square::~Square() {}