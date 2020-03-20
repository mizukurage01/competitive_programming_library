// reference0: https://snuke.hatenablog.com/entry/2014/12/01/235807
// reference1: https://snuke.hatenablog.com/entry/2017/07/18/101026
// reference2: http://potetisensei.hatenablog.com/entry/2017/07/10/174908


// MP
// a[i]:= s[0:i](<- 0,...,i-1)のprefixとsuffixが最大何文字一致しているか（ただし|s[0,i-1]|未満）
vector<int> MP(const string& s) {
    int n = s.size();
    vector<int> mp(n+1);
    mp[0] = -1;
    int j = -1;
    for (int i = 0; i < n; i++) {
        while (j >= 0 && s[i] != s[j]) j = mp[j];
        j++;
        mp[i+1] = j;
    }
    return mp;
}

// s[0:i](0,...,i-1)の最小周期は i - mp[i] で求まる


int FindKeyPos(const string& s, const string& key) {
    if (s.size() < key.size()) return -1;
    int n = s.size();
    int m = key.size();
    int j = 0;
    vector<int> mp = MP(key);
    for (int i = 0; i < n; i++) {
        while (s[i] != key[j] && j >= 0) j = mp[j];
        j++;
        if (j == m) return i - (m-1);
    }
    return -1;
}


// KMPはMPを少し変えるだけで実装できる（また今度）
