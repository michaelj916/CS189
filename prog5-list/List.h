#ifndef LIST_H
#define LIST_H
template <typename T>
class List
{
	struct ListNode
	{
		ListNode() {}
		T mData;
		ListNode* mPrev = nullptr;
		ListNode* mNext = nullptr;
	};

	ListNode* mHead = nullptr;
	ListNode* mTail = nullptr;
	mutable T mUndefined;
	int mSize = 0;

public:
	// default constructor, creates a doubly linked list
	List()
	{
		// Getting Head and Tail correct is not part of the Big 3.  It is hella mega required no matter what.
		mHead = new ListNode;
		mTail = new ListNode;
		mHead->mNext = mTail;
		mHead->mPrev = nullptr;
		mTail->mPrev = mHead;   // This RULES.  We always know we have 2 nodes, so we never have to check for null.
		mTail->mNext = nullptr;
	}

	// copy constructor
	List(const List& tOther)
	{
		*this = tOther;
	}

	// assignment operator
	List& operator = (const List& tRHS)
	{
		// check if L1 == L2 return L1
		if (this == &tRHS)
			return *this;
		
		Clear();

		for (int i = 0; i < tRHS.Size(); i++)
			this->mHead->mNext = tRHS.mHead->mNext;

		return *this;
	}

	~List()
	{
		//  maybe add bounds check and recursively call PopFront()
		Clear();
		delete mHead;
		delete mTail;
	}

	void PushFront(const T& tWhat)
	{
		Insert(Begin(), tWhat);
	}

	void PopFront()
	{
		Erase(Iterator(Begin()));
	}

	T& Front()
	{
		// front of the list is: mHead -> mNext
		return mHead->mNext->mData;
	}

	void PushBack(const T& tWhat)
	{
		Insert(End(), tWhat);
	}

	void PopBack()
	{
		Erase(Iterator(mTail->mPrev));
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
		while (Size() > 0)
			PopBack();
	}

	T& At(int tWhere) const
	{
		// if size <= parameter, return undefined
		if (tWhere >= Size())
			return mUndefined;

		// create node and iterate through list until you arrive At(tWhere);
		ListNode* walker = mHead->mNext;
		for (int i = 0; i < tWhere; i++)
			walker = walker->mNext;

		// return walker data
		return walker->mData;
	}

	class Iterator
	{
		friend List;

		ListNode* mCurrent = nullptr;
		T mUndefined;
	public:
		Iterator(ListNode* tStart)
		{
			mCurrent = tStart;
		}
		T& GetData()
		{
			return mCurrent->mData;
		}
		void Next()// As in "Move to the next item please"
		{
			mCurrent = mCurrent->mNext;
		}
		bool IsEqual(const Iterator& rhs)
		{
			return mCurrent == rhs.mCurrent;
		}
	};

	Iterator Insert(Iterator tWhere, const T& tWhat)
	{
		ListNode* new_node = new ListNode;
		new_node->mData = tWhat;
		
		new_node->mPrev = tWhere.mCurrent->mPrev;
		tWhere.mCurrent->mPrev->mNext = new_node;

		new_node->mNext = tWhere.mCurrent;
		tWhere.mCurrent->mPrev = new_node;

		mSize++;
		return Iterator(new_node);
	}

	Iterator Erase(Iterator tWhere)
	{
		if (tWhere.mCurrent == mTail || tWhere.mCurrent == mHead)
				return End();
		
		tWhere.mCurrent->mPrev->mNext = tWhere.mCurrent->mNext;
		tWhere.mCurrent->mNext->mPrev = tWhere.mCurrent->mPrev;

		ListNode* last = tWhere.mCurrent->mNext;
		delete tWhere.mCurrent;
		mSize--;
		return Iterator(last);
	}

	Iterator Begin()
	{
		// First good data
		return Iterator(mHead->mNext);
	}

	Iterator End()
	{
		// First Bad data
		return Iterator(mTail);
	}
};
#endif // LIST_H
