#ifndef VECTOR_H
#define VECTOR_H

template<typename T> 
class Vector
{
	// the data of the vector
	T* mData;

	// the size of the vector
	int mSize;

	// For testing purposes, initialize this to 15.  Whenever you allocate new memory, double it.
	int mCapacity = 15;

	// Lots of STL functions say that doing something naughty gets "undefined behavior".  It could throw, crash, make you eggs, or return nonsense.
	// Return this undefined one if anybody ever tries to go out of bounds. 
	// I've also seen this done with a static.  I'll do that in List later
	T mUndefined;
public:
	// initialize variables
	Vector() // O(1)
	{
		mSize = 0;
		mData = nullptr;
		Reserve(15);
	}

	// Big 3
	~Vector()
	{
		// Free all memory
		delete[] mData;
	}

	// copy constructor
	Vector(const Vector<T>& tOther) : Vector() // O(n)
	{
		for (int i = 0; i < mSize; i++)
			mData[i] = tOther.mData[i];

		mSize = tOther.mSize;
		mCapacity = tOther.mCapacity;
	}

	// There is a sneaky way to combine assignment and copy by having one call the other.  They are 90% the same.
	Vector& operator = (const Vector<T>& tRHS) // O(n)
	{
		// create new pointer
		int* pointer = new int[tRHS.mSize];

		// copy elements
		for (int i = 0; i < mSize; i++)
			pointer[i] = tRHS.mData[i];

		// delete old array
		delete[] mData;

		// add data, size to new vector
		this->mData = pointer;
		this->mSize = tRHS.mSize;

		// return dereferenced pointer
		return *this; // This line is weird so I'm just giving it to ya.  It has to be the last line.  It's just the definition of an =
	}

	void PushBack(const T& tItem) // O(1)
	{
		if (mSize >= mCapacity)
			Reserve(mCapacity * 2);

		mData[mSize] = tItem;
		mSize++;
	}

	void PopBack() // O(1)
	{
		// decrease size and call destructor on mData[mSize]
		if (mSize > 0)
			mSize--;
			mData[mSize].~T();
	}

	T& At(int tWhere) // O(1)
	{
		return mData[tWhere];
	}

	void Clear() // O(1)
	{
		// loop through mData and call the destructor for each elem
		for (int i = 0; i < mSize; i++)
			mData[i].~T();
		
		// set the size to 0
		mSize = 0;
	}

	int Size() // O(1)
	{
		return mSize;
	}

	void Reserve(int tCount) // O(n)
	{
		// allocate a new array
		T* tBlock = new T[tCount];

		// copy and move old elements
		if (tCount < mSize)
			mSize = tCount;

		for (int i = 0; i < mSize; i++)
			tBlock[i] = mData[i];

		// delete old array
		delete[] mData;
		mData = tBlock;
		mCapacity = tCount;
	}

	int Capacity() // O(1)
	{
		return mCapacity;
	}
};
#endif // VECTOR_H
