# CPP_EX1_24 - operators


## Author
- [Noam Cohen]
- Email: Noam12345002@gmail.com

## operators
The project implements in C++
The center of the project in  is operators 
And it is a continuation project of an project on graphs and algorithms - CPP_EX1_24

In my task there are many types of operators that I was required to implement

*Addition Operators*

`operator+( Graph &a) `

`operator+=( Graph &g)`

`operator+(int number)`

`operator+() `

*Subtraction Operators*
`operator-( Graph &a)`

`operator-=( Graph &g)`

`operator-() `

*Multiplication Operators*

`operator*( Graph &a) `

`operator*(int number)`

`operator*=(int number)`

`operator*=(Graph &g)`

*Increment and Decrement Operators*

`operator++()`

`operator++(int)`

`operator--()`

`operator--(int)`

*Comparison Operators*

`operator==( Graph &a) `

`operator>( Graph &a) `

`operator<( Graph &a) `

`operator<=( Graph &a)`

`operator>=( Graph &a) `

*Stream Output Operator*

`friend ostream &operator<<(ostream &cout_new,Graph &graph)`

## Changes made from CPP_EX1_24 
`printGraph()`Change 
and were added a few help functions:
3 functions that help to `<operator` by the deftion:

Graphs G1 and G2 will be called equal if they are of the same order of magnitude and
contain the same edges (and the weights of the edges are the same)
or if G1 is not greater than G2 and neither is G2 greater than G1.

1.`if_g1_contain_g2` - This method checks if g1 contains the subgraph represented by g2
2.`who_more_edges` -   This method checks if to g1 there are  more edges from g2
3.`sameAdjacencyMatrix` - This method checks if to g1 and g2 have same matrix
function that help to Determine whether the graph is directed after the operations of the operators

4.`isSymmetric` - This method checks matrix og g1 isSymmetric

helpe to `<<operator`

5.`print_with_ostream` - This method print the matrix with ostrem





## Tests
My code was checked with many tests in `Test.cpp` with the `make test` command.
and `make valgrind` To check for memory leaks.