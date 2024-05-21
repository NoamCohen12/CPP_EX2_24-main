#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <climits>
#include <string>
#include <sstream>
#include "Graph.hpp"

using namespace std;

namespace ariel
{

    class Algorithms
    {
    public:
        // functions for isConnected function
        static bool BFS(vector<vector<int> > adj, int start);
        static bool isConnected(Graph &graph);

        // functions for shortestPath function
        static string find_path_bfs(Graph &graph, size_t start, size_t end);
        static string dijkstra(const Graph &graph, size_t source, size_t target);
        static string bellmanFord(const Graph &graph, size_t source, size_t target);
        static string shortestPath(Graph &graph, size_t start, size_t end);

        // functions for isContainsCycle function
        static bool dfs_D_cycle_detection(Graph &graph, size_t source, vector<bool> &visited, vector<bool> &in_recursion_stack, vector<size_t> &path);
        static bool is_cycle_D(Graph &graph);
        static bool dfs_UD_cycle_detection(size_t vertex, const vector<vector<int> > &graph, vector<bool> &visited, int parent, vector<size_t> &current_cycle);
        static bool is_cycle_UD(const vector<vector<int> > &graph);

        static void print_cycle(vector<size_t> &cycle);
        static bool isContainsCycle(Graph &graph);

        // functions for isBipartite function
        static string constructSetString(const vector<int> &Group);
        static string Two_Color_Division(Graph &graph);
        static string isBipartite(Graph &graph);

        // functions for negativeCycle function
        static bool bellmanFord_negative_cycle(Graph &graph);
        static void printNegativeCycle(const vector<size_t> &cycle);
        static void relax(size_t verex1, size_t verex2, vector<int> &dist, vector<size_t> &pred, Graph &graph);
        static bool negativeCycle(Graph &graph);
    };
}
#endif