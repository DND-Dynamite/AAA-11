// Given two arrays, greed[] and cookie[] such that greed[i] denotes the minimum cookie size
//  wanted by ith child and cookie[i] denotes the size of ith cookie, 
//  we have to find the maximum number of children that can be satisfied by assigning 
//  them cookies, with each child getting at most 1 cookie.

// Note: A child will be satisfied if he is assigned a cookie of size at least equal to his 
// greed. In other words, the ith child will be satified with jth cookie only 
// if greed[i] <= cookie[j].

// Steps to solve the problem:

// Sort the greed array greed and the cookie arrays.
// Initialize two pointers: i (index for children), j (index for cookies)
// Initialize count = 0 to track the number of satisfied children.
// Iterate while both pointers are within their array bounds:
// If cookie[j] >= greed[i], the cookie can satisfy the child: Increment count and Move both pointers .
// Else cookie is too small and Move only the cookie pointer/
// Return count as the total number of satisfied children

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxChildren(vector<int> &greed, vector<int> &cookie) {
	sort(greed.begin(), greed.end());
    sort(cookie.begin(), cookie.end());
  
    // Initialize pointers to the beginning of the arrays
    int i = 0, j = 0;
    int cnt = 0;
  
    // Iterate until we reach the end of either array
    while(i < greed.size() && j < cookie.size()) {
      
        // If ith child can be satisfied with jth cookie,
        // assign it to him and increment the count 
    	if(greed[i] <= cookie[j]) {
        	cnt++;
            i++;
            j++;
        }
        
        // If ithe child cannot be satified with jth 
        // cookie, move to the next bigger cookie
        else 
            j++;
    }
    return cnt;
}

int main() {
	vector<int> greed = {1, 10, 3};
    vector<int> cookie = {1, 2,3};
  
    cout << maxChildren(greed, cookie);

    return 0;
}