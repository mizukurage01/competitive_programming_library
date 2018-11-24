long long GCD(long long a, long long b) {
    if (b == 0) return a;
    else return GCD(b, a % b);
}
