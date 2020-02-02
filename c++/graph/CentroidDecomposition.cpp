struct CentroidDecomposition {
    vector<vector<int>> graph; // コピーしている操作重そう（かつ省けそう）
    vector<int> rank; // 0-based
    vector<int> size_of_subtree;
    int n;

    CentroidDecomposition(vector<vector<int>>& _graph): graph(_graph), n(_graph.size()) {
        rank.assign(n, -1);
        size_of_subtree.resize(n);
        FindCentroidRecursive(0);
    }

    void TreeDP(int v, int parent=-1) {
        size_of_subtree[v] = 1;
        for (int nv: graph[v]) {
            if (nv == parent || rank[nv] != -1) continue;
            TreeDP(nv, v);
            size_of_subtree[v] += size_of_subtree[nv];
        }
    }

    // Find only one centroid
    int FindCentroid(int v, int parent, int total) {
        for (int nv: graph[v]) {
            if (nv == parent || rank[nv] != -1) continue;
            if (size_of_subtree[nv] * 2 > total) return FindCentroid(nv, v, total);
        }
        return v;
    }

    void FindCentroidRecursive(int v, int k=0) {
        TreeDP(v);
        v = FindCentroid(v, -1, size_of_subtree[v]);
        rank[v] = k;
        for (int nv: graph[v]) {
            if (rank[nv] != -1) continue;
            FindCentroidRecursive(nv, k+1);
        }
    }
};


// CF Ciel the Commander: https://codeforces.com/problemset/problem/321/C

int main() {
    int n; cin >> n;
    vector<vector<int>> graph(n);
    rep(i, n-1) {
        int a, b; cin >> a >> b;
        a--; b--;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    CentroidDecomposition cd(graph);
    rep(i, n) {
        char c = 'A' + cd.rank[i];
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
