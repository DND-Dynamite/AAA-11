// Given a 3×3 board with 8 tiles (each numbered from 1 to 8) and one empty space,
// the objective is to place the numbers to match the final configuration using the
// empty space. We can slide four adjacent tiles (left, right, above, and below) into
// the empty space.

// Limitations of DFS and BFS in the 8-Puzzle Problem
// DFS: Can get stuck in deep, unproductive paths, leading to excessive memory usage and slow performance.
// BFS: Explores all nodes at the current depth level, making it inefficient as it does not prioritize promising paths.
// Optimizing with Branch and Bound (B&B)
// Branch and Bound enhances search efficiency by using a cost function to guide exploration.

// Intelligent Node Selection: Prioritizes nodes closer to the goal, unlike DFS (blind) or BFS (equal priority).
// Pruning: Eliminates unpromising paths to save time and memory.

// Approach:
// Use a priority queue to store live nodes.
// Initialize the cost function for the root node.
// Expand the least-cost node first.
// Stop when a goal state is reached or when the queue is empty.
// Types of Nodes in B&B:
// Live Node: Generated but not yet explored.
// E-node (Expanding Node): Currently being expanded.
// Dead Node: No longer considered (either solution found or cost too high).
// Cost Function for 8-Puzzle
// C(X) = g(X) + h(X)C(X) = g(X) + h(X)

// Where:

// g(X) = Moves taken to reach the current state.
// h(X) = Number of misplaced tiles.
// Only nodes with the lowest cost function value are expanded, ensuring an optimal path.

#include <iostream>
#include <queue>
#include <climits>
#include <cstring>

using namespace std;
#define N 3

// State space tree node
struct Node
{
    Node *parent;
    int mat[N][N];
    int x, y;
    int cost;
    int level;
};

// Function to print N x N matrix
void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }
}

// Function to allocate a new node
Node *newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node *parent)
{
    Node *node = new Node;
    if (!node)
    {
        cout << "Memory allocation failed" << endl;
        exit(1);
    }

    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]); // Swap blank tile
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}

// Bottom, left, top, right movement
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Function to calculate misplaced tiles
int calculateCost(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                count++;
    return count;
}

// Function to check if coordinates are valid
bool isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Print path from root node to destination node
void printPath(Node *root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    cout << endl;
}

// Custom comparison object for priority queue
struct comp
{
    bool operator()(const Node *lhs, const Node *rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

// Function to solve the 8-puzzle using Branch and Bound
void solve(int initial[N][N], int x, int y, int final[N][N])
{
    priority_queue<Node *, vector<Node *>, comp> pq;
    Node *root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    pq.push(root);

    while (!pq.empty())
    {
        Node *min = pq.top();
        pq.pop();

        // If final state is reached, print the solution path
        if (min->cost == 0)
        {
            printPath(min);
            return;
        }

        // Generate all possible child nodes
        for (int i = 0; i < 4; i++)
        {
            int newX = min->x + row[i], newY = min->y + col[i];
            if (isSafe(newX, newY))
            {
                Node *child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq.push(child);
            }
        }

        // Free the memory of explored node
        delete min;
    }
}

// Driver Code
int main()
{
    // Initial configuration
    int initial[N][N] = {
        {1, 0, 2},
        {3, 4, 5},
        {6, 7, 8}};

    // Solvable Final configuration
    int final[N][N] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8}};

    // Blank tile coordinates in initial configuration
    int x = 0, y = 1;

    solve(initial, x, y, final);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cout << initial[i][j] << " ";
        cout << endl;
    
    return 0;
}