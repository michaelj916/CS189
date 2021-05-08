#pragma once
//#include <list>
#include <vector>
#include <iostream> // DEBUGGING
template< typename T, typename C>
class PriorityQueue // Omg this was fun to write.
{
    //std::list<T> mData;// A list sorted by C.  Front will be the next to be picked.
	std::vector<T> mHeap;    // a heap is a decorator around a vector
	C mCompare;

public:
	bool Empty()
	{
		return Size() == 0;
	}
	int Size()
	{
		// return mData.size();
		return mHeap.size();
	}
	T& Top()
	{
		return mHeap.front(); // Arbitrarily deciding that you are added in back and the "best" according to Mr C goes front
		// return mData.front();
	}
	void Pop()
	{
	
		
		//mData.pop_front();
	
	}
	void Clear()
	{
		mHeap.clear();
		//mData.clear();
	}
	void Push(T tWhat) 
	{
		if (Empty())
			mHeap.push_back(0);   // 0 index will always be 0

		mHeap.push_back(tWhat);

		std::cout << tWhat.mTestNumber << "\t<-TESTNUMBER" << std::endl;

		for (auto iter = mHeap.begin(); iter != mHeap.end(); ++iter)
		{
			if (mCompare((*iter), tWhat))
			{

				mHeap.insert(iter, tWhat);
			}
			//std::cout << (*iter).mTestNumber << std::endl;
		}
		
		// This for loop here is the source of the O(n).  A heap is O(log n)
		//auto iter = mData.begin();
		//for(  ; iter != mData.end(); iter++ )// Looper's scope is inside the for even though it is outside the {}.  For's syntax sucks, but foreach can't change the container without doing a lot of work.
		//{
		//	if( !mCompare((*iter), tWhat) ) // "Start at left, better than you, better than you, oh I'm not better than you so I'll insert on your left
		//		break;
		//}
		//mData.insert( iter, tWhat );// Insert means "before this iter"
	}
};