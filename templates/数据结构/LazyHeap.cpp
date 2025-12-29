//懒删除堆，用在操作次数较多，但查询次数较少的时候
// 最大堆 LazyHeap<int> max_pq;
// 最小堆 LazyHeap<int, greater<int>> min_pq;
template<typename T, typename Compare = less<T>>
class LazyHeap {
    priority_queue<T, vector<T>, Compare> pq;
    unordered_map<T, int> remove_cnt; // 每个元素剩余需要删除的次数
    size_t sz = 0; // 堆的实际大小

    // 正式执行删除操作
    void apply_remove() {
        while (!pq.empty() && remove_cnt[pq.top()] > 0) {
            remove_cnt[pq.top()]--;
            pq.pop();
        }
    }

public:
    // 删除堆中所有应该删除的元素后，堆的实际大小
    size_t size() {
        return sz;
    }

    // 删除
    void remove(T x) {
        remove_cnt[x]++; // 懒删除
        sz--;
    }

    // 查看堆顶
    T top() {
        apply_remove();
        return pq.top(); // 真正的堆顶
    }

    // 出堆
    T pop() {
        apply_remove();
        sz--;
        T x = pq.top();
        pq.pop();
        return x;
    }

    // 入堆
    void push(T x) {
        if (remove_cnt[x] > 0) {
            remove_cnt[x]--; // 抵消之前的删除
        } else {
            pq.push(x);
        }
        sz++;
    }
};