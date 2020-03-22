typedef pair<int, int> P;

struct Edge{
    int to; int cost;
    Edge(int t, int c): to(t), cost(c) { }
};
using Graph = vector<vector<Edge>>;

int MAX_V = 300;
vector<int> dijkstra(int s, Graph& g) {
    vector<int> dist(MAX_V, INF);
    dist[s] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push(P(0, s));
    while (!pq.empty()) {
        P q = pq.top(); pq.pop();
        int d = q.first;
        int v = q.second;
        if (dist[v] < d) continue;
        for (auto nexte: g[v]) {
            int nextd = nexte.cost;
            int nextv = nexte.to;
            if (dist[v] + nextd < dist[nextv]) {
                dist[nextv] = dist[v] + nextd;
                pq.push(P(dist[nextv], nextv));
            }
        }
    }
    return dist;
}

// Graph g(100);
// g[0].push_back(Edge(to, cost));
