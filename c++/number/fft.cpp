# reference: https://lumakernel.github.io/ecasdqina/

const double pi = 3.1415926535897932384626433832795028841971;
vector<complex<double> > dft(vector<complex<double> > a) {
    int n = a.size();
    if (n == 1) return a;

    vector<complex<double> > a0(n/2);
    vector<complex<double> > a1(n/2);

    for (int i = 0; i < n/2; i++) a0[i] = a[i * 2];
    for (int i = 0; i < n/2; i++) a1[i] = a[i * 2 + 1];

    vector<complex<double> > dft_a0 = dft(a0);
    vector<complex<double> > dft_a1 = dft(a1);

    vector<complex<double> > dft_a(n);
    for (int i = 0; i < n; i++) {
        complex<double> zeta = complex<double>(cos(2 * pi * i / n), sin(2 * pi * i / n));
        dft_a[i] = dft_a0[i % (n/2)] + zeta * dft_a1[i % (n/2)];
    }

    return dft_a;
}

vector<complex<double> > idft(vector<complex<double> > dft_a) {
    int n = dft_a.size();
    vector<complex<double> > arranged = dft(dft_a);

    vector<complex<double> > swaped(n);
    for (int i = 0; i < n; i++) swaped[i] = arranged[(n-i) % n];

    vector<complex<double> > a(n);
    for (int i = 0; i < n; i++) a[i] = swaped[i] / complex<double>(n, 0);

    return a;
}

vector<complex<double> > conv(vector<complex<double> > a, vector<complex<double> > b) {
    int deg = a.size() + b.size();
    int n = 1;
    while (n < deg) n <<= 1;
    a.resize(n); b.resize(n);

    vector<complex<double> > dft_a = dft(a);
    vector<complex<double> > dft_b = dft(b);

    vector<complex<double> > dft_c(n);
    for (int i = 0; i < n; i++) {
        dft_c[i] = dft_a[i] * dft_b[i];
    }
    vector<complex<double> > c = idft(dft_c);

    return c;
}
