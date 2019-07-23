#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <set>
#include <map>
#include <queue>
#include <iomanip>
#include <cassert>
#include <random>

using namespace std;



// 参考
// https://www.slideshare.net/iwiwi/2-12188757
// https://qiita.com/drken/items/1b7e6e459c24a83bb7fd

typedef long long VAL;

struct Tree {

    // 速い!!
    unsigned int randInt() {
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

        node_t() : val(0), size(1), sum(0) {lch = rch = NULL;}
        node_t(VAL v) : val(v), size(1), sum(v) {lch = rch = NULL;}
    };


    node_t* root;
    Tree() : root(NULL) {}
    Tree(node_t* t) : root(t) {}

    inline int size(node_t* t) {return !t ?0 :t->size;}
    inline int size() {return this->size(this->root);}

    inline VAL sum(node_t* t) {return !t ?0 :t->sum;}
    inline VAL sum() {return this->sum(this->root);}

    inline node_t* update(node_t* t) {
        t->size = size(t->lch) + size(t->rch) + 1;
        t->sum = sum(t->lch) + sum(t->rch) + t->val;
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

        if (randInt() % (l->size + r->size) < l->size) {
            l->rch = merge(l->rch, r);
            return update(l);
        } else {
            r->lch = merge(l, r->lch);
            return update(r);
        }
    }
    void merge(Tree add) {this->root = this->merge(this->root, add.root);}

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
        return Tree(s.second);
    }


    void insert(VAL val) {
        pair<node_t*, node_t*> s = this->split(this->root, this->lowerBound(val));
        this->root = this->merge(this->merge(s.first, new node_t(val)), s.second);
    }

    void erase(VAL val) {
        if (!(this->upperBound(val) - this->lowerBound(val))) return;
        pair<node_t*, node_t*> s = this->split(this->root, this->lowerBound(val));
        this->root = this->merge(s.first, this->split(s.second, 1).second);
    }
};



int main() {
    int q;
    cin >> q;
    Tree tree;
    int t;
    long long x;
    for (int i = 0; i < q; i++) {
        cin >> t >> x;
        if (t == 1) {
            tree.insert(x);
        } else {
            long long val = tree.get(x-1);
            cout << val << endl;
            tree.erase(val);
        }
    }
}

