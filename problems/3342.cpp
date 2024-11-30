/**
 * 3342. Find Minimum Time to Reach Last Room II
 * https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/
 *
 * Description:
 * There is a dungeon with n x m rooms arranged as a grid.
 * You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can 
 * start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between 
 * adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.
 * 
 * Return the minimum time to reach the room (n - 1, m - 1).
 * 
 * Two rooms are adjacent if they share a common wall, either horizontally or vertically.
 *
 * Difficulty: Medium
 */

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <set>

using namespace std;

class Solution
{
public:
    int minTimeToReach(vector<vector<int>> &moveTime)
    {
        int time = 0, n = moveTime.size(), m = moveTime[0].size();
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        set<vector<int>> heap;  
        vector<vector<int>> min_time (n, vector<int>(m, INT_MAX));

        min_time[0][0] = 0;
        heap.insert({0, 0, 0, 0});

        while (!heap.empty()) 
        {
            auto it = *heap.begin();
            heap.erase(heap.begin());
            int t = it[0], x = it[1], y = it[2], next = it[3];

            if (t > min_time[x][y])  // tempo atual é melhor que o tempo armazenado
                continue;
            
            for (auto [dx, dy] : directions) 
            {
                int nx = x + dx, ny = y + dy;

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) 
                {
                    int nt = t + next;
                    int next_cost = (next == 1) ? 2 : 1;

                    if (nt < moveTime[nx][ny])
                    {
                        nt = moveTime[nx][ny];
                        min_time[nx][ny] = nt;
                        heap.insert({nt, nx, ny, next_cost});
                    }

                }
            }
        }
        return min_time[n - 1][m - 1];
    }
};