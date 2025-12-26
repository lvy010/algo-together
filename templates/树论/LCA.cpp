class TreeAncestor {
    vector<int> depth;       // 深度
    vector<vector<int>> pa;  // 2^i祖先

public:
    TreeAncestor(vector<vector<int>>& edges) {  // 直接传边数组
        int n = edges.size() + 1;
        int m = bit_width(unsigned(n));
        vector<vector<int>> ma(n);  // 这里还是0-based
        for (auto& p : edges) {
            int x = p[0], y = p[1];
            ma[x].push_back(y);
            ma[y].push_back(x);
        }
        depth.resize(n);
        pa.resize(n, vector<int>(m, -1));
        auto dfs = [&](this auto&& dfs, int x, int fa) -> void {
            pa[x][0] = fa;
            for (int y : ma[x]) {
                if (y == fa) continue;
                depth[y] = depth[x] + 1;
                dfs(y, x);
            }
            return;
        };  // 预处理深度
        dfs(0, -1);
        for (int i = 0; i < m - 1; i++) {
            for (int x = 0; x < n; x++) {
                if (pa[x][i] == -1) continue;
                pa[x][i + 1] = pa[pa[x][i]][i];
            }
        }  // 预处理2^i祖先
    }

    int get_depth(int x) { return depth[x]; }  // 获取某个点的深度

    int get_kth_ancestor(int node, int k) {
        for (int x = k; node != -1 && x > 0; x -= lowbit(x)) {
            node = pa[node][countr_zero((unsigned)x)];
        }
        return node;
    }  // 得到第k个祖先，类似树状数组的倍增

    int get_lca(int x, int y) {
        if (depth[x] > depth[y]) swap(x, y);
        y = get_kth_ancestor(y, depth[y] - depth[x]);  // 先跳到深度相同
        if (x == y) return x;
        for (int i = pa[x].size() - 1; i >= 0; i--) {
            int px = pa[x][i], py = pa[y][i];
            if (px != py) {
                x = px, y = py;
            }  // 倍增跳
        }
        return pa[x][0];
    }  // 得到最近公共祖先
};