#pragma once
#include <string>
#include<list>
#include<unordered_map>
#include<iostream>
#include <queue>
#include <map>

// 		for( auto iter = container.begin(); iter != container.end(); ++iter ) {
// I can't stress enough how important that line is.  Every container has the ability to be looped through.  It's one of the reasons we have containers.
// But why do I access the item with (*iter) instead of iter-> ?  Because if your container is full of pointers you can't do iter->->, but you can do (*iter)->

class Graph
{
	struct Edge;
	struct Vertex
	{
		std::string _data;		// Could make the data a T, but it's an extra step we don't really need.  And by not being a template it is easier to debug.  (Hey, you should start every template homework as not template and change it after!
		std::list<Edge*> _ins;
		std::list<Edge*> _outs;

		int _hasLoopIns;// Used by HasLoopInternal

		int _bestDistance;
		std::string _fromWhere;
		bool _processed;

	};
	struct Edge
	{
		int _weight;
		Vertex* _from;
		Vertex* _to;
	};
	std::unordered_map<std::string, Vertex*> _mainData;// We want lookup speed, not range searching, so we didn't pick Map

	bool HasLoopInternal()
	{
		// The style of solution where you modify the components themselves.  You can clean up after or just init each time.
		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter )
		{
			(*mapIter).second->_hasLoopIns = (*mapIter).second->_ins.size();
		}

