#### We are going to dive deep into a few of the stl containers because it is cool.  But in real life the whole point of stl is to keep you from having to write them yourselves.  So the first data structure homework is about using stl.

## List, Vector, Stack, Queue, Set, Map, UnorderedMap, PriorityQueue

1. Make a Student class that has Name, GPA, and StudentDebt as properties
2. In main, make a List of ints.  Add some numbers to it
3. Use an iterator loop to print all those values on the screen
4. Make a Vector of Students.  Add some Student objects to it
5. Make a Stack of Student Pointers.  Push and pop some dynamically created Students to it.  Make sure you don't leak memory
  1. As in, have a for loop add in 10 dynamically created objects.  Then have another loop correctly delete the objects, not just remove the pointers from the stack.  SP21 - don't worry about using a loop to add anything.  It is important for the deleting step, but I don't want people getting stuck on making the test data.
6. Make a Set of ints.  Add some numbers to it
7. Make a Map of strings to ints.  Put some movie titles and the year they came out in it
8. Do #7 with an unordered map

### And then the hard ones that require both lessons this week

1. Make a priority queue that uses a Student's GPA for the sort criteria.  Add some Student objects and show that the next one that would be popped (the top one) is the highest GPA
2. Make a priority queue that uses a Student's Debt for the sort criteria.  Add some Student pointers for dynamically created Students and show the next one popped is the one with the least debt.

# (a cheatsheet of the STL and algorithms)[https://github.com/gibsjose/cpp-cheat-sheet/blob/master/Data%20Structures%20and%20Algorithms.md]
