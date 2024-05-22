#include "Algorithms.hpp"
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include "Graph.hpp"
using namespace std;
using namespace VOGDAN;

void dfs(Graph &G, size_t v, vector<bool> &visited);
string BellmanFord(Graph &G, size_t u, size_t v);
enum Color {
    WHITE,
    GRAY,
    BLACK,
};
string isContainsCycleDFS(Graph& g, size_t src, vector<Color>& colors, vector<int>& parents, vector<int>& path);
string constructCyclePath(const vector<int>& path, int start);

/* This is the implementaion of the four main Algorithms - isConnected, isBipartite, isContainsCycle and shortestPath.
   isConnected: This function checks if the graph is connected or not, for directed graph I check if strongly connected. 
   isBipartite: This Algorithm checks if we can color the graph vertcies in two colors, if so we return each colored group.
   ShortestPath: Returns the shortest path between two vertcies, if the graph is weighted we use BellmanFord else BFS algorithm.
   isContainsCycle: Returns if theres a cycle in the graph, if so it returns the cycle path.
*/

bool Algorithms::isConnected(Graph &G) {
size_t v = G.getVerticesCount();
    if (v == 0) {
        return true;
    }

    // Perform DFS on the original graph
    vector<bool> visited(v, false);
    dfs(G, 0, visited);

    // Check if all vertices are visited
    for (bool v : visited) {
        if (!v)
            return false;  // Graph is not connected
    }
    if(G.getIsDirected()){
    // Perform DFS on the transpose of the graph for checking strong connection.
    Graph GT = G.getTranspose();
    fill(visited.begin(), visited.end(), false); // Reset visited array
    dfs(GT, 0, visited); 
    }
    // Check if all vertices are visited
    for (bool v : visited) {
        if (!v)
            return false;  // Graph is not connected
    }
    return true;
}

void dfs(Graph &G, size_t v, vector<bool> &visited) { //simple dfs
    visited[v] = true;
    for (size_t i =0; i < G.getVerticesCount(); i++){             // iterating on each of the vertex neighbors
        if (G.getAdjacencyMatrix()[v][i] != 0 && !visited[i]){ // if we did visited him well get down to him and also mark him as visited. 
            dfs(G, i, visited);
        }
    }
}



string Algorithms::shortestPath(Graph &G, size_t u, size_t v) { 
    //lets first check if the graph is weighted or not
    size_t V = G.getVerticesCount();
    for (size_t i = 0; i < V; ++i) {
        for ( size_t j = 0; j < V; ++j){
            if(G.getAdjacencyMatrix()[i][j] > 1|| G.getAdjacencyMatrix()[i][j] < 0){        
            //if the graph is weighted we will use Bellman ford.
            return BellmanFord(G, u, v);
            }
        }
        } 
    //After checking for a weighted graph, if not we'll use BFS algorithm.
    const vector<vector<int>> &adjacencyMatrix = G.getAdjacencyMatrix();

    // Initialize distances and parent array
    vector<int> dist(V, -1);
    vector<size_t> parent(V, numeric_limits<size_t>::max());

    dist[u] = 0;
    queue<size_t> q;
    q.push(u);

    while (!q.empty()) {
        size_t current = q.front();
        q.pop();

        for (size_t i = 0; i < V; ++i) {
            if (adjacencyMatrix[current][i] != 0 && dist[i] == -1) {
                dist[i] = dist[current] + 1;
                parent[i] = current;
                q.push(i);
            }
        }
    }
    if (dist[v] == -1) {
        return "-1";  // No path exists
    }
    //construct the path
    string path;
    size_t current = v;
    while (current != numeric_limits<size_t>::max()) {
        path = to_string(current) + (current != v ? "->" : "") + path;
        current = parent[current];
    }
    return path;

}


