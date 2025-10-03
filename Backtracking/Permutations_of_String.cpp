#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// C++ Program to generate all unique
// permutations of a string

// Problem Statement:

// Given a string s, the task is to return all permutations of
// a given string in lexicographically sorted order.

// Note: A permutation is the rearrangement of all the elements of a string.
// Duplicate arrangement can exist.

using namespace std;

// Recursive function to generate 
// all permutations of string s
void recurPermute(int index, string &s, vector<string> &ans) {

    // Base Case
    if (index == s.size()) {
        ans.push_back(s);
        return;
    }

    // Swap the current index with all
    // possible indices and recursion
    for (int i = index; i < s.size(); i++) {
        swap(s[index], s[i]);
        recurPermute(index + 1, s, ans);
        swap(s[index], s[i]);
    }
}

// Function to find all unique permutations
vector<string> findPermutation(string &s) {

    // Stores the final answer
    vector<string> ans;

    recurPermute(0, s, ans);

    // sort the resultant vector
    sort(ans.begin(), ans.end());

    return ans;
}

int main() {
    string s;
    std::cout << "Enter the string: ";
    std::cin >> s;

    vector<string> res = findPermutation(s);
    for(auto x: res) {
        cout << x << " ";
    }
    return 0;
}