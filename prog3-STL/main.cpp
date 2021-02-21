#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include "Student.h"

int main()
{
	// list of integers
	std::list<int> myList;

	// add ints 0 - 30 to myList
	for (int i = 0; i < 31; i++)
		myList.push_back(i);

	// iterate through list, print out each value
	std::for_each(myList.begin(), myList.end(), [](int n) { std::cout << n << std::endl; });
	for (std::list<int>::iterator it = myList.begin(); it != myList.end(); it++)
		std::cout << *it << std::endl;

	// clear myList
	myList.clear();

	// vector of students
	std::vector<Student*> vStudents;

	// adding 7 student objects to the vector
	for (int j = 0; j < 6; j++)
		vStudents.push_back(new Student());

	// clear vStudents
	vStudents.clear();

	// stack of students
	std::stack<Student*> studentStack;

	// adding 12 student objects to the stack
	for (int x = 0; x < 11; x++)
		studentStack.push(new Student());

	// set of ints
	std::set<int> mySet;

	// adding int 0-10 to mySet
	for (int z = 0; z < 11; z++)
		mySet.insert(z);

	// clearing mySet
	mySet.clear();

	// map (string, int)
	std::map<std::string, int> moviesByYear;

	// add movies & release date to map
	moviesByYear.insert(std::pair<std::string, int>("The Hills Have Eyes", 1977));
	moviesByYear.insert(std::pair<std::string, int>("Eraserhead", 1977));
	moviesByYear.insert(std::pair<std::string, int>("Gummo", 1997));
	moviesByYear.insert(std::pair<std::string, int>("Scott Pilgrim vs. the World", 2010));
	moviesByYear.insert(std::pair<std::string, int>("A Clockwork Orange", 1971));

	// clearing map
	moviesByYear.clear();

	// unordered_map (string, int)
	std::unordered_map<std::string, int> uMoviesByYear;

	// add movies & release date to unordered_map
	uMoviesByYear.insert(std::pair<std::string, int>("The Hills Have Eyes", 1977));
	uMoviesByYear.insert(std::pair<std::string, int>("Eraserhead", 1977));
	uMoviesByYear.insert(std::pair<std::string, int>("Gummo", 1997));
	uMoviesByYear.insert(std::pair<std::string, int>("Scott Pilgrim vs. the World", 2010));
	uMoviesByYear.insert(std::pair<std::string, int>("A Clockwork Orange", 1971));

	// clearing unorderd_map
	uMoviesByYear.clear();

	/*-----------------------------------------------------------------------*/
	/*
	struct ByGPA {

	};

	struct ByDebt {
		bool operator()(const Student& s1, const Student& s2)
		{
			if (s1.GetDebt > s2.GetDebt) return true;
			if (s1.GetDebt < s2.GetDebt) return false;
		}
	};

	std::priority_queue<Student, std::vector<Student>, Student::ByGPA> myGPAPq;
	*/

	return 0;
}