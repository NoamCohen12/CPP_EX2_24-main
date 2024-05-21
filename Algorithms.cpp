#include "Algorithms.hpp"
using namespace ariel;
/*
Implementation of the BFS algorithm that helps to know if we have visited all the vertices
*/
bool Algorithms::BFS(vector<vector<int> > matrix, int start_node)
{
    vector<bool> visited(matrix.size(), false);

    queue<int> queue;

    queue.push(start_node);
    visited[(size_t)start_node] = true;

    while (!queue.empty())
    {
        int current_node = queue.front();
        queue.pop();

        for (int i = 0; i < matrix[(size_t)current_node].size(); i++)
        {
            if (matrix[(size_t)current_node][(size_t)i] != 0 && !visited[(size_t)i])
            {
                queue.push(i);
                visited[(size_t)i] = true;
            }
        }
    }
    for (size_t i = 0; i < visited.size(); i++)
    {
        if (!visited[(size_t)i])
        {
            return false;
        }
    }
    return true;
}
/*
I referred to cases of "Strong connectivity"

Undirected case:
use BFS algoritem that return us if  all the vertices visted


Directed case:
1.Use BFS in the first time on original graph
2.We will reverse the directions of the edges e.g: Transpose graph
3.Use BFS in the two time on Transpose graph
check if both return true isConnected return true
*/
bool Algorithms::isConnected(Graph &graph)
{
    size_t number_vertices = graph.getSize();
    if (number_vertices == 0 || number_vertices == 1) // assuming
    {
        return true;
    }

    else if (!graph.isDirectedG())
    {
        return BFS(graph.get_matrix(), 0);
    }

    else
    {
        bool One_Direction = BFS(graph.get_matrix(), 0);
        Graph GTranspose = graph.getTranspose();
        bool Second_Direction = BFS(GTranspose.get_matrix(), 0);
        return One_Direction && Second_Direction;
    }
}

