// You are the head of a company with n employees and n distinct jobs to be completed.
// Every employee takes a different amount of time to complete different jobs,
// given in the form of a cost[][] matrix, where cost[i][j] represents the time taken by
// the ith person to complete the jth job. Your task is to assign the jobs in such a way 
// that the total time taken by all employees is minimized.

// In both Breadth-First Search (BFS) and Depth-First Search (DFS),
// the selection of the next node to explore is blind—that is,
// it does not prioritize nodes that are more likely to lead to an optimal solution.
// These uninformed strategies treat all nodes equally, 
// without considering their potential to reach the goal efficiently.

// To overcome this limitation, we can use an informed search strategy that leverages an
// intelligent ranking function, often referred to as an approximate cost function.
// This function helps guide the search process by assigning a cost to each live node,
// enabling the algorithm to avoid exploring subtrees unlikely to contain optimal solutions.
// This approach is similar to BFS, but instead of following the strict FIFO order,
// it selects the live node with the lowest estimated cost.

// Although this method does not guarantee the optimal solution,
//  it significantly increases the chances of finding a near-optimal solution faster by
//   focusing the search on more promising paths.

// There are two common approaches to estimate the cost function:

// Row-based Minimization: For each worker (row), select the minimum 
// cost job from the list of unassigned jobs (i.e., take the minimum entry from each row).

// Column-based Minimization: For each job (column), choose the worker with the 
// lowest cost from the list of unassigned workers (i.e., take the minimum entry from
// each column).

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// state space tree node
class Node {
public:
    // stores parent node of current node
    // helps in tracing path when answer is found
    Node *parent;

    // contains cost for ancestors nodes
    // including current node
    int pathCost;

    // contains least promising cost
    int cost;

    // contain worker number
    int workerID;

    // contains Job ID
    int jobID;

    // Boolean array assigned will contains
    // info about available jobs
    vector<bool> assigned;

    Node(int x, int y, vector<bool> assigned, Node *parent) {
        this->workerID = x;
        this->jobID = y;
        this->assigned = assigned;
        this->parent = parent;
        this->pathCost = 0;
        this->cost = 0;
    }
};

// Function to calculate the least promising cost
// of node after worker x is assigned to job y.
int calculateCost(vector<vector<int>> &costMat, int x, int y, vector<bool> &assigned) {
    int n = costMat.size();
    int cost = 0;

    // to store unavailable jobs
    vector<bool> available(n, true);

    // start from next worker
    for (int i = x + 1; i < n; i++) {
        int min = INT_MAX, minIndex = -1;

        // do for each job
        for (int j = 0; j < n; j++) {

            // if job is unassigned
            if (!assigned[j] && available[j] && costMat[i][j] < min) {

                // store job number
                minIndex = j;

                // store cost
                min = costMat[i][j];
            }
        }

        // add cost of next worker
        cost += min;

        // job becomes unavailable
        available[minIndex] = false;
    }

    return cost;
}

// Comparison object to be used to order the heap
struct comp {
    bool operator()(const Node *lhs, const Node *rhs) const {
        return lhs->cost > rhs->cost;
    }
};

// Finds minimum cost using Branch and Bound.
int findMinCost(vector<vector<int>> &costMat) {
    int n = costMat.size();

    // Create a priority queue to store
    // live nodes of search tree;
    priority_queue<Node *, vector<Node *>, comp> pq;

    // initialize heap to dummy node with cost 0
    vector<bool> assigned(n, false);
    Node *root = new Node(-1, -1, assigned, nullptr);
    root->pathCost = root->cost = 0;
    root->workerID = -1;

    // Add dummy node to list of live nodes;
    pq.push(root);

    while (!pq.empty()) {

        // Find a live node with least estimated cost
        Node *min = pq.top();

        // The found node is deleted from the list
        pq.pop();

        // i stores next worker
        int i = min->workerID + 1;

        // if all workers are assigned a job
        if (i == n) {
            return min->cost;
        }

        // do for each job
        for (int j = 0; j < n; j++) {

            // If unassigned
            if (!min->assigned[j]) {

                // create a new tree node
                Node *child = new Node(i, j, min->assigned, min);
                child->assigned[j] = true;

                // cost for ancestors nodes including current node
                child->pathCost = min->pathCost + costMat[i][j];

                // calculate its lower bound
                child->cost = child->pathCost + calculateCost(costMat, i, j, child->assigned);

                // Add child to list of live nodes;
                pq.push(child);
            }
        }
    }

    // will not be used
    return -1;
}

int main() {
    vector<vector<int>> costMat = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    cout << findMinCost(costMat);
    return 0;
}