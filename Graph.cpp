#include "Graph.hpp"

#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;
using namespace VOGDAN;
/*In this Graph implementation, we have all the basic functions needed for the graph Algorithms.
  in Graph.hpp the class declaration. 
  we can declare the graph useing default contructor or constructor with needed parameters.
  in here (Graph.cpp) we have the following functions:
*/

/*loadGraph: this function takes the graph adjacency matrix and checking if 
  the representaion is valid by going thru the matrix and checking if the matrix is square.
  then it checks if the graph is directed or not by checking if the matrix is symmetric or not.
  and lastly if there are self vertex loops.
  and update the isDirected variable accordingly.
  then it loads the graph by assigning the adjacency matrix to the adjacencyMatrix variable.
*/
namespace VOGDAN{
void Graph::loadGraph(const vector<vector<int>>& adjacencyMatrix) {
    size_t n = adjacencyMatrix.size();
    for (size_t i = 0; i < n; ++i) {
        if (adjacencyMatrix[i].size() != n) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
    }

    bool isSymmetric = true;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (adjacencyMatrix[i][j] != adjacencyMatrix[j][i]) {
                isSymmetric = false;
                break;
            }
        }
        if (!isSymmetric) break;
    }
    for(size_t i=0; i<n;i++){
        if(adjacencyMatrix[i][i]!=0){
            throw invalid_argument("graph with self loops not allowed.");
        }
    }

    setDirected(!isSymmetric);
    this->adjacencyMatrix = adjacencyMatrix;
}
// Using for when graph is directed, creating a new graph with the transposed matrix.
Graph Graph::getTranspose() const {
    Graph GT;
    size_t n = adjacencyMatrix.size();
    vector<vector<int>> transpose(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            transpose[j][i] = adjacencyMatrix[i][j];
        }
    }
    GT.loadGraph(transpose); // Assign the transposed matrix to GT
    return GT;
}

bool Graph::getIsDirected() const {
    return isDirected;
}


void Graph::printGraph() {
    cout << "Graph with " << adjacencyMatrix.size() << " vertices and " << countEdges() << " edges." << endl;
}


void Graph::setDirected(bool isDirected) {
    this->isDirected = isDirected;
}


size_t Graph::countEdges() const {
    size_t edges = 0;
    if (isDirected) {
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = 0; j < adjacencyMatrix[i].size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    ++edges;
                }
            }
        }
    } else {
        for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
            for (size_t j = i; j < adjacencyMatrix[i].size(); ++j) {
                if (adjacencyMatrix[i][j] != 0) {
                    ++edges;
                }
            }
        }
    }
    return edges; 
}

const vector<vector<int>>& Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

size_t Graph::getVerticesCount() {
    return adjacencyMatrix.size();
}
// get neighbors -> returning the vertex row.
vector<int> Graph::getNeighbors(size_t v) {
    if (v < 0 || v >= adjacencyMatrix.size()) {
        throw out_of_range("Vertex out of range");
    }
    return adjacencyMatrix[v];
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Operators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Graph Graph::operator+(const Graph& G) const {
    size_t n = adjacencyMatrix.size();
    if (n != G.adjacencyMatrix.size()) {
        throw invalid_argument("Graphs have different number of vertices.");
    }

    vector<vector<int>> sum(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            sum[i][j] = adjacencyMatrix[i][j] + G.adjacencyMatrix[i][j];
        }
    }

    Graph result;
    result.loadGraph(sum);
    return result;
}

Graph Graph::operator-(const Graph& G) const {
    size_t n = adjacencyMatrix.size();
    if (n != G.adjacencyMatrix.size()) {
        throw invalid_argument("Graphs have different number of vertices.");
    }

    vector<vector<int>> diff(n, vector<int>(n, 0));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            diff[i][j] = adjacencyMatrix[i][j] - G.adjacencyMatrix[i][j];
        }
    }

    Graph result;
    result.loadGraph(diff);
    return result;
}

