vector<int> toposort(int n, vector<vector<int>> edges) {
    vector<vector<int>> ma(n);
    vector<int> deg(n);
    for (auto p : edges) {
        ma[p[0]].push_back(p[1]);
        ma[p[1]].push_back(p[0]);
    }
    queue<int> q;
    for (int i = 0; i <= n - 1; i++) {
        if (deg[i] == 0) q.push(i);
    }
    vector<int> res;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        res.push_back(node);
        for (int p : ma[node]) {
            if (--deg[p] == 0) q.push(p);
        }
    }
    return res;
}