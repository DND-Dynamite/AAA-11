// The three stacks s1, s2 and s3, each containing positive integers, are given. The task is to find the maximum possible equal sum that can be achieved by removing elements from the top of the stacks. Elements can be removed from the top of each stack, but the final sum of the remaining elements in all three stacks must be the same. The goal is to determine the maximum possible equal sum that can be achieved after removing elements.

// Note: The stacks are represented as arrays, where the first index of the array corresponds to the top element of the stack.

// Examples: 

// Input: s1 = [3, 2, 1, 1, 1], s2 = [2, 3, 4], s3 = [1, 4, 2, 5]
// Output: 5
// Explanation: We can pop 2 elements from the 1st stack, 1 element from the 2nd stack and 2 elements from the 3rd stack.

// Find-maximum-sum-possible-equal-sum-of-three-stacks-2
 
// Input: s1 = [3, 10]
//            s2 = [4, 5]
//           s3 = [2, 1]
// Output: 0
// Explanation: Sum can only be equal after removing all elements from all stacks.

// The idea is to compare the sum of each stack, if they are not same, remove the top element of the stack having the maximum sum.

// Algorithm for solving this problem: 

// Find the sum of all elements of in individual stacks.
// If the sum of all three stacks is the same, then this is the maximum sum.
// Else remove the top element of the stack having the maximum sum among three of stacks. Repeat step 1 and step 2.
// The approach works because elements are positive. To make sum equal, we must remove some element from stack having more sum, and we can only remove from the top.


#include <iostream>
#include <vector>

using namespace std;

int maxSum(vector<int>& s1, vector<int>& s2, vector<int>& s3) {
    int sum1 = 0, sum2 = 0, sum3 = 0;

    // Manually summing the elements of s1
    for (int i = 0; i < s1.size(); i++) {
        sum1 += s1[i];
    }

    // Manually summing the elements of s2
    for (int i = 0; i < s2.size(); i++) {
        sum2 += s2[i];
    }

    // Manually summing the elements of s3
    for (int i = 0; i < s3.size(); i++) {
        sum3 += s3[i];
    }

    int top1 = 0, top2 = 0, top3 = 0;

    while (true) {
        if (top1 == s1.size() || top2 == s2.size() || top3 == s3.size())
            return 0;

        if (sum1 == sum2 && sum2 == sum3)
            return sum1;

        if (sum1 >= sum2 && sum1 >= sum3)
            sum1 -= s1[top1++];
        else if (sum2 >= sum1 && sum2 >= sum3)
            sum2 -= s2[top2++];
        else
            sum3 -= s3[top3++];
    }
}

int main() {
    vector<int> s1 = {3, 2, 1, 1, 1};
    vector<int> s2 = {4, 3, 2};
    vector<int> s3 = {1, 1, 4, 1};

    cout << maxSum(s1, s2, s3) << endl;
    return 0;
}