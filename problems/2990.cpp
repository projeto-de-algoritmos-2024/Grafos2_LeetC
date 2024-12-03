/**
 * You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
 * 0 represents an empty cell,
 * 1 represents an obstacle that may be removed. 
 * You can move up, down, left, or right from and to an empty cell.
 * 
 * Return the minimum number of obstacles to remove so you can move from
 * the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).
 * 
 * Difficulty: Hard
 */

# include <iostream>
# include <vector>
# include <queue>
# include <algorithm>

using namespace std;

class Solution {
public:
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        
        vector<vector<int>> dist(m, vector<int>(n, INT_MAX));
        dist[0][0] = 0;
        
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
        pq.push({0, {0, 0}});
        
        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        
};
