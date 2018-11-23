//https://www.ioi-jp.org/camp/2011/2011-sp-tasks/2011-sp-day4.pdf
// Range Maximum Query
// initial value = 0

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric> //accumulate
#include <queue>
using namespace std;
typedef long long ll;

const int MAX_N = 1 << 17;

int segN;
ll dat[MAX_N * 4];
ll a[100010], w[100010];

void init(int n){
    segN = 1;
    while (segN < n) segN *= 2;
    for (int i = 0; i < 2 * segN - 1; i++) dat[i] = 0;
}

void update(int i, ll x){
    i += segN - 1;
    dat[i] = x;
    while (i > 0){
        i = (i - 1) / 2;
        dat[i] = max(dat[i*2+1], dat[i*2+2]);
    }
}

ll query(int a, int b, int k, int l, int r){
    if (r <= a || b <= l) return 0;
    if (a <= l && r <= b) return dat[k];
    else{
        ll vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
        ll vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
        return max(vl, vr);
    }
}

int main() {
    int n;
    cin >> n;
    init(n);
    ll sum = 0;
    for (int i = 0; i < n; i++){
        cin >> w[i];
        sum += w[i];
    }
    for (int i = 0; i < n; i++){
        cin >> a[i];
        a[i]--;
    }

    for (int i = 0; i < n; i++){
        ll p = query(0, a[i], 0, 0, segN);
        update(a[i], p + w[a[i]]);
    }

    cout << (sum - query(0, segN, 0, 0, segN)) * 2 << endl;
}
