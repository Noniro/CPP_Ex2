# System Programming 2 , assignment 2.

### Author
 Name:    Yuval Vogdan.
 Email:   yuvalv126@gmail.com
 git url: https://github.com/Noniro 

# Operator overloading on Graphs
This repository is the continues implementations of the Graph from Exercise 1, with the addition of operator overloading for the Graph
 class in C++.


### Overloaded Operators

 *Addition (+): Adds two graphs by adding the 
 corresponding entries in their adjacency matrices.

*Subtraction (-): Subtracts two graphs by subtracting the corresponding entries in their adjacency matrices.

*Addition and Assignment (+=): Adds a graph to the current graph and updates the current graph in-place.

*Subtraction and Assignment (-=): Subtracts a graph from the current graph and updates the current graph in-place.

*Comparison Operators (==, !=, <, <=, >, >=): Compares two graphs based on their adjacency matrices.

*Increment (++, ++(int)): Increments the graph by adding 1 to each edge weight.

*Decrement (--, --(int)): Decrements the graph by subtracting 1 from each edge weight.

*Multiplication (*): Multiplies two graphs using matrix multiplication. Note that multiplication is only defined for compatible graphs (where both are valid graph represented by an nXn matrix and the graphs diagnol is skipped in the prosses to keep the result valid).

*Multiplication by Scalar (*): Multiplies each edge weight in the graph by a scalar value.

*Output Stream Insertion (<<): Inserts the graph representation (adjacency matrix) into an output stream.

### Usage Examples:
some examples demonstrating the usage of the overloaded operators for the Graph class:

````cpp
// Create some example adjacency matrices
  vector<vector<int>> matrix1 = {
    {0, 1, 0},
    {1, 0, 1},
    {0, 1, 0}};
  vector<vector<int>> matrix2 = {
    {0, 0, 1},
    {0, 0, 1},
    {1, 1, 0}};

  // Create graphs from the adjacency matrices
  Graph g1, g2;
  g1.loadGraph(matrix1);
  g2.loadGraph(matrix2);

  // Addition (+)
  Graph g3 = g1 + g2;
  cout << "g1 + g2:" << endl << g3 << endl;

  // Subtraction (-)
  Graph g4 = g1 - g2;
  cout << "g1 - g2:" << endl << g4 << endl;

  // Addition and Assignment (+=)
  g1 += g2;
  cout << "g1 after g1 += g2:" << endl << g1 << endl;

  // Subtraction and Assignment (-=)
  g2 -= g1;
  cout << "g2 after g2 -= g1:" << endl << g2 << endl;

  // Comparison Operators (==, !=, <, <=, >, >=)
  bool areEqual = g1 == g2;
  cout << "g1 == g2: " << areEqual << endl;

  // Increment (++, ++(int)) (prefix\postfix)
  Graph g5 = g1++;
  cout << "g1 after g1++:" << endl << g1 << endl;
  cout << "g5 (before increment):" << endl << g5 << endl;
  g5=++g1;
  cout <<"g1 incremented first, g5:"<< endl << g5 <<endl;

  // Decrement (--, --(int))
  Graph g6 = g2--;
  cout << "g2 after g2--:" << endl << g2 << endl;
  cout << "g6 (before decrement):" << endl << g6 << endl;
  g6=--g2;
  cout <<"g2 decremented first, g6:" << endl << g6 << endl;

  // Multiplication (*) - assuming compatible graphs
  Graph g7 = g1 * g2;
  cout << "g1 * g2:" << endl << g7 << endl;

  // Multiplication by Scalar (*)
  Graph g8 = g1 * 2;
  cout << "g1 * 2:" << endl << g8 << endl;

  // Output Stream Insertion (<<)
  cout << "g1:" << endl << g1 << endl;

```

## Testing
I added a Test.cpp folder with different testing for the operation.

# CPP_Ex2
