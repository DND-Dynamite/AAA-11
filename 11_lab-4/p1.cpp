#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For std::fixed and std::setprecision

// Structure to represent an item with its weight, value, and value-to-weight ratio.
struct Item {
    int weight;
    int value;
    double ratio;
    int id; // To keep track of the original item number
};

/**
 * @brief Comparison function to sort items in descending order of their value-to-weight ratio.
 * This is the core of the greedy strategy. We prioritize items that give the most value per unit of weight.
 * @param a The first item to compare.
 * @param b The second item to compare.
 * @return True if item 'a' has a higher or equal ratio than item 'b', false otherwise.
 */
bool compareItems(const Item& a, const Item& b) {
    return a.ratio > b.ratio;
}

/**
 * @brief Solves the Fractional Knapsack problem using a greedy approach.
 * @param capacity The maximum weight the knapsack can hold.
 * @param items A vector of items available to be placed in the knapsack.
 * @return The maximum possible value that can be obtained.
 */
double fractionalKnapsack(int capacity, std::vector<Item>& items) {
    // Sort items based on value-to-weight ratio in descending order.
    std::sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    int currentWeight = 0;

    std::cout << "\n----------------------------------------\n";
    std::cout << "Processing items in greedy order (by highest value/weight ratio):\n";
    std::cout << "----------------------------------------\n";

    // Iterate through the sorted items and add them to the knapsack.
    for (const auto& item : items) {
        // If the item can be fully added without exceeding capacity
        if (currentWeight + item.weight <= capacity) {
            currentWeight += item.weight;
            totalValue += item.value;
            std::cout << "Took entire Item " << item.id << " (Weight: " << item.weight << ", Value: " << item.value << ")\n";
        } else {
            // If only a fraction of the item can fit
            int remainingWeight = capacity - currentWeight;
            if (remainingWeight > 0) {
                // Calculate the value of the fraction of the item and add it
                double fractionalValue = item.ratio * remainingWeight;
                totalValue += fractionalValue;
                std::cout << "Took a fraction of Item " << item.id << " (Weight: " << remainingWeight << ", Value: " << fractionalValue << ")\n";
            }
            // Knapsack is now full, so we can stop.
            break; 
        }
    }

    return totalValue;
}

int main() {
    int numItems;
    int knapsackCapacity;

    // --- User Input Section ---
    std::cout << "--- Fractional Knapsack Problem Solver ---\n\n";
    
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

        // Calculate the value-to-weight ratio
        if (items[i].weight > 0) {
            items[i].ratio = static_cast<double>(items[i].value) / items[i].weight;
        } else {
            items[i].ratio = 0; // Avoid division by zero
        }
    }

    // --- Calculation and Output ---
    double maxValue = fractionalKnapsack(knapsackCapacity, items);

    std::cout << "\n----------------------------------------\n";
    // Set precision for floating point output to 2 decimal places
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Maximum value in knapsack = " << maxValue << std::endl;
    std::cout << "----------------------------------------\n";

    return 0;
}

