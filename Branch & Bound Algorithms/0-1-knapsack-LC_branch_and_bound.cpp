// Problem Statement:

// Given N items with weights W[0..n-1], values V[0..n-1] and a knapsack with capacity C,
// select the items such that: 
 

// The sum of weights taken into the knapsack is less than or equal to C.
// The sum of values of the items in the knapsack is maximum among all the possible 
// combinations.

// Branch and Bound can be solved using FIFO, LIFO and LC strategies.
// The least cost(LC) is considered the most intelligent as it selects the next node
// based on a Heuristic Cost Function. It picks the one with the least cost

// Follow the steps below to solve the problem: 
 

// 1. Sort the items based on their value/weight(V/W) ratio.
// 2. Insert a dummy node into the priority queue.
// 3. Repeat the following steps until the priority queue is empty:
// 4. Extract the peek element from the priority queue and assign it to the current node.
// 5. If the upper bound of the current node is less than minLB, the minimum lower bound of all the nodes explored, then there is no point of exploration. So, continue with the next element. The reason for not considering the nodes whose upper bound is greater than minLB is that, the upper bound stores the best value that might be achieved. If the best value itself is not optimal than minLB, then exploring that path is of no use. 
 
// Update the path array.

// If the current node’s level is N, then check whether the lower bound of the current node
// is less than finalLB, minimum lower bound of all the paths that reached the final level.
// If it is true, update the finalPath and finalLB. Otherwise, continue with the next element.

// Calculate the lower and upper bounds of the right child of the current node.

// If the current item can be inserted into the knapsack, then calculate the lower
// and upper bound of the left child of the current node.

// Update the minLB and insert the children if their upper bound is less than minLB


#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

// Class to represent an item
class Item {
public:
    float weight;
    int value;
    int idx;

    // Constructor to initialize an item
    Item(int value, float weight, int idx) : value(value), weight(weight), idx(idx) {}
};

// Class to represent a node in the branch and bound algorithm
class Node {
public:
    float ub;    // Upper bound
    float lb;    // Lower bound
    int level;   // Level in the decision tree
    bool flag;   // Flag to indicate if the item is selected or not
    float tv;    // Total value of selected items
    float tw;    // Total weight of selected items

    // Default constructor
    Node() {}

    // Copy constructor
    Node(const Node& cpy) : tv(cpy.tv), tw(cpy.tw), ub(cpy.ub), lb(cpy.lb), level(cpy.level), flag(cpy.flag) {}
};

// Comparator to sort nodes based on lower bound
class sortByC {
public:
    bool operator()(const Node& a, const Node& b) const {
        return a.lb > b.lb;
    }
};

// Comparator to sort items based on value/weight ratio
class sortByRatio {
public:
    bool operator()(const Item& a, const Item& b) const {
        return static_cast<float>(a.value) / a.weight > static_cast<float>(b.value) / b.weight;
    }
};

// Function to assign values to a node
void assign(Node& a, float ub, float lb, int level, bool flag, float tv, float tw) {
    a.ub = ub;
    a.lb = lb;
    a.level = level;
    a.flag = flag;
    a.tv = tv;
    a.tw = tw;
}

// Function to calculate the upper bound (best case) considering fractional knapsack
float upperBound(float tv, float tw, int idx, Item arr[], int size, float capacity) {
    float value = tv;
    float weight = tw;

    // Iterate over the remaining items and add them to the knapsack if possible
    for (int i = idx; i < size; i++) {
        if (weight + arr[i].weight <= capacity) {
            weight += arr[i].weight;
            value -= arr[i].value;
        } else {
            // If the remaining capacity is not enough for the entire item, add a fraction of it
            value -= static_cast<float>(capacity - weight) / arr[i].weight * arr[i].value;
            break;
        }
    }
    return value;
}

// Function to calculate the lower bound (worst case) without considering fractional part of items
float lowerBound(float tv, float tw, int idx, Item arr[], int size, float capacity) {
    float value = tv;
    float weight = tw;

    // Iterate over the remaining items and add them to the knapsack if possible
    for (int i = idx; i < size; i++) {
        if (weight + arr[i].weight <= capacity) {
            weight += arr[i].weight;
            value -= arr[i].value;
        } else {
            break;
        }
    }
    return value;
}

// Function to solve the 0/1 knapsack problem using branch and bound
void solve(Item arr[], int size, float capacity) {
    // Sort the items based on the value/weight ratio
    sort(arr, arr + size, sortByRatio());

    // Initialize nodes
    Node current, left, right;
    current.tv = current.tw = current.ub = current.lb = 0;
    current.level = 0;
    current.flag = false;

    float minLB = 0, finalLB = numeric_limits<float>::max();
    current.tv = current.tw = current.ub = current.lb = 0;
    current.level = 0;
    current.flag = false;

    // Priority queue to store nodes based on lower bounds
    priority_queue<Node, vector<Node>, sortByC> pq;
    pq.push(current);

    // Arrays to store the current and final selection of items
    bool* currPath = new bool[size];
    bool* finalPath = new bool[size];

    // Explore nodes in the priority queue
    while (!pq.empty()) {
        current = pq.top();
        pq.pop();

        // Prune if the upper bound is greater than the minimum lower bound
        if (current.ub > minLB || current.ub >= finalLB) {
            continue;
        }

        // Store the selection if it reaches the final level
        if (current.level != 0)
            currPath[current.level - 1] = current.flag;

        // Check if it's the last level and update the final selection if the lower bound is better
        if (current.level == size) {
            if (current.lb < finalLB) {
                for (int i = 0; i < size; i++)
                    finalPath[arr[i].idx] = currPath[i];
                finalLB = current.lb;
            }
            continue;
        }

        int level = current.level;

        // Explore the right node (exclude current item)
        assign(right, upperBound(current.tv, current.tw, level + 1, arr, size, capacity),
               lowerBound(current.tv, current.tw, level + 1, arr, size, capacity),
               level + 1, false, current.tv, current.tw);

        // Explore the left node (include current item)
        if (current.tw + arr[current.level].weight <= capacity) {
            left.ub = upperBound(current.tv - arr[level].value, current.tw + arr[level].weight, level + 1, arr, size, capacity);
            left.lb = lowerBound(current.tv - arr[level].value, current.tw + arr[level].weight, level + 1, arr, size, capacity);
            assign(left, left.ub, left.lb, level + 1, true, current.tv - arr[level].value, current.tw + arr[level].weight);
        } else {
            // If the left node cannot be inserted, stop it from getting added to the priority queue
            left.ub = left.lb = 1;
        }

        // Update minLB
        minLB = min(minLB, left.lb);
        minLB = min(minLB, right.lb);

        // Add nodes to the priority queue if their upper bounds are less than minLB
        if (minLB >= left.ub)
            pq.push(left);
        if (minLB >= right.ub)
            pq.push(right);
    }

    // Print the final result
    cout << "Items taken into the knapsack are\n";
    for (int i = 0; i < size; i++) {
        if (finalPath[i])
            cout << "1 ";
        else
            cout << "0 ";
    }
    cout << "\nMaximum profit is " << -finalLB << endl;
    delete[] currPath;
    delete[] finalPath;
}

// Main function
int main() {
    int size = 4;
    float capacity = 15;

    // Create an array of items
    Item arr[] = {Item(10, 2, 0), Item(10, 4, 1), Item(12, 6, 2), Item(18, 9, 3)};

    // Call the solve function to solve the knapsack problem
    solve(arr, size, capacity);

    return 0;
}