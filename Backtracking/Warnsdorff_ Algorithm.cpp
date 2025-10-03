#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Problem Statement: 
// When solving the Knight's Tour problem,
//  backtracking works but is inefficient because it explores many unnecessary paths.
// If the correct move happens to be the last option, the algorithm wastes time trying
// all the wrong ones first.

// A smarter strategy is Warnsdorff’s Algorithm,
// which uses a heuristic to reduce backtracking. Instead of trying moves in random order,
// it always chooses the next move with the fewest onward moves (the cell with the smallest degree). 
// This prevents the knight from getting stuck early and greatly improves efficiency.

// Complexity Analysis:  O(n^3) Time and O(n^2) Space

// Define 8 knight moves globally
int dir[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

// Count the number of onward moves from position (x, y)
int countOptions(vector<vector<int>>& board, int x, int y) {
    int count = 0;
    int n = board.size();

    for (int i = 0; i < 8; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];
        if (nx >= 0 && ny >= 0 && nx < n && ny < n && board[nx][ny] == -1) {
            count++;
        }
    }
    return count;
}

// Generate valid knight moves from (x, y), sorted by fewest onward moves
vector<vector<int>> getSortedMoves(vector<vector<int>>& board, int x, int y) {
    vector<vector<int>> moveList;

    for (int i = 0; i < 8; i++) {
        int nx = x + dir[i][0];
        int ny = y + dir[i][1];

        if (nx >= 0 && ny >= 0 && nx < board.size() && ny < board.size() &&
            board[nx][ny] == -1) {
            int options = countOptions(board, nx, ny);
            moveList.push_back({options, i});
        }
    }

    // Sort using default vector<int> lexicographic comparison
    sort(moveList.begin(), moveList.end());

    return moveList;
}

// Recursive function to solve the Knight's Tour
bool knightTourUtil(int x, int y, int step, int n, vector<vector<int>>& board) {
    if (step == n * n) return true;

    vector<vector<int>> moves = getSortedMoves(board, x, y);

    for (vector<int> move : moves) {
        int dirIdx = move[1];
        int nx = x + dir[dirIdx][0];
        int ny = y + dir[dirIdx][1];

        board[nx][ny] = step;
        if (knightTourUtil(nx, ny, step + 1, n, board))
            return true;

        // Backtrack
        board[nx][ny] = -1;
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
    vector<vector<int>> result = knightTour(n);

    for (vector<int> row : result) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}