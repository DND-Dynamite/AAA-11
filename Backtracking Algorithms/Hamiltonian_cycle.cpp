#include <iostream>
#include <vector>
using namespace std;
// Problem  Statement:

// Hamiltonian Cycle or Circuit in a graph G is a cycle that visits every vertex of G
// exactly once and returns to the starting vertex.

// If a graph contains a Hamiltonian cycle, it is called Hamiltonian graph otherwise it
// is non-Hamiltonian.
// Finding a Hamiltonian Cycle in a graph is a well-known NP-complete problem,
// which means that there's no known efficient algorithm to solve it for all types of graphs. However, it can be solved for small or specific types of graphs.
// The Hamiltonian Cycle problem has practical applications in various fields,
// such as logistics, network design, and computer science

// The idea is to use backtracking to determine whether the given graph contains a
// Hamiltonian Cycle. Initialize an empty path array and place the starting
// vertex (e.g., vertex 0) at the first position. Recursively try to add
// the remaining vertices one by one. Before placing a vertex, 
// ensure it is adjacent to the previously added vertex and has not already been 
// used in the path. If a valid vertex is found, 
// proceed forward; otherwise, backtrack and try another option.

// C++ Code to check whether the given graph
// contains Hamiltonian Cycle using backtracking


// Check if it's valid to place vertex at current position
bool isSafe(int vertex, vector<vector<int>> &graph, vector<int> &path, int pos) {
    
    // The vertex must be adjacent to the previous vertex
    if (!graph[path[pos - 1]][vertex]) {
        return false;
    }

    // The vertex must not already be in the path
    for (int i = 0; i < pos; i++) {
        if (path[i] == vertex) {
            return false;
        }
    }

    return true;
}

// Recursive backtracking to construct Hamiltonian Cycle
bool hamCycleUtil(vector<vector<int>> &graph, vector<int> &path, int pos, int n) {
    
    // Base case: all vertices are in the path
    if (pos == n) {
        
        // Check if there's an edge from 
        // last to first vertex
        return graph[path[pos - 1]][path[0]];
    }

    // Try all possible vertices as next candidate
    for (int v = 1; v < n; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamCycleUtil(graph, path, pos + 1, n)) {
                return true;
            }

            // Backtrack if v doesn't lead to a solution
            path[pos] = -1;
        }
    }

    return false;
}

// Initialize path and invoke backtracking function
vector<int> hamCycle(vector<vector<int>> &graph) {
    int n = graph.size();
    vector<int> path(n, -1);

    // Start path with vertex 0
    path[0] = 0;

    if (!hamCycleUtil(graph, path, 1, n)) {
        return {-1};
    }

    return path;
}

// Driver Code
int main() {
    
    // Representation of the given graph
    //    (0)-(1)-(2) 
    //     |  / \  | 
    //     | /   \ | 
    //     |/     \| 
    //    (3)-----(4)
    vector<vector<int>> graph = {
        {0, 1, 0, 1, 0}, 
        {1, 0, 1, 1, 1}, 
        {0, 1, 0, 0, 1}, 
        {1, 1, 0, 0, 1}, 
        {0, 1, 1, 1, 0}
    };

    vector<int> path = hamCycle(graph);
    
    if(path[0] == -1) {
        
        cout << "Solution does not Exist";
    }
    else {
        
        for (int i = 0; i < path.size(); i++) {
           cout << path[i] << " ";
        }

        // Print the first vertex again 
        // to complete the cycle
        cout << path[0];
    }

    return 0;
}