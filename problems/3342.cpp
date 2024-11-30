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
        int n = moveTime.size(), m = moveTime[0].size();
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

        set<vector<int>> heap;
        vector<vector<int>> min_time(n, vector<int>(m, INT_MAX));

        min_time[0][0] = 0;
        heap.insert({0, 0, 0, 0});

        while (!heap.empty())
        {
            auto it = *heap.begin(); // Pega o primeiro nó
            heap.erase(heap.begin()); // Remove o primeiro nó

            int t = it[0], x = it[1], y = it[2], cost = it[3]; // t = tempo, x = linha, y = coluna, cost = custo

            if (min_time[x][y] != INT_MAX && t > min_time[x][y]) // tempo atual é melhor que o tempo armazenado
                continue;

            int next_cost = (cost == 1) ? 2 : 1;

            for (auto [dx, dy] : directions)  
            {
                int nx = x + dx, ny = y + dy; 

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) 
                {
                    if (min_time[nx][ny] == INT_MAX) 
                    {
                        if (t <= moveTime[nx][ny]) 
                        {
                            min_time[nx][ny] = moveTime[nx][ny] + next_cost; 
                        }
                        else 
                        {
                            min_time[nx][ny] = t + next_cost; 
                        }
                        heap.insert({min_time[nx][ny], nx, ny, next_cost}); 
                        continue;
                    }
                    if (t + next_cost < min_time[nx][ny] && t >= moveTime[nx][ny])
                    {
                        min_time[nx][ny] = t + next_cost;
                        heap.insert({min_time[nx][ny], nx, ny, next_cost});
                    }
                }
            }
        }
        return min_time[n - 1][m - 1];
    }
};