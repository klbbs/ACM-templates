/**   组合数（Comb, with. ModIntBase）
 *    2024-08-06: https://codeforces.com/contest/1999/submission/274744751
**/

/*
    食用方法:
    在此结构体上定义 using Z = xxx
    int或long long或者自动取模的类都可以(参见jiangly提交代码)
*/

struct Comb {
    int n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        // 这里记得把mod改为你要取模的变量/数
        _invfac[m] = _fac[m]^(long long)(mod-2);
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Z fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;


/**   组合数（小范围预处理，逆元+杨辉三角）
 *    2024-03-14: https://qoj.ac/submission/353877
 *    2023-10-06: https://qoj.ac/submission/203196
**/

/*
    使用方法:
    直接粘贴即可,设置好L和P以及改下main函数名
*/
constexpr int P = 1000000007;
constexpr int L = 10000;

int fac[L + 1], invfac[L + 1];
int sumbinom[L + 1][7];

int binom(int n, int m) {
    if (n < m || m < 0) {
        return 0;
    }
    return 1LL * fac[n] * invfac[m] % P * invfac[n - m] % P;
}

int power(int a, int b) {
    int res = 1;
    for (; b; b /= 2, a = 1LL * a * a % P) {
        if (b % 2) {
            res = 1LL * res * a % P;
        }
    }
    return res;
}

int main() {
    fac[0] = 1;
    for (int i = 1; i <= L; i++) {
        fac[i] = 1LL * fac[i - 1] * i % P;
    }
    invfac[L] = power(fac[L], P - 2);
    for (int i = L; i; i--) {
        invfac[i - 1] = 1LL * invfac[i] * i % P;
    }

    sumbinom[0][0] = 1;
    for (int i = 1; i <= L; i++) {
        for (int j = 0; j < 7; j++) {
            sumbinom[i][j] = (sumbinom[i - 1][j] + sumbinom[i - 1][(j + 6) % 7]) % P;
        }
    }
}