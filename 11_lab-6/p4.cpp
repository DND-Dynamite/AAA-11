#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream> // Required for file operations

using namespace std;

// Function to approximate Set Cover using greedy algorithm
set<int> approximateSetCover(vector<set<int>>& subsets, set<int>& universe) {
    set<int> result;
    set<int> uncovered = universe;
    
    while (!uncovered.empty()) {
        // Find the subset that covers the maximum number of uncovered elements
        int maxCover = -1;
        int bestSubset = -1;
        
        for (int i = 0; i < subsets.size(); i++) {
            int coverCount = 0;
            for (int element : subsets[i]) {
                if (uncovered.find(element) != uncovered.end()) {
                    coverCount++;
                }
            }
            
            if (coverCount > maxCover) {
                maxCover = coverCount;
                bestSubset = i;
            }
        }
        
        if (bestSubset == -1) break; // No more subsets can cover remaining elements
        
        // Add the best subset to result and remove covered elements
        result.insert(bestSubset);
        for (int element : subsets[bestSubset]) {
            uncovered.erase(element);
        }
    }
    
    return result;
}

// Function to approximate Vertex Cover using greedy algorithm (matching-based)
set<int> approximateVertexCover(map<int, vector<int>>& graph) {
    set<int> cover;
    vector<pair<int, int>> edges;
    
    // Create a list of all edges (assuming undirected graph)
    for (auto& node : graph) {
        int u = node.first;
        for (int v : node.second) {
            if (u < v) { // Avoid duplicate edges and self-loops
                edges.push_back({u, v});
            }
        }
    }
    
    // Greedy approach: repeatedly pick edges and add both endpoints
    while (!edges.empty()) {
        // Pick an arbitrary edge (the first one)
        auto edge = edges[0];
        int u = edge.first;
        int v = edge.second;
        
        // Add both endpoints to cover
        cover.insert(u);
        cover.insert(v);
        
        // Remove all edges incident to u or v. 
        // Note: C++11 and later allows in-place removal like this:
        edges.erase(remove_if(edges.begin(), edges.end(), 
                                [u, v](const pair<int, int>& e) {
                                    return e.first == u || e.second == u || 
                                           e.first == v || e.second == v;
                                }), edges.end());
    }
    
    return cover;
}

// Function to print a set
void printSet(const set<int>& s, const string& name) {
    cout << name << ": {";
    bool first = true;
    for (int element : s) {
        if (!first) cout << ", ";
        cout << element;
        first = false;
    }
    cout << "}" << endl;
}

// 🆕 New function to parse graph input from a file
map<int, vector<int>> parseGraphFromFile(const string& filename) {
    map<int, vector<int>> graph;
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cerr << "Error: Could not open file '" << filename << "'" << endl;
        return graph;
    }

    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') continue; // Skip empty lines and comments
        
        size_t colonPos = line.find(':');
        if (colonPos == string::npos) {
            cerr << "Warning: Skipping line with invalid format: " << line << endl;
            continue;
        }
        
        try {
            int node = stoi(line.substr(0, colonPos));
            string neighborsStr = line.substr(colonPos + 1);
            
            // Parse neighbors
            vector<int> neighbors;
            stringstream ss(neighborsStr);
            string neighbor;
            
            while (getline(ss, neighbor, ',')) {
                // Remove whitespace
                neighbor.erase(remove_if(neighbor.begin(), neighbor.end(), ::isspace), neighbor.end());
                if (!neighbor.empty()) {
                    neighbors.push_back(stoi(neighbor));
                }
            }
            
            graph[node] = neighbors;
        } catch (const std::exception& e) {
            cerr << "Warning: Error parsing line: " << line << " (" << e.what() << ")" << endl;
        }
    }
    
    return graph;
}

// Function to create subsets for set cover from graph
void createSubsetsFromGraph(const map<int, vector<int>>& graph, 
                            vector<set<int>>& subsets, set<int>& universe) {
    subsets.clear();
    universe.clear();

    // The universe is all unique node IDs in the graph
    for (const auto& node : graph) {
        universe.insert(node.first);
        for (int neighbor : node.second) {
            universe.insert(neighbor);
        }
    }
    
    // Each subset S_i is defined as the node i and its neighbors (A[i] union {i})
    for (const auto& node : graph) {
        set<int> subset;
        subset.insert(node.first);
        for (int neighbor : node.second) {
            subset.insert(neighbor);
        }
        subsets.push_back(subset);
    }
}

