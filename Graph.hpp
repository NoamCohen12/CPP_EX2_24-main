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

        /////////////////////////// operators ////////////////////////////////
//Functions with short implementationn I decided to implement in the class because in the case inLine is faster
//from the function that is not inLine
        /////////////////////////// addition operators ///////////////////////////

        
        // add operators
        /**
        @param: Graph
        @return: New graph
        @operation: add two graphs +
        @description: add two graphs a+b
        //out line
        */
        Graph operator+(const Graph &a) const; 
        /**
         * @param: Graph
         * @return: This graph
         * @operation: add two graphs +=
         * @description: add two graphs a+=b
         */
        Graph &operator+=(const Graph &g) 
        {
            *this = *this + g;
            return *this;
        }
        /**
         * @param: int
         * @return: New graph
         * @operation: add graph by number +
         * @description: add graph by number a+number
         */
        Graph operator+(int number) const;
        /**
         * @param: without parameters
         * @return: This graph
         * @operation: +graph
         * @description: Multiply the graph by 1
         */
        Graph operator+() const 
        {
            return *this;
        } 
        ///////////////////////////// redction operators ///////////////////////////
        /**
         * @param: Graph
         * @return: New graph
         * @operation: substract two graphs -
         * @description: substract two graphs a-b
         *
         * */
        Graph operator-(const Graph &a) const; 
        /**
         * @param: graph
         * @return: This graph
         * @operation: substract two graphs -
         * @description: substract two graphs a-=b
         *
         **/
        Graph &operator-=(const Graph &g) 
        {
            *this = *this - g;
            return *this;
        }
        /**
         * @param: without parameters
         * @return: New graph
         * @operation: -graph
         * @description: Multiply the graph by -1
         *
         * */
        Graph operator-() const; 
                                 
        // multiplication operators
        /**
         * @param: Graph
         * @return: New graph
         * @operation: multiply two graphs *
         * @description: multiply two graphs a*b
         *
         * */
        Graph operator*(const Graph &a) const; 
        /**
         * @param: int
         * @return: New graph
         * @operation: multiply graph by number *
         * @description: multiply graph by number a*number
         *
         * */
        Graph operator*(int number) const; 
        /**
         * @param: Graph
         * @return: This graph
         * @operation: multiply two graphs *
         * @description: multiply two graphs a*=b
         *
         * */
        Graph operator*=(int number)
        {
            *this = *this * number;
            return *this;
        }
        /**
         * @param: Graph
         * @return: This graph
         * @operation: multiply two graphs *
         * @description: multiply two graphs a*=b
         *
         * */
        Graph operator*=(Graph &g) 
        {
            *this = *this * g;
            return *this;
        }
        
        /////////////////////////////// ++|--  operators ///////////////////////////////////
        /**
         * @param: without parameters
         * @return: This graph
         * @operation: graph--
         * @description: reduce the graph by 1 and return the graph
         */
        Graph operator--() 
        {
            *this = *this + (-1);
            return *this;
        }
        /**
         * @param: without parameters
         * @return: New graph
         * @operation: --graph
         * @description: return graph and after reduce by 1
         */
        Graph operator--(int) // after
        {
            Graph temp = *this;
            *this = *this + (-1);
            return temp;
        }
        /**
         * @param: without parameters
         * @return: This graph
         * @operation: graph++
         * @description: increase the graph by 1 and return the graph
         */
        Graph &operator++(); 
        /**
         * @param: without parameters
         * @return: New graph
         * @operation: ++graph
         * @description: return graph and after increase by 1
         */
        Graph operator++(int); 

        /////////////////////////////// comparison operators ///////////////////////////////////
        
        /**
         * Graphs G1 and G2 will be called equal if they are of the same order of magnitude and
         *  contain the same edges (and the weights of the edges are the same)
         * or if G1 is not greater than G2 and neither is G2 greater than G1.
         */
        /**
         * @param: Graph
         * @return: bool
         * @operation: compare two graphs ==
         * @description: compare two graphs a==b
         */
        bool operator==(const Graph &a) const
        {
            bool sameMatrix = sameAdjacencyMatrix(*this, a);
            bool not_big = !(*this > a) && !(a > *this);

            return sameMatrix || not_big;
        }
        /**
         * @param: Graph
         * @return: bool
         * @operation: compare two graphs !=
         * @description: compare two graphs a!=b
         */
        bool operator!=(const Graph &a) const
        {
            return !(*this == a);
        }
        /**
         * @param: Graph
         * @return: bool
         * @operation: compare two graphs >
         * @description: compare two graphs a>b
         */
        bool operator>(const Graph &a) const; // binary
        /**
         * @param: Graph
         * @return: bool
         * @operation: compare two graphs <
         * @description: compare two graphs a<b
         */
        bool operator<(const Graph &a) const
        {
            return a > *this;
        }
        /**
         * @param: Graph
         * @return: bool
         * @operation: compare two graphs <=
         * @description: compare two graphs a<=b
         */
        bool operator<=(const Graph &a)
        {
            return (*this < a) || (*this == a);
        }
        /**
         * @param: Graph
         * @return: bool
         * @operation: compare two graphs >=
         * @description: compare two graphs a>=b
         */
        bool operator>=(const Graph &a) const
        {
            return (*this > a) || (*this == a);
        }
        ////////////////////////////// print operators //////////////////////////////////////
        /**
         * @param: ostream
         * @return: ostream
         * @operation: print graph
         * @description: print graph
         * the function is friend function because it is not a member of the class
         */
        //<< function
        friend ostream &operator<<(ostream &cout_new, const Graph &graph);

        //////////////////////////////  help functions //////////////////////////////////////
       
        void print_with_ostream(ostream &cout_new) const;

         bool if_g1_contain_g2(const Graph &g2) const;

         bool sameAdjacencyMatrix(const Graph &a, const Graph &b) const;

//there are two functions that are not implemented in the class becauae they are not operators and 
//they are not member functions of the class also thay not shuold the data member of the class
//1.who_more_edges
//2.isSymmetric

    };

}

#endif
