#include <iostream>

using namespace std;

// verified by http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1508 (配列と似た使い方)
// and https://atcoder.jp/contests/arc033/tasks/arc033_3 (setと似た使い方)

// 参考
// https://www.slideshare.net/iwiwi/2-12188757
// https://qiita.com/drken/items/1b7e6e459c24a83bb7fd

// コメント
// lowerBoundなどを用いて、値でソートした木構造にすることもできるが、
// 値でソートせず、配列をそのまま扱うような形で木構造を扱うこともできる。
// それぞれに応じて、insertやeraseを作成している。

typedef long long VAL;
long long INF = 1LL << 60;

struct Tree {

    // 乱数生成。速い!
    unsigned int xor128() {
        static unsigned int tx = 123456789, ty=362436069, tz=521288629, tw=88675123;
        unsigned int tt = (tx^(tx<<11));
        tx = ty; ty = tz; tz = tw;
        return ( tw=(tw^(tw>>19))^(tt^(tt>>8)) );
    }


    struct node_t{
        VAL val;
        node_t* lch;
        node_t* rch;
        int size;
        VAL sum;
        VAL mi;

        node_t() : val(0), size(1), sum(0), mi(INF) {lch = rch = NULL;}
        node_t(VAL v) : val(v), size(1), sum(v), mi(v) {lch = rch = NULL;}
    };


    node_t* root;
    Tree() : root(NULL) {}
    Tree(node_t* t) : root(t) {}

    inline int size(node_t* t) {return !t ?0 :t->size;}
    inline int size() {return this->size(this->root);}

    inline VAL sum(node_t* t) {return !t ?0 :t->sum;}
    inline VAL sum() {return this->sum(this->root);}

    inline VAL mi(node_t* t) {return !t ?INF :t->mi;}
    inline VAL mi() {return this->mi(this->root);}

    inline node_t* update(node_t* t) {
        t->size = size(t->lch) + size(t->rch) + 1;
        t->sum = sum(t->lch) + sum(t->rch) + t->val;
        t->mi = min(min(mi(t->lch), mi(t->rch)), t->val);
        return t;
    }

    inline int lowerBound(node_t* t, VAL val) {
        if (!t) return 0;
        if (val <= t->val) return lowerBound(t->lch, val);
        else return size(t->lch) + lowerBound(t->rch, val) + 1;
    }
    inline int lowerBound(VAL val) {return this->lowerBound(this->root, val);}

    inline int upperBound(node_t* t, VAL val) {
        return lowerBound(t, val+1);
    }
    inline int upperBound(VAL val) {return this->lowerBound(this->root, val+1);}

    inline int count(VAL val) {return this->lowerBound(this->root, val+1) - this->lowerBound(this->root, val);}


    inline VAL get(node_t* t, int k) {
        if (!t) return -1;
        if (k == size(t->lch)) return t->val;
        if (k < size(t->lch)) return get(t->lch, k);
        else return get(t->rch, k - size(t->lch) - 1);
    }
    inline VAL get(int k) {return get(this->root, k);}


    node_t* merge(node_t* l, node_t* r) {
        if (!l || !r) return !l ?r :l;

        if (xor128() % (l->size + r->size) < l->size) {
            l->rch = merge(l->rch, r);
            return update(l);
        } else {
            r->lch = merge(l, r->lch);
            return update(r);
        }
    }
    void merge(Tree add) {this->root = this->merge(this->root, add.root);} // 右から木構造を繋げる。

    pair<node_t*, node_t*> split(node_t* t, int k) { // [0, k), [k, n)
        if (!t) return make_pair(t, t);

        if (k <= size(t->lch)) {
            pair<node_t*, node_t*> s = split(t->lch, k);
            t->lch = s.second;
            return make_pair(s.first, update(t));
        } else {
            pair<node_t*, node_t*> s = split(t->rch, k - size(t->lch) - 1);
            t->rch = s.first;
            return make_pair(update(t), s.second);
        }
    }
    Tree split(int k) {
        pair<node_t*, node_t*> s = split(this->root, k);
        this->root = s.first;
        return Tree(s.second); // [k, n)側を返す
    }


    // setのような機能を実現（valに対して昇順となるように管理）
    void insert(VAL val) {
        pair<node_t*, node_t*> s = this->split(this->root, this->lowerBound(val));
        this->root = this->merge(this->merge(s.first, new node_t(val)), s.second);
    }

    void erase(VAL val) {
        if (!(this->upperBound(val) - this->lowerBound(val))) return;
        pair<node_t*, node_t*> s = this->split(this->root, this->lowerBound(val));
        this->root = this->merge(s.first, this->split(s.second, 1).second);
    }

    // 普通にk番目に挿入(or k番目を削除)（kに対して昇順となるように管理。高機能な配列を扱っているような感じ。）
    // valに対して昇順になる訳ではないことに注意。
    // 上のinsert, eraseと併用することはなさそう。
    void insert(int k, VAL val) {
        pair<node_t*, node_t*> s = this->split(this->root, k);
        this->root = this->merge(this->merge(s.first, new node_t(val)), s.second);
    }
    void erase(int k) {
        if (k >= this->root->size) return;
        pair<node_t*, node_t*> s = this->split(this->root, k);
        this->root = this->merge(s.first, this->split(s.second, 1).second);
    }
};


int main() {
    int n, q;
    cin >> n >> q;

    Tree tree;
    long long a;
    for (int i = 0; i < n; i++) {
        cin >> a;
        tree.insert(i, a);
    }

    int x;
    for (int i = 0; i < q; i++) {
        cin >> x;
        if (x == 0) {
            int l, r;
            cin >> l >> r;
            Tree s = tree.split(r+1);
            Tree t = tree.split(r);
            Tree u = tree.split(l);
            tree.merge(t);
            tree.merge(u);
            tree.merge(s);

        } else if (x == 1) {
            int l, r;
            cin >> l >> r;
            // [l, r]の最小値を求めるために、[l, r]だけ取り出す
            Tree s = tree.split(r+1); // sは[r+1, )
            Tree t = tree.split(l); // tは[l, r+1)
            cout << t.root->mi << endl;

            // 元に戻す
            tree.merge(t);
            tree.merge(s);

        } else if (x == 2) {
            int pos;
            long long val;
            cin >> pos >> val;
            tree.erase(pos);
            tree.insert(pos, val);
        }
    }
}

