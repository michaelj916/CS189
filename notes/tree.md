# Binary Search Trees
## Recap
- A vector was an array that could grow
	- O(1) Add
	- O(n) Insert
	- O(1) Access
	- O(n) Find
- A list was a chain of nodes ( pointers )
	- O(1) Add
	- O(1) Insert
	- O(n) Access
	- O(n) Find

## Binary Search Tree
![Binary Tree](https://external-content.duckduckgo.com/iu/?u=http%3A%2F%2Fwww.btechsmartclass.com%2Fdata_structures%2Fds_images%2FBST%2520Construction.png&f=1&nofb=1)
- A BST is a structure where every piece of data has up to two children
	- Draw this as an upside down tree with a single root (at the top)
- Everything lower is somewhere on the left, and everything greater is on the right, **no duplicates**
- We get O(log n) for anything involving lookups because each left-right decision skips half the tree
	- `double` or `half` is a sure sign of log 
	- "the time taken does not increase until the input size doubles"

## Binary Search Trees in STL
- BST is not an STL container on its own, it's the technology
	- LIke Vector was based on arrays
- A Set is the simplest ADT that *uses* a BST, so we'll push that off for a day and concentrate on just the basic workings of a tree

## Binary Search Tree Code
```cpp
struct TreeNode {
     T mData;
     TreeNode *mLeft;
     TreeNode *mRight;
};
```
- There are many different ways to implement a tree
	- info hiding! you choose your own way
- We are going to have a Node like List, and two pointers to other Nodes
	- We'll call ours right and left instead of next and prev though
	- Everything smaller is on my left, everything larger is on my right
- Next week we'll make sure a tree can't get really lopsided by giving it the ability to change itself

## Important Tree `Methods`
- `Insert`
	- Put this data at the right position
- `Erase`
	- Remove this data from the tree
- `Contains`
	- Is this data in the tree?
		- Real STL has "Find", but Find requires something from next week so we'll have just True/False
- `Big 3!`
	- Next week we will go over the new features of C++, they have 7. 
