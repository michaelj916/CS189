// 189 Recursion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Maze.h"

int main()
{
	Maze tTestMaze;
	std::stack<std::string> tPath;
	tPath = tTestMaze.SolveMaze();

	while (!tPath.empty())
	{
		std::string temp = tPath.top();
		std::cout << temp;
		tPath.pop();		
	}
}

