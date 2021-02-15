#ifndef SHAPE_H
#define SHAPE_H
class Shape
{

public:
	Shape();
	virtual void SetSize(double) = 0; 
	virtual double GetArea() = 0;
	virtual ~Shape();
};
#endif // SHAPE_H