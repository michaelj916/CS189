# Recap from last week: List.h



# Iterators

## Abstract Accessing
- The user does not know a vector is an array and a list of nodes
	- info hiding !
- so how can the user access the data if they don't know the format?
	- vector has an index, but not everyone does
- an "iterator" is the abstraction of "one piece of data"
	- in list, only we know it is the mData inside a ListNode

## Iterator Struct
```cpp
list<int> x;

.

.

for (auto iter = x.begin(); iter != x.end(); iter++)
	std::cout << (*iter)

// auto means find my type
```

## Using Iterators
- In that loop you saw begin() and end()
- the user does not know they want "head to tail" or "0 to size -1". they want to go from "begin to end"
- begin is the first good piece of data
- end is the first bad piece of data
	- for vector, that is "size"
	- for lsit, that is "tail"
- an iterator outside of begin and end gives "unspecified behavior" 

## Friend!
- So iterator is an inner class so other containers can have iterators
	- scope naming (code style?)
- It is public, so the user can use it 
- **BUT**, there are certain things that List needs to make it work that we don't want to expose to the user
	- Want private data that is hidden to the user but available **ONLY** to the `List`
- 

## const = `cannot change`
```cpp
// cannot change the rock pointed at
const Rock *x;

// cannot change the pointer
Rock const *x;

// method safe to call with const pointer
void Func() const

// safe reference that cannot change target
const Rock &x;

// unchangable value (immutable data)
const int SIZE = 69420;
```
- in general, const means cannot change
- its meaning depends on which of five-ish different places you put it
- the syntax is pretty clear, but on is connected to a fundamental ADT fact
	- when you put something in a cointainer, it gets copied
	- when you ask for something from a container, you get a reference to the actual thing in there
	- be careful you do not accidentally copy data out by sticking it in a temp variable
	- always using pointers instead of objects in containers keeps you from being confused
