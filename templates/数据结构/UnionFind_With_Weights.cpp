template <typename T>
class UnionFind {
public:
    vector<int> fa;
    vector<T> dis;  // 表示x到x所在集合的代表元的距离

    UnionFind(int n) : fa(n), dis(n) {
        for (int i = 0; i <= n - 1; i++) fa[i] = i;
    }

    int get(int x) {
        if (fa[x] != x) {
            int root = get(fa[x]);
            dis[x] += dis[fa[x]];  // 递归更新x到其代表元的距离
            fa[x] = root;
        }
        return fa[x];
    }

    bool same(int x, int y) { return get(x) == get(y); }

    // 计算从from到to的相对距离，需要它们在同一个集合中
    T get_relative_distance(int from, int to) {
        get(from), get(to);
        return dis[from] - dis[to];
    }

    // 合并from和to，新增信息to-from=value
    // 若to和from不在一个集合，则返回true，否则返回是否与当前信息矛盾
    bool merge(int from, int to, T value) {
        int x = get(from), y = get(to);
        if (x == y) return dis[from] - dis[to] == value;
        dis[x] = value + dis[to] - dis[from]; // 更新代表元之间的距离
        fa[x] = y;
        return true;
    }
};