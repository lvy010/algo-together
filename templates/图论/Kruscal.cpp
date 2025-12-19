class UnionFind {
    vector<int> fa;
    vector<int> sz;

public:
    int cc;
    UnionFind(int n) : fa(n), cc(n), sz(n, 1) {
        for (int i = 0; i <= n - 1; i++) fa[i] = i;
    }
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        int dx = find(x), dy = find(y);
        if (dx == dy) return false;
        fa[dx] = dy;
        sz[dy] += sz[x];
        cc--;
        return true;
    }
    int get_size(int x) { return sz[find(x)]; }
};

ll Kruskal(int n, vector<vector<int>> edges) {
    sort(edges.begin(), edges.end(), [&](const vector<int>& x, const vector<int>& y) { return x[2] < y[2]; });
    UnionFind u(n);
    ll ans = 0;
    for (auto p : edges) {
        if (u.merge(p[0], p[1])) {
            ans += 1LL * p[2];
        }
    }
    if (u.cc > 1) return -1;
    return ans;
}