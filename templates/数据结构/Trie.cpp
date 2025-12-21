struct Node {
    Node* son[26]{};
    bool end = false;
};
class Trie {
    Node* root = new Node();

    int find(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (!cur->son[c]) return 0;
            cur = cur->son[c];
        }
        return cur->end ? 2 : 1;
    }
    string findpre(string word) {
        Node* cur = root;
        int cnt = 0;
        for (char c : word) {
            if (cur->end) return word.substr(0, cnt);
            c -= 'a';
            cnt++;
            if (!cur->son[c]) return "";
            cur = cur->son[c];
        }
        return "";
    }
    void destory(Node* node) {
        if (!node) return;
        for (Node* son : node->son) destory(son);
        delete node;
    }

public:
    // 析构函数
    ~Trie() { destory(root); }

    // 往trie中插入word
    void insert(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (!cur->son[c]) cur->son[c] = new Node();
            cur = cur->son[c];
        }
        cur->end = true;
    }

    // 查询trie中是否有word的前缀，若有返回，若无返回空串
    string pre(string word) { return findpre(word); }

    // 查询是否存在与word相等的字符串
    bool search(string word) { return find(word) == 2; }

    // 查询是否存在以prefix为前缀的字符串
    bool startsWith(string prefix) { return find(prefix) != 0; }
};