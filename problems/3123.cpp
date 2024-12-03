/**
 * 3123. Find Edges in Shortest Paths
 * https://leetcode.com/problems/find-edges-in-shortest-paths/description/
 *
 * Description:
 * You are given an undirected weighted graph of n nodes numbered from 0 to n - 1.
 * The graph consists of m edges represented by a 2D array edges, where edges[i] =
 * [ai, bi, wi] indicates that there is an edge between nodes ai and bi with weight
 * wi.
 * Consider all the shortest paths from node 0 to node n - 1 in the graph. You need
 * to find a boolean array answer where answer[i] is true if the edge edges[i] is
 * part of at least one shortest path. Otherwise, answer[i] is false.
 *
 * Return the array answer.
 *
 * Note that the graph may not be connected.
 *
 * Difficulty: Hard
 */

#include <iostream>
#include <vector>
#include <tuple>
#include <queue>
#include <climits>

using namespace std;

class Solution
{
public:
    vector<bool> findAnswer(int n, vector<vector<int>> &edges)
    {
        int m = edges.size();

        vector<vector<tuple<int, int, int>>> adj(n);

        for (auto i = 0; i < m; i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];
            int weight = edges[i][2];

            adj[from].emplace_back(to, weight, i);
            adj[to].emplace_back(from, weight, i);
        }

        auto dijkstra = [&](int start)
        {
            vector<int> dist(n, INT_MAX);
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

            dist[start] = 0;
            heap.emplace(0, start);

            while (!heap.empty())
            {
                auto [d, u] = heap.top();
                heap.pop();

                if (d > dist[u])
                    continue;

                for (auto &[v, w, i] : adj[u])
                {
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        heap.emplace(dist[v], v);
                    }
                }
            }
            return dist;
        };

        vector<int> dist_start = dijkstra(0);
        vector<int> dist_end = dijkstra(n - 1);
        int shortest_path = dist_start[n - 1];

        vector<bool> answer(m, false);

        if (shortest_path == INT_MAX)
            return answer;

        for (int i = 0; i < m; i++)
        {
            int from = edges[i][0];
            int to = edges[i][1];
            int weight = edges[i][2];

            if (static_cast<long long>(dist_start[from]) + weight + dist_end[to] == shortest_path ||
                static_cast<long long>(dist_start[to]) + weight + dist_end[from] == shortest_path)
            {
                answer[i] = true;
            }
        }
        return answer;
    }
};
