# Graphs
- A *Directed Acyclical Graph* (DAG) is a set of nodes (vertexes) connected by arrows (edges) that don't make a loop
	- And "Draw a picture" is again essential
- To represent in code you need to:
	- Support arbitrary number of nodes and arbitrary number of edges
	- Be able to find all edges leaving a vertex as fast as possible
		- Remember, to pick a structure you need to know what you are using it for
	- We don't want to waste too much space in overhead
## Two Solutions
- 2D Array ! (Vector of vector of bools)
	- mData[x][y] is true if there is an edge leading from x to y.
	- n^2 memory used, and 90% empty
	- O(1) lookup for "Are X and Y connected"
	- O(n) lookup for "All X point at"
- Map!
	- Vertex is Key, list of edges out is Value
	- Use unordered version since order doesn't matter
	- O(n) lookup for "Are X and Y connected"
	- O(1) lookup for "All X point at"
## Which is best?
- The answer is "it depends"...
	- a recurring theme in this class
- you need to analyze all the choices based on what your program and data need
- we are using choice B there. An unordered map of vertices to lists of edges
	- book example use the 2D array
- We can look at just the graph structure I provided now
# Has Loop
## Topological Search
- imagine vertexes are tasks, and arrows are dependencies
	- x -> Y means that X must be done before Y can be done. Y depends on X
		- Each graph algo answers a diff problem
- Is there a way I could finish every task, if I can only finish a task that is depending on nothing?
- If the graph has a loop, then no I can't
	- Topological Sort is the term for the order you can finish all tasks successfully
## Graph vs Brain
- If I draw a graph on the board, your eyes and brain could find a loop in moments
- Computer doesn't have spacial awareness, and graphs don't exist in 2D space anyway
	- Graphs don't have a shape either, just points and arrows
	- half of the brain power to solve this is done the moment i draw it on the board
##
