#include "Graph.hpp"

using namespace ariel;

Graph::Graph(bool isDirected1)
{
    this->num_vertices = 0;
    this->isDirected = isDirected1;
    this->type_graph = 0;
}

size_t Graph::getSize() const
{
    return this->num_vertices;
}

void Graph::loadGraph(vector<vector<int>> &graph)
{
    this->num_vertices = graph.size();
    this->matrix = graph;
    for (size_t i = 0; i < num_vertices; i++)
    {
        if (graph[i].size() != num_vertices)
        {
            cout << graph[i].size() << endl;
            cout << num_vertices << endl;

            throw invalid_argument("the size between graphs diffrent");
        }
    }

    for (size_t i = 0; i < matrix.size(); i++)
    {
        if (matrix[i][i] != 0)
        {
            throw invalid_argument("your matrix should have ZERO in diagonal");
        }
    }

    // Clear the existing matrix and resize to match the input graph size
    matrix.clear();
    this->num_vertices = graph.size();
    this->type_graph = graph_type(graph);
    matrix.resize(num_vertices, vector<int>(num_vertices, 0));
    for (size_t i = 0; i < graph.size(); i++)
    {
        for (size_t j = 0; j < graph.size(); j++)
        {
            matrix[i][j] = graph[i][j];
        }
    }
}

void Graph::printGraph() const
{
    int num_edges = 0;
    int vertices = this->num_vertices;
    for (size_t i = 0; i < vertices; i++)
    {
        // only count the upper triangle of the matrix
        for (size_t j = 0; j < vertices; j++)
        {
            if (this->matrix[i][j] != 0)
            {
                num_edges++;
            }
        }
    }
    if (this->isDirected)
    {
        cout << "The graph is directed. V(G) = " << vertices << ", E(G) = " << num_edges << endl;
    }
    else
    {
        cout << "The graph is undirected. V(G) = " << vertices << " E(G) = " << (num_edges / 2) << endl;
    }
}

vector<vector<int>> Graph::get_matrix() const
{
    return this->matrix;
}

bool Graph::isDirectedG() const
{
    return this->isDirected;
}

int Graph::get_type_graph() const
{
    return this->type_graph;
}

Graph Graph::getTranspose() const
{
    Graph gTranspose(true);
    size_t num_vertices = this->num_vertices;
    vector<vector<int>> transpose(num_vertices, vector<int>(num_vertices, 0));
    for (size_t i = 0; i < num_vertices; ++i)
    {
        for (size_t j = 0; j < num_vertices; ++j)
        {
            transpose[j][i] = this->matrix[i][j];
        }
    }
    gTranspose.loadGraph(transpose); // Assign the transposed matrix to GT
    return gTranspose;
}

Graph Graph::add_opposite_edges() const
{
    Graph fix_graph(true);
    size_t num_vertices = this->num_vertices;
    vector<vector<int>> new_matrix(num_vertices, vector<int>(num_vertices, 0));
    for (size_t i = 0; i < num_vertices; ++i)
    {
        for (size_t j = 0; j < num_vertices; ++j)
        {
            if (this->matrix[i][j] != 0 && this->matrix[j][i] == 0)
            {
                new_matrix[i][j] = this->matrix[i][j];
                new_matrix[j][i] = this->matrix[i][j];
            }
            if (this->matrix[i][j] == 0 && this->matrix[j][i] != 0)
            {
                new_matrix[j][i] = this->matrix[j][i];
                new_matrix[i][j] = this->matrix[j][i];
            }
            if (this->matrix[i][j] == 0 && this->matrix[j][i] == 0)
            {
                new_matrix[j][i] = 0;
                new_matrix[i][j] = 0;
            }
        }
    }
    fix_graph.loadGraph(new_matrix); // Assign the new_matrix to fix_graph

    return fix_graph;
}

int Graph::graph_type(vector<vector<int>> &graph)
{
    int type = without_weights_edges;
    for (size_t i = 0; i < matrix.size(); i++)
    {
        for (size_t j = 0; j < matrix[i].size(); j++)
        {
            if (matrix[i][j] < 0)
            {
                return negative_edges;
            }
            if (matrix[i][j] > 0)
            {
                type = positive_edges;
            }
        }
    }
    return type;
}

bool isSymmetric(const vector<vector<int>> &matrix)
{
    // Check if the matrix is square
    int n = matrix.size();
    for (const auto &row : matrix)
    {
        if (row.size() != n)
        {
            return false; // Not square, hence not symmetric
        }
    }

    // Check if the matrix is symmetric
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < i; ++j)
        {
            if (matrix[i][j] != matrix[j][i])
            {
                return false; // Not symmetric
            }
        }
    }

    return true; // Symmetric
}
// in function load_graph i just allow to load matrix NxN so i dont check this.
//  opretors
Graph Graph::operator+(const Graph &g) const // binary 1
{
    if (this->getSize() != g.getSize())
    {
        throw invalid_argument("the size between graphs diffrent");
    }

    vector<vector<int>> matrix_g = g.get_matrix();
    vector<vector<int>> new_matrix(g.getSize(), vector<int>(g.getSize(), 0));

    for (size_t i = 0; i < matrix_g.size(); i++)
    {
        for (size_t j = 0; j < matrix_g.size(); j++)
        {
            new_matrix[i][j] = this->get_matrix()[i][j] + matrix_g[i][j];
        }
    }

    // Assuming Graph constructor takes a matrix and loads it internally
    Graph new_g(isSymmetric(new_matrix));
    new_g.loadGraph(new_matrix);
    return new_g;
}

