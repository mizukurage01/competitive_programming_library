Problem: https://yukicoder.me/problems/no/430
Reference: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6

struct RollingHash {
    const uint64_t MASK30 = (1uLL << 30) - 1;
    const uint64_t MASK31 = (1uLL << 31) - 1;
    const uint64_t MOD = (1uLL << 61) - 1;
    const uint64_t POSITIVIZER = MOD * ((1uLL << 3) - 1);
    static uint32_t Base;
    vector<uint64_t> powMemo;
    vector<uint64_t> hash;

    RollingHash(const string &s) {
        int n = (int)s.size();
        hash.assign(n+1, 0);
        powMemo.assign(n+1, 1);

        for (int i = 0; i < n; i++) {
            hash[i+1] = CalcMod(Mul(hash[i], Base) + s[i]);
            powMemo[i+1] = CalcMod(Mul(powMemo[i], Base));
        }
    }

    inline uint64_t Slice(int start, int len) {
        return CalcMod(hash[start + len] + POSITIVIZER - Mul(hash[start], powMemo[len]));
    }

    inline uint64_t CalcMod(uint64_t val) {
        val = (val & MOD) + (val >> 61);
        if (val > MOD) val -= MOD;
        return val;
    }

    inline uint64_t Mul(uint64_t a, uint64_t b) {
        uint64_t au = a >> 31;
        uint64_t ad = a & MASK31;
        uint64_t bu = b >> 31;
        uint64_t bd = b & MASK31;
        uint64_t mid = ad * bu + au * bd;
        uint64_t midu = mid >> 30;
        uint64_t midd = mid & MASK30;
        return ((au * bu) << 1) + midu + (midd << 31) + ad * bd;
    }
};
uint32_t RollingHash::Base = rand() + 1000;


int main() {
    string s; cin >> s;
    int m; cin >> m;

    RollingHash rh(s);

    int ans = 0;
    
    for(i = 0; i < m; i++) {
        string c; cin >> c;
        RollingHash rh_c(c);
        for (int j = 0; j < (int)s.size() - (int)c.size() + 1; j++) {
            if (rh.Slice(j, c.size()) == rh_c.hash[c.size()]) ans++;
        }
    }
    
    cout << ans << endl;

    return 0;
}
