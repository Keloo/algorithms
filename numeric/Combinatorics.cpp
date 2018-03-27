class Combinatorics {
private:
    vector<long long> factorial;
public:
    long long size;
    long long mod;
    Combinatorics(long long _size, long long _mod = 1e18): size(_size), mod(_mod){
        factorial.resize(_size+1);
    };
    long long fact(long long x) {
        if (!x) return 1;
        if (factorial[x]) return factorial[x];
        return factorial[x] = ((x % mod) * fact(x - 1)) % mod;
    }
};