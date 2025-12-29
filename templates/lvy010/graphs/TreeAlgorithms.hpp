#pragma once

#include <queue>
#include <utility>
#include <vector>

namespace contest {

struct TreeAlgorithms {
    int n = 0;
    int LOG = 0;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> up;
    std::vector<int> depth;
    std::vector<int> tin, tout;
    int timer = 0;

    TreeAlgorithms() = default;
    explicit TreeAlgorithms(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        LOG = 1;
        while ((1 << LOG) <= n) ++LOG;
        adj.assign(n, {});
        up.assign(LOG, std::vector<int>(n, -1));
        depth.assign(n, 0);
        tin.assign(n, 0);
        tout.assign(n, 0);
        timer = 0;
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void build(int root = 0) {
        dfs(root, root);
    }

    int lca(int u, int v) const {
        if (isAncestor(u, v)) return u;
        if (isAncestor(v, u)) return v;
        for (int k = LOG - 1; k >= 0; --k) {
            if (!isAncestor(up[k][u], v)) u = up[k][u];
        }
        return up[0][u];
    }

    int distance(int u, int v) const {
        int w = lca(u, v);
        return depth[u] + depth[v] - 2 * depth[w];
    }

    std::pair<int, int> diameterEndpoints() const {
        auto dist0 = bfs(0);
        int u = 0;
        for (int i = 0; i < n; ++i) if (dist0[i] > dist0[u]) u = i;
        auto distU = bfs(u);
        int v = u;
        for (int i = 0; i < n; ++i) if (distU[i] > distU[v]) v = i;
        return {u, v};
    }

private:
    void dfs(int u, int p) {
        tin[u] = ++timer;
        up[0][u] = p;
        for (int k = 1; k < LOG; ++k) up[k][u] = up[k - 1][up[k - 1][u]];
        for (int v : adj[u]) if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
        tout[u] = ++timer;
    }

    bool isAncestor(int u, int v) const {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
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
};

}  // namespace contest

