// Given an array prices[] of n different candies, where prices[i] represents the price of the ith candy and all prices are distinct. The store has an offer where for every candy you buy, you can get up to k other different candies for free. Find the minimum and maximum amount of money needed to buy all the candies.
// Note: In both cases, you must take the maximum number of free candies possible during each purchase.

// Examples: 

// Input: prices[] = [3, 2, 1, 4], k = 2
// Output: [3, 7]
// Explanation: For minimum cost, buy the candies costing 1 and 2. for maximum cost, buy the candies costing 4 and 3.

// Input: prices[] = [3, 2, 1, 4, 5], k = 4
// Output: [1, 5]
// Explanation: For minimum cost, buy the candy costing 1. for maximum cost, buy the candy costing 5.

// Step By Step Implementations:

// Sort the prices array in ascending order to access the cheapest and most expensive candies easily.
// For minimum cost
// -> use a pointer i starting from the beginning and a variable n for the total candies.
// -> in each step, buy the candy at i (add to minCost) and move i forward.
// -> reduce n by k to simulate getting up to k candies for free.
// For maximum cost
// -> use a pointer i starting from the end and an index marker initialized to -1.
// -> in each step, buy the candy at i (add to maxCost) and move i backward.
// -> increase index by k to simulate taking free candies.
// Return both minCost and maxCost as the final result.


#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> minMaxCandy(vector<int>& prices, int k) {
  
    // Sort the array to arrange candies by price
    sort(prices.begin(), prices.end());
    
    // Calculate minimum cost by traversing from beginning
    int n = prices.size();
    int minCost = 0;
    for (int i = 0; i < n; i++) {
        minCost += prices[i];
        n -= k;
    }

    // Calculate maximum cost by traversing from end
    int index = -1, maxCost = 0; 
    for (int i = prices.size() - 1; i > index; i--) {
        maxCost += prices[i];
        index += k;
    }

    return {minCost, maxCost};
}

int main() {
    vector<int> prices = {3, 2, 1, 4};
    int k = 2;
    vector<int> res = minMaxCandy(prices, k);
    cout << res[0] << " " << res[1] << endl;
    return 0;
}