string BellmanFord(Graph &G, size_t u, size_t v) {
    //if the graph is weighted we will use bellman ford algorithm:
    size_t V = G.getVerticesCount();
    const vector<vector<int>> &adjacencyMatrix = G.getAdjacencyMatrix();

    // Initialize distances and parent array
    vector<int> dist(V, numeric_limits<int>::max());
    vector<size_t> parent(V, numeric_limits<size_t>::max());

    dist[u] = 0;

    // Relax edges |V| - 1 times
    for (size_t i = 1; i < V; ++i) {
        for (size_t src = 0; src < V; ++src) {
            for (size_t dest = 0; dest < V; ++dest) {
                int weight = adjacencyMatrix[src][dest];
                if (weight != 0 && dist[src] != numeric_limits<int>::max() && dist[src] + weight < dist[dest]) {
                    dist[dest] = dist[src] + weight;
                    parent[dest] = src;
                }
            }
        }
    }

    // Check for negative weight cycles
    for (size_t src = 0; src < V; ++src) {
        for (size_t dest = 0; dest < V; ++dest) {
            int weight = adjacencyMatrix[src][dest];
            if (weight != 0 && dist[src] != numeric_limits<int>::max() && dist[src] + weight < dist[dest]) {
                return string("Negative cycle detected");
            }
        }
    }
    if (dist[v] == numeric_limits<int>::max()) {
        return string("-1");
    }
    // Reconstruct shortest path
    string path;
    size_t current = v;
    while (current !=numeric_limits<size_t>::max()) {
        path = to_string(current) + (current != v ? "->" : "") + path;
        current = parent[current];
    }

    return path;
}

string Algorithms::isContainsCycle(Graph& g) {
    vector<Color> colors(g.getVerticesCount(), WHITE);
    vector<int> parents(g.getVerticesCount(), -1);
    vector<int> path;

    for (size_t i = 0; i < g.getVerticesCount(); i++) {
        if (colors[i] == WHITE) {
            string cycle = isContainsCycleDFS(g, i, colors, parents, path);
            if (!cycle.empty()) {
                return cycle;
            }
        }
    }
    return "-1";
}

    
string isContainsCycleDFS(Graph& g, size_t src, vector<Color>& colors, vector<int>& parents, vector<int>& path) {
    colors[src] = GRAY;
    path.push_back(src);  // add the vertex to the path

    for (size_t v = 0; v < g.getVerticesCount(); v++) {
        if(g.getAdjacencyMatrix()[src][v] != 0){
            if (colors[v] == WHITE) {
                parents[v] = static_cast<int>(src);
                string cycle = isContainsCycleDFS(g, v, colors, parents, path);
                if (!cycle.empty()) {
                    return cycle;
                }
            } else if (colors[v] == GRAY) {
                if (!g.getIsDirected() && parents[src] == v) {
                    continue;
                }
                return constructCyclePath(path, v);
            }
        }
    }

    colors[src] = BLACK;
    path.pop_back();
    return "";
}

string constructCyclePath(const vector<int>& path, int start) {
    string cycle;
    size_t v = 0;
    for (v = 0; v < path.size(); v++) {
        if (path[v] == start) {
            break;
        }
    }
    for (size_t i = v; i < path.size(); i++) {
        cycle += std::to_string(path[i]) + "->";
    }
    // Add the starting vertex to close the cycle
    cycle += std::to_string(start);
    return cycle;
}





/*isBipartite: 

*/
string Algorithms::isBipartite(Graph &G) {
    size_t n = G.getVerticesCount();

    if (!G.getIsDirected()) {
        vector<int> color(n, -1);      // -1 means no color, 0 and 1 are the two colors
        vector<vector<int>> groups(2); // groups[0] and groups[1] are the two groups of vertices

        for (size_t start = 0; start < n; ++start) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0;
                groups[0].push_back(start);

                while (!q.empty()) {
                    size_t node = static_cast<size_t>(q.front());
                    q.pop();

                    for (size_t i = 0; i < n; ++i) {
                        if (G.getAdjacencyMatrix()[node][i] != 0) {
                            if (color[i] == -1) {
                                // If the node has not been colored, color it with the opposite color and add it to the corresponding group
                                color[i] = 1 - color[node];
                                (color[i] == 0 ? groups[0] : groups[1]).push_back(i);
                                q.push(i);
                            } else if (color[i] == color[node]) {
                                // If the node has been colored and its color is the same as the current node, the graph is not bipartite
                                return "The graph is not bipartite";
                            }
                        }
                    }
                }
            }
        }

        string result = "The graph is bipartite: A={";
        for (size_t i = 0; i < groups[0].size(); ++i) {
            result += to_string(groups[0][i]);
            if (i != groups[0].size() - 1) {
                result += ", ";
            }
        }
        result += "}, B={";
        for (size_t i = 0; i < groups[1].size(); ++i) {
            result += to_string(groups[1][i]);
            if (i != groups[1].size() - 1) {
                result += ", ";
            }
        }
        result += "}.";
        return result;
    } else {
        
        return "The graph is not bipartite";
    }
}

// using the bellman ford again because im lazy.
bool Algorithms::negativeCycle(Graph &G) {
    size_t u = 0, v = 0;
    string result = shortestPath(G, u, v);
    return result == "Negative cycle detected";
}