#include <iostream>
#include <fstream> // Required for file operations
#include <sstream> // Required for parsing lines
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

#define INF INT_MAX

class TSP {
private:
    int n;
    vector<vector<int>> dist;
    vector<int> bestPath;
    int minCost;

    void bruteForce(vector<int>& path, vector<bool>& visited, int count, int cost, int pos) {
        // Base case: All cities have been visited
        if (count == n) {
            // Check if a path back to the starting city (0) exists
            if (dist[pos][0] != INF) {
                int totalCost = cost + dist[pos][0];
                if (totalCost < minCost) {
                    minCost = totalCost;
                    bestPath = path;
                    bestPath.push_back(0); // Complete the cycle
                }
            }
            return;
        }

        // Recursive step: Try every unvisited city
        for (int i = 1; i < n; i++) {
            if (!visited[i] && dist[pos][i] != INF) {
                visited[i] = true;
                path.push_back(i);
                bruteForce(path, visited, count + 1, cost + dist[pos][i], i);
                path.pop_back(); // Backtrack
                visited[i] = false; // Backtrack
            }
        }
    }

public:
    TSP(int cities) : n(cities), minCost(INF) {
        dist.resize(n, vector<int>(n));
        bestPath.clear();
    }

    void inputGraph() {
        cout << "\nEnter distance matrix (use " << INF << " for no direct path):\n";
        for (int i = 0; i < n; i++) {
            cout << "City " << i << ": ";
            for (int j = 0; j < n; j++) {
                cin >> dist[i][j];
            }
        }
    }

    void setGraph(const vector<vector<int>>& graph) {
        dist = graph;
    }

    void solve() {
        vector<int> path = {0};
        vector<bool> visited(n, false);
        visited[0] = true;
        
        cout << "\nSolving TSP using Brute Force...\n";
        // The brute force approach calculates (n-1)! permutations
        bruteForce(path, visited, 1, 0, 0);
    }

    void displayResult() {
        if (minCost == INF) {
            cout << "\nNo valid tour exists!\n";
            return;
        }

        cout << "\n========== TSP SOLUTION ==========\n";
        cout << "Optimal Tour: ";
        for (size_t i = 0; i < bestPath.size(); i++) {
            cout << bestPath[i];
            if (i < bestPath.size() - 1) cout << " -> ";
        }
        cout << "\n\nTotal Distance: " << minCost << "\n";
        
        cout << "\nDetailed Path:\n";
        for (size_t i = 0; i < bestPath.size() - 1; i++) {
            cout << "  City " << bestPath[i] << " to City " << bestPath[i+1] 
                  << " : " << dist[bestPath[i]][bestPath[i+1]] << "\n";
        }
        cout << "==================================\n";
    }

    void displayGraph() {
        cout << "\n=== Distance Matrix ===\n";
        cout << "     ";
        for (int i = 0; i < n; i++) {
            cout << setw(6) << "C" + to_string(i);
        }
        cout << endl;
        cout << string(6 + n * 6, '-') << endl;

        for (int i = 0; i < n; i++) {
            cout << "C" << i << " | ";
            for (int j = 0; j < n; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(6) << "INF";
                } else {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << endl;
        }
    }
};

void runTSP(TSP& tsp) {
    tsp.displayGraph();
    tsp.solve();
    tsp.displayResult();
}

void testCase1() {
    cout << "\n### TEST CASE 1: 6 Cities ###\n";
    
    vector<vector<int>> graph = {
        {0, 10, 15, 20, 25, 30},
        {10, 0, 35, 25, 30, 20},
        {15, 35, 0, 30, 20, 25},
        {20, 25, 30, 0, 15, 35},
        {25, 30, 20, 15, 0, 10},
        {30, 20, 25, 35, 10, 0}
    };

    TSP tsp(6);
    tsp.setGraph(graph);
    runTSP(tsp);
}

void testCase2() {
    cout << "\n### TEST CASE 2: 7 Cities (Asymmetric) ###\n";
    
    vector<vector<int>> graph = {
        {0, 12, 10, INF, INF, INF, 12},
        {12, 0, 8, 12, INF, INF, INF},
        {10, 8, 0, 11, 3, INF, 9},
        {INF, 12, 11, 0, 11, 10, INF},
        {INF, INF, 3, 11, 0, 6, 7},
        {INF, INF, INF, 10, 6, 0, 9},
        {12, INF, 9, INF, 7, 9, 0}
    };

    TSP tsp(7);
    tsp.setGraph(graph);
    runTSP(tsp);
}

void testCase3() {
    cout << "\n### TEST CASE 3: 8 Cities (Dense Graph) ###\n";
    
    vector<vector<int>> graph = {
        {0, 20, 42, 25, 30, 50, 45, 35},
        {20, 0, 30, 34, 40, 55, 60, 25},
        {42, 30, 0, 12, 10, 25, 20, 45},
        {25, 34, 12, 0, 15, 30, 35, 40},
        {30, 40, 10, 15, 0, 20, 25, 50},
        {50, 55, 25, 30, 20, 0, 10, 60},
        {45, 60, 20, 35, 25, 10, 0, 55},
        {35, 25, 45, 40, 50, 60, 55, 0}
    };

    TSP tsp(8);
    tsp.setGraph(graph);
    runTSP(tsp);
}

void customInput() {
    int n;
    cout << "\nEnter number of cities: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of cities." << endl;
        return;
    }

    TSP tsp(n);
    tsp.inputGraph();
    runTSP(tsp);
}

// 🆕 New function for file input
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

    TSP tsp(V);
    vector<vector<int>> graph(V, vector<int>(V));
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
            int weight;
            if (!(ss >> weight)) {
                cout << "**Error:** Missing weight at row " << i << ", column " << j << "." << endl;
                return;
            }
            graph[i][j] = weight;
        }
    }

    cout << "\nGraph loaded successfully from " << filename << endl;
    tsp.setGraph(graph);
    runTSP(tsp);
}

int main() {
    cout << "============================================\n";
    cout << "  TRAVELLING SALESMAN PROBLEM SOLVER\n";
    cout << "  (Exact Solution using Brute Force)\n";
    cout << "============================================\n";

    int choice;
    cout << "\nSelect option:\n";
    cout << "1. Test Case 1 (6 cities - Symmetric)\n";
    cout << "2. Test Case 2 (7 cities - Asymmetric with INF)\n";
    cout << "3. Test Case 3 (8 cities - Dense Graph)\n";
    cout << "4. Custom Input (Console)\n";
    cout << "**5. Custom Input (Text File)**\n"; // New option
    cout << "6. Run All Test Cases\n";
    cout << "Enter choice: ";
    
    if (!(cin >> choice)) {
        cout << "Invalid input for choice." << endl;
        return 1;
    }

    switch (choice) {
        case 1:
            testCase1();
            break;
        case 2:
            testCase2();
            break;
        case 3:
            testCase3();
            break;
        case 4:
            customInput();
            break;
        case 5:
            useFileGraph(); // Call the new function
            break;
        case 6:
            testCase1();
            testCase2();
            testCase3();
            break;
        default:
            cout << "Invalid choice!\n";
    }

    return 0;
}