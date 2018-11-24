problem: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B

// 1-indexed


#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric> //accumulate
#include <queue>
using namespace std;
typedef long long ll;

int n;
int bit[1000010];
void add(int a, int w){
    for (int x = a; x <= n; x += x & -x) bit[x] += w;
}

int sum(int a){
    int ret = 0;
    for (int x = a; x > 0; x -= x & -x) ret += bit[x];
    return ret;
}

int main() {
    int q;
    cin >> n >> q;
    vector<int> com(q), x(q), y(q);
    for (int i = 0; i < q; i++){
        cin >> com[i] >> x[i] >> y[i];
    }

    for (int i = 0; i < q; i++){
        if (com[i] == 0){
            add(x[i], y[i]);
        }
        else{
            cout << sum(y[i]) - sum(x[i] - 1) << endl;
        }
    }

}