int main() {
    cout << "=== Approximate Set Cover and Vertex Cover Problems ===" << endl;
    cout << "Choose input method:" << endl;
    cout << "1. Use predefined sample graph" << endl;
    cout << "2. Enter graph manually (console)" << endl;
    cout << "**3. Load graph from text file**" << endl;
    cout << "Enter choice (1, 2, or 3): ";
    
    int choice;
    cin >> choice;
    cin.ignore(); // Clear newline character
    
    map<int, vector<int>> graph;
    
    if (choice == 1) {
        // Predefined Sample graph
        graph = {
            {0, {1, 2, 3, 4}},
            {1, {0, 2, 5, 6}},
            {2, {0, 1, 3, 7}},
            {3, {0, 2, 4, 8}},
            {4, {0, 3, 5, 9}},
            {5, {1, 4, 6, 8}},
            {6, {1, 5, 7, 9}},
            {7, {2, 6, 8}},
            {8, {3, 5, 7, 9}},
            {9, {4, 6, 8}}
        };
        cout << "Using predefined sample graph." << endl;
    } else if (choice == 2) {
        // Manual Input (using the existing parsing logic)
        cout << "Enter graph in format 'node: neighbor1, neighbor2, ...' (empty line to finish):" << endl;
        string line;
        while (getline(cin, line)) {
            if (line.empty()) break;
            
            size_t colonPos = line.find(':');
            if (colonPos == string::npos) {
                cout << "Invalid format. Skipping line." << endl;
                continue;
            }
            
            try {
                int node = stoi(line.substr(0, colonPos));
                string neighborsStr = line.substr(colonPos + 1);
                
                vector<int> neighbors;
                stringstream ss(neighborsStr);
                string neighbor;
                
                while (getline(ss, neighbor, ',')) {
                    neighbor.erase(remove_if(neighbor.begin(), neighbor.end(), ::isspace), neighbor.end());
                    if (!neighbor.empty()) {
                        neighbors.push_back(stoi(neighbor));
                    }
                }
                graph[node] = neighbors;
            } catch (const std::exception& e) {
                cerr << "Warning: Error parsing input line. (" << e.what() << ")" << endl;
            }
        }
    } else if (choice == 3) {
        // 🆕 File Input
        string filename;
        cout << "Enter graph filename (e.g., graph.txt): ";
        getline(cin, filename);
        graph = parseGraphFromFile(filename);
        if (graph.empty()) {
            cout << "Failed to load graph or graph is empty." << endl;
            return 1;
        }
        cout << "Graph loaded from file." << endl;
    } else {
        cout << "Invalid choice. Exiting." << endl;
        return 1;
    }
    
    // Print the graph
    cout << "\nGraph (Adjacency List):" << endl;
    for (const auto& node : graph) {
        cout << node.first << ": [";
        for (size_t i = 0; i < node.second.size(); i++) {
            cout << node.second[i];
            if (i < node.second.size() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
    
    // Solve Vertex Cover Problem
    cout << "\n=== Vertex Cover Problem (Approximation) ===" << endl;
    set<int> vertexCover = approximateVertexCover(graph);
    cout << "Approximate Vertex Cover Size: " << vertexCover.size() << endl;
    printSet(vertexCover, "Vertex Cover");
    
    // Solve Set Cover Problem
    cout << "\n=== Set Cover Problem (Approximation) ===" << endl;
    vector<set<int>> subsets;
    set<int> universe;
    createSubsetsFromGraph(graph, subsets, universe);
    
    cout << "Universe size: " << universe.size() << endl;
    cout << "Number of subsets: " << subsets.size() << endl;
    
    set<int> setCover = approximateSetCover(subsets, universe);
    cout << "Approximate Set Cover Size: " << setCover.size() << endl;
    printSet(setCover, "Set Cover (subset indices)");
    
    // Print the actual subsets used
    cout << "\nSubsets used in Set Cover:" << endl;
    for (int subsetIndex : setCover) {
        // Since we created subsets directly from the map iteration, 
        // the subsetIndex corresponds to the node ID if the map keys are 0, 1, 2...
        // For general graph, it is just the index of the subset vector.
        cout << "Subset " << subsetIndex << " (Node " << subsetIndex << " and neighbors): {";
        bool first = true;
        for (int element : subsets[subsetIndex]) {
            if (!first) cout << ", ";
            cout << element;
            first = false;
        }
        cout << "}" << endl;
    }
    
    return 0;
}