#pragma once

#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

namespace contest {

struct Dinic {
    struct Edge {
        int to;
        int rev;
        long long cap;
    };

    int n = 0;
    std::vector<std::vector<Edge>> g;
    std::vector<int> level, ptr;

    Dinic() = default;
    explicit Dinic(int n_) { init(n_); }

    void init(int n_) {
        n = n_;
        g.assign(n, {});
        level.resize(n);
        ptr.resize(n);
    }

    void addEdge(int u, int v, long long cap, bool directed = true) {
        Edge a{v, static_cast<int>(g[v].size()), cap};
        Edge b{u, static_cast<int>(g[u].size()), directed ? 0 : cap};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    long long maxFlow(int s, int t) {
        const long long INF = std::numeric_limits<long long>::max();
        long long flow = 0;
        while (bfs(s, t)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, t, INF)) flow += pushed;
        }
        return flow;
    }

private:
    bool bfs(int s, int t) {
        std::fill(level.begin(), level.end(), -1);
        std::queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto& e : g[v]) if (e.cap > 0 && level[e.to] == -1) {
                level[e.to] = level[v] + 1;
                q.push(e.to);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, int t, long long pushed) {
        if (v == t || pushed == 0) return pushed;
        for (int& i = ptr[v]; i < static_cast<int>(g[v].size()); ++i) {
            Edge& e = g[v][i];
            if (e.cap == 0 || level[e.to] != level[v] + 1) continue;
            long long tr = dfs(e.to, t, std::min(pushed, e.cap));
            if (tr == 0) continue;
            e.cap -= tr;
            g[e.to][e.rev].cap += tr;
            return tr;
        }
        return 0;
    }
};

} 

