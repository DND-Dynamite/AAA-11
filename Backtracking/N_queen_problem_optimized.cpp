#include <iostream>
#include<vector>
using namespace std;

// Problem Solution:

// Instead of checking every row and diagonal, use three arrays to track occupied columns
// and diagonals. A queen can be placed at a cell only if its column and both diagonals
// are free. This reduces the safe-check from O(n) to O(1).

// We use three arrays to efficiently check if a queen can be placed at (i, j) without conflicts:

// cols[] – Tracks if a queen is already placed in a column.
// cols[j] = 1 means column j is occupied.
// rightDiagonal[] – Tracks diagonals where i + j is constant.
// On a chessboard, all cells on the same top-left to bottom-right diagonal have the same sum of row and column indices (i + j).
// So we use rightDiagonal[i + j] to quickly check if that diagonal is occupied.
// leftDiagonal[] – Tracks diagonals where i - j is constant.
// All cells on the same top-right to bottom-left diagonal have the same difference (i - j).
// To avoid negative indices, we shift by n - 1: leftDiagonal[i - j + n - 1].
// This lets us represent all diagonals with non-negative indices in the array.


// Recursive function to place queens
void placeQueens(int i, vector<int> &cols, vector<int> &leftDiagonal,
                     vector<int> &rightDiagonal, vector<int> &cur, 
                     vector<vector<int>> &result) {
    int n = cols.size();

    // base case: If all queens are placed
    if(i == n) {
        result.push_back(cur);
        return;
    }

    // Consider the row and try placing
    // queen in all columns one by one
    for(int j = 0; j < n; j++){

        // Check if the queen can be placed
        if(cols[j] || rightDiagonal[i + j] || 
                        leftDiagonal[i - j + n - 1]) 
            continue;
        
        // mark the cell occupied
        cols[j] = 1;
        rightDiagonal[i+j] = 1; 
        leftDiagonal[i - j + n - 1] = 1;
        cur.push_back(j+1);

        placeQueens(i + 1, cols, leftDiagonal, rightDiagonal, cur, result);

        // remove the queen from current cell
        cur.pop_back();
        cols[j] = 0;
        rightDiagonal[i+j] = 0; 
        leftDiagonal[i - j + n - 1] = 0;        
    }
}

// Function to find the solution
// to the N-Queens problem
vector<vector<int>> nQueen(int n) {

    // array to mark the occupied cells
    vector<int> cols(n, 0);
    vector<int> leftDiagonal(n*2, 0);
    vector<int> rightDiagonal(n*2, 0);
    vector<int> cur;
    vector<vector<int>> result;

    // Place queens
    placeQueens(0, cols, leftDiagonal, rightDiagonal, cur, result);

    return result;
}

int main() {
    int n = 4;
    vector<vector<int>> ans = nQueen(n);
    for(auto &a: ans){
        for(auto i: a){
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}