Graph Graph::operator+() const // onary 3
{
    Graph g(this->isDirected);
    for (size_t i = 0; i < this->getSize(); i++)
    {
        for (size_t j = 0; j < this->getSize(); j++)
        {
            g.get_matrix()[i][j] = this->get_matrix()[i][j];
        }
    }
    return g;
}
Graph Graph::operator-() const // onary 4
{
    Graph g(this->isDirected);
    for (size_t i = 0; i < this->getSize(); i++)
    {
        for (size_t j = 0; j < this->getSize(); j++)
        {
            this->get_matrix()[i][j] = -1 * this->get_matrix()[i][j];
        }
    }

    return g;
}
Graph Graph::operator-(const Graph &g) const // binary 5
{
    if (this->getSize() != g.getSize())
    {
        throw invalid_argument("the size between graphs diffrent");
    }

    vector<vector<int>> matrix1 = g.get_matrix();
    vector<vector<int>> new_matrix(matrix1.size(), vector<int>(matrix1.size(), 0));

    for (size_t i = 0; i < matrix1.size(); i++)
    {
        for (size_t j = 0; j < matrix1.size(); j++)
        {
            new_matrix[i][j] = matrix[i][j] - matrix1[i][j];
        }
    }

    // Assuming Graph constructor takes a matrix and loads it internally
    Graph g_new(isSymmetric(new_matrix));
    g_new.loadGraph(new_matrix);
    return g_new;
}
Graph Graph::operator*=(int number)
{ // modifing the graph by multiply by scalar
    for (size_t i = 0; i < this->getSize(); i++)
    {
        for (size_t j = 0; j < this->getSize(); j++)
        {
            this->get_matrix()[i][j] = this->get_matrix()[i][j] * number;
        }
    }
    return *this;
}

Graph Graph::operator*(const Graph &g) const
{
    if (matrix.size() != g.get_matrix().size())
    {
        throw invalid_argument("the size between graphs diffrent");
    }

    // Initialize a new matrix to store the new_matrix
    vector<vector<int>> new_matrix(matrix.size(), vector<int>(g.matrix[0].size(), 0));

    // Perform matrix multiplication
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < g.matrix[0].size(); ++j)
        {
            for (size_t k = 0; k < matrix[0].size(); ++k)
            {
                new_matrix[i][j] += matrix[i][k] * g.matrix[k][j];
            }
        }
    }

    // Create a new Graph object with the resulting matrix
    Graph new_g(isSymmetric(new_matrix)); // Assuming isSymmetric checks if the matrix is symmetric
    new_g.loadGraph(new_matrix);          // Assuming loadGraph loads the matrix into the Graph object
    return new_g;
}

// Overloading the '>' operator to check if the current graph contains the given graph as a submatrix
bool Graph::if_g1_contain_g2(const Graph &a) const
{
    // Reference to the current graph's matrix
    const vector<vector<int>> &A = this->get_matrix();
    // Reference to the given graph's matrix
    const vector<vector<int>> &B = a.get_matrix();

    // Loop through each possible position in the current graph's matrix
    for (size_t i = 0; i <= this->getSize() - a.getSize(); i++)
    {
        for (size_t j = 0; j <= this->getSize() - a.getSize(); j++)
        {
            bool match = true; // Variable to check for match

            // Loop through each element of the given graph's matrix
            for (size_t row = 0; row < a.getSize(); row++)
            {
                for (size_t culm = 0; culm < a.getSize(); culm++)
                {
                    // Check if elements do not match
                    if (A[i + row][j + culm] != B[row][culm])
                    {
                        match = false; // Set match to false if any element does not match
                        break;         // Break the innermost loop
                    }
                }
                if (!match)
                {
                    break; // Break the outer loop if no match is found
                }
            }

            if (match)
            {
                return true; // Return true if a submatrix match is found
            }
        }
    }
    return false; // Return false if no submatrix match is found
}

bool who_more_edges(const Graph &g1, const Graph &g2)
{
    int num_edges_g1 = 0;
    int num_edges_g2 = 0;
    for (size_t i = 0; i < g1.getSize(); i++)
    {
        for (size_t j = 0; j < g1.getSize(); j++)
        {
            if (g1.get_matrix()[i][j] != 0)
            {
                num_edges_g1++;
            }
        }
    }
    for (size_t i = 0; i < g2.getSize(); i++)
    {
        for (size_t j = 0; j < g2.getSize(); j++)
        {
            if (g2.get_matrix()[i][j] != 0)
            {
                num_edges_g2++;
            }
        }
    }
    return num_edges_g1 > num_edges_g2;
}

bool Graph::sameAdjacencyMatrix(const Graph &a, const Graph &b) const
{
    if (a.get_matrix().empty() && b.get_matrix().empty())
    {
        return false;
    }
    if (a.getSize() != b.getSize())
    {
        return false;
    }
    for (size_t i = 0; i < a.getSize(); i++)
    {
        for (size_t j = 0; j < a.getSize(); j++)
        {
            if (a.get_matrix()[i][j] != b.get_matrix()[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
bool Graph::operator>(const Graph &g2) const // binary
{
    // Check if the adjacency matrices are the same
    if (this->sameAdjacencyMatrix(*this, g2))
    {
        return false;
    }
    // Check if the current graph contains the given graph as a submatrix
    if (if_g1_contain_g2(g2))
    {
        return true;
    }
    // Check if the number of edges in the current graph is greater than the given graph
    else if (who_more_edges(*this, g2))
    {
        return true;
    }
    // Check if the size of the current graph is greater than the given graph
    return this->getSize() > g2.getSize();
}
ostream &operator<<(ostream &cout_new, const Graph &graph)
{

    graph.print_with_ostream(cout_new);

    return cout_new;
}
void Graph::print_with_ostream(ostream &cout_new)
{
    
}