
//Miller-Rabin O(klogn^3)
//素数测试
//不保证正确 但在5个底正确率即可达到99% 

//前置： 快速乘、快速幂

//int 范围内只需检查 2, 7, 61
//long long 范围 2, 325, 9375, 28178, 450775, 9780504, 1795265022
//3E15内 2, 2570940, 880937, 610386380, 4130785767
//4E13内 2, 2570940, 211991001, 3749873356 
//可以用FFT加速到O(klogn) 

bool checkQ(ll a, ll n) {
    if (n == 2 || a >= n) return 1;
    if (n == 1 || !(n & 1)) return 0;
    ll d = n - 1;
    while (!(d & 1)) d >>= 1;
    ll t = bin(a, d, n);  // 不一定需要快速乘
    while (d != n - 1 && t != 1 && t != n - 1) {
        t = mul(t, t, n);
        d <<= 1;
    }
    return t == n - 1 || d & 1;
}

bool primeQ(ll n) {
    static vector<ll> t = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if (n <= 1) return false;
    for (ll k: t) if (!checkQ(k, n)) return false;
    return true;
}


//Pollard-Rho 
//质因数分解  
//随机算法 期望时间O(n^1/4)
mt19937 mt(time(0));
ll pollard_rho(ll n, ll c) {
    ll x = uniform_int_distribution<ll>(1, n - 1)(mt), y = x;
    auto f = [&](ll v) { ll t = mul(v, v, n) + c; return t < n ? t : t - n; };
    while (1) {
        x = f(x); y = f(f(y));
        if (x == y) return n;
        ll d = gcd(abs(x - y), n);
        if (d != 1) return d;
    }
}

ll fac[100], fcnt;

//得到的因子在0-（fcnt-1）
//保留重复质因子 但质因子顺序无法保证 需要排序 
//注意重复调用时需要清空 
void get_fac(ll n, ll cc = 19260817) {
    if (n == 4) { fac[fcnt++] = 2; fac[fcnt++] = 2; return; }
    if (primeQ(n)) { fac[fcnt++] = n; return; }
    ll p = n;
    while (p == n) p = pollard_rho(n, --cc);
    get_fac(p); get_fac(n / p);
}


//版本2
namespace miller_rabin
{
    typedef long long ll;
    typedef long double ld;

    // Number of attempts
    const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

    const int __S = sizeof(primes) / sizeof(int);

    inline ll mmul(ll a, ll b, ll MOD)
    {
        return (a*b - ll(ld(a*b)/MOD)*MOD) % MOD;
    }

    inline ll mpow(ll a, ll b, ll MOD)
    {
        ll ans = 1;
        while (b)
        {
            if (b & 1) ans = mmul(ans, a, MOD);
            a = mmul(a, a, MOD);
            b >>= 1;
        }
        return ans % MOD;
    }

    inline bool check(ll p)
    {
        for (int i = 0; i < __S; i++)
        {
            if (p == primes[i]) return true;
        }
        if (p < primes[__S-1]) return false;
        if (!(p&1)) return false;

        ll pp = p - 1;
        while (!(pp&1)) pp >>= 1;
        for (int i = 0; i < __S; i++)
        {
            ll a = primes[i];
            ll x = mpow(a, pp, p);
            ll y = x;
            ll tp = pp;
            while (tp < p)
            {
                y = mmul(x, x, p);
                if (y == 1 && x != 1 && x != p-1) return false;
                x = y;
                tp <<= 1;
            }
            if (x != 1) return false;
        }
        return true;
    }
}