#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// Problem Statement:

// Where the goal is to assign each letter a digit from 0 to 9 so that the arithmetic
// works out correctly. The rules are that all occurrences of a letter must be assigned
// the same digit, and no digit can be assigned to more than one letter. 
// You are given three strings a, b, and sum, representing the crypt-arithmetic puzzles,
// your task is to solve the puzzle and print the three strings representing its solution.

// The idea is to firstly create a list of all the characters that need assigning
// to pass to Solve. Now use backtracking to assign all possible digits to the characters.

// If all characters are assigned, return true if puzzle is solved, false otherwise
// Otherwise, consider the first unassigned character
// for (every possible choice among the digits not in use)
// If all digits have been tried and nothing worked, return false to trigger backtracking


// C++ program to implement 
// Cryptarithmetic Puzzle Solver


// Function to remove preceeding zeroes
void removeZeroes(string &a) {
    reverse(a.begin(), a.end());

    while(a.size() > 1 && a.back() == '0') {
        a.pop_back();
    }

    reverse(a.begin(), a.end());
}

// function change character string
// to digit string
string charToDigit(string a, vector<char> &digits) {

    string res = "";
    for(int i = 0; i<a.size(); i++) {
        res += digits[a[i]-'a'];
    }
    return res;
}

// function to find sum of numbers
// in the form of strings
string findSum(string a, string b) {

    // Before proceeding further, make sure length
    // of b is larger.
    if (a.length() > b.length())
        swap(a, b);
 
    // Take an empty string for storing result
    string str = "";
 
    // Calculate length of both string
    int n1 = a.length(), n2 = b.length();
 
    // Reverse both of strings
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
 
    int carry = 0;
    for (int i=0; i<n1; i++) {

        // Do school mathematics, compute sum of
        // current digits and carry
        int sum = ((a[i]-'0')+(b[i]-'0')+carry);
        str.push_back(sum%10 + '0');
 
        // Calculate carry for next step
        carry = sum/10;
    }
 
    // Add remaining digits of larger number
    for (int i=n1; i<n2; i++) {

        int sum = ((b[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
 
    // Add remaining carry
    if (carry)
        str.push_back(carry+'0');
    
    // reverse resultant string
    reverse(str.begin(), str.end());

    // remove preceeding zeroes
    removeZeroes(str);

    return str;
}



// function to check if puzzle is solved
bool isSolved(string &a, string &b, 
        string &sum, vector<char> &digits) {
    
    // convert the character string to digit string
    string x = charToDigit(a, digits);
    string y = charToDigit(b, digits);
    string z = charToDigit(sum, digits);

    // sum of string x and y
    string res = findSum(x, y);

    removeZeroes(z);

    // check if res and z is equal
    if(z == res) 
        return true;
    else return false;
}

// Function to solve Cryptarithmetic
// Puzzle using backtracking
bool cryptarithmeticSolver(int ind, vector<char> &digits, 
    vector<int> &characters, string &a, string &b, string &sum) {

    // if all characters are assigned
    // a unique digit
    if(ind == 26) {
        return isSolved(a, b, sum, digits);
    }

    // if current character is assigned a value
    // or need not to be assigned
    if(digits[ind] != '+') 
        return cryptarithmeticSolver(ind + 1, 
                    digits, characters, a, b, sum);

    // try to assign all possible digits
    for(char i = '0'; i <= '9'; i++) {

        // if digit is not used yet
        if(characters[i-'0'] == 0) {
            characters[i-'0'] = 1;
            digits[ind] = i;
            if(cryptarithmeticSolver(ind + 1, 
                digits, characters, a, b, sum) == true)
                return true;
            digits[ind] = '+';
            characters[i-'0'] = 0;
        }
    }

    return false;
}

// Function to solve Cryptarithmetic Puzzle
vector<string> solvePuzzle(string &a, string &b, 
                                    string &sum) {

    // to map digit assigned to the character
    vector<char> digits(26,'-');

    // to map character assigned to the digit 
    vector<int> characters(10, 0);

    // mark character that need a digit to
    // be assigned by a "+" sign
    for(auto i:a)
        digits[i-'a'] = '+';
    for(auto i:b)
        digits[i-'a'] = '+';
    for(auto i:sum)
        digits[i-'a'] = '+';

    // check if the assignment of digits is
    // possible, and find the correct one
    if(cryptarithmeticSolver(0, digits,
             characters, a, b, sum) == true) {
            
        // change the string a to digit string
        string x = charToDigit(a, digits);

        // change the string b to digit string
        string y = charToDigit(b, digits);

        // change the string sum to digit string
        string res = charToDigit(sum, digits);

        // return all three digit strings
        return {x, y, res};
    }

    // if no possible assignment exist
    else return {"-1"};
}

int main() {
    string a = "s";
    string b = "p";
    string sum = "f";
    vector<string> ans = solvePuzzle(a, b, sum);
    for(auto i:ans) {
        cout<<i<<" ";
    }
    return 0;
}