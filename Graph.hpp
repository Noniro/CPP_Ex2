#pragma once
#include <vector>
#include <iostream>
using namespace std;
namespace VOGDAN{
//graph class, contains the private fields and the public functionalities declarations.
    class Graph { 
    private:
        vector<vector<int>> adjacencyMatrix;
        bool isDirected;

    public:
        Graph(): isDirected(false) {} // Default constructor
        Graph(vector<vector<int>>& adjacencyMatrix); // Constructor
        void loadGraph(const vector<vector<int>>& adjacencyMatrix);
        Graph getTranspose() const;
        void printGraph();
        size_t countEdges() const;
        size_t getVerticesCount();
        vector<int> getNeighbors(size_t v);
        const vector<vector<int>>& getAdjacencyMatrix()const;
        Graph(bool isDirected);
        bool getIsDirected() const;
        int getEdgeWeight(int u, int v);
        void setDirected(bool isDirected);

        //operators overloading
        Graph operator+(const Graph& G)const; 
        Graph operator-(const Graph& G)const;
        Graph operator+=(const Graph& G); 
        Graph operator-=(const Graph& G);
        Graph operator+(int n)const;
        Graph operator-(int n)const;
        Graph operator-()const;
        Graph operator+()const;
        
        bool operator<(const Graph& G)const;
        bool operator>(const Graph& G)const;
        bool operator<=(const Graph& G)const;
        bool operator>=(const Graph& G)const;
        bool operator==(const Graph& G)const;
        bool operator!=(const Graph& G)const;

        bool isSubGraphOf(const Graph& G) const;

        Graph operator++();//pre-increment
        Graph operator--();
        Graph operator++(int);//post-increment
        Graph operator--(int);
        Graph operator*(const Graph& G)const;
        Graph operator*(int n)const; // graph * int
        friend Graph operator*(int n, const Graph& G); // int * graph
        //cout overloading
        friend std::ostream& operator<<(std::ostream& os, const Graph& G);

    };
}