#ifndef STUDENT_H
#define STUDENT_H
#include <string>

class Student
{
public:
	Student();
	void SetName(std::string);
	void SetGPA(double);
	void SetDebt(double);
	std::string GetName();
	double GetGPA();
	double GetDebt();
	struct ByGPA;
	struct ByDebt;
	~Student();
private:
	double GPA;
	double StudentDebt;
	std::string Name;	
};

#endif // STUDENT_H
