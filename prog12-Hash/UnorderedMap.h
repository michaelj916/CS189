#pragma once
#include <vector>
#include <list>

// Key, Value, Hasher, Equalitor
template< typename K, typename V, typename H, typename E >
class UnorderedMap
{
	struct HashEntry
	{
		K mKey;
		V mValue;
	};

	struct HashNode
	{
		std::list<HashEntry> mEntries;
	}; 

	std::vector<HashNode> mData;

	int GetNextSize()
	{
		return mData.size() + 13;
	}

	int mBucketsInUse = 0;  // When this gets to half the vector size, we need to rehash.
	int mDebugData = 0;     // Not part of our algorithm

public:
	UnorderedMap()
	{
		// A vector comes empty, so we need to force it to embiggen to allow us to access spot 90 immediately.
		mBucketsInUse = 0;
		mData.resize(17); // Fills the vector with default-constructed HashNodes.  NOT Reserve.
	}

	void Clear()
	{
		//We want to end up just like we were when we were constructed.
		for( auto tIter = mData.begin(); tIter != mData.end(); ++tIter ) // Foreach is darkside.  It copies.
			(*tIter).mEntries.clear();
		mBucketsInUse = 0;
		mDebugData = 0;
	}

	void SetWithKey(K tKey, const V &tValue) // Adding to an unordered-map in stl adds a copy, and returns a reference
	{
		E tEqualitor;               // Equalitor functor
		H tHashor;					// Hashor functor
		int tHash = tHashor(tKey) % mData.size();  // hash the key and mod the hash table size

		if( mData[tHash].mEntries.size() == 0 )
			mBucketsInUse++;

		HashEntry tNew;
		tNew.mKey = tKey;
		tNew.mValue = tValue;

		for (auto iter = mData[tHash].mEntries.begin(); iter != mData[tHash].mEntries.end(); ++iter) // loop through all hash nodes for our tables current hash
		{
			if (tEqualitor(tNew.mKey, (*iter).mKey))  // if two keys are equal
			{
				mData[tHash].mEntries.erase(iter); // erase one, break out 
				break;
			}
		}

		mData[tHash].mEntries.push_back(tNew);

		if( mBucketsInUse > (mData.size() / 2) )
			Rehash();   // This just changed the size so do it last

		mDebugData++; // for debug dump
	}

	V& GetWithKey(K kTkey)
	{
		H tHashor;			// Hashor functor
		E tEqualitor;       // Equalitor functor

		int tHash = tHashor(kTkey) % mData.size(); // hash the key

		for (auto iter = mData[tHash].mEntries.begin(); iter != mData[tHash].mEntries.end(); ++iter)  // loop through all hash nodes for our tables current hash
		{
			if (tEqualitor(kTkey, (*iter).mKey)) // if there is a match
			{
				return (*iter).mValue;  // return the value
				break;
			}
		}
	}

	std::string DebugDump()
	{
		// I'm leaving this pile because I got mad string doesn't have useful methods.  This is C.
		char buff[100];
		snprintf(buff, 100, "\nThere are %d out of %d buckets in use holding %d items.\n", mBucketsInUse, mData.size(), mDebugData);
		std::string tOutput(buff);
		return tOutput;
	}

private:
	void Rehash()
	{
		// The real unordered_map probably resizes on data count, not used bucket count.  But we are testing spread here so we want bucket count.
		std::list<HashEntry> tAllEntries;

		// Gather all of the entries out of the nodes.  (remember with chaining there can be more than one in each node)
		for( int i = 0; i < mData.size(); i++ )
		{
			for( auto tIter = mData[i].mEntries.begin(); tIter != mData[i].mEntries.end(); ++tIter )
				tAllEntries.push_back(*tIter);
		}

		Clear();						// take all the data out since we have gathered all the entries
		mData.resize(GetNextSize());    // make the table bigger

		// Throw all the old entries back in to the hash.
		for( auto tIter = tAllEntries.begin(); tIter != tAllEntries.end(); ++tIter )
		{
			SetWithKey((*tIter).mKey, (*tIter).mValue);
		}
	}
};