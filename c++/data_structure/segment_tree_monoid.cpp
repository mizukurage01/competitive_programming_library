template<typename Monoid_Set>
struct SegmentTree {
private:
    using bo = function<Monoid_Set(Monoid_Set, Monoid_Set)>; // Monoid - binary operation
    int n;
    vector<Monoid_Set> node;
    Monoid_Set identity_element;
    bo operation_for_internal_node;
    bo operation_for_external_node;

public:
    SegmentTree(vector<Monoid_Set> v, Monoid_Set _identity_element, bo _operation_for_internal_node, bo _operation_for_external_node): identity_element(_identity_element), operation_for_internal_node(_operation_for_internal_node), operation_for_external_node(_operation_for_external_node) {
        int sz = v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = operation_for_internal_node(node[2*i+1], node[2*i+2]);
    }

    void update(int x, Monoid_Set val) {
        x += (n - 1);
        node[x] = operation_for_external_node(node[x], val);
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = operation_for_internal_node(node[2*x+1], node[2*x+2]);
        }
    }

    Monoid_Set query(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        if(r <= a || b <= l) return identity_element;
        if(a <= l && r <= b) return node[k];

        Monoid_Set vl = query(a, b, 2*k+1, l, (l+r)/2);
        Monoid_Set vr = query(a, b, 2*k+2, (l+r)/2, r);
        return operation_for_internal_node(vl, vr);
    }
};

// AOJ - Range Minimum Query (http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A&lang=jp)
int main() {
    const ll _INF = (1LL << 31) - 1LL;
    int n, q; cin >> n >> q;
    vector<ll> a(n, _INF);

    SegmentTree<ll> seg(a, _INF, [](ll a, ll b){return min(a, b);}, [](ll a, ll b) {return b;});

    rep(i, q) {
        ll com, x, y; cin >> com >> x >> y;
        if (com == 0) seg.update(x, y);
        else cout << seg.query(x, y+1) << endl;
    }

    return 0;
}
