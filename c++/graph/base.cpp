struct Edge{
    int to; int cost;
    Edge(int t, int c): to(t), cost(c) { }
};
using Graph = vector<vector<Edge>>;

int MAX_V = 300;
template<typename T>
vector<T> dijkstra(int s, Graph& g, T INF) {
    vector<T> dist(MAX_V, INF);
    dist[s] = 0;
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
    pq.push(pair<T, int>(0, s));
    while (!pq.empty()) {
        pair<T, int> q = pq.top(); pq.pop();
        T d = q.first;
        int v = q.second;
        if (dist[v] < d) continue;
        for (auto nexte: g[v]) {
            T nextd = nexte.cost;
            int nextv = nexte.to;
            if (dist[v] + nextd < dist[nextv]) {
                dist[nextv] = dist[v] + nextd;
                pq.push(pair<T, int>(dist[nextv], nextv));
            }
        }
    }
    return dist;
}



// Bellman-Ford: vector<tuple<int, int, int>> g;  g.emplace_back(from,to,cost)
// Warshall-Floyd: vector<vector<int>> g(n, vector<int>(n,INF));


// "Bellman-Ford"
// vector<int> dist(n, INF);
// int sv = 0;
// dist[sv] = 0;
// bool update = true;
// int iter = 0;
// while (update) {
//     update = false;
//     rep(i, m) {
//         int from, to, cost;
//         tie(from, to, cost) = g[i];
//         int newdist = dist[from] + cost;
//         if (dist[to] > newdist) {
//             update = true;
//             dist[to] = newdist;
//         }
//     }
//     iter++;
//     if (iter > n) {
//         cout << -1 << endl;
//         return 0;
//     }
// }
