#pragma once 
#include <string>
#include <list>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <map>

// for( auto iter = container.begin(); iter != container.end(); ++iter ) {}
// I can't stress enough how important that line is.  Every container has the ability to be looped through.  It's one of the reasons we have containers.
// --- 
// But why do I access the item with (*iter) instead of iter-> ? 
// Because if your container is full of pointers you can't do iter->->, but you can do (*iter)->

class Graph
{
	struct Edge;                     // edges are the arrows of a graph
	struct Vertex                    // vertices are the nodes
	{
		std::string _data;		// Could make the data a T, but it's an extra step we don't really need.  And by not being a template it is easier to debug.  (Hey, you should start every template homework as not template and change it after!)
		std::list<Edge*> _ins;		// each node has input arrow('s)
		std::list<Edge*> _outs;		// each node has output arrow('s)

		int _hasLoopIns = 0;  // initialized 

		int _bestDistance = 0;
		std::string _fromWhere;
		bool _processed = false;

	};
	struct Edge
	{
		int _weight;
		Vertex* _from;  // each arrow can come from a node
		Vertex* _to;    // each arrow can go to a node
	};

	std::unordered_map<std::string, Vertex*> _mainData; // We want lookup speed, not range searching, so we didn't pick Map

	bool HasLoopInternal() // was bool HasL0opInteral()
	{
		// The style of solution where you modify the components themselves.  You can clean up after or just init each time.

		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter ) // loop through main data structure
		{
			// set _hasLoopIns for each vertex to their amount of _ins
			(*mapIter).second->_hasLoopIns = (*mapIter).second->_ins.size(); 
		}

		bool found = false;
		do
		{
			for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter ) // loop through main data structure, unordered_map<string, Vertex*> _mainData;
			{
				found = false;
				Vertex* current = (*mapIter).second;
				if( current->_hasLoopIns == 0 )          // if there are no arrows pointing to me
				{
					for( auto outIter : current->_outs )	// for every output arrow 
					{
						(*outIter)._to->_hasLoopIns--;			// decrease vertex count
					}
					current->_hasLoopIns = -1;		
					found = true;
					break;
				}
			}
		} while( found );

		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter ) // loop through main data structure
		{
			if( (*mapIter).second->_hasLoopIns != -1 ) // return true if there are internal loops
				return true;
		}

		return false; // base case
	}

	bool HasLoopExternal()
	{
		// The kind of solution where you use an external score pad to keep track of the algo's progress.

		std::map<std::string, int> hasLoopIns; // table to tally each vertex "in" edge count -- added int type

		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter ) // loop through main data structure, unordered_map<string, Vertex*> _mainData;
		{
			hasLoopIns[(*mapIter).first] = (*mapIter).second->_ins.size();			   // create a map of all vertices and their "in" edges
		}

		bool found = false;
		do
		{
			for( auto iter = hasLoopIns.begin(); iter != hasLoopIns.end(); ++iter )	     // loop through internal data structure we just made
			{
				found = false;
				if( (*iter).second == 0 )			                // if there are no arrows pointing at my node
				{
					Vertex* current = _mainData[(*iter).first];	    // Vertex of mainData for hasLoopIns string
					for( auto outIter : current->_outs )			// loop through that vertices ouput edges
					{
						hasLoopIns[(*outIter)._to->_data] = hasLoopIns[(*outIter)._to->_data] - 1;  // decrease count
						//hasLoopIns[(*outIter)._to->_data]--;
					}
					hasLoopIns[current->_data] = -1;
					found = true;
					break;
				}
				//std::cout << "sanity" << std::endl;
			}
			//std::cout << "sanity" << std::endl;
		} while( found ); // changed logic

		//std::cout << "sanity" << std::endl;

		for( auto iter = hasLoopIns.begin(); iter != hasLoopIns.end(); ++iter ) // loop through internal data structure
		{
			if( (*iter).second != -1 ) // if a vertex has not been processed, there is a loop
				return true;
		}

		return false;
	}

	bool HasLoopCopy()
	{
		// The type of solution where you make a whole copy of the graph so you can mangle it and throw it away.

		Graph copyGraph = *this;     // create internal structure to copy the graph

		std::queue<Vertex*> myQueue; // create internal structure to hold nodes
		for( std::unordered_map<std::string, Vertex*>::iterator mapIter = copyGraph._mainData.begin(); mapIter != copyGraph._mainData.end(); ++mapIter ) // loop through the copy graph of mainData
		{
			if( mapIter->second->_ins.size() == 0 ) // if a vertex has no "in" edges (arrows pointing towards it)
			{
				myQueue.push( mapIter->second );		// push it to the queue
			}
		}

		while( myQueue.size() != 0 ) // if the queue has vertices 
		{
			Vertex* topVertex = myQueue.front();
			for( std::list<Edge*>::iterator edgeIter = topVertex->_outs.begin(); edgeIter != topVertex->_outs.end(); ++edgeIter ) // loop through the topVertex "out" edges (arrows poiting away from the top node) 
			{
				if( (*edgeIter)->_to->_ins.size() == 1 ) // if the vertex my edge points to only has 1 input arrow
				{
					myQueue.push((*edgeIter)->_to); // push the vertex I point at into myQueue
				}
			}
			myQueue.pop();
			copyGraph.Remove( topVertex->_data ); // destroy the node on our copied graph (whole point of this approach)
		}
		if( copyGraph._mainData.size() == 0 ) 
			return false;
		else
			return true;
	}

