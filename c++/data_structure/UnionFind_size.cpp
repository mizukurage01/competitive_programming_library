class UnionFind {
public:
    int n;
    vector<int> parent;
    vector<int> rank;
    vector<int> cnt;
    UnionFind(int m) {
        n = m;
        parent.resize(n);
        rank.resize(n, 0);
        cnt.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) {
            return node;
        } else {
            parent[node] = find(parent[node]);
            return parent[node];
        }
    }

    void unite(int node1, int node2) {
        node1 = find(node1);
        node2 = find(node2);
        if (node1 == node2) {
            return;
        } else {
            if (rank[node1] < rank[node2]) {
                parent[node1] = node2;
                cnt[node2] += cnt[node1];
            } else if (rank[node1] > rank[node2]) {
                parent[node2] = node1;
                cnt[node1] += cnt[node2];
            } else {
                parent[node1] = node2;
                rank[node1] += 1;
                cnt[node2] += cnt[node1];
            }
        }
    }

    int size(int node) {
        return cnt[find(node)];
    }

    bool same(int node1, int node2) {
        node1 = find(node1);
        node2 = find(node2);
        if (node1 == node2) {
            return true;
        } else {
            return false;
        }
    }
};
