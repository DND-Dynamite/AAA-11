#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <climits>
#include <sstream>

using namespace std;

#define INF INT_MAX

class FloydWarshall {
private:
    int V;
    vector<vector<long long>> dist;
    vector<vector<int>> next;

public:
    FloydWarshall(int vertices) : V(vertices) {
        dist.resize(V, vector<long long>(V, INF));
        next.resize(V, vector<int>(V, -1));
    }

    void inputGraph() {
        cout << "\n=== Graph Input ===" << endl;
        cout << "Enter adjacency matrix (use " << INF << " for infinity):" << endl;
        cout << "Format: Enter " << V << " rows with " << V << " values each" << endl;
        
        for (int i = 0; i < V; i++) {
            cout << "Row " << i << ": ";
            for (int j = 0; j < V; j++) {
                long long weight;
                cin >> weight;
                dist[i][j] = weight;
                if (i != j && weight != INF) {
                    next[i][j] = j;
                }
            }
        }
    }

    void setGraph(const vector<vector<long long>>& graph) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                dist[i][j] = graph[i][j];
                // next[i][j] is used to reconstruct the path. 
                // If there's a direct edge (weight != INF and i != j), the next stop is j.
                if (i != j && graph[i][j] != INF) {
                    next[i][j] = j;
                }
                // Handle the case where there is no direct edge, ensuring next remains -1 unless an edge exists
                else if (i != j && graph[i][j] == INF) {
                    next[i][j] = -1; 
                }
            }
        }
    }

    bool computeShortestPaths() {
        // Floyd-Warshall Algorithm
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    // Check for overflow before addition (INF + anything is problematic)
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (int i = 0; i < V; i++) {
            if (dist[i][i] < 0) {
                return false;
            }
        }
        return true;
    }

    void printDistanceMatrix() {
        cout << "\n=== All-to-All Shortest Distances ===" << endl;
        cout << "     ";
        for (int i = 0; i < V; i++) {
            cout << setw(8) << "V" + to_string(i);
        }
        cout << endl;
        cout << string(9 + V * 8, '-') << endl;

        for (int i = 0; i < V; i++) {
            cout << "V" << i << " | ";
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(8) << "INF";
                } else {
                    cout << setw(8) << dist[i][j];
                }
            }
            cout << endl;
        }
    }

    void printPath(int start, int end) {
        if (dist[start][end] == INF) {
            cout << "No path exists from V" << start << " to V" << end << endl;
            return;
        }

        vector<int> path;
        int current = start;
        path.push_back(current);

        // Path reconstruction using the next matrix
        while (current != end) {
            current = next[current][end];
            if (current == -1) { // Should not happen if dist[start][end] != INF, but good safeguard
                cout << "Error: Path reconstruction failed from V" << start << " to V" << end << endl;
                return;
            }
            path.push_back(current);
        }

        cout << "Path from V" << start << " to V" << end << " (Distance: " << dist[start][end] << "): ";
        for (size_t i = 0; i < path.size(); i++) {
            cout << "V" << path[i];
            if (i < path.size() - 1) cout << " -> ";
        }
        cout << endl;
    }

    void printAllPaths() {
        cout << "\n=== All Shortest Paths ===" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && dist[i][j] != INF) {
                    printPath(i, j);
                }
            }
        }
    }

    void queryPath() {
        int start, end;
        cout << "\nEnter source vertex (0-" << V-1 << "): ";
        cin >> start;
        cout << "Enter destination vertex (0-" << V-1 << "): ";
        cin >> end;

        if (start < 0 || start >= V || end < 0 || end >= V) {
            cout << "Invalid vertices!" << endl;
            return;
        }

        printPath(start, end);
    }
};

void runFloydWarshall(FloydWarshall& fw) {
    cout << "\nComputing shortest paths..." << endl;
    if (fw.computeShortestPaths()) {
        fw.printDistanceMatrix();
        
        char choice;
        cout << "\nDo you want to see all paths? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            fw.printAllPaths();
        }

        while (true) {
            cout << "\nQuery specific path? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') break;
            fw.queryPath();
        }
    } else {
        cout << "Graph contains a **negative weight cycle**!" << endl;
    }
}

void usePredefinedGraph() {
    vector<vector<long long>> graph = {
        {0, 3, 8, INF, -4, INF, INF, INF},
        {INF, 0, INF, 1, 7, INF, INF, INF},
        {INF, 4, 0, INF, INF, INF, 2, INF},
        {2, INF, -5, 0, INF, INF, INF, INF},
        {INF, INF, INF, 6, 0, 5, INF, 3},
        {INF, INF, INF, INF, INF, 0, 1, 8},
        {INF, INF, 3, INF, INF, INF, 0, -2},
        {INF, INF, INF, INF, INF, INF, INF, 0}
    };

    int V = graph.size();
    FloydWarshall fw(V);
    fw.setGraph(graph);
    runFloydWarshall(fw);
}

void useCustomGraph() {
    int V;
    cout << "Enter number of vertices: ";
    if (!(cin >> V) || V <= 0) {
        cout << "Invalid number of vertices." << endl;
        return;
    }

    FloydWarshall fw(V);
    fw.inputGraph();
    runFloydWarshall(fw);
}

// **New method for file input**
void useFileGraph() {
    string filename;
    cout << "Enter the filename (e.g., graph.txt): ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "**Error:** Could not open file: " << filename << endl;
        return;
    }

    int V;
    if (!(file >> V) || V <= 0) {
        cout << "**Error:** Invalid or missing number of vertices in the first line." << endl;
        return;
    }

    FloydWarshall fw(V);
    vector<vector<long long>> graph(V, vector<long long>(V));
    string line;
    
    // Consume the rest of the first line after reading V
    getline(file, line); 

    for (int i = 0; i < V; i++) {
        if (!getline(file, line)) {
            cout << "**Error:** File ended unexpectedly. Expected " << V << " rows for the matrix." << endl;
            return;
        }
        stringstream ss(line);
        for (int j = 0; j < V; j++) {
            long long weight;
            if (!(ss >> weight)) {
                cout << "**Error:** Missing weight at row " << i << ", column " << j << "." << endl;
                return;
            }
            graph[i][j] = weight;
        }
    }

    cout << "\nGraph loaded successfully from " << filename << endl;
    fw.setGraph(graph);
    runFloydWarshall(fw);
}

int main() {
    cout << "=======================================" << endl;
    cout << "  Floyd-Warshall Algorithm" << endl;
    cout << "  All-to-All Shortest Paths" << endl;
    cout << "=======================================" << endl;

    int choice;
    cout << "\nChoose input method:" << endl;
    cout << "1. Use predefined graph (8 vertices)" << endl;
    cout << "2. Input custom graph from console" << endl;
    cout << "**3. Input custom graph from text file**" << endl; // New option
    cout << "Enter choice (1, 2, or 3): ";
    
    if (!(cin >> choice)) {
        cout << "Invalid input for choice." << endl;
        return 1;
    }

    switch (choice) {
        case 1:
            usePredefinedGraph();
            break;
        case 2:
            useCustomGraph();
            break;
        case 3:
            useFileGraph(); // Call the new function
            break;
        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}