// The task is to generate a binary string of length N using branch and bound technique Examples:

// Input: N = 3 Output: 000 001 010 011 100 101 110 111 Explanation: 
// Numbers with 3 binary digits are 0, 1, 2, 3, 4, 5, 6, 7 Input: N = 2 Output: 00 01 10 11



// Approach: Generate Combinations using Branch and Bound :

// It starts with an empty solution vector.
// While Queue is not empty remove partial vector from queue.
// If it is a final vector print the combination else,
// For the next component of partial vector create k child vectors by fixing all possible states for the next component insert vectors into the queue.


// CPP Program to generate
// Binary Strings using Branch and Bound
#include <iostream>
#include <queue>

using namespace std;

// Creating a Node class
class Node
{
public:
    int *soln;
    int level;
    vector<Node *> child;
    Node *parent;

    Node(Node *parent, int level, int N)
    {
        this->parent = parent;
        this->level = level;
        this->soln = new int[N];
    }
};

// Utility function to generate binary strings of length n
void generate(Node *n, int &N, queue<Node *> &Q)
{
    // If list is full print combination
    if (n->level == N)
    {
        for (int i = 0; i < N; i++)
            cout << n->soln[i];
        cout << endl;
    }
    else
    {
        int l = n->level;

        // iterate while length is not equal to n
        for (int i = 0; i <= 1; i++)
        {
            Node *x = new Node(n, l + 1, N);
            for (int k = 0; k < l; k++)
                x->soln[k] = n->soln[k];
            x->soln[l] = i;
            n->child.push_back(x);
            Q.push(x);
        }
    }
}

// Driver Code
int main()
{
    // Initiate Generation
    // Create a root Node
    int N = 3;
    Node *root;
    root = new Node(NULL, 0, N);

    // Queue that maintains the list of live Nodes
    queue<Node *> Q;
    
    // Instantiate the Queue
    Q.push(root);

    while (!Q.empty())
    {
        Node *E = Q.front();
        Q.pop();
        generate(E, N, Q);
    }

    return 0;
}