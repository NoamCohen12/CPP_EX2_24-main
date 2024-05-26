#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(false);
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "0, 2, 1\n2, 0, 3\n1, 3, 0\n");
}

TEST_CASE("Test graph multiplication *")
{
    ariel::Graph g1(false);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(true);
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    g4.loadGraph(expectedGraph);
    CHECK(g4.printGraph() == "0, 0, 2\n1, 0, 1\n1, 0, 0\n");
    ariel::Graph g6(true);
    vector<vector<int>> graph6 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 5},
        {0, 0, 5, 0}};
    g6.loadGraph(graph6);
    ariel::Graph g7(true);
    vector<vector<int>> graph7 = {
        {0, 7, 0, 0},
        {7, 0, 1, 0},
        {0, 1, 0, 5},
        {0, 0, 5, 0}};
    g7.loadGraph(graph7);
    ariel::Graph g8 = g6 * g7;
    CHECK(g8.printGraph() == "0, 0, 1, 0\n0, 0, 0, 5\n7, 0, 0, 0\n0, 5, 0, 0\n");
        ariel::Graph g11(true);

//    g11 =ariel::3 ariel::* g8 ;
    //CHECK(g11.printGraph() == "0, 0, 3, 0\n0, 0, 0, 15\n21, 0, 0, 0\n0, 15, 0, 0\n");
}
TEST_CASE("Test small graph multiplication")
{
    ariel::Graph g1(true); // small matrix 3x3
    vector<vector<int>> graph1 = {
        {0, 1, 9},
        {1, 0, 1},
        {9, 1, 0}};
    g1.loadGraph(graph1);
    ariel::Graph g2(true);
    vector<vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g2.loadGraph(graph2);
    ariel::Graph g3 = g1 * g2;

    CHECK(g3.printGraph() == "0, 0, 0\n0, 0, 0\n0, 0, 0\n");
}
TEST_CASE("Invalid operations")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(false); // Does not matter
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5(true);
    vector<vector<int>> zeroGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(zeroGraph);
    ariel::Graph g6 = -g5;
    ariel::Graph g3(false); // Does not matter
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0}};
    g3.loadGraph(graph3);

    CHECK_THROWS(g5 * g3);
    CHECK_THROWS(g1 * g3);

    // Addition of two graphs with different dimensions
    ariel::Graph g8(true);
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g8.loadGraph(graph4);
    CHECK_THROWS(g1 + g8);
}
TEST_CASE("Addition + unary operator")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2 = +g1;
    CHECK(g2.printGraph() == "0, 1, 0\n1, 0, 1\n0, 1, 0\n");
}

