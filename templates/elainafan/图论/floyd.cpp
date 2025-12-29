vector<vector<ll>> floyd(int n, vector<vector<int>> edges) {
    vector<vector<ll>> dp(n, vector<ll>(n, LLONG_MAX / 2));
    for (int i = 0; i <= n - 1; i++) dp[i][i] = 0;
    for (auto p : edges) {
        dp[p[0]][p[1]] = min(dp[p[0]][p[1]], 1LL * p[2]);
        dp[p[1]][p[0]] = min(dp[p[1]][p[0]], 1LL * p[2]);
    }
    for (int k = 0; k <= n - 1; k++) {
        for (int i = 0; i <= n - 1; i++) {
            if (dp[i][k] == LLONG_MAX / 2) continue;
            for (int j = 0; j <= n - 1; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    return dp;
}