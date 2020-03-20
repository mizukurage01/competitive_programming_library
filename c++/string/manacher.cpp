// reference: https://snuke.hatenablog.com/entry/2014/12/02/235837
// ex. abaaababa -> 121412321
// 偶数長の回文は a$b$cのようにダミー文字を間に挟むことで検出できる
// snukeさんの場合分けしたコード（下のものではない）がわかりやすい

vector<int> Manacher(const string& s) {
    int i = 0, j = 0, n = s.size();
    vector<int> radius(n);
    while (i < n) {
        while (i-j >= 0 && i+j < n && s[i-j] == s[i+j]) ++j;
        radius[i] = j;
        int k = 1;
        while (i-k >= 0 && i+k < n && k+radius[i-k] < j) radius[i+k] = radius[i-k], ++k;
        i += k; j -= k;
    }
}

