class Tree {
    vector<int> tree;
public:
    Tree(int n) : tree(n) {}
    void add(int i, int val) {
        for (int x = i; x < tree.size(); x += lowbit(x)) tree[x] += val;
        return;
    }
    int pre(int x) {
        int res = 0;
        for (; x > 0; x -= lowbit(x)) res += tree[x];
        return res;
    }
};

//离散化

auto sorted = nums;
ranges::sort(sorted);
sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
int m = sorted.size();
int tem1 = ranges::lower_bound(sorted, nums[0]) - sorted.begin() + 1;