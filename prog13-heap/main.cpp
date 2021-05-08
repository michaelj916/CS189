// 189 Heap-PQ.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "PriorityQueue.h"
#include <string>

using namespace std; // NEVER OUTSIDE SCHOOL

class SomeClass
{
public: // Being lazy and skipping proper public/private/get/set step since not point of assignment.
	int mTestNumber;
	SomeClass( int tNumber ) :mTestNumber( tNumber ) {}

	struct BestIsLow
	{
		bool operator()( const SomeClass& tLHS, const SomeClass& tRHS )
		{
			return tLHS.mTestNumber < tRHS.mTestNumber;
		}
	};
	struct BestIsHigh // Yay functors!  Without them we'd have to give operator < to SomeClass itself, and that would mean only one choice.
	{
		bool operator()( const SomeClass& tLHS, const SomeClass& tRHS )
		{
			return tLHS.mTestNumber > tRHS.mTestNumber;
		}
	};
};

int main()
{
	PriorityQueue<SomeClass, SomeClass::BestIsLow> tLowWins;
	PriorityQueue<SomeClass, SomeClass::BestIsHigh> tHighWins;

	tLowWins.Push( SomeClass( 4 ) );
	tLowWins.Push( SomeClass( 66 ) );
	tLowWins.Push( SomeClass( 14 ) );
	tLowWins.Push( SomeClass( 9 ) );
	tLowWins.Push( SomeClass( 33 ) );
	tLowWins.Push( SomeClass( 89 ) );
	tLowWins.Push( SomeClass( 42 ) );
	tLowWins.Push( SomeClass( 665 ) );
	tLowWins.Push( SomeClass( 9001 ) );
	tLowWins.Push( SomeClass( 1 ) );
	tLowWins.Push( SomeClass( 5 ) );
	tLowWins.Push( SomeClass( 44 ) );
	tLowWins.Push( SomeClass( 208 ) );

	//tHighWins.Push( SomeClass( 4 ) );
	//tHighWins.Push( SomeClass( 66 ) );
	//tHighWins.Push( SomeClass( 14 ) );
	//tHighWins.Push( SomeClass( 9 ) );
	//tHighWins.Push( SomeClass( 33 ) );
	//tHighWins.Push( SomeClass( 89 ) );
	//tHighWins.Push( SomeClass( 42 ) );
	//tHighWins.Push( SomeClass( 665 ) );
	//tHighWins.Push( SomeClass( 9001 ) );
	//tHighWins.Push( SomeClass( 1 ) );
	//tHighWins.Push( SomeClass( 5 ) );
	//tHighWins.Push( SomeClass( 44 ) );
	//tHighWins.Push( SomeClass( 208 ) );
	//
	//cout << "Low: ";
	//while( !tLowWins.Empty() )
	//{
	//	cout << tLowWins.Top().mTestNumber << " ";
	//	tLowWins.Pop();
	//}
	//cout << endl;
	//cout << endl;
	//
	//cout << "High: ";
	//while( !tHighWins.Empty() )
	//{
	//	cout << tHighWins.Top().mTestNumber << " ";
	//	tHighWins.Pop();
	//}
	//cout << endl;

	tLowWins.Clear();
	tHighWins.Clear();
}