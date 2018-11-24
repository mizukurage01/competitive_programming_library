reference: https://qiita.com/drken/items/b97ff231e43bce50199a#3-4-拡張ユークリッドの互除法のアルゴリズム的記述

// extended euclidean algorithm
// ap + bq = gcd(a, b)
// calculate p, q   return d = gcd(a, b)
long long extGcd(long long a, long long b, long long &p, long long &q) {
    if (b == 0) {p = 1; q = 0; return a;}
    long long d = extGcd(b, a%b, q, p);
    q -= a/b * p;
    return d;
}
