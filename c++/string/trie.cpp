// ref: https://ei1333.github.io/luzhiled/snippets/structure/trie.html

template<int char_size>
struct TrieNode {
    int nxt[char_size];
    int exist;

    TrieNode(): exist(0) {
        memset(nxt, -1, sizeof(nxt));
    }
};

template<int char_size, int margin>
struct Trie {
    using Node = TrieNode<char_size>;
    vector<Node> nodes;
    int root;

    Trie(): root(0) {
        nodes.push_back(Node());
    }

    void add(const string &str, int str_index=0, int node_index=0) {
        if (str_index == str.size()) return;
        const int c = str[str_index] - margin;
        if (nodes[node_index].nxt[c] == -1) {
            nodes[node_index].nxt[c] = (int)nodes.size();
            nodes.push_back(Node());
        }
        add(str, str_index + 1, nodes[node_index].nxt[c]);
        nodes[node_index].exist++;
    }

    bool find(const string &str, int str_index=0, int node_index=0) {
        if (str_index == str.size()) return true;
        const int c = str[str_index] - margin;
        if (nodes[node_index].nxt[c] == -1) return false;
        return find(str, str_index + 1, nodes[node_index].nxt[c]);
    }

    int add_count() const {
        return nodes[0].exist;
    }

    int node_size() const {
        return (int)nodes.size();
    }
};
