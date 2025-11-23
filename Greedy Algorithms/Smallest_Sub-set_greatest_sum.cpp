// // Given an array of non-negative integers, the task is to find the minimum number of elements 
// // such that their sum should be greater than the sum of the rest of the elements of the array.

// Input: arr[] = [ 3 , 1 , 7, 1 ]
// Output: 1
// Explanation: Smallest subset is {7}. Sum of this subset is greater than the sum of all other elements left after removing subset {7} from the array

// Input:  arr[] = [ 2 , 1 , 2 ]
// Output: 2
// Explanation: Smallest subset is {2 , 1}. Sum of this subset is greater than the sum of all other elements left after removing subset {2 , 1} from the array

// Expected Approach - O(n Log n) Time and O(1) Space
// The idea to solve this problem is based on the greedy approach that we pick the largest 
// elements to form the subset having sum greater than all others. 
// We first sort the array in reverse order. 
// Then we traverse the sorted array from the left (largest element) and compute 
// sum of elements. If sum of current elements become more than the remaining sum,
// we return count of current elements as result.

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric> // for accumulate
using namespace std;

// function to find minimum elements needed
int minElements(vector<int>& arr) {
  
    // calculate total sum of the array
    int totalSum = accumulate(arr.begin(), arr.end(), 0);

    // sort the array in descending order
    sort(arr.begin(), arr.end(), greater<int>());

    int res = 0, currSum = 0;
    for (int x : arr) {
        currSum += x;
        res++;

        // current sum greater than the remaining sum
        if (currSum > totalSum - currSum)
            return res;
    }
    return res;
}

int main() {
    vector<int> arr = { 3, 1, 7, 1 };
    cout << minElements(arr) << endl;
    return 0;
}