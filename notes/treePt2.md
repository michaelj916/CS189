# Recap
- A tree gives us the ability to lookup data

# Recursive?
- a tree does not automatically mean recursion
- the guiding principle is if an algo needs to fork, it is recursive. Otherwise, use a loop

# Deleting Nodes
- draw a picture of a tree
- deleting a leaf is easy, but what if there are two children?
- Algorith is:
	- no children? delete it
	- one child? whoever was pointing at me now points at my child. (skip me.) now delete.
	- two children? don't delete the node! find the next highest piece of data, swap data, and delete *their* old node. (which might have a right child.)
		- "next highest" = take one step right and then as many lefts as you can
			- "The Smallest Data Bigger Than Us"
