template <typename T>
class SegmentTree {
    int n;
    vector<T> tree;
    T merge_val(T a, T b) const { return max(a, b); } // 合并子树

    void maintain(int node) { // 维护整棵树
        tree[node] = merge_val(tree[node * 2], tree[node * 2 + 1]);
    }

    void build(const vector<T>& a, int node, int l, int r) { 
        if (l == r) {
            tree[node] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(a, node * 2, l, m);
        build(a, node * 2 + 1, m + 1, r);
        maintain(node);
    } // 建树

    void update(int node, int l, int r, int i, T val) {
        if (l == r) {
            tree[node] = val;
            return;
        }
        int m = (l + r) / 2;
        if (i <= m)
            update(node * 2, l, m, i, val);
        else
            update(node * 2 + 1, m + 1, r, i, val);
        maintain(node);
    } // 更新i处的值为val

    T query(int node, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return tree[node];
        int m = (l + r) / 2;
        if (qr <= m) return query(node * 2, l, m, ql, qr);
        if (ql > m) return query(node * 2 + 1, m + 1, r, ql, qr);
        T l_res = query(node * 2, l, m, ql, qr);
        T r_res = query(node * 2 + 1, m + 1, r, ql, qr);
        return merge_val(l_res, r_res);
    } // 查询[ql,qr]的值

public:
    SegmentTree(int n, T init_val) : SegmentTree(vector<T>(n, init_val)) {}

    SegmentTree(const vector<T>& a)
        : n(a.size()), tree(2 << bit_width(a.size() - 1)) {
        build(a, 1, 0, n - 1);
    } // 传入一个数组维护

    void update(int i, T val) { update(1, 0, n - 1, i, val); } // 更新i的值为val

    T query(int ql, int qr) const { return query(1, 0, n - 1, ql, qr); } // 查询[ql,qr]的值

    T get(int i) const { return query(1, 0, n - 1, i, i); } // 取出i处的值

    T find(int val, int node, int l, int r) {
        if (tree[node] < val) return -1;
        if (l == r) {
            tree[node] = -1;
            return l;
        }
        int mid = (l + r) / 2;
        int res = find(val, node * 2, l, mid);
        if (res < 0) res = find(val, node * 2 + 1, mid + 1, r);
        maintain(node);
        return res;
    } // 线段树二分，查询最早的大于等于val的下标

    
};

    int find(int val, int node, int l, int r, int qr) {
        if (M - tree[node].first < val) return -1;
        if (l > qr) return -1;
        if (l == r) return l;
        int mid = (l + r) / 2;
        if (M - tree[node * 2].first >= val) return find(val, node * 2, l, mid, qr);
        if (qr > mid) return find(val, node * 2 + 1, mid + 1, r, qr);
        return -1;
    }  // 线段树二分，查询最早的大于等于val的下标