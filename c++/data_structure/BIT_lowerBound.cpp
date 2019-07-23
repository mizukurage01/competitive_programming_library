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

using namespace std;

typedef long long ll;


// 参考
// http://hos.ac/slides/20140319_bit.pdf
int N = 1 << 18;
int bit[1 << 18];

void add(int a, int w) { 
    for (int x = a; x <= N; x += (x & -x)) bit[x] += w;
}

int sum(int a) {
    int res = 0;
    for (int x = a; x > 0; x -= (x & -x)) res += bit[x];
    return res;
}

int lowerBound(int w) {
    if (w <= 0) return 0;
    int x = 0;
    for (int k = N; k > 0; k /= 2) {
        if (x + k <= N && bit[x + k] < w) {
            w -= bit[x + k];
            x += k;
        }
    }
    return x + 1;
}

int main() {
    int q;
    cin >> q;
    int t, x;
    for (int i = 0; i < q; i++) {
        cin >> t >> x;
        if (t == 1) {
            add(x, 1);
        } else {
            assert(t==2);
            int k = lowerBound(x);
            cout << k << endl;
            assert(sum(k) - sum(k-1) == 1);
            add(k, -1);
        }
    }


    return 0;
}

