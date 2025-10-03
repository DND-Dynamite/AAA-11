#include <iostream>
#include <vector>
#include <algorithm>

// Structure to represent an item with its weight and value.
struct Item {
    int weight;
    int value;
    int id; // To keep track of the original item number
};

/**
 * @brief Solves the 0/1 Knapsack problem using dynamic programming.
 * @param capacity The maximum weight the knapsack can hold.
 * @param items A vector of items available to be placed in the knapsack.
 * @param numItems The total number of items.
 * @return The maximum possible value that can be obtained.
 */
int zeroOneKnapsack(int capacity, const std::vector<Item>& items, int numItems) {
    // Create a DP table. dp[i][w] will be the maximum value that can be
    // obtained with a knapsack of capacity 'w' using the first 'i' items.
    std::vector<std::vector<int>> dp(numItems + 1, std::vector<int>(capacity + 1, 0));

    // Build the table dp[][] in a bottom-up manner.
    for (int i = 1; i <= numItems; ++i) {
        for (int w = 1; w <= capacity; ++w) {
            // Get the current item's weight and value.
            // i-1 because vector is 0-indexed and our loop is 1-indexed.
            int currentWeight = items[i - 1].weight;
            int currentValue = items[i - 1].value;

            // If the current item's weight is less than or equal to the current capacity 'w'
            if (currentWeight <= w) {
                // We have two choices:
                // 1. Include the current item: its value + value from remaining capacity.
                // 2. Don't include the current item: value from the previous state.
                // We take the maximum of these two choices.
                dp[i][w] = std::max(currentValue + dp[i - 1][w - currentWeight], dp[i - 1][w]);
            } else {
                // If the current item is heavier than the capacity 'w', we can't include it.
                // So, the value is the same as the value from the previous state.
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // The final answer is in the bottom-right cell of the DP table.
    return dp[numItems][capacity];
}

int main() {
    int numItems;
    int knapsackCapacity;

    // --- User Input Section ---
    std::cout << "--- 0/1 Knapsack Problem Solver ---\n\n";

    std::cout << "Enter the number of items: ";
    std::cin >> numItems;

    std::cout << "Enter the capacity of the knapsack: ";
    std::cin >> knapsackCapacity;

    std::vector<Item> items(numItems);
    std::cout << "\nEnter the weight and value for each item:\n";
    for (int i = 0; i < numItems; ++i) {
        items[i].id = i + 1;
        std::cout << "Item " << items[i].id << " Weight: ";
        std::cin >> items[i].weight;
        std::cout << "Item " << items[i].id << " Value:  ";
        std::cin >> items[i].value;
    }

    // --- Calculation and Output ---
    int maxValue = zeroOneKnapsack(knapsackCapacity, items, numItems);

    std::cout << "\n----------------------------------------\n";
    std::cout << "Maximum value in knapsack = " << maxValue << std::endl;
    std::cout << "----------------------------------------\n";

    return 0;
}


