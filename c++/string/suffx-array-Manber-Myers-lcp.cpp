// Manber&Myers ( O(n (logn)^2) )
// 実装参考: 蟻本、http://drken1215.hatenablog.com/entry/2019/09/16/014600
// lcpは雑に実装した。
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

    // lcpを求める処理を追加。
    // 参考: 蟻本、https://blog.shibayu36.org/entry/2017/01/06/103956 (ここではsuffixの長い順に更新しているよう。蟻本の理解の助けに。)
    vector<int> construct_lcp() {
        int n = (int)s.size();
        vector<int> lcp(n+1); // s[sa[i]] と s[sa[i+1]]の先頭で共通している文字数。
        for (int i = 0; i <= n; i++) rank[sa[i]] = i;

        int h = 0; // 共通文字数。
        lcp[0] = 0; // 空文字なので。
        for (int i = 0; i < n; i++) {
            // suffixの長い順に処理していく（実際に更新するlcpは、処理中のsuffixの辞書順で1つ前の配列。i=n+1の処理をしなくて済むので。）
            // rank[i]は長いものからi番目(0-indexed)のsuffixの番号。
            int j = sa[rank[i]-1];

            // 共通文字数はh-1以上になる（ここの理解が1つのポイント）。（次でh以上に変更しておく。）
            if (h > 0) h--;
            for (; j+h < n && i+h < n; h++) {
                if (s[j+h] != s[i+h]) break;
            }

            lcp[rank[i]-1] = h;
        }
        return lcp;
    }
};