Graph Graph::operator+(int n) const {
    size_t m = adjacencyMatrix.size();
    vector<vector<int>> sum(m, vector<int>(m, 0));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if(i!=j && adjacencyMatrix[i][j]!=0 ){sum[i][j] = adjacencyMatrix[i][j] + n;}
        }
    }

    Graph result;
    result.loadGraph(sum);
    return result;
}

Graph Graph::operator-(int n) const {
    size_t m = adjacencyMatrix.size();
    vector<vector<int>> diff(m, vector<int>(m, 0));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < m; ++j) {
           if(i!=j && adjacencyMatrix[i][j]!=0 ){ diff[i][j] = adjacencyMatrix[i][j] - n;}
        }
    }

    Graph result;
    result.loadGraph(diff);
    return result;
}

Graph Graph::operator+=(const Graph& G) {
    *this = *this + G;
    return *this;
}

Graph Graph::operator-=(const Graph& G) {
    *this = *this - G;
    return *this;
}


bool Graph::operator<(const Graph& G) const {
    size_t thisSize = adjacencyMatrix.size();
    size_t otherSize = G.adjacencyMatrix.size();

    if (thisSize != otherSize) {
        return thisSize < otherSize;
    }

    for (size_t i = 0; i < thisSize; ++i) {
        for (size_t j = 0; j < thisSize; ++j) {
            if (adjacencyMatrix[i][j] != G.adjacencyMatrix[i][j]) {
                return adjacencyMatrix[i][j] < G.adjacencyMatrix[i][j];
            }
        }
    }

    return false;
}


bool Graph::operator>(const Graph& G) const {
    return G < *this;
}

bool Graph::operator<=(const Graph& G) const {
    return !(*this > G);
}

bool Graph::operator>=(const Graph& G) const {
    return !(*this < G);
}

bool Graph::operator==(const Graph& G) const {
    return !(*this < G) && !(*this > G);
}

bool Graph::operator!=(const Graph& G) const {
    return !(*this == G);
}

Graph Graph::operator++() {
    *this = *this + 1;
    return *this;
}

Graph Graph::operator--() {
    *this = *this - 1;
    return *this;
}

Graph Graph::operator++(int) {
    Graph temp = *this;
    *this = *this + 1;
    return temp;
}

Graph Graph::operator--(int) {
    Graph temp = *this;
    *this = *this - 1;
    return temp;
}

Graph Graph::operator*(const Graph& G) const {
    if (adjacencyMatrix[0].size() != G.adjacencyMatrix.size()) {
        throw std::invalid_argument("Graphs have incompatible sizes.");
    }

    Graph result;
    result.adjacencyMatrix.resize(adjacencyMatrix.size(), vector<int>(G.adjacencyMatrix[0].size()));

    for (size_t i = 0; i < adjacencyMatrix.size(); ++i) {
        for (size_t j = 0; j < G.adjacencyMatrix[0].size(); ++j) {
            if(i==j)continue;
            for (size_t k = 0; k < adjacencyMatrix[0].size(); ++k) {
                result.adjacencyMatrix[i][j] += adjacencyMatrix[i][k] * G.adjacencyMatrix[k][j];
            }
        }
    }

    return result;
}

Graph Graph::operator*(int n) const {
    size_t m = adjacencyMatrix.size();
    vector<vector<int>> product(m, vector<int>(m, 0));
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < m; ++j) {
            product[i][j] = adjacencyMatrix[i][j] * n;
        }
    }

    Graph result;
    result.loadGraph(product);
    return result;
}

Graph operator*(int n, const Graph& G) {
    return G * n;
}

std::ostream& operator<<(std::ostream& os, const Graph& G){
    for (size_t i = 0; i < G.getAdjacencyMatrix().size(); i++)
    {
        for (size_t j = 0; j <G.getAdjacencyMatrix()[i].size(); j++)
        {
            os<<G.getAdjacencyMatrix()[i][j]<<" ";
        }
        os<<std::endl;
    }
    return os;
}

} 




