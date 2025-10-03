#include <iostream>
#include <vector>
using namespace std;

// problem statement:
// Given an integer n, consider an n × n chessboard.
// A Knight starts at the top-left corner (0, 0) and 
// must visit every cell exactly once following the Knight’s standard moves 
// in chess (two steps in one direction and one step perpendicular).

// Return the n × n grid where each cell contains the step number (starting from 0)
// at which the Knight visits that cell.
// If no valid tour exists, return -1.

// 8 directions of knight moves
int dx[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};

// Utility function to check if the 
// move is valid
bool isSafe(int x, int y, int n, vector<vector<int>> &board) {
    return (x >= 0 && y >= 0 && x < n &&
            y < n && board[x][y] == -1);
}

// Recursive function to solve Knight's Tour
bool knightTourUtil(int x, int y, int step, int n, vector<vector<int>> &board) {

    // If all squares are visited
    if (step == n * n) {
        return true;
    }

    // Try all 8 possible knight moves
    for (int i = 0; i < 8; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (isSafe(nx, ny, n, board)) {
            board[nx][ny] = step;

            if (knightTourUtil(nx, ny, step + 1, n, board)) {
                return true;
            }

            // Backtrack
            board[nx][ny] = -1;
        }
    }

    return false;
}

// Function to start Knight's Tour
vector<vector<int>> knightTour(int n) {
    vector<vector<int>> board(n, vector<int>(n, -1));

    // Start from top-left corner
    board[0][0] = 0;

    if (knightTourUtil(0, 0, 1, n, board)) {
        return board;
    }

    return {{-1}};
}

int main() {
    int n = 5;

    vector<vector<int>> res = knightTour(n);

    for (auto &row : res) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}