#pragma once

#include <algorithm>
#include <deque>
#include <functional>
#include <limits>
#include <queue>
#include <tuple>
#include <vector>

namespace contest {

struct WeightedGraph {
    struct Edge {
        int to;
        long long w;
    };

    int n = 0;
    bool directed = false;
    std::vector<std::vector<Edge>> adj;

    WeightedGraph() = default;
    WeightedGraph(int n_, bool directed_ = false) { init(n_, directed_); }

    void init(int n_, bool directed_) {
        n = n_;
        directed = directed_;
        adj.assign(n, {});
    }

    void addEdge(int u, int v, long long w) {
        adj[u].push_back({v, w});
        if (!directed) adj[v].push_back({u, w});
    }

    std::vector<long long> dijkstra(int source) const {
        const long long INF = std::numeric_limits<long long>::max() / 4;
        std::vector<long long> dist(n, INF);
        using State = std::pair<long long, int>;
        std::priority_queue<State, std::vector<State>, std::greater<State>> pq;
        dist[source] = 0;
        pq.push({0, source});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (auto [v, w] : adj[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    std::vector<long long> zeroOneBfs(int source) const {
        const long long INF = std::numeric_limits<long long>::max() / 4;
        std::vector<long long> dist(n, INF);
        std::deque<int> dq;
        dist[source] = 0;
        dq.push_back(source);
        while (!dq.empty()) {
            int u = dq.front();
            dq.pop_front();
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    if (w == 0) dq.push_front(v);
                    else dq.push_back(v);
                }
            }
        }
        return dist;
    }

    std::vector<long long> spfa(int source) const {
        const long long INF = std::numeric_limits<long long>::max() / 4;
        std::vector<long long> dist(n, INF);
        std::vector<int> inQueue(n, 0);
        std::queue<int> q;
        dist[source] = 0;
        q.push(source);
        inQueue[source] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inQueue[u] = 0;
            for (auto [v, w] : adj[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    if (!inQueue[v]) {
                        inQueue[v] = 1;
                        q.push(v);
                    }
                }
            }
        }
        return dist;
    }
};

}  // namespace contest

