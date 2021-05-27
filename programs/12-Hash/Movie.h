#pragma once
#include <string>

class Movie
{
	std::string mTitle;
	int mYear;
	int mMinutes;

public:
	Movie(std::string tTitle, int tYear, int tMinutes);
	Movie();
	~Movie();

	struct Hashor
	{
		int operator()(const Movie& tWhat)
		{
			int tRunningTotal = 0;

			// loop through size of movie title, perform bit operations
			for (int i = 0; i < tWhat.mTitle.size(); ++i)
			{																		// char is considered a number by default when used in arithmatic 
				tRunningTotal = ((tRunningTotal >> 2) + (tRunningTotal >> 2)) + (tWhat.mYear >> 3) + (tWhat.mTitle[i] << 5) * (tWhat.mYear << 2);
			}

			return tRunningTotal;
		}
	};
	struct Equalitor
	{
		bool operator()(const Movie &tLHS, const Movie &tRHS)
		{
			if (tLHS.mTitle == tRHS.mTitle && tLHS.mMinutes == tRHS.mMinutes && tLHS.mYear == tRHS.mYear) // if the member variables between two objs are the same
				return true;     

			return false;  // by default return false
		}
	};
};