/*
    This function finds a path between two vertices using BFS and prints the path.
*/
string ariel::Algorithms::find_path_bfs(Graph &graph, size_t start, size_t end)
{
    vector<vector<int> > matrix = graph.get_matrix();
    unordered_map<size_t, int> parent_map;
    queue<size_t> Queue;
    Queue.push(start);
    parent_map[start] = -1; // -1 indicates no parent

    // Perform BFS to find the path
    while (!Queue.empty())
    {
        size_t current = (size_t)Queue.front();
        Queue.pop();

        if (current == end)
        {
            // Reconstruct the path
            vector<int> path;
            int node = (int)end;
            while (node != -1)
            {
                path.push_back(node);
                node = parent_map[(size_t)node];
            }
            // Construct the path string
            stringstream ans;
            for (int i = (int)path.size() - 1; i >= 0; --i)
            {
                ans << path[(size_t)i];
                if (i > 0)
                {
                    ans << "->";
                }
            }
            return ans.str();
        }

        // Iterate through neighbors of current node
        for (size_t neighbor = 0; neighbor < matrix[current].size(); ++neighbor)
        {
            if (matrix[current][neighbor] != 0 && parent_map.find(neighbor) == parent_map.end())
            {
                Queue.push(neighbor);
                parent_map[neighbor] = (int)current;
            }
        }
    }
    return "-1"; // No path found
}
/*
    This function implements Dijkstra's algorithm
    to find the shortest path between two vertices.
*/
string Algorithms::dijkstra(const Graph &graph, size_t source, size_t target)
{
    size_t number_vertices = graph.get_matrix().size();
    vector<int> dist(number_vertices, INT_MAX);
    vector<int> parent(number_vertices, -1);
    vector<bool> visited(number_vertices, false);
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Pqueue;

    dist[source] = 0;
    Pqueue.push({0, source});

    while (!Pqueue.empty())
    {
        size_t vertex = (size_t)Pqueue.top().second;
        Pqueue.pop();

        if (visited[vertex])
        {
            continue;
        }
        visited[vertex] = true;

        if (vertex == target)
        {
            break;
        }

        for (size_t k = 0; k < number_vertices; ++k)
        {
            if (graph.get_matrix()[vertex][k] != 0 && !visited[k] && dist[vertex] + graph.get_matrix()[vertex][k] < dist[k])
            {
                dist[k] = dist[vertex] + graph.get_matrix()[vertex][k];
                parent[k] = (int)vertex;
                Pqueue.push({dist[k], k});
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int current = (int)target;
    while (current != -1)
    {
        path.push_back(current);
        current = parent[(size_t)current];
    }

    if (parent[target] == -1)
    {
        return "-1"; // No path found
    }

    // Convert the path to string
    string shortest_path;
    for (size_t i = path.size() - 1; i >= 0; --i)
    {
        shortest_path += to_string(path[i]);
        if (i > 0)
        {
            shortest_path += "->";
        }
    }

    return shortest_path;
}
/*
    This function implements the Bellman-Ford algorithm
     to find the shortest path between two vertices,
    considering graphs with negative edge weights.
*/
string Algorithms::bellmanFord(const Graph &graph, size_t source, size_t target)
{
    size_t number_vertices = graph.get_matrix().size();
    vector<int> dist(number_vertices, INT_MAX);
    vector<int> parent(number_vertices, -1);

    dist[source] = 0;

    // Relax all edges |V| - 1 times
    for (size_t i = 0; i < number_vertices - 1; ++i)
    {
        for (size_t j = 0; j < number_vertices; ++j)
        {
            for (size_t k = 0; k < number_vertices; ++k)
            {
                if (graph.get_matrix()[j][k] != 0 && dist[j] != INT_MAX && dist[j] + graph.get_matrix()[j][k] < dist[k])
                {
                    dist[k] = dist[j] + graph.get_matrix()[j][k];
                    parent[k] = (int)j;
                }
            }
        }
    }

    // Check for negative cycles
    for (size_t j = 0; j < number_vertices; ++j)
    {
        for (size_t k = 0; k < number_vertices; ++k)
        {
            if (graph.get_matrix()[j][k] != 0 && dist[j] != INT_MAX && dist[j] + graph.get_matrix()[j][k] < dist[k])
            {
                // Negative cycle detected
                cout << "Graph contains negative weight cycle" << endl;
                return "-1";
            }
        }
    }

    // Reconstruct the shortest path
    vector<int> path;
    int current = (int)target;
    while (current != -1)
    {
        path.push_back(current);
        current = parent[(size_t)current];
    }

    if (parent[target] == -1)
    {
        return "-1"; // No path found
    }

    // Convert the path to string
    string shortest_path;
    for (size_t i = path.size() - 1; i >= 0; --i)
    {
        shortest_path += to_string(path[i]);
        if (i > 0)
        {
            shortest_path += "->";
        }
    }

    return shortest_path;
}
/*
    This function calculates the shortest path between two vertices in a graph.
    It handles three cases:
    1. If the graph is empty or either the start or end vertex is out of range, it throws an invalid_argument exception.
    2. If the graph contains a negative weight cycle, it returns "-1" to indicate that there is no shortest path.
    3. Depending on the type of graph, it uses different algorithms to find the shortest path:
        - For graphs without weighted edges, it uses BFS to find the shortest path.
        - For graphs with positive edge weights, it uses Dijkstra's algorithm.
        - For graphs with negative edge weights, it uses the Bellman-Ford algorithm.
*/

string Algorithms::shortestPath(Graph &graph, size_t start, size_t end)
{
    if (start >= graph.get_matrix().size() || start < 0 || end >= graph.get_matrix().size() || end < 0)
    {
        throw invalid_argument("Invalid source or destination vertex");
    }

    if (negativeCycle(graph))
    {
        return "-1"; // if there is negative cycle there is not shortest path
    }

    if (start == end)
    {
        return to_string(start);
    }
    if (graph.get_type_graph() == without_weights_edges)
    {

        return find_path_bfs(graph, start, end);
    }
    if (graph.get_type_graph() == positive_edges)
    {
        return dijkstra(graph, start, end);
    }
    if (graph.get_type_graph() == negative_edges)
    {
        return bellmanFord(graph, start, end);
    }

    return "-1";
}
/* This function performs a depth-first search (DFS) to detect cycles in a directed graph.
   It marks vertices as visited and tracks the current path to detect cycles.
   If a vertex is encountered that is already in the current path, a cycle is detected and the function returns true.
   Otherwise, it backtracks and removes vertices from the current path as it explores the graph.
   */

bool Algorithms::dfs_D_cycle_detection(Graph &graph, size_t source, vector<bool> &visited, vector<bool> &in_recursion_stack, vector<size_t> &path)
{
    visited[source] = true;
    in_recursion_stack[source] = true;
    path.push_back(source);

    for (size_t neighbor = 0; neighbor < graph.get_matrix()[source].size(); ++neighbor)
    {
        if (graph.get_matrix()[source][neighbor] != 0) // Check if there's an edge
        {
            if (!visited[neighbor])
            {
                if (dfs_D_cycle_detection(graph, neighbor, visited, in_recursion_stack, path))
                {
                    return true;
                }
            }
            else if (in_recursion_stack[neighbor])
            {
                return true; // Cycle detected
            }
        }
    }
    in_recursion_stack[source] = false; // Remove from recursion stack when backtracking
    path.pop_back();                    // Remove from the current path
    return false;
}
/*
    This function implements a DFS-based cycle detection algorithm for directed graphs.
*/
bool Algorithms::is_cycle_D(Graph &graph)
{
    size_t number_vertices = graph.getSize();
    vector<bool> visited(number_vertices, false);
    vector<bool> in_recursion_stack(number_vertices, false);
    vector<size_t> path;

    for (size_t i = 0; i < number_vertices; ++i)
    {
        if (!visited[i])
        {
            if (dfs_D_cycle_detection(graph, i, visited, in_recursion_stack, path))
            {
                print_cycle(path);
                return true;
            }
        }
    }
    // No cycle found
    cout << "-1" << endl;
    return false;
}
/*
This function detects cycles in an undirected graph using depth-first search (DFS).
It recursively explores each vertex's neighbors and tracks visited vertices to identify cycles.
If a neighbor is visited and not the parent of the current vertex, a cycle is detected.
The function returns true if a cycle is found, otherwise false.
*/
bool Algorithms::dfs_UD_cycle_detection(size_t vertex, const vector<vector<int> > &graph, vector<bool> &visited, int parent, vector<size_t> &current_cycle)
{
    visited[vertex] = true;
    for (size_t neighbor = 0; neighbor < graph.size(); ++neighbor)
    {
        if (graph[vertex][neighbor] != 0)
        { // Check if there is an edge between the vertices
            if (!visited[neighbor])
            {
                current_cycle.push_back(vertex); // Add current vertex to cycle
                if (dfs_UD_cycle_detection(neighbor, graph, visited, (int)vertex, current_cycle))
                {
                    return true;
                }
                current_cycle.pop_back(); // Remove current vertex if no cycle found in subtree
            }
            else if (neighbor != parent)
            {
                current_cycle.push_back(vertex);   // Add current vertex to cycle
                current_cycle.push_back(neighbor); // Add neighbor to cycle (the last in a cycle)
                return true;                       // Cycle detected
            }
        }
    }
    return false; // No cycle found
}
/*
    This function implements a DFS-based cycle detection algorithm for undirected graphs.
*/
bool Algorithms::is_cycle_UD(const vector<vector<int> > &graph)
{
    size_t number_vertices = graph.size();
    vector<bool> visited(number_vertices, false);

    for (size_t k = 0; k < number_vertices; ++k)
    {
        if (!visited[k])
        {
            vector<size_t> current_cycle;
            if (dfs_UD_cycle_detection(k, graph, visited, -1, current_cycle))
            {
                cout << "Cycle found: ";
                print_cycle(current_cycle);
                // cout << current_cycle[0]; // Print the first vertex again to close the cycle
                // cout << endl;
                return true; // Cycle detected
            }
        }
    }
    // cout << "No cycle found" << endl;

    return false; // No cycle found
}
void Algorithms::print_cycle(vector<size_t> &cycle)
{
    // cout << "Cycle found: ";
    for (size_t i = 0; i < cycle.size(); ++i)
    {
        cout << cycle[i];
        if (i < cycle.size() - 1)
        {
            cout << "->";
        }
    }
    cout << endl;
}

/*
 This function checks whether the given graph contains a cycle.
 If the graph is empty or has only one vertex, it cannot contain a cycle, so the function returns false.
 For directed graphs, it calls the is_cycle_D function to check for cycles.
 For undirected graphs, it calls the is_cycle_UD function to check for cycles.

I assume a cycle in this directed graph:
 v->u , u->v this cycle!
I assume one vertix is not cycle!

*/
bool Algorithms::isContainsCycle(Graph &graph)
{
    if (graph.getSize() == 0 || graph.getSize() == 1) // asume that one vertix is not cycle.
    {
        return false;
    }

    if (graph.isDirectedG())
    {
        return (is_cycle_D(graph));
    }
    return (is_cycle_UD(graph.get_matrix()));
}
/*
    This function checks if a graph is bipartite
     using a two-coloring algorithm based on BFS.
*/
string Algorithms::Two_Color_Division(Graph &graph)
{
    vector<int> Group_A;
    vector<int> Group_B;
    vector<int> color(graph.getSize(), -1);
    queue<int> Queue;

    // Start BFS traversal from each unvisited node
    for (size_t i = 0; i < graph.getSize(); i++)
    {
        if (color[i] == -1)
        { // Unvisited node
            cout << "Starting BFS from node " << i << endl;

            Queue.push(i);
            color[i] = 0; // Assign color 0 to start with

            while (!Queue.empty())
            {
                size_t curr = (size_t)Queue.front();
                Queue.pop();
                cout << "Visiting node " << curr << endl;
                if (color[curr] == 0)
                {
                    cout << "Assigning node " << curr << " to Group_A" << endl;
                    Group_A.push_back(curr);
                }
                else if (color[curr] != -1)
                {
                    cout << "Assigning node " << curr << " to Group_B" << endl;
                    Group_B.push_back(curr);
                }
                // Traverse neighbors of curr

                for (size_t k = 0; k < graph.get_matrix()[(size_t)curr].size(); k++)
                {
                    if (graph.get_matrix()[(size_t)curr][(size_t)k] != 0)
                    {
                        cout << "Checking edge between nodes " << curr << " and " << k << endl;
                        if (color[k] == -1)
                        { // Unvisited neighbor
                            cout << "Neighbor " << k << " is unvisited. Assigning color." << endl;
                            color[k] = 1 - color[curr]; // Assign opposite color

                            Queue.push(k);
                        }
                        else if (color[k] == color[curr])
                        {
                            // If neighbor has same color as curr, not bipartite
                            cout << "Neighbor " << k << " has the same color as node " << curr << ". Not bipartite." << endl;
                            return "-1";
                        }
                    }
                }
            }
        }
    }

    // Construct strings representing sets A and B
    string setA = constructSetString(Group_A);
    string setB = constructSetString(Group_B);

    return "The graph is bipartite: A=" + setA + ", B=" + setB;
}
string Algorithms::constructSetString(const vector<int> &Group)
{
    string setStr = "{";
    for (int node : Group)
    {
        setStr += to_string(node) + ", ";
    }
    if (!setStr.empty())
    {
        setStr.pop_back(); // Remove the last comma
        setStr.pop_back(); // Remove the space
    }
    setStr += "}";
    return setStr;
}
/*
    This function checks if a graph is bipartite using a two-coloring algorithm.
    Undirected case:
    checks if a graph is two-coloring.



    the algoritem work just on undirected graph so We will make the directed graph undirected

    Directed case:
    1.add opposite edges
    2.checks if a graph is two-coloring.


*/
string Algorithms::isBipartite(Graph &graph)
{
    if (graph.getSize() == 0)
    {
        return "-1"; // assume
    }

    if (!graph.isDirectedG())
    {
        return Two_Color_Division(graph);
    }
    Graph fix_graph = graph.add_opposite_edges();
    return Two_Color_Division(fix_graph);
}
/*
Bellman-Ford algorithm which also finds a negative cycle
*/
bool Algorithms::bellmanFord_negative_cycle(Graph &graph)
{
    vector<size_t> cycle;
    size_t number_vertices = graph.getSize();
    size_t source = 0;
    vector<bool> in_path(graph.getSize(), false); // Mark vertices in the current path
    vector<int> dist(number_vertices, INT_MAX);
    vector<size_t> pred(number_vertices, 0); // Store predecessors for tracing the cycle
    dist[source] = 0;

    // Relax all edges |V| - 1 times
    for (size_t i = 0; i < number_vertices - 1; ++i)
    {
        for (size_t j = 0; j < number_vertices; ++j)
        {
            for (size_t k = 0; k < number_vertices; ++k)
            {
                relax(j, k, dist, pred, graph);
            }
        }
    }
    // Check for negative cycles
    for (size_t j = 0; j < number_vertices; ++j)
    {
        for (size_t k = 0; k < number_vertices; ++k)
        {
            if (graph.get_matrix()[j][k] != 0 && dist[j] != INT_MAX && dist[j] + graph.get_matrix()[j][k] < dist[k])
            {
                // Negative cycle detected
                size_t curr = k;
                while (!in_path[curr])
                {
                    in_path[curr] = true; // Mark the current vertex
                    curr = pred[curr];
                }

                vector<size_t> cycle;
                size_t start = curr;
                do
                {
                    cycle.push_back(curr);
                    curr = pred[curr];
                } while (curr != start);

                printNegativeCycle(cycle);

                return true; // Negative cycle found
            }
        }
    }

    return false; // No negative cycle found
}
/*
    Utility function to print the negative weight
    cycle found by Bellman-Ford algorithm.
*/
void Algorithms::printNegativeCycle(const vector<size_t> &cycle)
{
    cout << "Graph contains negative weight cycle: ";
    for (size_t i = cycle.size() - 1; i > 0; --i)
    {
        cout << cycle[i] << "->";
    }
    cout << cycle[0];
    cout << "->" << cycle[cycle.size() - 1] << endl;
}
/*
    Utility function to relax edges during the Bellman-Ford algorithm.
*/
void Algorithms::relax(size_t verex1, size_t verex2, vector<int> &dist, vector<size_t> &pred, Graph &graph)
{
    if (graph.get_matrix()[verex1][verex2] != 0 && dist[verex1] != INT_MAX && dist[verex1] + graph.get_matrix()[verex1][verex2] < dist[verex2])
    {
        dist[verex2] = dist[verex1] + graph.get_matrix()[verex1][verex2];
        pred[verex2] = verex1; // Update predecessor
    }
}
/*
    This function checks if a graph contains a negative weight cycle
      using the Bellman-Ford algorithm.
*/
bool Algorithms::negativeCycle(Graph &graph)
{
    if (graph.getSize() == 0)
    {
        return false;
    }

    return bellmanFord_negative_cycle(graph);
}
