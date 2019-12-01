template<typename T>
struct LazySegmentTree {
private:
    int n;
    vector<T> node, lazy;
    
public:
    LazySegmentTree(vector<T> v) {
        int sz = (int)v.size();
        n = 1; while(n < sz) n *= 2;
        node.resize(2*n-1);
        lazy.assign(2*n-1, -INF);
        
        for(int i=0; i<sz; i++) node[i+n-1] = v[i];
        for(int i=n-2; i>=0; i--) node[i] = max(node[i*2+1], node[i*2+2]);
    }   
    
    void eval(int k, int l, int r) {
        if(lazy[k] != -INF) {
            node[k] = lazy[k];
            if(r-l > 1) {
                lazy[2*k+1] = lazy[k];
                lazy[2*k+2] = lazy[k];
            }   
            lazy[k] = -INF;
        }   
    }   
    
    void update(int a, int b, T x, int k=0, int l=0, int r=-1) {
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
    
    T getmax(int a, int b, int k=0, int l=0, int r=-1) {
        if(r < 0) r = n; 
        eval(k, l, r);
        if(b <= l || r <= a) return -INF;
        if(a <= l && r <= b) return node[k];
        T vl = getmax(a, b, 2*k+1, l, (l+r)/2);
        T vr = getmax(a, b, 2*k+2, (l+r)/2, r);
        return max(vl, vr);
    }   
}; 
