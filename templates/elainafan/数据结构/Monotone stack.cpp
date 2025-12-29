int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> r(n, n);
    vector<int> l(n, -1);
    stack<int> s;
    for (int i = n - 1; i >= 0; i--) {
        while (!s.empty() && heights[s.top()] >= heights[i]) s.pop();
        if (!s.empty()) r[i] = s.top();
        s.push(i);
    }
    while (!s.empty()) s.pop();
    for (int i = 0; i <= n - 1; i++) {
        while (!s.empty() && heights[s.top()] >= heights[i]) s.pop();
        if (!s.empty()) l[i] = s.top();
        s.push(i);
    }
    int maxx = INT_MIN;
    for (int i = 0; i <= n - 1; i++) maxx = max(maxx, heights[i] * (r[i] - l[i] - 1));
    return maxx;
}