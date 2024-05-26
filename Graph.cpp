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

void Graph::loadGraph(const vector<vector<int>> &graph)
{
    if (graph.empty())
    {
        throw invalid_argument("the graph is empty");
    }

    this->num_vertices = graph.size();
    this->matrix = graph;
    for (size_t i = 0; i < num_vertices; i++)
    {
        if (graph[i].size() != num_vertices)
        {
            // cout << graph[i].size() << endl;
            // cout << num_vertices << endl;

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

string Graph::printGraph() const
{
    int vertices = this->getSize();
    string result;
    for (size_t i = 0; i < vertices; i++)
    {
        for (size_t j = 0; j < vertices; j++)
        {
            result += to_string(this->matrix[i][j]);
            if (j != vertices - 1)
            {
                result += ", ";
            }
        }
        result += "\n";
    }
    return result;
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

int Graph::graph_type(const vector<vector<int>> &graph)
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
    int numberV = matrix.size();
    for (const auto &row : matrix)
    {
        if (row.size() != numberV)
        {
            return false; // Not square, hence not symmetric
        }
    }

    // Check if the matrix is symmetric
    for (size_t i = 0; i < numberV; ++i)
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
Graph Graph::operator+(const Graph &graph) const
{
    if (this->get_matrix().empty() || graph.get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    if (this->getSize() != graph.getSize())
    {
        throw invalid_argument("the size between graphs diffrent");
    }

    vector<vector<int>> matrix_g = graph.get_matrix();
    vector<vector<int>> new_matrix(graph.getSize(), vector<int>(graph.getSize(), 0));

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
Graph Graph::operator+(int number) const
{
    if (this->get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    size_t num_vertices = this->num_vertices;
    vector<vector<int>> new_matrix(num_vertices, vector<int>(num_vertices, 0));
    for (size_t i = 0; i < num_vertices; i++)
    {
        for (size_t j = 0; j < num_vertices; j++)
        {
            if (this->get_matrix()[i][j] != 0)
            {
                new_matrix[i][j] = this->get_matrix()[i][j] + number;
            }
        }
    }
    Graph g_new(isSymmetric(new_matrix));
    g_new.loadGraph(new_matrix);
    return g_new;
}

Graph &Graph::operator++() // unary before
{
    *this = *this + 1;
    return *this;
}
Graph Graph::operator++(int) // unary after
{
    Graph temp = *this;
    *this = *this + 1;
    return temp;
}
Graph Graph::operator-() const
{
    if (this->get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    if (this->get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    Graph graph(this->isDirected);
    vector<vector<int>> new_matrix(this->getSize(), vector<int>(this->getSize(), 0));
    for (size_t i = 0; i < this->getSize(); i++)
    {
        for (size_t j = 0; j < this->getSize(); j++)
        {
            new_matrix[i][j] = -1 * this->get_matrix()[i][j];
        }
    }
    graph.loadGraph(new_matrix);

    return graph;
}
Graph Graph::operator-(const Graph &graph) const
{
    if (this->get_matrix().empty() || graph.get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    if (this->getSize() != graph.getSize())
    {
        throw invalid_argument("the size between graphs diffrent");
    }

    vector<vector<int>> matrix1 = graph.get_matrix();
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
Graph Graph::operator*(int number) const
{ // modifing the graph by multiply by scalar

    if (this->get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    Graph graph(this->isDirected);
    vector<vector<int>> new_matrix(this->getSize(), vector<int>(this->getSize(), 0));

    for (size_t i = 0; i < this->getSize(); i++)
    {
        for (size_t j = 0; j < this->getSize(); j++)
        {
            new_matrix[i][j] = this->get_matrix()[i][j] * number;
        }
    }
    graph.loadGraph(new_matrix);
    return graph;
}

Graph Graph::operator*(const Graph &graph) const
{
    if (this->get_matrix().empty()||graph.get_matrix().empty())
    {
        throw invalid_argument("the size between graphs diffrent");
    }
    if (matrix.size() != graph.get_matrix().size())
    {
        throw invalid_argument("the size between graphs diffrent");
    }

    // Initialize a new matrix to store the new_matrix
    vector<vector<int>> new_matrix(matrix.size(), vector<int>(graph.matrix[0].size(), 0));

    // Perform matrix multiplication
    for (size_t i = 0; i < matrix.size(); ++i)
    {
        for (size_t j = 0; j < graph.matrix[0].size(); ++j)
        {
            for (size_t k = 0; k < matrix[0].size(); ++k)
            {
                new_matrix[i][j] += matrix[i][k] * graph.matrix[k][j];
            }
        }
    }
    for (size_t i = 0; i < new_matrix.size(); i++)
    {
        for (size_t j = 0; j < new_matrix.size(); j++)
        {
            if (i == j)
            {
                new_matrix[i][j] = 0;
            }
        }
    }
    // Create a new Graph object with the resulting matrix
    Graph new_g(isSymmetric(new_matrix)); // Assuming isSymmetric checks if the matrix is symmetric
    new_g.loadGraph(new_matrix);          // Assuming loadGraph loads the matrix into the Graph object
    return new_g;
}

// Overloading the '>' operator to check if the current graph contains the given graph as a submatrix
bool Graph::if_g1_contain_g2(const Graph &graph) const
{
    if (!this->get_matrix().empty()&&graph.get_matrix().empty()) 
    {
       return true;
    }
    
    if (this->getSize() < graph.getSize())
    {
        return false;
    }

    // Reference to the current graph's matrix
    const vector<vector<int>> &Group_A = this->get_matrix();
    // Reference to the given graph's matrix
    const vector<vector<int>> &Group_B = graph.get_matrix();

    // Loop through each possible position in the current graph's matrix
    for (size_t i = 0; i <= this->getSize() - graph.getSize(); i++)
    {
        for (size_t j = 0; j <= this->getSize() - graph.getSize(); j++)
        {
            bool match = true; // Variable to check for match

            // Loop through each element of the given graph's matrix
            for (size_t row = 0; row < graph.getSize(); row++)
            {
                for (size_t culm = 0; culm < graph.getSize(); culm++)
                {
                    // Check if elements do not match
                    if (Group_A[i + row][j + culm] != Group_B[row][culm])
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

bool who_more_edges(const Graph &graph1, const Graph &graph2)
{
    int num_edges_g1 = 0;
    int num_edges_g2 = 0;
    for (size_t i = 0; i < graph1.getSize(); i++)
    {
        for (size_t j = 0; j < graph1.getSize(); j++)
        {
            if (graph1.get_matrix()[i][j] != 0)
            {
                num_edges_g1++;
            }
        }
    }
    for (size_t i = 0; i < graph2.getSize(); i++)
    {
        for (size_t j = 0; j < graph2.getSize(); j++)
        {
            if (graph2.get_matrix()[i][j] != 0)
            {
                num_edges_g2++;
            }
        }
    }
    return num_edges_g1 > num_edges_g2;
}

bool Graph::sameAdjacencyMatrix(const Graph &graph1, const Graph &graph2) const
{
    if (graph1.get_matrix().empty() && graph2.get_matrix().empty())
    {
        return false;
    }
    if (graph1.getSize() != graph2.getSize())
    {
        // cout<<"a bigger"<<endl;
        return false;
    }
    for (size_t i = 0; i < graph1.getSize(); i++)
    {
        for (size_t j = 0; j < graph1.getSize(); j++)
        {
            if (graph1.get_matrix()[i][j] != graph2.get_matrix()[i][j])
            {
                return false;
            }
        }
    }
    return true;
}
bool Graph::operator>(const Graph &graph2) const // binary
{
    if (this->get_matrix().empty() && !graph2.get_matrix().empty())
    {
        return false;
    }
    
    // Check if the adjacency matrices are the same
    if (this->sameAdjacencyMatrix(*this, graph2))
    {
        return false;
    }
    // Check if the current graph contains the given graph as a submatrix
    if (if_g1_contain_g2(graph2))
    {
        // cout<<"graph1 contain graph2"<<endl;
        return true;
    }
    // Check if the number of edges in the current graph is greater than the given graph
    else if (who_more_edges(*this, graph2))
    {
        // cout<<"graph1 more edges"<<endl;
        return true;
    }
    // cout<<"graph2 more edges"<<endl;
    //  Check if the size of the current graph is greater than the given graph
    return this->getSize() > graph2.getSize();
}

void Graph::print_with_ostream(ostream &cout_new) const
{
    size_t vertices = this->num_vertices;
    for (size_t i = 0; i < vertices; i++)
    {
        cout_new << "[ ";
        for (size_t j = 0; j < vertices; j++)
        {
            cout_new << this->matrix[i][j] << " ";
        }
        cout_new << "]" << endl;
    }
}

ostream &ariel::operator<<(ostream &cout_new, const Graph &graph)
{

    graph.print_with_ostream(cout_new);

    return cout_new;
}
// /**
//          * @param: Graph
//          * @return: New graph
//          * @operation: multiply graph with number *
//          * @description: multiply two graphs graph*number
//          *
//          * */
     