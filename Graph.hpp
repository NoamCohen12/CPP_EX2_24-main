#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
#include <vector>
#define without_weights_edges 0
#define positive_edges 1
#define negative_edges 2
using namespace std;
namespace ariel
{
    class Graph

    {
    private:
        vector<vector<int>> matrix; // adjacency list
        size_t num_vertices;        // number of vertixs
        bool isDirected;
        int type_graph;

    public:
        // main function
        Graph(bool isDirected);
        void loadGraph(vector<vector<int>> &graph);
        string printGraph() const;
        // help function
        int graph_type(vector<vector<int>> &graph);

        // gets
        size_t getSize() const;
        vector<vector<int>> get_matrix() const;
        bool isDirectedG() const;
        int get_type_graph() const;

        // creation functions
        Graph getTranspose() const;
        Graph add_opposite_edges() const;

        //////////////////////////////////////////////////////////////////////////////// operators
       // bool isSymmetric(const vector<vector<int>> &matrix);
        // add
        /**
        @param: Graph
        @return: Graph
        @operation: add two graphs
        @description: add two graphs

        */
        Graph operator+(const Graph &a)const; // binary
        /**
         * @param: Graph
         * @return: Graph
         * @operation: add two graphs
         * @description: add two graphs
         */
        Graph &operator+=(const Graph &g) // binary
        {
            *this = *this + g;
            return *this;
        }
        /**
         * @param: int
         *
         */
        Graph operator+() const; // unary in cpp
        //***********************************************************************************

        // redction
        Graph operator-(const Graph &a)const;  // binary in cpp
        Graph &operator-=(const Graph &g) // binary
        {
            *this = *this - g;
            return *this;
        }
        Graph operator-() const; // unary
                           //***********************************************************************************
        // multiplication
        Graph operator*(const Graph &a)const; // binary in cpp
        Graph operator*=(int number);  // binary in cpp




        Graph operator*=(Graph &g) // binary
        {
            Graph result = *this * g;
            *this = result;
            return *this;
        }
        Graph operator+(int number) ; // binary
        //***********************************************************************************
        //++|--
        Graph &operator--() // unary
        {
            *this = *this + (-1);
            return *this;
        }
        Graph &operator++()  // unary
        {
            *this = *this + 1;
            return *this;
        }
        //***********************************************************************************

        // comparison
        /***
         * Graphs G1 and G2 will be called equal if they are of the same order of magnitude and
         *  contain the same edges (and the weights of the edges are the same) 
         * or if G1 is not greater than G2 and neither is G2 greater than G1.
        */
        bool operator==(const Graph &a) const
        {
            bool sameMatrix = sameAdjacencyMatrix(*this, a);
            bool not_big = !(*this > a) && !(a > *this);

            return sameMatrix || not_big;
        }
        bool operator!=(const Graph &a) const
        {
            return !(*this == a);
        }

        bool operator>(const Graph &a) const; // binary
        bool operator<(const Graph &a) const  // binary
        {
            return a > *this;
        }
        bool operator<=(const Graph &a) {
            return (*this < a)||(*this == a);
        }
        bool operator>=(const Graph &a) const{
            return (*this > a)||(*this == a);
        }
        //***********************************************************************************

//<< function
        friend ostream& operator<<(ostream& cout_new, const Graph& graph);


        //***********************************************************************************
        // help functions
        void print_with_ostream(ostream &cout_new) const;

        bool if_g1_contain_g2(const Graph &g2) const;
        // bool who_more_edges(const Graph &g1, const Graph &g2) ;
        bool sameAdjacencyMatrix(const Graph &a, const Graph &b) const;
        
    };

}

#endif
