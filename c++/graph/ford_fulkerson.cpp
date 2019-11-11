// problem: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=jp

#include<bits/stdc++.h>

using namespace std;
typedef long long ll;


const int MAX_V = 110;
const ll INF = 1e18;

struct edge {
    int to, rev;
    ll cap;
    edge(int to, ll cap, int rev): to(to), cap(cap), rev(rev) { }
};

vector<edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to, ll cap) {
    G[from].push_back(edge(to, cap, G[to].size()));
    G[to].push_back(edge(from, 0, G[from].size() - 1));
}

ll dfs(int v, int t, ll f) {
    if (v == t) return f;
    used[v] = true;
    for (int i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            ll d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

ll max_flow(int s, int t) {
    ll flow = 0;
    for (;;) {
        memset(used, 0, sizeof(used));
        ll f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }

    cout << max_flow(0, V-1) << endl;

    return 0;
}
