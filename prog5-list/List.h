#ifndef LIST_H
#define LIST_H
template <typename T>
class List
{
	struct ListNode
	{
		ListNode()
		{
		}
		T mData;
		ListNode* mPrev;
		ListNode* mNext;
	};

	ListNode* mHead;
	ListNode* mTail;
	mutable T mUndefined;
	int mSize = 0;

public:
	// default constructor, creates a doubly linked list
	List()
	{
		// Getting Head and Tail correct is not part of the Big 3.  It is hella mega required no matter what.
		//mHead = nullptr;
		//mTail = nullptr;// bleh.  Full of crash.
		mHead = new ListNode;
		mTail = new ListNode;
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;
		mTail->mPrev = mHead;   // This RULES.  We always know we have 2 nodes, so we never have to check for null.
		mTail->mNext = nullptr;
	}

	// copy constructor
	List( const List& tOther )
	{
		//*this = tOther;
		
	}

	// assignment operator
	List& operator = ( const List& tRHS )
	{
	}

	~List()
	{
		//  maybe add bounds check and recursively call PopFront()

		delete mHead;
		delete mTail;
		mSize = 0;
	}

	void PushFront( const T& tWhat )
	{
		// front of the list is accessed thorugh: mTail->mPrev
		// add tWhat to front of list
		mTail->mPrev->mData = tWhat;
		mSize++;
	}

	void PopFront()
	{
		// mHead->mNext = nullptr;
		// remove first item in list
		// mHead->mNext->mData = NULL;
		mSize--;
	}

	T& Front()
	{
		// front of the list is: mHead -> mNext
		return mHead->mNext->mData;
	}

	void PushBack( const T& tWhat )
	{
		// back of list is accessed through: mHead->mNext
		// add tWhat to back of list
		mHead->mNext->mData = tWhat;
		mSize++;
	}

	void PopBack()
	{
		// mTail->mPrev = nullptr
		// remove last item in list 
		// mTail->mPrev->mData = NULL;
		mSize--;
	}

	T& Back()
	{	
		// back of the list is: mTail -> mPrev -> mData
		return mTail->mPrev->mData;
	}

	int Size() const
	{
		return mSize;
	}

	void Clear()
	{
		// loop through size, clear each data, decrease size
		for (int i = 0; i < mSize; i++)
		{
			mHead->mNext->mData = NULL;
			mSize--
		}
		mSize = 0;
	}

	T& At( int tWhere ) const
	{
		
		// return the value of the list At ( tWhere )
		// iterate through nodes, return tWhere value of list
		
		
		
		return tWhere;

	}

	///////////////////////////////////////////////////////////////////
	// Iterators
	
	class Iterator
	{
		friend List;

		ListNode* mCurrent;
		T mUndefined;

	public:
		Iterator( ListNode* tStart )
		{
		}

		T& GetData()
		{
			return mUndefined;
		}

		void Next()// As in "Move to the next item please"
		{
		}

		bool IsEqual( const Iterator& rhs )
		{
			return false;
		}
	};

	Iterator Insert( Iterator tWhere, const T& tWhat )
	{
	}

	Iterator Erase( Iterator tWhere )
	{
	}

	Iterator Begin()
	{
		// First good data
		return Iterator( nullptr );
	}

	Iterator End()
	{
		// First Bad data
		return Iterator( nullptr );
	}
	
};
#endif // LIST_H
