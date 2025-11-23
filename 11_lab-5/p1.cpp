#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <set>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
    char u_char, v_char; // For display purposes
    
    Edge(char u_c, char v_c, int w) {
        u_char = u_c;
        v_char = v_c;
        weight = w;
    }
};

class Graph {
private:
    int vertices;
    vector<Edge> edges;
    map<char, int> vertex_map;
    vector<char> vertex_chars;
    
public:
    Graph(int v) : vertices(v) {}
    
    void addEdge(char u, char v, int weight) {
        edges.push_back(Edge(u, v, weight));
        
        // Build vertex mapping
        if (vertex_map.find(u) == vertex_map.end()) {
            vertex_map[u] = vertex_chars.size();
            vertex_chars.push_back(u);
        }
        if (vertex_map.find(v) == vertex_map.end()) {
            vertex_map[v] = vertex_chars.size();
            vertex_chars.push_back(v);
        }
    }
    
    // Union-Find data structure for cycle detection
    class UnionFind {
    private:
        vector<int> parent, rank;
        
    public:
        UnionFind(int n) {
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }
        
        int find(int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }
        
        void unite(int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            
            if (rootX != rootY) {
                if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                } else if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }
        
        bool connected(int x, int y) {
            return find(x) == find(y);
        }
    };
    
    // Check if a subset of edges forms a spanning tree
    bool isSpanningTree(const vector<bool>& subset) {
        UnionFind uf(vertices);
        int edgeCount = 0;
        
        // Add edges and check for cycles
        for (int i = 0; i < edges.size(); i++) {
            if (subset[i]) {
                int u = vertex_map[edges[i].u_char];
                int v = vertex_map[edges[i].v_char];
                
                if (uf.connected(u, v)) {
                    return false; // Cycle detected
                }
                uf.unite(u, v);
                edgeCount++;
            }
        }
        
        // Check if all vertices are connected (spanning tree has V-1 edges)
        return edgeCount == vertices - 1;
    }
    
    // Calculate total weight of a subset of edges
    int calculateWeight(const vector<bool>& subset) {
        int total = 0;
        for (int i = 0; i < edges.size(); i++) {
            if (subset[i]) {
                total += edges[i].weight;
            }
        }
        return total;
    }
    
    // Generate all possible subsets using bitmasking
    void findMST() {
        int n = edges.size();
        int minWeight = INT_MAX;
        vector<bool> bestSubset;
        
        cout << "Generating all possible subsets of edges..." << endl;
        cout << "Total possible subsets: " << (1LL << n) << endl;
        
        // Generate all subsets using bitmask
        long long totalSubsets = 1LL << n;
        int validTrees = 0;
        
        for (long long mask = 0; mask < totalSubsets; mask++) {
            vector<bool> subset(n, false);
            int edgeCount = 0;
            
            // Create subset from bitmask
            for (int i = 0; i < n; i++) {
                if (mask & (1LL << i)) {
                    subset[i] = true;
                    edgeCount++;
                }
            }
            
            // Only consider subsets with exactly V-1 edges (necessary condition for spanning tree)
            if (edgeCount == vertices - 1) {
                if (isSpanningTree(subset)) {
                    validTrees++;
                    int weight = calculateWeight(subset);
                    if (weight < minWeight) {
                        minWeight = weight;
                        bestSubset = subset;
                    }
                }
            }
            
            // Progress indicator for large graphs
            if (mask % 1000000 == 0 && mask > 0) {
                cout << "Processed " << mask << " subsets... Found " << validTrees << " valid spanning trees so far." << endl;
            }
        }
        
        cout << "\n=== RESULTS ===" << endl;
        cout << "Total valid spanning trees found: " << validTrees << endl;
        cout << "Minimum Spanning Tree Weight: " << minWeight << endl;
        cout << "Edges in MST:" << endl;
        
        for (int i = 0; i < n; i++) {
            if (bestSubset[i]) {
                cout << edges[i].u_char << " - " << edges[i].v_char << " : " << edges[i].weight << endl;
            }
        }
    }
    
    void displayGraph() {
        cout << "\nGraph Information:" << endl;
        cout << "Vertices: " << vertices << endl;
        cout << "Edges: " << edges.size() << endl;
        cout << "Edge List:" << endl;
        for (const auto& edge : edges) {
            cout << edge.u_char << " - " << edge.v_char << " : " << edge.weight << endl;
        }
    }
};

int main() {
    int vertices, numEdges;
    
    cout << "Number of vertices: ";
    cin >> vertices;
    
    cout << "Edges: ";
    cin >> numEdges;
    
    Graph graph(vertices);
    
    cout << "Enter edges (format: vertex1 vertex2 weight):" << endl;
    for (int i = 0; i < numEdges; i++) {
        char u, v;
        int weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }
    
    graph.displayGraph();
    
    cout << "\n=== FINDING MST USING GENERATE-AND-TEST METHOD ===" << endl;
    cout << "Warning: This method has exponential time complexity O(2^E)" << endl;
    cout << "For large graphs, this will be very slow!" << endl;
    
    graph.findMST();
    
    return 0;
}