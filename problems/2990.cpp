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
#define pi pair<int, int>
# include <iostream>
# include <vector>
# include <queue>

using namespace std;

class Solution {
  public: 
  int minimumObstacles(vector<vector<int>>& grid) {
    int gridSize = grid.size();
    int gridColSize = grid[0].size();
    vector<vector<int>> visited(gridSize, vector<int>(gridColSize, 0));
    priority_queue<pair<int, pair<pi, pi>>, vector<pair<int, pair<pi, pi>>>, greater<pair<int, pair<pi, pi>>>> pq;
    pq.push({0, {{0, 0}, {0, 0}}});
    while (!pq.empty()){
        auto top = pq.top();
        int ncost = top.first;
        pi p1 = top.second.first;
        pi p2 = top.second.second;
        pq.pop();
        int nx = p1.second, ny = p1.first;
        if (nx == gridColSize - 1 && ny == gridSize - 1) {
            return ncost;
        }
        visited[ny][nx] = 1;
        if (nx + 1 < gridColSize){
            if (!visited[ny][nx+1]){
                int cost = grid[ny][nx+1];
                pi p = {ny, nx+1};
                pq.push({ncost + cost, {p, p1}});
            }
        }
        if (nx - 1 >= 0){
            if (!visited[ny][nx-1]){
                int cost = grid[ny][nx-1];
                pi p = {ny, nx-1};
                pq.push({ncost + cost, {p, p1}});
            }
        }
        if (ny + 1 < gridSize){
            if (!visited[ny+1][nx]){
                int cost = grid[ny+1][nx];
                pi p = {ny+1, nx};
                pq.push({ncost + cost, {p, p1}});
            }
        }
        if (ny - 1 >= 0){
            if (!visited[ny-1][nx]){
                int cost = grid[ny-1][nx];
                pi p = {ny-1, nx};
                pq.push({ncost + cost, {p, p1}});
            }
        }
    }
    return -1;
}
};
