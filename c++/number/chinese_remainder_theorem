// reference: https://qiita.com/drken/items/ae02240cd1f8edfc86fd


inline long long mod(long long a, long long m) {
    return (a % m + m) % m;
}

// extended euclidean algorithm
// ap + bq = gcd(a, b)
// calculate p, q   return d = gcd(a, b)
long long extGcd(long long a, long long b, long long &p, long long &q) {
    if (b == 0) {p = 1; q = 0; return a;}
    long long d = extGcd(b, a%b, q, p);
    q -= a/b * p;
    return d;
}

// Chinese Remainder Theorem
// x ≡ b1 (mod. m1)
// x ≡ b2 (mod. m2)
// >> x ≡ r (mod. lcm(m1, m2))
// return (r, m) if there is a solution, else (0, -1)
pair<long long, long long> ChineseRem(long long b1, long long m1, long long b2, long long m2) {
    long long p, q;
    long long d = extGcd(m1, m2, p, q);
    if ((b2 - b1) % d != 0) return make_pair(0, -1);
    long long m = m1 * (m2/d); // lcm of (m1, m2)
    long long tmp = (b2 - b1) / d * p % (m2/d);
    long long r = mod(b1 + m1 * tmp, m);
    return make_pair(r, m);
}
