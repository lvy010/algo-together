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
    void destory(Node* node) {
        if (!node) return;
        for (Node* son : node->son) destory(son);
        delete node;
    }

public:
    ~Trie() { destory(root); }

    void insert(string word) {
        Node* cur = root;
        for (char c : word) {
            c -= 'a';
            if (!cur->son[c]) cur->son[c] = new Node();
            cur = cur->son[c];
        }
        cur->end = true;
    }

    bool search(string word) { return find(word) == 2; }

    bool startsWith(string prefix) { return find(prefix) != 0; }
};