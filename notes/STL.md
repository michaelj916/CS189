# Standard Template Library (STL)
- An 'abstract data type' (ADT) is not data on its own
> - it is a shape to use for data
- STL is a set of ADT's that have been developed over the years

## Vector
`stl::vector<int> myVector;`
- a vector is an array that automatically resizes itself if you put too much data in it
- many of the commands for vector are shared across many ADTs
`begin , end , size , front , back , push_back , pop_back , clear`
- and some are more vector specific
`at, [], resize, reserve, insert`

## Template < >
- a vector is 'abstract' because it does not mean anything
- an ADT is commonly read with the phrase "of what" so it has data
```cpp
// i.e. a vector of ints
stl::vector<int> vector;
```
- a templated class is written in a single h file
- since ADT is abstract, it does not exist so it does not compile
- when the compiler sees you declaring a "vector of ints", it copies the vector file into a new file
	- then it does a find replace using what you have in `< >`

## List 
`list<int> myList;`
- a long chain of data without *special powers*
- uses methods like 
`begin, end, front, back, size, push_back, pop_back, clear`
- has a few different ones
`push_front, pop_front`


## Algorithms
`#include <algorithms>` 

## Iterator Syntax
# extremely common loop -v
```cpp
for ( auto iter = myList.begin(); iter != myList.end(); iter++ )
{
	std::cout << (*iter);
	// Operator asterisk is as if it were iter.GetData()
}

for ( auto one : myList ) {}
// for each thing in the list 
```
- this is the STL version of a for loop'
`for( int i = 0; i < count; i++ ) {}`
- "auto" means "please figure out the type for me"
	- it looks at the return type of what's on the right and assumes that's what you want
- "*iter" is meant to look like a dereference operator, but remember that iter is not a pointer
	- it is actually an operator overload
