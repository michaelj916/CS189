#include "Maze.h"

Maze::Maze()
{
	// Making a test maze by hand to make testing easy without giving away the extra credit of the maze maker.

	mStart = new Cell;
	mStart->mNorth = new Cell;
	mStart->mNorth->mNorth = new Cell;
	mStart->mEast = new Cell;
	mStart->mEast->mEast = new Cell;
	mStart->mEast->mEast->mNorth = new Cell;
	mStart->mEast->mEast->mNorth->mNorth = new Cell;
	mStart->mEast->mEast->mNorth->mNorth->mIsExit = true;
	// This is a big U 
}

// recursive destructor driver
Maze::~Maze()
{
	// call recursive function
	RecursiveCleanUp(mStart);
}

void Maze::RecursiveCleanUp(Maze::Cell* tCurrent)
{
	// if a start cell exists, recursively check its neighbors and delete 
	if (tCurrent) 
	{
		if (tCurrent->mNorth)
		{
			RecursiveCleanUp(tCurrent->mNorth);
		}
		if (tCurrent->mEast)
		{
			RecursiveCleanUp(tCurrent->mEast);
		}
		if (tCurrent->mSouth)
		{
			RecursiveCleanUp(tCurrent->mSouth);
		}
		if (tCurrent->mWest)
		{
			RecursiveCleanUp(tCurrent->mWest);
		}

		delete tCurrent;
	}
}

bool Maze::MazeRecursive(Maze::Cell* tCurrent, std::stack<std::string>* tPath)
{
	// return true if we are the exit
	if (tCurrent->mIsExit)
	{
		tPath->push("Successful Exit\t");
		return true;
	}

	// mark cell as processed
	tCurrent->mProcessed = true;

	/* ---- check neighbor cells, same for each direction ---- */
	if (tCurrent->mNorth)
	{
		// check if north cell is not processed
		if (!tCurrent->mNorth->mProcessed)
		{
			// check if recursive call on north cell is true
			if (MazeRecursive(tCurrent->mNorth, tPath))
			{
				// push to the stack and return true
				tPath->push("N -> ");
				return true;
			}
		}
	}
	
	if (tCurrent->mEast)
	{
		if (!tCurrent->mEast->mProcessed)
		{
			if (MazeRecursive(tCurrent->mEast, tPath))
			{
				tPath->push("E -> ");
				return true;
			}
		}
	}

	if (tCurrent->mSouth)
	{
		if (!tCurrent->mSouth->mProcessed)
		{
			if (MazeRecursive(tCurrent->mSouth, tPath))
			{
				tPath->push("S -> ");
				return true;
			}
		}
	}

	if (tCurrent->mWest)
	{
		if (!tCurrent->mWest->mProcessed)
		{
			if (MazeRecursive(tCurrent->mWest, tPath))
			{
				tPath->push("W -> ");
				return true;
			}
		}
	}

	// stub
	return false;
}

// Driver
std::stack<std::string> Maze::SolveMaze()
{
	// Don't need to change this.
	std::stack<std::string> tAnswer;
	MazeRecursive(mStart, &tAnswer);
	return tAnswer;
}
