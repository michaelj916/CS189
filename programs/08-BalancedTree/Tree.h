#pragma once
#include <list>
#include <iostream> // For debugging

template <typename T>
class Tree
{
	struct TreeNode
	{
		enum BalanceType
		{
			AVL_OK,
			AVL_LEFT_LEFT,
			AVL_LEFT_RIGHT,
			AVL_RIGHT_RIGHT,
			AVL_RIGHT_LEFT
		};
		T mData;
		TreeNode* mLeft;
		TreeNode* mRight;
		TreeNode* mParent;
		int mHeight;

		TreeNode()
		{
			mLeft = nullptr;
			mRight = nullptr;
			mParent = nullptr;
			mHeight = 0;
		}
		TreeNode( T tData ) : TreeNode()
		{
			mData = tData;
			mLeft = nullptr;
			mRight = nullptr;
			mParent = nullptr;
			mHeight = 0;
		}
		BalanceType GetBalanceType()
		{
			int tLeft = mLeft?mLeft->mHeight:-1; // if left node exists, return its height, else return -1
			int tRight = mRight?mRight->mHeight:-1; // if a right node exists, return its height, else return -1

			if( tRight - tLeft >= 2 )
			{
				//Right...
				int tRightLeft = mRight->mLeft?mRight->mLeft->mHeight:-1;
				int tRightRight = mRight->mRight?mRight->mRight->mHeight:-1;

				if( tRightLeft > tRightRight )
					return TreeNode::AVL_RIGHT_LEFT;
				else
					return TreeNode::AVL_RIGHT_RIGHT;
			}
			else if( tLeft - tRight >= 2 )
			{
				int tLeftLeft = mLeft->mLeft?mLeft->mLeft->mHeight:-1;
				int tLeftRight = mLeft->mRight?mLeft->mRight->mHeight:-1;

				if( tLeftLeft > tLeftRight )
					return TreeNode::AVL_LEFT_LEFT;
				else
					return TreeNode::AVL_LEFT_RIGHT;
			}

			return TreeNode::AVL_OK;
		}
	};
	TreeNode* mHead;
	bool mDebugOn = false; // Used to add couts to Dump.	

	// The balance code works.  You are just changing what node you are passing in.  Every node, or one of a list of nodes
	// I'd recomend changing the name of this to BalanceNode
	bool BalanceNode( TreeNode* tNode )
	{
		if( tNode == nullptr )
			return false;

		// Part one of the homework wants you to only check the nodes
		// on the way up instead of all of them

		// Part two of the homework updates this so that the heights 
		// of the nodes you process are updated as you go (and in the rotate code)

		while (tNode->mParent) // loop through all the parents above me
		{
			typename TreeNode::BalanceType tCheck = tNode->GetBalanceType();
			if( tCheck != TreeNode::AVL_OK )
			{
				bool tHeadCheck = mHead == tNode;

				if (tCheck == TreeNode::AVL_LEFT_LEFT)
				{
					tNode = RotateLeftUp(tNode);
					tNode->mHeight++;
					tNode->mLeft->mHeight--;
				}
				else if( tCheck == TreeNode::AVL_LEFT_RIGHT )
				{
					tNode->mLeft = RotateRightUp( tNode->mLeft );
					tNode = RotateLeftUp( tNode );
				}
				else if (tCheck == TreeNode::AVL_RIGHT_RIGHT)
				{
					tNode = RotateRightUp(tNode);
					tNode->mHeight++;
					tNode->mRight->mHeight--;
				}
				else if( tCheck == TreeNode::AVL_RIGHT_LEFT )
				{
					tNode->mRight = RotateLeftUp( tNode->mRight );
					tNode = RotateRightUp( tNode );
				}
				if( tHeadCheck )
					mHead = tNode;

				return true;
			}

			return false;
		}

		return false;
	}

