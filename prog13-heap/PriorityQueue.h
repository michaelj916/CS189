#pragma once
#include <vector>
template< typename T, typename C>
class PriorityQueue // Omg this was fun to write, says the professor.  -- omg this was difficult and challenging, says the student.
{
	std::vector<T> mHeap;    // a heap is a decorator around a vector
	C mCompare;

public:
	bool Empty()
	{
		return Size() == 0;
	}
	int Size()
	{
		return mHeap.size();
	}
	T& Top()
	{
		return mHeap.front();
	}
	void Pop()
	{
		int tRoot = 1;

		mHeap[tRoot] = mHeap[Size() - 1];  // take the last item and put it in the roots spot
		mHeap.pop_back();

		int idx = Size() - 1;

		while (tRoot != idx) // loop from root until end of heap
		{
			idx /= 2;  // update for parent
			
			int tLeft = tRoot * 2;
			int tRight = (tRoot * 2) + 1;

			if (mCompare(mHeap[tRoot], mHeap[tLeft]) && mCompare(mHeap[tRoot], mHeap[tRight]))  // if both children are greater
			{
				if (mCompare(mHeap[tRoot], mHeap[tLeft]))  // compare left and swap, update root index
				{
					T temp = mHeap[tRoot];
					mHeap[tRoot] = mHeap[tLeft];
					mHeap[tLeft] = temp;

					tRoot += 1;
				}
				else if (mCompare(mHeap[tRoot], mHeap[tRight]))  // compare right and swap, update root index
				{
					T temp = mHeap[tRoot];
					mHeap[tRoot] = mHeap[tRight];
					mHeap[tRight] = temp;

					tRoot += 2;
				}
				else
				{
					break;
				}
			}

			if (mCompare(mHeap[tRoot], mHeap[tRoot / 2]))  // if we are better than our parent
			{
				// swap with it
				T temp = mHeap[tRoot];
				mHeap[tRoot] = mHeap[tRoot / 2];
				mHeap[tRoot / 2] = temp;

				tRoot /= 2;
			}
			else
			{
				break;
			}
		}
	}

	void Clear()
	{
		mHeap.clear();
	}
	void Push(T tWhat)
	{
		if (Empty())
			mHeap.push_back(0);   // 0 index will always be 0

		mHeap.push_back(tWhat);

		int idx = Size() - 1;  // current index tWhat is at

		while (idx != 1) // loop until root
		{
			idx /= 2;    // update current by its parent (i/2 = parent)

			if (mCompare(tWhat, mHeap[idx])) // if we are better than our parent
			{
				// swap with it
				T temp = mHeap[idx];
				mHeap[idx] = tWhat;
				mHeap[idx * 2] = temp;

			}
			else   // stop if they are better than us
				break;
		}
	}
};