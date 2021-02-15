#include <iostream>
#include <vector>
#include "Shape.h"
#include "Square.h"
#include "Circle.h"

int main()
{
	std::vector<Shape*> shapes;

	// loop through by an arbitrary amount and add Square 
	// and Circle objects to the shapes vector
	for (int i = 0; i < 5; i++)
	{
		shapes.push_back(new Square());
		shapes.push_back(new Circle());
	}

	// loop through the vector and call GetArea() method on each shape
	for (int j = 0; j < shapes.size(); j++)
	{
		std::cout << shapes.at(j)->GetArea() << std::endl;
	}

	return 0;
}