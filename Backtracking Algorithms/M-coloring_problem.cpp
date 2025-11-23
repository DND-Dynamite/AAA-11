#include <iostream>
#include <vector>
using namespace std;

// Given an edges of graph and a number m, the your task is to check it is possible to
// color the given graph with at most m colors such that no two adjacent vertices of
// the graph are colored with the same color

bool goodcolor(const vector<vector<int>> &adj, const vector<int> &col)
{

    for (int i = 0; i < col.size(); i++)
    {
        for (auto it : adj[i])
        {
            if (i != it && col[i] == col[it])
                return false;
        }
    }
    return true;
}

bool genratecolor(int i, vector<int> &col, int m, const vector<vector<int>> &adj)
{
    if (i >= col.size())
    {
        if (goodcolor(adj, col))
            return true;

        return false;
    }

    for (int j = 0; j < m; j++)
    {
        col[i] = j;
        if (genratecolor(i + 1, col, m, adj))
            return true;
        col[i] = -1;
    }
    return false;
}

bool graphColoring(int v, vector<vector<int>> &edges, int m)
{
    vector<vector<int>> adj(v);

    // Build adjacency list from edges
    for (auto it : edges)
    {
        adj[it[0]].push_back(it[1]);
        adj[it[1]].push_back(it[0]);
    }

    vector<int> color(v, -1);
    return genratecolor(0, color, m, adj);
}

int main()
{
    int V = 4;
    vector<vector<int>> edges = {{0, 1}, {0, 2}, {0, 3}, {1, 3}, {2, 3}};
    int m = 3;

    // Check if the graph can be colored with m colors
    // such that no adjacent nodes share the same color
    cout << (graphColoring(V, edges, m) ? "true" : "false") << endl;

    return 0;
}