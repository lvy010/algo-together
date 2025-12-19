vector<int> kmp(const string& text, const string& pattern) {
    int m = pattern.size();
    vector<int> pi(m);
    int cnt = 0;
    for (int i = 1; i < m; i++) {
        char b = pattern[i];
        while (cnt && pattern[cnt] != b) cnt = pi[cnt - 1];
        if (pattern[cnt] == b) cnt++;
        pi[i] = cnt;
    }
    vector<int> res;
    cnt = 0;
    for (int i = 0; i < text.size(); i++) {
        char b = text[i];
        while (cnt && pattern[cnt] != b) {
            cnt = pi[cnt - 1];
        }
        if (pattern[cnt] == b) cnt++;
        if (cnt == m) {
            res.push_back(i - m + 1);
            cnt = pi[cnt - 1];
        }
    }
    return res;
}