public:
	Graph()
	{
	}
	Graph( const Graph& other )
	{
		*this = other;
	}
	Graph& operator = ( const Graph& tRhs )
	{
		Clear();
		for( auto mapIter = tRhs._mainData.begin(); mapIter != tRhs._mainData.end(); ++mapIter )
		{
			Add( mapIter->first );
		}
		for( auto mapIter = tRhs._mainData.begin(); mapIter != tRhs._mainData.end(); ++mapIter )
		{
			for( auto inIter : mapIter->second->_ins )
			{
				Connect( inIter->_from->_data, inIter->_to->_data, inIter->_weight );
				// Connect( inIter->_to->_data, inIter->_from->_data, inIter->_weight ); this sneaky line had me debugging for hours
			}
		}
		return *this;
	}
	~Graph()
	{
		Clear();
	}
	void Clear()
	{
		while( _mainData.size() > 0 )
		{
			std::string one = _mainData.begin()->first;
			Remove( one );
		}
	}

	void Add( std::string nodeName )
	{
		if( _mainData.find( nodeName ) != _mainData.end() ) // fixed logic, this rejects duplicates
			return;
		Vertex* newVert = new Vertex();
		newVert->_data = nodeName;
		_mainData[nodeName] = newVert;
	}

	void Remove( std::string nodeName )
	{
		if( _mainData.find( nodeName ) == _mainData.end() )// Stop if we don't have it
			return;
		for( auto inIter : _mainData[nodeName]->_ins )
		{// Since the vertex is going, all edges in and out are going, so tell the vertices at the other end
			inIter->_from->_outs.remove( inIter );
			delete inIter;
		}
		for( auto outIter : _mainData[nodeName]->_outs )
		{
			outIter->_to->_ins.remove( outIter );
			delete outIter;
		}
		delete _mainData[nodeName];
		_mainData.erase( nodeName );
	}

	// overloaded Connect method
	void Connect( std::string from, std::string to )
	{
		Connect( from, to, 1 );
	}

	void Connect( std::string from, std::string to, int weight ) // siwtched parameters to match function above (connects node From 'from' To 'to')
	{
		if( _mainData.find( from ) == _mainData.end() || _mainData.find( to ) == _mainData.end() ) // Check they both exist
			return;

		Edge* newEdge = new Edge();			// One edge exists per arrow on the white board.  Each vertex has a pointer to it
		newEdge->_weight = weight;			
		newEdge->_from = _mainData[from];
		newEdge->_to = _mainData[to];

		_mainData[from]->_outs.push_back( newEdge );
		_mainData[to]->_ins.push_back( newEdge );
	}

	void Disconnect( std::string from, std::string to )
	{
		if( _mainData.find( from ) == _mainData.end() || _mainData.find( to ) == _mainData.end() )
			return;
		for( auto inIter : _mainData[to]->_ins )
		{// Disconnecting leaves the vertices in place, but deltes the edge after removing it
			if( inIter->_from == _mainData[from] )
			{
				inIter->_from->_outs.remove( inIter );
				_mainData[to]->_ins.remove( inIter );
				delete inIter;
				break;
			}
		}
	}

	void Dump() // prints structure
	{
		for( auto mapIter : _mainData )
		{
			std::cout << mapIter.first << ") Ins:";
			for( auto inIter : mapIter.second->_ins )
				std::cout << inIter->_from->_data << " ";
			std::cout << "\tOuts: ";
			for( auto outIter : mapIter.second->_outs )
				std::cout << outIter->_to->_data << " ";
			std::cout << std::endl;
		}
		std::cout << std::endl; 
		std::cout << std::endl; 
		std::cout << std::endl; 
	}

	bool HasLoop() // checks for loop by calling all private loop methods
	{
		return HasLoopInternal() && HasLoopCopy() && HasLoopExternal();
		//return HasLoopExternal();
		// return HasLoopCopy();
	}

	int BestDistance( std::string from, std::string to ) 
	{
		return BestDistance( from, to, nullptr );       // Overloading again in case you don't need the path.
	}

	int BestDistance( std::string from, std::string to, std::list<std::string>* path )
	{
		// all have the same keys, but different values for different uses
		std::map<std::string, int> currentDistance;       // "Best" row in notes
		std::map<std::string, std::string> previousNode;  // "From" row in notes
		std::map<std::string, bool> processed;            // "Done" row in notes

		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter ) // loop through main data structure
		{
			currentDistance[(*mapIter).first] = INT_MAX;  // set all vertices to "infinity"
			previousNode[(*mapIter).first] = "";          // we don't know from yet
			processed[(*mapIter).first] = false;          // we haven't processed yet
		}
		currentDistance[from] = 0;                        // set from vertex to 0, like in notes

		bool found = false;
		do
		{
			int bestDistance = INT_MAX;	
			std::string bestVertex = "";
			found = false; 					// reset found
			for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter ) // loop through main data structure, unordered_map<string, Vertex*> _mainData;
			{ 
				if( !processed[(*mapIter).first] && currentDistance[(*mapIter).first] < bestDistance ) // find minimum vertex
				{
					found = true;											// set found for next block to run
					bestDistance = currentDistance[(*mapIter).first];       
					bestVertex = (*mapIter).first;							// set bestVertex to mainData's first vertex for next block's current
				}
			}
			if( found )
			{
				Vertex* current = _mainData[bestVertex];	
				processed[current->_data] = true;			// process current vertex
				for( auto outIter : current->_outs )
				{
					if( (*outIter)._weight == 0 )
						continue;
					int potential = currentDistance[current->_data] + (*outIter)._weight; // account for edge weight
					if( potential < currentDistance[(*outIter)._to->_data] )				// if there is a faster route
					{
						currentDistance[(*outIter)._to->_data] = potential;						// update distance
						(*outIter)._to->_fromWhere = current->_data;							// update from
						previousNode[(*outIter)._to->_data] = bestVertex;						// update "from" row, take that route
					}
				}
			}
		} while( found );

		// write to path for output
		if( path )
		{
			path->clear();
			if( previousNode[to] != "" )
			{
				std::string walker = to;
				path->push_front( to );
				do
				{
					walker = previousNode[walker];
					path->push_front( walker );
				} while( walker != from );
			}
		}

		if (currentDistance[to] == INT_MAX) // if there is no path
			return 0;						//   just return
		else                                // else
			return currentDistance[to];     //   return the distance
	}

	// NEXT WEEK ---v
	int MaxFlow( std::string from, std::string to )
	{
		return 0;
	}

	int FindMinimalCover( Graph* tAnswer )
	{
		return 0;
	}

};

