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

struct Student::ByGPA {
	bool operator()(const Student &tStudent1, const Student &tStudent2)
	const
	{
	return tStudent1.GPA < tStudent2.GPA;
	}
};

struct Student::ByDebt {
	bool operator()(const Student &tStudent1, const Student &tStudent2)
	const
	{
	return tStudent1.StudentDebt < tStudent2.StudentDebt;
	}
};

Student::~Student() {}
