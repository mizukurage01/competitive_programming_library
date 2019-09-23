// Manber&Myers ( O(n (logn)^2) )
// 実装参考: 蟻本、http://drken1215.hatenablog.com/entry/2019/09/16/014600
// validation: https://www.spoj.com/problems/SARRAY/
struct SuffixArray {
    string s;
    vector<int> sa;
    inline int& operator[] (int i) {return sa[i];}

    SuffixArray(const string& s_) : s(s_) {construct_sa();}

    vector<int> rank;
    vector<int> tmp;

    // 比較関数に多くの変数が出てくるので、classとかstructでかくと簡単。
    // 比較基準はoperator()として定義すればよい。
    struct Compare_sa {
        int n, k;
        const vector<int>& rank;
        Compare_sa(int n_, int k_, const vector<int>& rank_): n(n_), k(k_), rank(rank_) {} // 初期化子リストで初期化。
        bool operator()(int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            else {
                int rank_ik = i + k <= n ? rank[i + k] : -1;
                int rank_jk = j + k <= n ? rank[j + k] : -1;
                return rank_ik < rank_jk;
            }
        }
    };

    void construct_sa() {
        int n = (int)s.size();
        sa.resize(n+1);
        rank.resize(n+1);
        tmp.resize(n+1);

        for (int i = 0; i <= n; i++) {
            sa[i] = i;
            rank[i] = i < n ? s[i] : -1;
        }

        for (int k = 1; k <= n; k *= 2) {
            // 各suffixのk*2までのprefix成分のsort
            Compare_sa csa(n, k, rank);
            sort(sa.begin(), sa.end(), csa);

            // rankの更新
            tmp[sa[0]] = 0;
            for (int i = 1; i <= n; i++) {
                tmp[sa[i]] = tmp[sa[i-1]] + (csa(sa[i-1], sa[i]) ? 1 : 0);
            }
            for (int i = 0; i <= n; i++) {
                rank[i] = tmp[i];
            }
        }
    }
};

int main() {
    string s;
    cin >> s;
    int n = s.size();
    
    SuffixArray sa(s);

    for (int i = 1; i <= n; i++) {
        cout << sa[i] << endl;
    }

    return 0;
}

