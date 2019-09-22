// 参考: https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/
void getZarr(string s, vector<int>& z) {
    int n = s.length();
    int l, r, k;
    l = r = 0;
    for (int i = 1; i < n; i++) {
        if (i > r) {
            // de novoで一致する文字列を探す。
            l = r = i;
            while (r < n && s[r-l] == s[r]) r++;
            z[i] = r-l;
            r--;
        } else {
            k = i-l;
            if (z[k] < r-i+1) {
                // 元のprefixと一致する区間[l, r]から、重なる文字列が一意に定まる。
                z[i] = z[k];
            } else {
                // 元のprefixと一致する区間[l, r]からはみ出した部分は、一致するか一つ一つ確かめる必要がある。
                l = i;
                while (r < n && s[r-l] == s[r]) r++;
                z[i] = r-l;
                r--;
            }
        }
    }
}
