#include <iostream>
#include <fstream>   // Required for file operations
#include <sstream>   // Required for parsing lines
#include <vector>
#include <algorithm>
#include <climits>
#include <iomanip>

using namespace std;

// Using INT_MAX for infinity, consistent with the original code
#define INF INT_MAX

struct Edge
{
    int src, dest, weight;
    // Overload the < operator to sort edges by weight
    bool operator<(const Edge &other) const
    {
        return weight < other.weight;
    }
};

class UnionFind
{
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int x, int y)
    {
        int px = find(x), py = find(y);
        if (px == py)
            return false;
        if (rank[px] < rank[py])
            swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py])
            rank[px]++;
        return true;
    }
};

class TSP_MST
{
private:
    int n;
    vector<vector<int>> dist;
    vector<Edge> mstEdges;
    vector<int> tour;
    int tourCost;

    void kruskalMST()
    {
        vector<Edge> edges;
        // Collect all edges (only i < j to avoid duplicates in this undirected context)
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                // Only consider edges with a finite weight
                if (dist[i][j] != INT_MAX)
                {
                    edges.push_back({i, j, dist[i][j]});
                }
            }
        }

        sort(edges.begin(), edges.end());
        UnionFind uf(n);
        mstEdges.clear();

        for (const Edge &e : edges)
        {
            if (uf.unite(e.src, e.dest))
            {
                mstEdges.push_back(e);
                if (mstEdges.size() == n - 1)
                    break;
            }
        }
    }

    // Preorder traversal (DFS) on the MST
    void dfs(int node, vector<vector<int>> &adj, vector<bool> &visited)
    {
        visited[node] = true;
        tour.push_back(node);

        for (int neighbor : adj[node])
        {
            if (!visited[neighbor])
            {
                dfs(neighbor, adj, visited);
            }
        }
    }

    void constructTour()
    {
        // Build adjacency list for the MST
        vector<vector<int>> adj(n);
        for (const Edge &e : mstEdges)
        {
            adj[e.src].push_back(e.dest);
            adj[e.dest].push_back(e.src);
        }

        vector<bool> visited(n, false);
        tour.clear();
        
        // Start DFS from City 0 (arbitrary start)
        dfs(0, adj, visited);
        
        // Complete the Hamiltonian Cycle by returning to the start city
        tour.push_back(0);

        // Calculate the cost of the constructed tour
        tourCost = 0;
        for (size_t i = 0; i < tour.size() - 1; i++)
        {
            tourCost += dist[tour[i]][tour[i + 1]];
        }
    }

public:
    TSP_MST(int cities) : n(cities), tourCost(0)
    {
        dist.resize(n, vector<int>(n));
    }

    void setGraph(const vector<vector<int>> &graph)
    {
        dist = graph;
    }

    void solve()
    {
        cout << "\nStep 1: Constructing MST using Kruskal's Algorithm...\n";
        kruskalMST();

        cout << "Step 2: Performing DFS (Preorder Traversal) on MST...\n";
        constructTour();

        cout << "Step 3: Forming Hamiltonian Cycle...\n";
    }

    void displayMST()
    {
        cout << "\n=== Minimum Spanning Tree ===\n";
        int mstWeight = 0;
        for (const Edge &e : mstEdges)
        {
            cout << "Edge: " << e.src << " -- " << e.dest
                 << "  Weight: " << e.weight << "\n";
            mstWeight += e.weight;
        }
        cout << "Total MST Weight: " << mstWeight << "\n";
    }

    void displayTour()
    {
        cout << "\n=== TSP Approximate Tour ===\n";
        cout << "Tour: ";
        for (size_t i = 0; i < tour.size(); i++)
        {
            cout << tour[i];
            if (i < tour.size() - 1)
                cout << " -> ";
        }
        cout << "\n\nTotal Tour Cost: " << tourCost << "\n";

        cout << "\nDetailed Path:\n";
        for (size_t i = 0; i < tour.size() - 1; i++)
        {
            cout << "  City " << tour[i] << " to City " << tour[i + 1]
                 << " : " << dist[tour[i]][tour[i + 1]] << "\n";
        }
    }

    void displayGraph()
    {
        cout << "\n=== Distance Matrix ===\n";
        cout << "     ";
        for (int i = 0; i < n; i++)
        {
            cout << setw(6) << "C" + to_string(i);
        }
        cout << "\n"
             << string(6 + n * 6, '-') << "\n";

        for (int i = 0; i < n; i++)
        {
            cout << "C" << i << " | ";
            for (int j = 0; j < n; j++)
            {
                if (dist[i][j] == INT_MAX)
                {
                    cout << setw(6) << "INF";
                }
                else
                {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << "\n";
        }
    }

    int getTourCost() const { return tourCost; }
};

// 🆕 New function to handle file input
void useFileGraph() {
    string filename;
    cout << "\nEnter the filename containing the graph data (e.g., graph.txt): ";
    cin >> filename;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "**Error:** Could not open file: " << filename << endl;
        return;
    }

    int n;
    // Read the number of cities (V) from the first line
    if (!(file >> n) || n <= 0) {
        cout << "**Error:** Invalid or missing number of cities in the first line." << endl;
        return;
    }

    if (n < 2) {
        cout << "**Error:** Number of cities must be at least 2!\n";
        return;
    }

    TSP_MST tsp(n);
    vector<vector<int>> graph(n, vector<int>(n));
    string line;
    
    // Consume the rest of the first line
    getline(file, line); 

    // Read the N x N matrix
    for (int i = 0; i < n; i++) {
        if (!getline(file, line)) {
            cout << "**Error:** File ended unexpectedly. Expected " << n << " rows for the matrix." << endl;
            return;
        }
        stringstream ss(line);
        for (int j = 0; j < n; j++) {
            int weight;
            if (!(ss >> weight)) {
                cout << "**Error:** Missing weight at row " << i << ", column " << j << "." << endl;
                return;
            }
            graph[i][j] = weight;
        }
    }

    cout << "\nGraph loaded successfully from " << filename << " (" << n << " cities)." << endl;
    
    tsp.setGraph(graph);
    tsp.displayGraph();

    cout << "\n================================================\n";
    cout << "Solving TSP using MST-based 2-Approximation...\n";
    cout << "================================================\n";

    tsp.solve();
    tsp.displayMST();
    tsp.displayTour();
}

