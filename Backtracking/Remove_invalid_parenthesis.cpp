
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;


// Problem  Statement:

// Given a string str consisting only of lowercase letters and the characters '(' and ')'. Your task is to delete minimum parentheses so that the resulting string is balanced, i.e., every opening parenthesis has a matching closing parenthesis in the correct order, and no extra closing parentheses appear. Print all distinct strings you can obtain by performing the minimum number of removals.

// Examples:

// Input: str = "()())()"
// Output: "()()()"  "(())()"
// Explanation: We can remove the closing bracket at index 3 to obtain the balanced string "()()()". Similarly, we can remove the closing bracket at index 1 to obtain the balanced string "(())()".

// Input: str = "(v)())()"
// Output: "(v)()()"  "(v())()"
// Explanation: The given string is the modified version of first string containing a letter 'v' . As the letters do not differ the parentheses, the solution remains the same. 

// Input: S = ")("
// Output: ""

// Initialize an empty visit map, a queue q, a result vector res, and a boolean level = false.
// Push the original str into q and mark visit[str] = 1.
// While q is not empty:
// Dequeue temp from q.
// If isValidString(temp) returns true:
// Append temp to res.
// Set level = true.
// If level is true, skip further removals at this depth and continue.
// Otherwise, for each index i in temp where temp[i] is ‘(’ or ‘)’:
// Form cur = temp.substr(0, i) + temp.substr(i + 1).
// If visit.count(cur) == 0, enqueue cur into q and set visit[cur] = 1.
// Return res



// method returns true if string 
// contains valid parenthesis
bool isValidString(string str) {
    int cnt = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(')
            cnt++;
        else if (str[i] == ')')
            cnt--;
        if (cnt < 0)
            return false;
    }
    return (cnt == 0);
}

//  function to remove invalid parenthesis
vector<string> validParenthesis(string &str) {

    // to ignore already visited string
    unordered_map<string, int> visit;

    //  queue to maintain BFS
    queue<string> q;

    // to store the valid strings
    vector<string> res;
    bool level = false;

    //  pushing given string as starting node into queue
    q.push(str);
    
    // mark the string as visited
    visit[str] = 1;

    // while queue is not empty
    while (!q.empty()) {
        string temp = q.front();
        q.pop();

        // check if the string is valid
        if (isValidString(temp)) {
            
            // if valid, store it
            res.push_back(temp);

            // make level true, so that valid string 
            // of only that level are processed.
            level = true;
        }
        if (level)
            continue;

        for (int i = 0; i < temp.length(); i++) {

            // if current character is not a parenthesis
            // continue to next character
            if (temp[i] != '(' && temp[i] != ')')
                continue;

            // Removing parenthesis from str and
            // pushing into queue,if not visited already
            string cur = temp.substr(0, i) + temp.substr(i + 1);
            if (visit.count(cur) == 0) {
                q.push(cur);
                visit[cur] = 1;
            }
        }
    }
    return res;
}

int main() {
    string str = "(v)())()";
    vector<string> res = validParenthesis(str);
    for (string s : res) {
        cout << s << endl;
    }
    return 0;
}