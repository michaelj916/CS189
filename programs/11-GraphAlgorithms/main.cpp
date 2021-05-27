// 189 Graphs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Graph.h"

using namespace std; // NEVER OUTSIDE SCHOOL

int main()
{
	Graph myGraph;
	myGraph.Add( "A" );
	myGraph.Add( "B" );
	myGraph.Add( "C" );
	myGraph.Add( "D" );
	myGraph.Add( "E" );
	myGraph.Add( "F" );
	myGraph.Add( "G" );

	myGraph.Connect( "A", "B", 4 );   // connections with weights 
	myGraph.Connect( "A", "C", 1 );	  // connections with weights 
	myGraph.Connect( "B", "D", 3 );	  // connections with weights 
	myGraph.Connect( "C", "F", 7 );	  // connections with weights 
	myGraph.Connect( "C", "G", 10 );  // connections with weights 
	myGraph.Connect( "D", "E", 1 );	  // connections with weights 
	myGraph.Connect( "E", "F", 2 );	  // connections with weights 
	myGraph.Connect( "F", "G", 1 );	  // connections with weights 

	myGraph.Dump();

	std::list<std::string> path;

	cout << "Path A to G is 9: " << myGraph.BestDistance( "A", "G", &path ) << endl;
	for( auto step : path )
		cout << step << " ";
	cout << endl;

	cout << "Path A to F is 8: " << myGraph.BestDistance( "A", "F", &path ) << endl;
	for( auto step : path )
		cout << step << " ";
	cout << endl;

	cout << "Path B to C is Fail: " << myGraph.BestDistance( "B", "C", &path ) << endl;
	for( auto step : path )
		cout << step << " ";
	cout << endl;

	cout << "\nThere is " << (myGraph.HasLoop() ? "a bug." : "not a loop.") << endl;

	myGraph.Disconnect( "F", "G" );
	cout << "Path A to G is now 11: " << myGraph.BestDistance( "A", "G", &path ) << endl;
	for( auto step : path )
		cout << step << " ";
	cout << endl; 

	cout << "\nThere is " << (myGraph.HasLoop()?"a bug.":"not a loop.") << endl;

	myGraph.Connect( "G", "A", 5 );

	cout << "\nThere is now " << (myGraph.HasLoop()?"a loop.":"a bug.") << endl;
	
	cout << "Disconnected F -> G, Connected G -> A: \n" << endl;

	myGraph.Dump();
	
	cout << "-------------------------------------\nProg11 Output: \n" << endl;

	myGraph.Disconnect( "G", "A" );

	cout << "Max Flow A to G is 1: " << myGraph.MaxFlow( "A", "G" ) << endl;
	myGraph.Connect( "B", "E", 20 );
	myGraph.Connect( "E", "G", 5 );
	cout << "\nMax Flow A to G is now 5: " << myGraph.MaxFlow( "A", "G" ) << endl;
	
	cout << "|disconnected G->A|\t|connected B->E (20)|\t|connected E->G (5)|" << endl;
	
	myGraph.Dump();
	
	Graph answerGraph;
	int value = myGraph.FindMinimalCover( &answerGraph );
	cout << "Minimal Cover dump with value 16: " << value << endl;
	answerGraph.Dump();

	myGraph.Connect( "A", "F", 2 );
	int newValue = myGraph.FindMinimalCover( &answerGraph );
	cout << "Minimal Cover dump with new value 14: " << newValue << endl;
	answerGraph.Dump();
}