void testCase1() {
    cout << "\n########## TEST CASE 1: 6 Cities ##########\n";

    vector<vector<int>> graph = {
        {0, 10, 15, 20, 25, 30},
        {10, 0, 35, 25, 30, 20},
        {15, 35, 0, 30, 20, 25},
        {20, 25, 30, 0, 15, 35},
        {25, 30, 20, 15, 0, 10},
        {30, 20, 25, 35, 10, 0}};

    TSP_MST tsp(6);
    tsp.setGraph(graph);
    tsp.displayGraph();
    tsp.solve();
    tsp.displayMST();
    tsp.displayTour();
}

void testCase2() {
    cout << "\n########## TEST CASE 2: 8 Cities ##########\n";

    vector<vector<int>> graph = {
        {0, 20, 42, 25, 30, 50, 45, 35},
        {20, 0, 30, 34, 40, 55, 60, 25},
        {42, 30, 0, 12, 10, 25, 20, 45},
        {25, 34, 12, 0, 15, 30, 35, 40},
        {30, 40, 10, 15, 0, 20, 25, 50},
        {50, 55, 25, 30, 20, 0, 10, 60},
        {45, 60, 20, 35, 25, 10, 0, 55},
        {35, 25, 45, 40, 50, 60, 55, 0}};

    TSP_MST tsp(8);
    tsp.setGraph(graph);
    tsp.displayGraph();
    tsp.solve();
    tsp.displayMST();
    tsp.displayTour();
}

void testCase3() {
    cout << "\n########## TEST CASE 3: 10 Cities ##########\n";

    vector<vector<int>> graph = {
        {0, 29, 20, 21, 16, 31, 100, 12, 4, 31},
        {29, 0, 15, 29, 28, 40, 72, 21, 29, 41},
        {20, 15, 0, 15, 14, 25, 81, 9, 23, 27},
        {21, 29, 15, 0, 4, 12, 92, 12, 25, 13},
        {16, 28, 14, 4, 0, 16, 94, 9, 20, 16},
        {31, 40, 25, 12, 16, 0, 95, 24, 36, 3},
        {100, 72, 81, 92, 94, 95, 0, 90, 101, 99},
        {12, 21, 9, 12, 9, 24, 90, 0, 15, 25},
        {4, 29, 23, 25, 20, 36, 101, 15, 0, 35},
        {31, 41, 27, 13, 16, 3, 99, 25, 35, 0}};

    TSP_MST tsp(10);
    tsp.setGraph(graph);
    tsp.displayGraph();
    tsp.solve();
    tsp.displayMST();
    tsp.displayTour();
}

void runTests() {
    testCase1();
    testCase2();
    testCase3();
}

void customInput() {
    int n;
    cout << "\nEnter number of cities: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid number of cities." << endl;
        return;
    }
    if (n < 2) {
        cout << "Number of cities must be at least 2!\n";
        return;
    }

    TSP_MST tsp(n);
    vector<vector<int>> graph(n, vector<int>(n));

    cout << "\nEnter distance matrix (" << n << "x" << n << "):\n";
    cout << "(Enter distance from city i to city j)\n";

    for (int i = 0; i < n; i++) {
        cout << "Row " << i << " (distances from City " << i << "): ";
        for (int j = 0; j < n; j++) {
            if (!(cin >> graph[i][j])) {
                 cout << "**Error:** Invalid input. Aborting.\n";
                 return;
            }
        }
    }

    tsp.setGraph(graph);
    tsp.displayGraph();

    cout << "\n================================================\n";
    cout << "Solving TSP using MST-based 2-Approximation...\n";
    cout << "================================================\n";

    tsp.solve();
    tsp.displayMST();
    tsp.displayTour();
}

int main()
{
    cout << "================================================\n";
    cout << "  TSP APPROXIMATION USING MST\n";
    cout << "  (2-Approximation Algorithm)\n";
    cout << "================================================\n";

    int choice;
    cout << "\nChoose input method:\n";
    cout << "1. Run Predefined Test Cases (6, 8, and 10 cities)\n";
    cout << "2. Custom Input (Console)\n";
    cout << "**3. Custom Input (Text File)**\n"; // New option
    cout << "Enter choice (1, 2, or 3): ";

    if (!(cin >> choice)) {
        cout << "Invalid input for choice.\n";
        return 1;
    }

    switch (choice) {
        case 1:
            runTests();
            break;
        case 2:
            customInput();
            break;
        case 3:
            useFileGraph();
            break;
        default:
            cout << "Invalid choice!\n";
    }

    return 0;
}