#pragma once
#include <string>
#include <vector>

#include "Graph.hpp"
using namespace std;
using namespace VOGDAN;
namespace VOGDAN{
//Algorithms class, represents only algorithms - like a namespace.
class Algorithms {
   public:
    static bool isConnected(Graph& G);
    static string shortestPath(Graph& G, size_t u, size_t v);
    static string isContainsCycle(Graph& G);
    static string isBipartite(Graph& G);
    static bool negativeCycle(Graph& G);
    
};
}