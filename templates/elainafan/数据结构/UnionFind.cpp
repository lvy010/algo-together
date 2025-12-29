class UnionFind {
    vector<int> fa;
    vector<int> sz;  // 集合大小
public:
    int cc;  // 连通块个数
    UnionFind(int n) : fa(n), sz(n, 1), cc(n) { ranges::iota(fa, 0); }
    int get(int x) {
        if (fa[x] != x) fa[x] = get(fa[x]);
        return fa[x];
    }
    bool is_same(int x, int y) { return get(x) == get(y); }
    bool merge(int from, int to) {
        int x = get(from), y = get(to);
        if (x == y) return false;
        fa[x] = y;
        sz[y] += sz[x];
        cc--;
        return true;
    }
    int get_size(int x) {  // 查询x所在集合大小
        return sz[get(x)];
    }
};