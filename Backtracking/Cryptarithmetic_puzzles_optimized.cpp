#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
using namespace std;

// Below is the step-by-step approach:

// Start by examining the rightmost digit of the topmost row, with a carry of 0
// If we are beyond the leftmost digit of the puzzle, return true if no carry, false otherwise
// If we are currently trying to assign a char in one of the addends If char already assigned, just recur on the row beneath this one, adding value into the sum If not assigned, then
// for (every possible choice among the digits not in use) make that choice and then on row beneath this one, if successful, return true if !successful, unmake assignment and try another digit
// return false if no assignment worked to trigger backtracking
// Else if trying to assign a char in the sum
// If char assigned & matches correct, recur on next column to the left with carry, if success return true,
// If char assigned & doesn't match, return false
// If char unassigned & correct digit already used, return false
// If char unassigned & correct digit unused, assign it and recur on next column to left with carry, if success return true
// return false to trigger backtracking


// Function to check if the puzzle is solvable with the given character assignments
bool solvePuzzleHelper(const string &a, const string &b, const string &sum, 
    int pos, int carry, unordered_map<char, int> &charToDigit, bitset<10> &usedDigits) {

    // Base case: if we have processed all digits
    if (pos >= sum.size()) {
        return carry == 0;
    }
    
    // Calculate sum at current position
    int sumVal = carry;
    if (pos < a.size() && charToDigit.count(a[a.size() - 1 - pos])) {
        sumVal += charToDigit[a[a.size() - 1 - pos]];
    }
    if (pos < b.size() && charToDigit.count(b[b.size() - 1 - pos])) {
        sumVal += charToDigit[b[b.size() - 1 - pos]];
    }
    
    char sumChar = sum[sum.size() - 1 - pos];
    
    // If sumChar is already assigned, check if it matches
    if (charToDigit.count(sumChar)) {
        if (charToDigit[sumChar] != sumVal % 10) {
            return false;
        }
        return solvePuzzleHelper(a, b, sum, pos + 1, 
                        sumVal / 10, charToDigit, usedDigits);
    }
    
    // Ensure digit is not already used
    if (usedDigits[sumVal % 10]) {
        return false;
    }
    
    // Assign the digit to sumChar
    charToDigit[sumChar] = sumVal % 10;
    usedDigits[sumVal % 10] = 1;
    
    // Recur for next position
    if (solvePuzzleHelper(a, b, sum, pos + 1, 
                    sumVal / 10, charToDigit, usedDigits)) {
        return true;
    }
    
    // Backtrack if assignment fails
    charToDigit.erase(sumChar);
    usedDigits[sumVal % 10] = 0;
    return false;
}

// Function to assign digits to unique characters and check if assignment is valid
bool assignDigits(const string &a, const string &b, const string &sum, int index, 
    const string &order, unordered_map<char, int> &charToDigit, bitset<10> &usedDigits) {
        
    // Base case: If all characters are assigned
    if (index == order.size()) {
        return solvePuzzleHelper(a, b, sum, 0, 0, charToDigit, usedDigits);
    }
    
    char ch = order[index];
    
    // Try assigning each digit to the character
    for (int digit = 0; digit < 10; digit++) {
        if (!usedDigits[digit]) {
            charToDigit[ch] = digit;
            usedDigits[digit] = 1;
            if (assignDigits(a, b, sum, index + 1, order, charToDigit, usedDigits)) {
                return true;
            }
            // Backtrack if unsuccessful
            usedDigits[digit] = 0;
            charToDigit.erase(ch);
        }
    }
    return false;
}

// Main function to solve Cryptarithmetic puzzle
vector<string> solvePuzzle(string a, string b, string sum) {
    unordered_map<char, int> charToDigit;
    bitset<10> usedDigits;
    unordered_set<char> uniqueChars;
    string order;
    
    // Identify unique characters in the input strings
    for (char ch : a + b + sum) {
        if (uniqueChars.insert(ch).second) {
            order += ch;
        }
    }
    
    // Assign digits to characters and check validity
    if (assignDigits(a, b, sum, 0, order, charToDigit, usedDigits)) {
        string x, y, z;
        for (char ch : a) x += '0' + charToDigit[ch];
        for (char ch : b) y += '0' + charToDigit[ch];
        for (char ch : sum) z += '0' + charToDigit[ch];
        return {x, y, z};
    }
    return {"-1"};
}

int main() {
    string a = "send", b = "more", sum = "money";
    vector<string> ans = solvePuzzle(a, b, sum);
    for (const auto &res : ans) {
        cout << res << " ";
    }
    return 0;
}