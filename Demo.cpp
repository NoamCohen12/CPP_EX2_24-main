/*
 * Demo program for Exercise 3.
 * Author: Benjamin Saldman.
 */

#include "Graph.hpp"
#include "Algorithms.hpp"
#include <iostream>
#include <stdexcept>
#include <vector>

using ariel::Algorithms;
using namespace std;

int main()
{
    ariel::Graph g1(false);
    // 3x3 matrix that represents a connected graph.
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
        
    g1.loadGraph(graph); // Load the graph to the object.
        ariel::Graph g2(false);
  
    g2 = -g1;
    g2 = g1--;
    cout << g2.printGraph() << endl;
     cout << g2 << endl; // Should print the matrix of the graph: [0, 3, 0], [3, 0, 3], [0, 3, 0]

 ariel::Graph g10(true);
    vector<vector<int>> graph10 = {
        {0, 1},
        {1, 0}};
    g10.loadGraph(graph10);

    ariel::Graph g11(true);
    vector<vector<int>> graph11 = {
        {0, 1},
        {1, 0}};
    g11.loadGraph(graph11);
    g10 *= g11;

    cout<<g10.printGraph()<<endl;//zero matrix


    // 3x3 matrix that represents a weighted connected graph.
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    ariel::Graph g19(true);
    g19.loadGraph(weightedGraph); // Load the graph to the object.

    ariel::Graph g3 = g1 + g19; // Add the two graphs together.
    cout<<g3;           // Should print the matrix of the graph: [0, 2, 1], [2, 0, 3], [1, 3, 0]

    g1 *= -2;        // Multiply the graph by -2.
    cout<<g1; // Should print the matrix of the graph: [0, -2, 0], [-2, 0, -2], [0, -2, 0]

  
   ariel::Graph g4 = g1 * g2; // Multiply the two graphs together.
    cout<<g4;           // Should print the multiplication of the matrices of g1 and g2: [0, 0, 2], [1, 0, 1], [1, 0, 0]

    // 5x5 matrix that represents a connected graph.
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    ariel::Graph g5(true);
    g5.loadGraph(graph2); // Load the graph to the object.
    try
    {
        ariel::Graph g6 = g5 * g1; // Multiply the two graphs together.
    }
    catch (const std::invalid_argument &e)
    {
        cout << e.what() << endl; // Should print "The number of columns in the first matrix must be equal to the number of rows in the second matrix."
    }
}
