#include <iostream>
#include <vector>
using namespace std;


// Problem Statement:

// Given an integer n, place n queens on an n × n chessboard such that no two queens attack
// each other. A queen can attack another queen if they are placed in the same row, 
// the same column, or on the same diagonal.

// Find all possible distinct arrangements of the queens on the board that satisfy these conditions.

// The output should be an array of solutions,
// where each solution is represented as an array of integers of size n, and the i-th integer denotes the column position of the queen in the i-th row. If no solution exists, return an empty array.

// The idea is to use backtracking to place queens on an n × n chessboard.
// We can proceed either row by row or column by column.
// For each row (or column), try placing a queen in every column (or row) and
// check if it is safe (i.e., no other queen in the same column, row, or diagonals). 
// If safe, place the queen and move to the next row/column. 
// If no valid position exists, backtrack to the previous step and try a different position.
// Continue until all queens are placed or all possibilities are explored.



// Function to check if it is safe to place
int isSafe(vector<vector<int>>& mat, 
                    int row, int col) {
    int n = mat.size();
    int i, j;

    // Check this col on upper side
    for (i = 0; i < row; i++)
        if (mat[i][col])
            return 0;

    // Check upper diagonal on left side
    for (i = row-1, j = col-1; i >= 0 && j >= 0; i--, j--)
        if (mat[i][j])
            return 0;

    // Check upper diagonal on right side
    for (i = row-1, j = col+1; j < n && i >= 0; i--, j++)
        if (mat[i][j])
            return 0;

    return 1;
}

// Recursive function to place queens
void placeQueens(int row, vector<vector<int>>& mat, vector<vector<int>>&result) {
    int n = mat.size();

    // base case: If all queens are placed
    if(row == n) {
        
        // store current solution
        vector<int> ans;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(mat[i][j]){
                    ans.push_back(j + 1);
                }
            }
        }
        result.push_back(ans);
        return;
    }

    // Consider the row and try placing
    // queen in all columns one by one
    for(int i = 0; i < n; i++){
        
        // Check if the queen can be placed
        if(isSafe(mat, row, i)){
            mat[row][i] = 1;
            placeQueens(row + 1, mat, result);
            
            // backtrack
            mat[row][i] = 0; 
        }
    }
}

// Function to find all solutions
vector<vector<int>> nQueen(int n) {

    // Initialize the board
    vector<vector<int>> mat(n, vector<int>(n, 0));
    vector<vector<int>> result;

    // Place queens
    placeQueens(0, mat, result);

    return result;
}

int main() {
    int n = 4;
    vector<vector<int>> result = nQueen(n);
    for(auto &ans : result){
        for(auto i: ans){
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}