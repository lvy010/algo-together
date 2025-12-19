vector<ll> dij(int n, vector<vector<int>> edges, int st) {
    vector<vector<pair<int, int>>> ma(n);
    for (auto p : edges) {
        ma[p[0]].emplace_back(p[1], p[2]);
        ma[p[1]].emplace_back(p[0], p[2]);
    }
    vector<ll> dis(n, LLONG_MAX);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> q;
    dis[st] = 0;
    q.emplace(0, st);
    while (!q.empty()) {
        auto [dis_x, x] = q.top();
        q.pop();
        if (dis_x > dis[x]) continue;
        for (auto [y, z] : ma[x]) {
            ll new_y = dis_x + z;
            if (new_y < dis[y]) {
                dis[y] = new_y;
                q.emplace(new_y, y);
            }
        }
    }
    return dis;
}