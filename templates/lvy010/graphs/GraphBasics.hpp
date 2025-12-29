#pragma once

#include <queue>
#include <vector>

namespace contest {

struct Graph {
    int n = 0;
    std::vector<std::vector<int>> adj;
    bool directed = false;

    Graph() = default;
    Graph(int n_, bool directed_ = false) { init(n_, directed_); }

    void init(int n_, bool directed_) {
        n = n_;
        directed = directed_;
        adj.assign(n, {});
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        if (!directed) adj[v].push_back(u);
    }

    std::vector<int> bfs(int source) const {
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        dist[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    }

    std::vector<int> multiSourceBfs(const std::vector<int>& sources) const {
        std::vector<int> dist(n, -1);
        std::queue<int> q;
        for (int s : sources) {
            dist[s] = 0;
            q.push(s);
        }
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : adj[u]) if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return dist;
    }

    std::vector<int> topoSort() const {
        std::vector<int> indeg(n);
        for (int u = 0; u < n; ++u) for (int v : adj[u]) ++indeg[v];
        std::queue<int> q;
        for (int i = 0; i < n; ++i) if (indeg[i] == 0) q.push(i);
        std::vector<int> order;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u]) {
                if (--indeg[v] == 0) q.push(v);
            }
        }
        if (static_cast<int>(order.size()) != n) order.clear();
        return order;
    }
};

}  // namespace contest

