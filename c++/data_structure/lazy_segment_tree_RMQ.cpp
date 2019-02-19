# problem: https://atcoder.jp/contests/nikkei2019-final/tasks/nikkei2019_final_d


#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric> // accumulate
#include <queue>
#include <string>
#include <cmath> // sqrt
#include <map>
#include <complex>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

struct LazySegmentTree {
private:
    int n;
    vector<ll> node, lazy;

public:
    LazySegmentTree(vector<ll> v) {
        int sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        lazy.resize(2*n-1, 0);

        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = max(node[i*2+1], node[i*2+2]);
    }

    void eval(int k, int l, int r) {
        if(lazy[k] != 0) {
            node[k] = lazy[k];
            if(r-l > 1) {
                lazy[2*k+1] = lazy[k];
                lazy[2*k+2] = lazy[k];
            }
            lazy[k] = 0;
        }
    }

    void update(int a, int b, ll x, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        eval(k, l, r);
        if(b <= l || r <= a) return;
        if(a <= l && r <= b) {
            lazy[k] = x;
            eval(k, l, r);
        }
        else {
            update(a, b, x, 2*k+1, l, (l+r)/2);
            update(a, b, x, 2*k+2, (l+r)/2, r);
            node[k] = max(node[2*k+1], node[2*k+2]);
        }
    }

    ll getmax(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        eval(k, l, r);
        if(b <= l || r <= a) return 0;
        if(a <= l && r <= b) return node[k];
        ll vl = getmax(a, b, 2*k+1, l, (l+r)/2);
        ll vr = getmax(a, b, 2*k+2, (l+r)/2, r);
        return max(vl, vr);
    }

};


int main() {
    int n, m;
    cin >> n >> m;
    LazySegmentTree seg(vector<ll> (n, 0));

    for (int i = 0; i < m; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        seg.update(l-1, r, t);
    }

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ans += seg.getmax(i, i+1);
    }

    cout << ans << endl;

    return 0;
}
