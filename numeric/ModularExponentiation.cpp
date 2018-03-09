// Modular Exponentiation
template <class T1, class T2>
T1 fastPow(T1 base, T2 power) {
    T1 rs = 1;
    while (power) {
        if (power & 1) rs *= base, power--;
        power >>= 1;
        base *= base;
    }

    return rs;
}

// Modular Exponentiation with MOD
template <class T1, class T2, class T3>
T1 fastPow(T1 base, T2 power, T3 mod) {
    T1 rs = 1;
    base %= mod;
    while (power) {
        if (power & 1) rs = (rs * base) % mod, power--;
        power >>= 1;
        base = (base * base) % mod;
    }

    return rs;
}