	// Part two of the balance homework needs you to update the heights of the nodes when you do these rotations.
	TreeNode* RotateRightUp( TreeNode* tNode )
	{
		// Using variable names from book pg 257 to make easier to read:
		// Addition of Parent pointers that we do to be like a Set is 
		// not in those pictures though.  Just keep that in mind.
		TreeNode* P = tNode;
		TreeNode* Q = P->mRight;

		P->mRight = Q->mLeft;
		if (Q->mLeft)
		{
			Q->mLeft->mParent = P;
			Q->mHeight--;        
			P->mHeight++;
		}
		Q->mLeft = P;

		Q->mParent = P->mParent;
		P->mParent = Q;
		
		P->mHeight--;
		Q->mHeight++;

		if( Q->mParent )
		{
			if( Q->mParent->mRight == P )
				Q->mParent->mRight = Q;
			else
				Q->mParent->mLeft = Q;
		}


		return Q;
	}

	TreeNode* RotateLeftUp( TreeNode* tNode )
	{
		TreeNode* P = tNode;
		TreeNode* Q = P->mLeft;

		P->mLeft = Q->mRight;
		if (Q->mRight)
		{
			Q->mRight->mParent = P;
			Q->mHeight--;
			P->mHeight++;
		}
		Q->mRight = P;

		Q->mParent = P->mParent;
		P->mParent = Q;

		P->mHeight--;
		Q->mHeight++;

		if( Q->mParent )
		{
			if( Q->mParent->mRight == P )
				Q->mParent->mRight = Q;
			else
				Q->mParent->mLeft = Q;
		}

		return Q;
	}

	void CopyTree( TreeNode* tNode )
	{
		if( tNode != nullptr )
		{
			Add( tNode->mData );
			CopyTree( tNode->mLeft );
			CopyTree( tNode->mRight );
		}

	}

	void DeleteTree( TreeNode* tNode )
	{
		if( tNode != nullptr )
		{
			DeleteTree( tNode->mLeft );
			DeleteTree( tNode->mRight );
			delete tNode;
		}
	}

	void DumpTree( std::list<T>* tLeftToRight, TreeNode* tNode ) const
	{
		if( tNode != nullptr )
		{
			if( tNode->mLeft )
			{
				if( mDebugOn )
					std::cout << "L ";
				DumpTree( tLeftToRight, tNode->mLeft );
			}

			// To help debug avl balancing, I'm going to make this thing output.  This is generally a naughty thing to do outside of main because it makes a dependency between your code and the console.
			if( mDebugOn )
				std::cout << tNode->mData << "(" << tNode->mHeight << ")" << " ";

			if( tLeftToRight )
				tLeftToRight->push_back( tNode->mData ); // Without the extra couts, this is the real part of recursive dump

			if( tNode->mRight )
			{
				if( mDebugOn )
					std::cout << "R ";
				DumpTree( tLeftToRight, tNode->mRight );
			}
			if( mDebugOn )
				std::cout << "^ ";
		}
	}

	// Add, contain, and remove all want to know the same thing.  Where they should activate.
	// Add wants to know what the new node should attach to, contains just wants to see if it is there, and remove wants to know who to mark dead.
	// So all I did was copy the duplicated code here, remove the add/contain specific code, and return the node.
	TreeNode* PrivateFind( T tWhat )
	{
		if( mHead == nullptr )
			return nullptr;

		TreeNode* tWalker = mHead;
		while( true )
		{
			if( tWalker->mData == tWhat )
				return tWalker;
			else if( tWalker->mData > tWhat )
			{
				if( tWalker->mLeft == nullptr )
					return tWalker;
				else
					tWalker = tWalker->mLeft;
			}
			else
			{
				if( tWalker->mRight == nullptr )
					return tWalker;
				else
					tWalker = tWalker->mRight;
			}
		}
	}

public:
	Tree()
	{
		mHead = nullptr;
		mDebugOn = true;
	}
	Tree( const Tree& tOther ) : Tree()
	{
		std::list<T> tAllNodes;
		tOther.Dump( &tAllNodes );// I'm using dump instead of copy to intentionally force balances to happen in a reliable order.  Just for grading balances.

		for( auto iter = tAllNodes.begin(); iter != tAllNodes.end(); ++iter )
			Add( *iter );
	}
	Tree& operator= ( const Tree& tRHS )
	{
		if( this == &tRHS )
			return *this;

		DeleteTree( mHead );
		mHead = nullptr;

		std::list<T> tAllNodes;
		tRHS.Dump( &tAllNodes );

		for( auto iter = tAllNodes.begin(); iter != tAllNodes.end(); ++iter )
			Add( *iter );

		return *this;
	}
	~Tree()
	{
		DeleteTree( mHead );
	}

