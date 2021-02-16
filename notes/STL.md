# Standard Template Library (STL)
- An 'abstract data type' (ADT) is not data on its own
> - it is a shape to use for data
- STL is a set of ADT's that have been developed over the years

# Vector
`stl::vector<int> myVector;`
- a vector is an array that automatically resizes itself if you put too much data in it
- many of the commands for vector are shared across many ADTs
`begin , end , size , front , back , push_back , pop_back , clear`
- and some are more vector specific
`at, [], resize, reserve, insert`

# Template < >
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

# List 
`list<int> myList;`
- a long chain of data without *special powers*
- uses methods like 
`begin, end, front, back, size, push_back, pop_back, clear`
- has a few different ones
`push_front, pop_front`

# Algorithms
`#include <algorithms>` 

# Iterator Syntax
#### extremely common loop -v
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

# Functors
- sorting ints is easy
- sorting strings is easy
- how do you sort Students?
- what if you want to sort Students two different ways?
- STL abstraction is essential
	- ADT is the abstraction of a bunch of data
	- Iterator is the abstraction of one piece of data
	- Functor is the abstraction of an operation

### why functors?
- some ADTs require their data to be sortable
	- set and map store data smallest to largest
- ints work because they already understand `<, <=, >, >=`
	- a templated class is just copy-paste-find-replace
	- "if (x < y)" is somewhere in the sort code
- we could put a Student in a set if we gave it operator<
	- but then we could not choose to sort on gpa sometimes and age other times

### how functors work
```cpp
// inside the Student class
struct CompareByAge {
bool operator()
	(const Student &A,
	const Student &B)
	const
	{
	return A.height < B.height;
	}
};
```
- C++ lets us overload operators. including ()
- calling a function in C looks exactly the same as operator() in C++
	- backwards compatibility !
- still do not want to give () to Student, so we give it to one of our functors
- Student can have many of these
	- `Student::CompareByAge" because of scope

### using functors : priority queue
```cpp
priority_queue< Student, vector<Student>, Student::ByAge > myPQ;
// type, internal memory choice, name of functor
- a queue let the first data in be the first data out
- PQ changes that to "the most important data is the first one out"
- "Most important" is where the functor comes in
	- by default, "biggest" using < is the most important
		- ints also have access to built-in functors like "less" and "greater"

