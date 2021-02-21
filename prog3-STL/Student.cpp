#include "Student.h"
#include <string>

Student::Student() 
{
	GPA = 0.0;
	StudentDebt = 0.0;
	Name = "";
}

void Student::SetName(std::string tName)
{
	Name = tName;
}

void Student::SetGPA(double tGPA)
{
	GPA = tGPA;
}

void Student::SetDebt(double tDebt)
{
	StudentDebt = tDebt;
}

std::string Student::GetName()
{
	return Name;
}

double Student::GetGPA()
{
	return GPA;
}

double Student::GetDebt()
{
	return StudentDebt;
}

Student::~Student() {}