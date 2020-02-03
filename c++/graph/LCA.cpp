struct LCA{
    vector<vector<int>> parent;
    vector<int> depth;
    int n;
    int max_k;
    vector<vector<int>> graph;

    LCA(vector<vector<int>>& _graph, int v=0): graph(_graph), n(_graph.size()), max_k(int(log2(n)) + 1) {
        parent.assign(max_k+1, vector<int>(n, -1));
        depth.assign(n, 0);
        dfs(v);
        doubling();
    }

    void dfs(int v, int p=-1) {
        for (int nv: graph[v]) {
            if (nv == p) continue;
            depth[nv] = depth[v] + 1;
            parent[0][nv] = v;
            dfs(nv, v);
        }
    }

    void doubling() {
        for (int k = 0; k < max_k; ++k) {
            for (int i = 0; i < n; ++i) {
                if (parent[k][i] == -1) {
                    parent[k+1][i] = -1;
                } else {
                    parent[k+1][i] = parent[k][parent[k][i]];
                }
            }
        }
    }

    int get_lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        for (int k = max_k; k >= 0; --k) {
            if (((depth[u] - depth[v]) >> k) & 1) {
                u = parent[k][u];
            }
        }
        if (u == v) return u;
        for (int k = max_k; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    int get_path_length(int u, int v) {
        int lca = get_lca(u, v);
        return (depth[u] - depth[lca]) + (depth[v] - depth[lca]);
    }
};




// AOJ (Lowest Common Ancestor): http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_C&lang=jp
int main() {
    int n; cin >> n;
    vector<vector<int>> graph(n);
    rep(i, n) {
        int k; cin >> k;
        rep(j, k) {
            int v; cin >> v;
            graph[i].push_back(v);
        }
    }

    LCA lca(graph);

    int q; cin >> q;
    rep(i, q) {
        int u, v; cin >> u >> v;
        cout << lca.get_lca(u, v) << endl;
    }
    

    return 0;
}
