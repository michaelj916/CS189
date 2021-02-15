# Program 2: Polymorphism
## Instructions: 
#### This program will be as simple as I can make it since you'll have entire classes devoted to it in University.

> 1. Make Square and Circle classes.
> 2. Make a base class for both called Shape
> 3. Two methods: SetSize and GetArea
> 4. (Size of an edge for square and the radius for circle)
> 5. Put those two methods where you think they should go.  Avoid duplication and make sure Shape is polymorphic

#### To test these classes, do the following

> 1. Make a vector of Shape pointers
> 2. (If you haven't ever seen vectors, it's "std::vector<Shape*> shapes;")
> 3. Dynamically create some circles and squares and put them in the vector
> 4. (That's the push_back command.)
> 5. Loop through vector calling GetArea on each Shape
> 6. (The actual size of anything doesn't matter.  Don't waste your time making a menu and using input though.)
> 7. Make sure you have no memory leaks
