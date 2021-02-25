# Big O Definition
- picture a graph for an algorithm with the y axis being time and the x axis being input size
	- to count n pencils, i touch n pencils
	- to count n + 1 pencils, I touch n + 1 pencils
	- this is a linear graph

- That is "Big O of n" or "O(n)"
	- "This algorithm finishes in no more than linear time"
	- "Omega (ω) of n" changes that to "no less than"
	- "Theta (θ) of n" changes that to "exactly"
	- The reason why O is the most used over Theta is **we don't actually care about the precise speed, just the worst case**
		- `testing for speed is benchmarking`
	- we also only **care about the shape, not the curve**
![Big O Graph](bigo.png)

# O(n^2)
- everyone in class has to shake everyone's hand
- one more person appears. how many more handshakes is that?
	- for pencils, one more pencil was one more actions
	- here the new person must shake n persons hands
	- "for each person, shake each person"
- technically "(n^2 - n) / 2" 
- we do not want the exact curve, just the shape
	- n^2 is the worst there, so it dominates at n = 10,000,000

# O(log n)
- the curve decelerates, just like how n-squared accelerated
- it takes me a minute to eat half of the cookies
	- 3: Nom, 1, Nom
	- 4: Nom, 2, Nom, 1, Nom
	- 5: Nom, 2, Nom
	- 6: Nom, 3, Nom
	- 7: Nom, 3, Nom
	- 8: Nom, 4, Nom

# Big O Guidelines
- if any part of an algoorithm is n^2, it is O(n^2)
- a loop is O(n)
	- do something to everything
- a loop in a loop is O(n^2)
	- for each thing, do something to everything
- recursion can be exponential O(2^n) if you are not careful
	- for each thing... run the program on each thing
- the cost of anything not related to n is irrelevant
	- branches, funciton calls, variables
