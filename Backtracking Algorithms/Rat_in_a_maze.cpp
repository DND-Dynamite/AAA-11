#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


// Problem Statement:

// Given a square binary matrix mat[][] representing a maze.
// A rat starts at the top-left corner (0,0) and needs to reach 
// the bottom-right corner (n-1, n-1). The rat can move in 
// four directions: Up (U), Down (D), Left (L), Right (R).
// Find all possible paths from (0, 0) to (n-1, n-1). 
// If multiple paths exist, return them in lexicographically sorted order
// otherwise If no path exists, return empty list.

// Note:

// 1) A rat cannot visit the same cell more than once in a path.
// 2) 1 represents an open cell (rat can visit), and 0 represents a blocked cell (rat cannot visit)

// Time Complexity: O(4n*n), because on every cell we have to try 4 different directions.
// Auxiliary Space: O(n2), Maximum Depth of the recursion tree.

// Directions: Down, Left, Right, Up
string dir = "DLRU";
int dr[4] = {1, 0, 0, -1};
int dc[4] = {0, -1, 1, 0};

// Check if a cell is valid (inside the maze and open)
bool isValid(int r, int c, int n, vector<vector<int>>& maze) {
    return r >= 0 && c >= 0 && r < n && c < n && maze[r][c];
}

// Function to find all valid paths
void findPath(int r, int c, vector<vector<int>>& maze, string& path, vector<string>& res) {
    int n = maze.size(); 

    // If destination is reached, store the path
    if (r == n - 1 && c == n - 1) {
        res.push_back(path);
        return;
    }
    
    // Mark current cell as visited
    maze[r][c] = 0; 

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (isValid(nr, nc, n, maze)) {
            path.push_back(dir[i]);
            
            // Move to the next cell recursively
            findPath(nr, nc, maze, path, res); 
            
            // Backtrack
            path.pop_back();
        }
    }
    
    // Unmark current cell
    maze[r][c] = 1;  
}

// Function to find all paths and return them
vector<string> ratInMaze(vector<vector<int>>& maze) {
    vector<string> result;
    int n = maze.size();
    string path = "";

    if (maze[0][0] == 1 && maze[n - 1][n - 1] == 1) {
        
        // Start from (0,0)
        findPath(0, 0, maze, path, result);  
    }

    // Sort results lexicographically
    sort(result.begin(), result.end());
    
    return result;
}

int main() {
    vector<vector<int>> maze = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };

    vector<string> result = ratInMaze(maze);

    for (auto p : result) {
        cout << p << " ";
    }
    
    return 0;
}