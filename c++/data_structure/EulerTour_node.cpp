struct EulerTour {
    vector<int> euler_tour;
    vector<int> left;
    vector<int> right;
    int n;
    int k;

    EulerTour(vector<vector<int>>& graph): n(graph.size()) {
        euler_tour.reserve(2*n);
        left.resize(n);
        right.resize(n);
        k = 0;
        dfs(0, -1, graph);
    }
    
    void dfs(int v, int p, vector<vector<int>>& graph) {
        euler_tour.push_back(v);
        left[v] = k++;
        for (int nv: graph[v]) {
            if (nv == p) continue;
            dfs(nv, v, graph);
            euler_tour.push_back(v);
            k++;
        }
        right[v] = k;
    }
};
