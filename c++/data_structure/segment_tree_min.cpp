// reference: http://tsutaj.hatenablog.com/entry/2017/03/29/204841

template<typename T>
struct SegmentTree {
private:
    int n;
    vector<T> node;

public:
    SegmentTree(vector<T> v) {
        int sz = v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = min(node[2*i+1], node[2*i+2]);
    }

    void update(int x, T val) {
        x += (n - 1);
        node[x] = val;
        while(x > 0) {
            x = (x - 1) / 2;
            node[x] = min(node[2*x+1], node[2*x+2]);
        }
    }

    T getmin(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n;
        if(r <= a || b <= l) return INF;
        if(a <= l && r <= b) return node[k];

        T vl = getmin(a, b, 2*k+1, l, (l+r)/2);
        T vr = getmin(a, b, 2*k+2, (l+r)/2, r);
        return min(vl, vr);
    }
};