TEST_CASE("Addition + binary operator")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(false);
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g3.printGraph() == "0, 2, 1\n2, 0, 3\n1, 3, 0\n");

    ariel::Graph g4(true);
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5(false);
    vector<vector<int>> weightedGraph5 = {
        {0, 1, 1, 1, 1},
        {1, 0, 2, 1, 1},
        {1, 2, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g5.loadGraph(weightedGraph5);
    ariel::Graph g6 = g4 + g5;
    CHECK(g6.printGraph() == "0, 2, 1, 1, 2\n2, 0, 3, 1, 1\n1, 3, 0, 2, 1\n1, 1, 2, 0, 2\n2, 1, 1, 2, 0\n");
    ariel::Graph g7(true);
    vector<vector<int>> graph7 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g7.loadGraph(graph7);

    ariel::Graph g8(true);
    vector<vector<int>> zeroGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g8.loadGraph(zeroGraph);

    ariel::Graph g9 = g7 + g8;
    CHECK(g9.printGraph() == "0, 1, 0\n1, 0, 1\n0, 1, 0\n");

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

    ariel::Graph g12 = g10 + g11;

    CHECK(g12.printGraph() == "0, 2\n2, 0\n");
}
TEST_CASE("Addition - binary operator")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(false);
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 - g2;
    CHECK(g3.printGraph() == "0, 0, -1\n0, 0, -1\n-1, -1, 0\n");

    ariel::Graph g4(true);
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5(false);
    vector<vector<int>> weightedGraph5 = {
        {0, 1, 1, 1, 1},
        {1, 0, 2, 1, 1},
        {1, 2, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g5.loadGraph(weightedGraph5);
    ariel::Graph g6 = g4 - g5;
    CHECK(g6.printGraph() == "0, 0, -1, -1, 0\n0, 0, -1, -1, -1\n-1, -1, 0, 0, -1\n-1, -1, 0, 0, 0\n0, -1, -1, 0, 0\n");
}

TEST_CASE("rediction - unary operator")
{
    ariel::Graph g3(true);
    vector<vector<int>> graph3 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g3.loadGraph(graph3);
    ariel::Graph g4 = -g3;
    CHECK(g4.printGraph() == "0, -1, 0\n-1, 0, -1\n0, -1, 0\n");

    ariel::Graph g5(true);
    vector<vector<int>> graph5 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g5.loadGraph(graph5);
    ariel::Graph g6 = -g5;
    CHECK(g6.printGraph() == "0, 0, 0\n0, 0, 0\n0, 0, 0\n");
}

TEST_CASE("Addition g++ and ++g unary operator")
{
    // g++
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    vector<vector<int>> expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};

    ariel::Graph g2 = g1++;

    CHECK(g2.get_matrix() == graph);
    CHECK(g1.get_matrix() == expectedGraph);

    //++g
    ariel::Graph g3 = ++g1;
    vector<vector<int>> expectedGraph2 = {
        {0, 3, 0},
        {3, 0, 3},
        {0, 3, 0}};
    CHECK(g3.get_matrix() == expectedGraph2);
}
TEST_CASE("redection g-- and --g unary operator")
{
    // g--
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    vector<vector<int>> expectedGraph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    ariel::Graph g2 = g1--;

    CHECK(g2.get_matrix() == graph);
    CHECK(g1.get_matrix() == expectedGraph);
    g1--;
    CHECK(g1.get_matrix() == expectedGraph); // 0 not change to -1
    //--g
    ariel::Graph g4(true);
    vector<vector<int>> graph4 = {
        {0, 7, 5, 7},
        {7, 0, 7, 5},
        {5, 7, 0, 7},
        {7, 5, 7, 0}};
    g4.loadGraph(graph4);
    ariel::Graph g5(false);
    g5 = --g4;
    vector<vector<int>> graph5 = {
        {0, 6, 4, 6},
        {6, 0, 6, 4},
        {4, 6, 0, 6},
        {6, 4, 6, 0}};
    CHECK(g5.get_matrix() == graph5);
    CHECK(g4.get_matrix() == graph5);
}

TEST_CASE("Addition +=")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2(false);
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1 += g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    CHECK(g1.get_matrix() == expectedGraph);
    g1 += -g1;
    vector<vector<int>> expectedGraph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.get_matrix() == expectedGraph3);
}
TEST_CASE("redction -=")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);

    ariel::Graph g2(false);
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);

    g1 -= g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, -1},
        {0, 0, -1},
        {-1, -1, 0}};
    CHECK(g1.get_matrix() == expectedGraph);
    g1 += -g1;
    vector<vector<int>> expectedGraph3 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g1.get_matrix() == expectedGraph3);
}
TEST_CASE("multiplication *")
{
    ariel::Graph g1(false);
    vector<vector<int>> graph = {
        {0, 1, 1000},
        {1, 0, 1},
        {10000, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(true);
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph1);
    ariel::Graph g3 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 1000, 1},
        {0, 0, 0},
        {1, 10000, 0}};
    CHECK(g3.get_matrix() == expectedGraph);
    ariel::Graph g4(true);
}
TEST_CASE("multiplication * scalr")
{
    ariel::Graph g1(false);
    vector<vector<int>> graph = {
        {0, 1, 20},
        {1, 0, 1},
        {-5, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2(false);
    g2 = g1 * 2;

    vector<vector<int>> expectedGraph = {
        {0, 2, 40},
        {2, 0, 2},
        {-10, 2, 0}};
    CHECK(g2.get_matrix() == expectedGraph);

    g2 = g1 * 0;
    vector<vector<int>> expectedGraph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    CHECK(g2.get_matrix() == expectedGraph2);
}
TEST_CASE("multiplication *=  *= scalar ")
{
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
    vector<vector<int>> expectedGraph = {
        {0, 0},
        {0, 0}};
    CHECK(g10.get_matrix() == expectedGraph);
    ariel::Graph g1(false);
    vector<vector<int>> graph = {
        {0, 1, 20},
        {1, 0, 1},
        {-5, 1, 0}};
    g1.loadGraph(graph);
    g1 *= 2;
    vector<vector<int>> expectedGraph2 = {
        {0, 2, 40},
        {2, 0, 2},
        {-10, 2, 0}};
    CHECK(g1.get_matrix() == expectedGraph2);
}
TEST_CASE("Comparisons ==  > < >= <=")
{
    ariel::Graph g10(true);
    vector<vector<int>> graph10 = {
        {0, 1},
        {1, 0}};
    g10.loadGraph(graph10);

    ariel::Graph g11(true);
    vector<vector<int>> graph11 = {
        {0, 2},
        {1, 0}};
    g11.loadGraph(graph11);
    CHECK((g10 == g11) == true);
    CHECK((g10 < g11) == false);
    CHECK((g10 > g11) == false);
    CHECK((g10 >= g11) == true);
    CHECK((g10 <= g11) == true);

    ariel::Graph g5(true);
    vector<vector<int>> graph5 = {
        {0, 6, 4, 6},
        {6, 0, 6, 4},
        {4, 6, 0, 6},
        {6, 4, 6, 0}};
    g5.loadGraph(graph5);

    ariel::Graph g6(true);
    vector<vector<int>> graph6 = {
        {0, 6},
        {6, 0}};
    g6.loadGraph(graph6);
    CHECK((g5 > g6) == true);
    CHECK((g5 < g6) == false);
    CHECK((g5 >= g6) == true);
    CHECK((g5 == g6) == false);
    CHECK_FALSE((g5 <= g6) == true);
}
TEST_CASE("<<")
{
    ariel::Graph g1(true);
    vector<vector<int>> graph = {
            {0,   1,   1},
            {1,   0,   1},
            {1,   1,   0}};
    
    g1.loadGraph(graph);

    stringstream ss;
    ss << g1;
    string expected  = "[ 0 1 1 ]\n[ 1 0 1 ]\n[ 1 1 0 ]\n";
    CHECK(ss.str() == expected);
}