		bool found = false;
		do
		{
			for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter )
			{
				found = false;
				Vertex* current = (*mapIter).second;
				if( current->_hasLoopIns == 0 )
				{
					for( auto outIter : current->_outs )
					{
						(*outIter)._to->_hasLoopIns--;
					}
					current->_hasLoopIns = -1;
					found = true;
					break;
				}
			}
		} while( found );

		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter )
		{
			if( (*mapIter).second->_hasLoopIns != -1 )
				return true;
		}

		return false;
	}

	bool HasLoopExternal()
	{
		// The kind of solution where you use an external score pad to keep track of the algo's progress.
		std::map<std::string, int> hasLoopIns;

		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter )
		{
			hasLoopIns[(*mapIter).first] = (*mapIter).second->_ins.size();
		}

		bool found = false;
		do
		{
			for( auto iter = hasLoopIns.begin(); iter != hasLoopIns.end(); ++iter )
			{
				found = false;
				if( (*iter).second == 0 )
				{
					Vertex* current = _mainData[(*iter).first];
					for( auto outIter : current->_outs )
					{
						hasLoopIns[(*outIter)._to->_data] = hasLoopIns[(*outIter)._to->_data] - 1;
					}
					hasLoopIns[current->_data] = -1;
					found = true;
					break;
				}
			}
		} while( found );

		for( auto iter = hasLoopIns.begin(); iter != hasLoopIns.end(); ++iter )
		{
			if( (*iter).second != -1 )
				return true;
		}

		return false;
	}

	bool HasLoopCopy()
	{
		// The type of solution where you make a whole copy of the graph so you can mangle it and throw it away.
		Graph copyGraph = *this;

		std::queue<Vertex*> myQueue;
		for( std::unordered_map<std::string, Vertex*>::iterator mapIter = copyGraph._mainData.begin(); mapIter != copyGraph._mainData.end(); ++mapIter )
		{
			if( mapIter->second->_ins.size() == 0 )
			{
				myQueue.push( mapIter->second );
			}
		}

		while( myQueue.size() != 0 )
		{
			Vertex* topVertex = myQueue.front();
			for( std::list<Edge*>::iterator edgeIter = topVertex->_outs.begin(); edgeIter != topVertex->_outs.end(); ++edgeIter )
			{
				if( (*edgeIter)->_to->_ins.size() == 1 )
				{
					myQueue.push( (*edgeIter)->_to );
				}
			}
			myQueue.pop();
			copyGraph.Remove( topVertex->_data );
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
		if( _mainData.find( nodeName ) != _mainData.end() )// Reject dupes
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
	void Connect( std::string from, std::string to )
	{// "Overloading" like this prevents copypaste, and the BestDistance method needs weights
		Connect( from, to, 1 );
	}
	void Connect( std::string from, std::string to, int weight )
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
	void Dump()
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
		std::cout << std::endl; // why three?
	}

	bool HasLoop()
	{
		return HasLoopInternal() && HasLoopExternal() && HasLoopCopy();
	}

	int BestDistance( std::string from, std::string to )
	{
		return BestDistance( from, to, nullptr );// Overloading again in case you don't need the path.
	}
	int BestDistance( std::string from, std::string to, std::list<std::string>* path )
	{
		std::map<std::string, int> currentDistance;
		std::map<std::string, std::string> previousNode;
		std::map<std::string, bool> processed;
		for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter )
		{
			currentDistance[(*mapIter).first] = INT_MAX;
			previousNode[(*mapIter).first] = "";
			processed[(*mapIter).first] = false;
		}
		currentDistance[from] = 0;

		bool found = false;
		do
		{
			int bestDistance = INT_MAX;
			std::string bestVertex = "";
			found = false;
			for( auto mapIter = _mainData.begin(); mapIter != _mainData.end(); ++mapIter )
			{
				if( !processed[(*mapIter).first] && currentDistance[(*mapIter).first] < bestDistance )
				{
					found = true;
					bestDistance = currentDistance[(*mapIter).first];
					bestVertex = (*mapIter).first;
				}
			}
			if( found )
			{
				Vertex* current = _mainData[bestVertex];
				processed[current->_data] = true;
				for( auto outIter : current->_outs )
				{
					if( (*outIter)._weight == 0 )
						continue;
					int potential = currentDistance[current->_data] + (*outIter)._weight;
					if( potential < currentDistance[(*outIter)._to->_data] )
					{
						currentDistance[(*outIter)._to->_data] = potential;
						(*outIter)._to->_fromWhere = current->_data;
						previousNode[(*outIter)._to->_data] = bestVertex;
					}
				}
			} 
		} while( found );

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
		return currentDistance[to];
	}

	int MaxFlow( std::string from, std::string to )
	{
		Graph working( *this );  // create a copy of the graph -1.) fixed syntax w0rking 

		// Find a path and reverse flow equal to the smallest link.  Keep a running total of what gets reversed.  (Or look at from's ins total)
		bool found = false;
		int flow = 0;
		do
		{
			// if DJ finds a path
			found = working.BestDistance( from, to ) != INT_MAX; // -2.) changed == to !=
			if( found ) 
			{
				int smallest = INT_MAX;  // -3.) set smallest to infinity (to compare weight < smallest)
				std::string tracer = to;
				std::list<Edge*> path;
				while( tracer != from )  
				{
					for( auto edge : working._mainData[tracer]->_ins ) // -4.) for every edge coming in to the tracer vertex 
					{
						if( edge->_from->_data == working._mainData[tracer]->_fromWhere ) // if the vertices data where that edge is from is equal to where I come from
						{
							if( edge->_weight < smallest )  // -5.) if weight is less than smallest
								smallest = edge->_weight;					// update smallest
							path.push_front( edge );						// keep a running total of what gets reversed
							tracer = edge->_from->_data;					// update tracer to follow path
							break;
						}
					}
				}
				for( auto edge : path ) 
				{
					working.Connect( edge->_to->_data, edge->_from->_data );    // create backlinks
					edge->_weight -= smallest;									// subtract smallest from each edge weight
				}
				flow += smallest;  
			}
		} while( found ); // if DJ fails, just sum weights and return flow

		return flow;
	}

	int FindMinimalCover( Graph* tAnswer )  
	{
	    tAnswer->Clear();					
		for( auto one : _mainData )			 // loop through main data
		{
			tAnswer->Add( one.first );		 // populate the graph
			one.second->_processed = false;  // -6.) mark each vertex as unprocessed  -- 'was _fromWhere'
		}
		_mainData.begin()->second->_processed = true;  // start with any vertex and mark it processed

		bool found = false;
		int totalWeight = 0;
		do
		{
			found = false;
			int lowest = INT_MAX;		
			Edge* lowestEdge = nullptr;
			for( auto one : _mainData )  // loop through main data (one.first = string, one.second = Vertex*)
			{
				if (!one.second->_processed)  // if a node is unprocessed
					continue;
				for( auto edge : one.second->_outs )  // loop through its "out" edges -- added ->_outs
				{
					if( !edge->_to->_processed && edge->_weight < lowest ) // if the edge I point to is unprocessed and its weight is less than the lowest
					{
					    found = true;						
					    lowest = edge->_weight;			// update lowest
					    lowestEdge = edge;				// update lowest edge
					}
				}
			}
			if( found )
			{
				tAnswer->Connect( lowestEdge->_from->_data, lowestEdge->_to->_data, lowest ); // create connection on tAnswer
				totalWeight += lowestEdge->_weight; // increment total
				lowestEdge->_to->_processed = true;		// mark both nodes as processed in the connection
				lowestEdge->_from->_processed = true;
			}

		} while( found );

		return totalWeight; // return total
	}
};

