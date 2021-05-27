// TreeSetup.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <list>
#include "Tree.h"

using namespace std;

int main()
{
	Tree<int> tTreeOne;
	tTreeOne.SetDebug( true );

	tTreeOne.Add( 50 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 30 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 80 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 90 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 100 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 60 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 20 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 10 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 15 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 55 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 110 );
	tTreeOne.Dump( nullptr );
	tTreeOne.Add( 120 );
	tTreeOne.Dump( nullptr );
	// I bet drawing that out on paper first would help.

	if( tTreeOne.Contains( 15 ) )
		cout << "Check 1\n" << endl;
	if( tTreeOne.Contains( 50 ) )
		cout << "Check 2\n" << endl;
	if( tTreeOne.Contains( 60 ) )
		cout << "Check 3\n" << endl;
	if( tTreeOne.Contains( 110 ) )
		cout << "Check 4\n" << endl;
	if( !tTreeOne.Contains( 99 ) )
		cout << "Check 5\n" << endl;

	Tree<int> tTreeTwo( tTreeOne );
	tTreeOne.Remove( 90 );
	if( tTreeTwo.Contains( 90 ) )
		cout << "Check 6\n" << endl;

	Tree<int> tTreeThree;
	tTreeThree.Add( 999 );
	tTreeThree = tTreeOne; // overwritten the 999, tree 3 is now tree 1
	tTreeOne.Remove( 20 );

	if( tTreeThree.Contains( 20 ) )
		cout << "Check 7\n" << endl;
	if( !tTreeThree.Contains( 999 ) )
		cout << "Check 8\n" << endl;
	//tTreeThree.Dump(nullptr);
	if( !tTreeOne.Contains( 20 ) )
		cout << "Check 9\n" << endl;

	tTreeOne.Add( 90 );
	if( tTreeOne.Contains( 90 ) )
		cout << "Check 10\n" << endl;

	//std::list<int> tOneFlattened;
	//tTreeOne.Dump( &tOneFlattened );
	//for( auto iter = tOneFlattened.begin(); iter != tOneFlattened.end(); ++iter )
	//	cout << (*iter) << " ";
	//cout << endl;
	tTreeOne.SetDebug( true );
	tTreeOne.Dump(nullptr);

	return 0;
}

