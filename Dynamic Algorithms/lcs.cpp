#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
public:
    // Method 1: Standard Dynamic Programming Approach
    // Time: O(n²), Space: O(n²)
    int longestPalindromicSubsequence(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        // Create DP table
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base case: single characters are palindromes of length 1
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
        }
        
        // Fill the table for substrings of length 2 to n
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                
                if (s[i] == s[j] && length == 2) {
                    dp[i][j] = 2;
                } else if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[0][n - 1];
    }
    
    // Method 2: Space-Optimized DP Approach
    // Time: O(n²), Space: O(n)
    int longestPalindromicSubsequence_optimized(string s) {
        int n = s.length();
        if (n == 0) return 0;
        
        vector<int> prev(n, 0);
        vector<int> curr(n, 0);
        
        for (int i = n - 1; i >= 0; i--) {
            curr[i] = 1;  // Single character is always palindrome
            for (int j = i + 1; j < n; j++) {
                if (s[i] == s[j]) {
                    curr[j] = 2 + ((j > i + 1) ? prev[j - 1] : 0);
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }
        
        return curr[n - 1];
    }
    
    // Method 3: LCS-based Approach (Alternative solution)
    // LPS(s) = LCS(s, reverse(s))
    int longestPalindromicSubsequence_lcs(string s) {
        string reversed_s = s;
        reverse(reversed_s.begin(), reversed_s.end());
        return longestCommonSubsequence(s, reversed_s);
    }
    
private:
    int longestCommonSubsequence(string s1, string s2) {
        int m = s1.length(), n = s2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return dp[m][n];
    }
};

// Test function to verify all approaches
void runTestCases() {
    Solution sol;
    
    vector<pair<string, int>> testCases = {
        {"bbabcbcab", 7},
        {"abcd", 1},
        {"a", 1},
        {"aa", 2},
        {"ab", 1},
        {"abcba", 5},
        {"racecar", 7},
        {"", 0},
        {"abba", 4},
        {"abcde", 1},
        {"aabaa", 5}
    };
    
    cout << "Testing Longest Palindromic Subsequence:\n";
    cout << "========================================\n";
    
    for (const auto& testCase : testCases) {
        string input = testCase.first;
        int expected = testCase.second;
        
        int result1 = sol.longestPalindromicSubsequence(input);
        int result2 = sol.longestPalindromicSubsequence_optimized(input);
        int result3 = sol.longestPalindromicSubsequence_lcs(input);
        
        cout << "Input: \"" << input << "\"\n";
        cout << "Expected: " << expected << "\n";
        cout << "DP Result: " << result1;
        cout << (result1 == expected ? " Right" : " Wrong") << "\n";
        cout << "Optimized DP: " << result2;
        cout << (result2 == expected ? " Right" : " Wrong") << "\n";
        cout << "LCS-based: " << result3;
        cout << (result3 == expected ? " Right" : " Wrong") << "\n";
        cout << "---\n";
    }
}

// Main function with example usage
int main() {
    Solution sol;
    
    // Example 1
    string s1 = "bbabcbcab";
    cout << "Example 1:\n";
    cout << "String: " << s1 << "\n";
    cout << "Longest Palindromic Subsequence length: " 
         << sol.longestPalindromicSubsequence(s1) << "\n\n";
    
    // Example 2
    string s2 = "abcd";
    cout << "Example 2:\n";
    cout << "String: " << s2 << "\n";
    cout << "Longest Palindromic Subsequence length: " 
         << sol.longestPalindromicSubsequence(s2) << "\n\n";
    
    // Run comprehensive tests
    runTestCases();
    
    return 0;
}