	void SetDebug( bool tOn )
	{
		mDebugOn = tOn;
	}

	void Add( T tWhat )
	{
		if( mHead == nullptr )
		{
			mHead = new TreeNode( tWhat );
			mHead->mHeight++;
			return;
		}

		TreeNode* tFound = PrivateFind( tWhat );
		if( tFound->mData == tWhat )
			return;// no dupes
		else if( tFound->mData > tWhat )
		{
			tFound->mLeft = new TreeNode( tWhat );
			tFound->mLeft->mParent = tFound;
		}
		else
		{
			tFound->mRight = new TreeNode( tWhat );
			tFound->mRight->mParent = tFound;
		}
	}

	bool Contains( T tWhat )
	{
		TreeNode* tFound = PrivateFind( tWhat );
		if( tFound != nullptr && tFound->mData == tWhat )
			return true;

		return false;
	}

	void Remove( T tWhat )
	{
		TreeNode* tFound = PrivateFind( tWhat );
		if( tFound == nullptr || tFound->mData != tWhat )
			return;
		if( mHead == nullptr )
			return;

		bool tHeadRemoval = false;
		if( mHead == tFound )
			tHeadRemoval = true;

		if( tFound->mRight == nullptr && tFound->mLeft == nullptr ) // 0 child
		{
			if( tHeadRemoval )// no parent
			{
				delete mHead;
				mHead = nullptr;
			}
			else
			{
				if( tFound->mParent->mLeft == tFound )
					tFound->mParent->mLeft = nullptr;
				else
					tFound->mParent->mRight = nullptr;
				delete tFound;
			}
		}
		else if( tFound->mLeft != nullptr && tFound->mRight == nullptr )// left child
		{
			if( tHeadRemoval )
			{
				TreeNode* tOldHead = mHead;
				delete tOldHead;
				mHead = tOldHead->mLeft;
			}
			else
			{
				if( tFound->mParent->mLeft == tFound )
					tFound->mParent->mLeft = tFound->mLeft;
				else
					tFound->mParent->mRight = tFound->mLeft;
				tFound->mLeft->mParent = tFound->mParent;
				delete tFound;
			}
		}
		else if( tFound->mLeft == nullptr && tFound->mRight != nullptr )// right child
		{
			if( tHeadRemoval )
			{
				TreeNode* tOldHead = mHead;
				delete tOldHead;
				mHead = tOldHead->mRight;
			}
			else
			{
				if( tFound->mParent->mLeft == tFound )
					tFound->mParent->mLeft = tFound->mRight;
				else
					tFound->mParent->mRight = tFound->mRight;
				tFound->mRight->mParent = tFound->mParent;
				delete tFound;
			}
		}
		else // two child (No special head case since the head node doesn't change in a two child)
		{
			TreeNode* tWalker = tFound;
			tWalker = tWalker->mRight;
			bool tWentLeft = false;
			while( tWalker->mLeft != nullptr )
			{
				tWentLeft = true;
				tWalker = tWalker->mLeft;
			}

			T tTransplant = tWalker->mData;
			tFound->mData = tTransplant;

			// Walker is the one we want to kill.  Found is the one with two kids that is stealing walker's data
			if( tWentLeft )
				tWalker->mParent->mLeft = tWalker->mRight;// Might be null, that's okay
			else
				tWalker->mParent->mRight = tWalker->mRight;

			if( tWalker->mRight )// If there is something to connect back up
				tWalker->mRight->mParent = tWalker->mParent;
			delete tWalker;
		}
	}

	void Dump( std::list<T>* tLeftToRight ) const
	{
		std::cout << "Tree: " << std::endl;// Naughty to have output in utility class, but need to debug
		DumpTree( tLeftToRight, mHead );
		std::cout << "\n" << std::endl;
	}
};