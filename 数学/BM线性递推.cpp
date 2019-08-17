//BM 适用于mod为质数
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
using namespace std;
#define rep(i,a,n) for (int i=a;i<n;i++)
#define per(i,a,n) for (int i=n-1;i>=a;i--)
#define pb push_back
#define mp make_pair
#define all(x) (x).begin(),(x).end()
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
typedef vector<int> VI;
typedef long long ll;
typedef pair<int,int> PII;
const ll mod=1000000007;
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
 
int _,n;
namespace linear_seq {
    const int N=10010;
    ll res[N],base[N],_c[N],_md[N];
 
    vector<int> Md;
    void mul(ll *a,ll *b,int k) {
        rep(i,0,k+k) _c[i]=0;
        rep(i,0,k) if (a[i]) rep(j,0,k) _c[i+j]=(_c[i+j]+a[i]*b[j])%mod;
        for (int i=k+k-1;i>=k;i--) if (_c[i])
            rep(j,0,SZ(Md)) _c[i-k+Md[j]]=(_c[i-k+Md[j]]-_c[i]*_md[Md[j]])%mod;
        rep(i,0,k) a[i]=_c[i];
    }
    int solve(ll n,VI a,VI b) {  
        ll ans=0,pnt=0;
        int k=SZ(a);
        assert(SZ(a)==SZ(b));
        rep(i,0,k) _md[k-1-i]=-a[i];_md[k]=1;
        Md.clear();
        rep(i,0,k) if (_md[i]!=0) Md.push_back(i);
        rep(i,0,k) res[i]=base[i]=0;
        res[0]=1;
        while ((1ll<<pnt)<=n) pnt++;
        for (int p=pnt;p>=0;p--) {
            mul(res,res,k);
            if ((n>>p)&1) {
                for (int i=k-1;i>=0;i--) res[i+1]=res[i];res[0]=0;
                rep(j,0,SZ(Md)) res[Md[j]]=(res[Md[j]]-res[k]*_md[Md[j]])%mod;
            }
        }
        rep(i,0,k) ans=(ans+res[i]*b[i])%mod;
        if (ans<0) ans+=mod;
        return ans;
    }
    VI BM(VI s) {
        VI C(1,1),B(1,1);
        int L=0,m=1,b=1;
        rep(n,0,SZ(s)) {
            ll d=0;
            rep(i,0,L+1) d=(d+(ll)C[i]*s[n-i])%mod;
            if (d==0) ++m;
            else if (2*L<=n) {
                VI T=C;
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                L=n+1-L; B=T; b=d; m=1;
            } else {
                ll c=mod-d*powmod(b,mod-2)%mod;
                while (SZ(C)<SZ(B)+m) C.pb(0);
                rep(i,0,SZ(B)) C[i+m]=(C[i+m]+c*B[i])%mod;
                ++m;
            }
        }
        return C;
    }
    int gao(VI a,ll n) {
        VI c=BM(a);
        c.erase(c.begin());
        rep(i,0,SZ(c)) c[i]=(mod-c[i])%mod;
        return solve(n,c,VI(a.begin(),a.begin()+SZ(c)));
    }
};
 
int main() {
    for (scanf("%d",&_);_;_--) {
        scanf("%d",&n);
        printf("%d\n",linear_seq::gao(VI{2,24,96,416,1536,5504,18944,64000,212992,702464},n-1));
    }
}

//普适版本    
// given first m items init[0..m-1] and coefficents trans[0..m-1] or
// given first 2 *m items init[0..2m-1], it will compute trans[0..m-1]
// for you. trans[0..m] should be given as that
//      init[m] = sum_{i=0}^{m-1} init[i] * trans[i]
struct LinearRecurrence
{
    using int64 = long long;
    using vec = std::vector<int64>;
   
    static void extand(vec& a, size_t d, int64 value = 0)
    {
        if (d <= a.size()) return;
        a.resize(d, value);
    }
    static vec BerlekampMassey(const vec& s, int64 mod)
    {
        std::function<int64(int64)> inverse = [&](int64 a) {
            return a == 1 ? 1 : (int64)(mod - mod / a) * inverse(mod % a) % mod;
        };
        vec A = {1}, B = {1};
        int64 b = s[0];
        for (size_t i = 1, m = 1; i < s.size(); ++i, m++)
        {
            int64 d = 0;
            for (size_t j = 0; j < A.size(); ++j)
            {
                d += A[j] * s[i - j] % mod;
            }
            if (!(d %= mod)) continue;
            if (2 * (A.size() - 1) <= i)
            {
                auto temp = A;
                extand(A, B.size() + m);
                int64 coef = d * inverse(b) % mod;
                for (size_t j = 0; j < B.size(); ++j)
                {
                    A[j + m] -= coef * B[j] % mod;
                    if (A[j + m] < 0) A[j + m] += mod;
                }
                B = temp, b = d, m = 0;
            }
            else
            {
                extand(A, B.size() + m);
                int64 coef = d * inverse(b) % mod;
                for (size_t j = 0; j < B.size(); ++j)
                {
                    A[j + m] -= coef * B[j] % mod;
                    if (A[j + m] < 0) A[j + m] += mod;
                }
            }
        }
        return A;
    }
    static void exgcd(int64 a, int64 b, int64& g, int64& x, int64& y)
    {
        if (!b)
            x = 1, y = 0, g = a;
        else
        {
            exgcd(b, a % b, g, y, x);
            y -= x * (a / b);
        }
    }
    static int64 crt(const vec& c, const vec& m)
    {
        int n = c.size();
        int64 M = 1, ans = 0;
        for (int i = 0; i < n; ++i) M *= m[i];
        for (int i = 0; i < n; ++i)
        {
            int64 x, y, g, tm = M / m[i];
            exgcd(tm, m[i], g, x, y);
            ans = (ans + tm * x * c[i] % M) % M;
        }
        return (ans + M) % M;
    }
    static vec ReedsSloane(const vec& s, int64 mod)
    {
        auto inverse = [](int64 a, int64 m) {
            int64 d, x, y;
            exgcd(a, m, d, x, y);
            return d == 1 ? (x % m + m) % m : -1;
        };
        auto L = [](const vec& a, const vec& b) {
            int da = (a.size() > 1 || (a.size() == 1 && a[0])) ? a.size() - 1 : -1000;
            int db = (b.size() > 1 || (b.size() == 1 && b[0])) ? b.size() - 1 : -1000;
            return std::max(da, db + 1);
        };
        auto prime_power = [&](const vec& s, int64 mod, int64 p, int64 e) {
            // linear feedback shift register mod p^e, p is prime
            std::vector<vec> a(e), b(e), an(e), bn(e), ao(e), bo(e);
            vec t(e), u(e), r(e), to(e, 1), uo(e), pw(e + 1);
            ;
            pw[0] = 1;
            for (int i = pw[0] = 1; i <= e; ++i) pw[i] = pw[i - 1] * p;
            for (int64 i = 0; i < e; ++i)
            {
                a[i] = {pw[i]}, an[i] = {pw[i]};
                b[i] = {0}, bn[i] = {s[0] * pw[i] % mod};
                t[i] = s[0] * pw[i] % mod;
                if (t[i] == 0)
                {
                    t[i] = 1, u[i] = e;
                }
                else
                {
                    for (u[i] = 0; t[i] % p == 0; t[i] /= p, ++u[i])
                        ;
                }
            }
            for (size_t k = 1; k < s.size(); ++k)
            {
                for (int g = 0; g < e; ++g)
                {
                    if (L(an[g], bn[g]) > L(a[g], b[g]))
                    {
                        ao[g] = a[e - 1 - u[g]];
                        bo[g] = b[e - 1 - u[g]];
                        to[g] = t[e - 1 - u[g]];
                        uo[g] = u[e - 1 - u[g]];
                        r[g] = k - 1;
                    }
                }
                a = an, b = bn;
                for (int o = 0; o < e; ++o)
                {
                    int64 d = 0;
                    for (size_t i = 0; i < a[o].size() && i <= k; ++i)
                    {
                        d = (d + a[o][i] * s[k - i]) % mod;
                    }
                    if (d == 0)
                    {
                        t[o] = 1, u[o] = e;
                    }
                    else
                    {
                        for (u[o] = 0, t[o] = d; t[o] % p == 0; t[o] /= p, ++u[o])
                            ;
                        int g = e - 1 - u[o];
                        if (L(a[g], b[g]) == 0)
                        {
                            extand(bn[o], k + 1);
                            bn[o][k] = (bn[o][k] + d) % mod;
                        }
                        else
                        {
                            int64 coef = t[o] * inverse(to[g], mod) % mod * pw[u[o] - uo[g]] % mod;
                            int m = k - r[g];
                            extand(an[o], ao[g].size() + m);
                            extand(bn[o], bo[g].size() + m);
                            for (size_t i = 0; i < ao[g].size(); ++i)
                            {
                                an[o][i + m] -= coef * ao[g][i] % mod;
                                if (an[o][i + m] < 0) an[o][i + m] += mod;
                            }
                            while (an[o].size() && an[o].back() == 0) an[o].pop_back();
                            for (size_t i = 0; i < bo[g].size(); ++i)
                            {
                                bn[o][i + m] -= coef * bo[g][i] % mod;
                                if (bn[o][i + m] < 0) bn[o][i + m] -= mod;
                            }
                            while (bn[o].size() && bn[o].back() == 0) bn[o].pop_back();
                        }
                    }
                }
            }
            return std::make_pair(an[0], bn[0]);
        };
   
        std::vector<std::tuple<int64, int64, int>> fac;
        for (int64 i = 2; i * i <= mod; ++i)
        {
            if (mod % i == 0)
            {
                int64 cnt = 0, pw = 1;
                while (mod % i == 0) mod /= i, ++cnt, pw *= i;
                fac.emplace_back(pw, i, cnt);
            }
        }
        if (mod > 1) fac.emplace_back(mod, mod, 1);
        std::vector<vec> as;
        size_t n = 0;
        for (auto&& x : fac)
        {
            int64 mod, p, e;
            vec a, b;
            std::tie(mod, p, e) = x;
            auto ss = s;
            for (auto&& x : ss) x %= mod;
            std::tie(a, b) = prime_power(ss, mod, p, e);
            as.emplace_back(a);
            n = std::max(n, a.size());
        }
        vec a(n), c(as.size()), m(as.size());
        for (size_t i = 0; i < n; ++i)
        {
            for (size_t j = 0; j < as.size(); ++j)
            {
                m[j] = std::get<0>(fac[j]);
                c[j] = i < as[j].size() ? as[j][i] : 0;
            }
            a[i] = crt(c, m);
        }
        return a;
    }
   
    LinearRecurrence(const vec& s, const vec& c, int64 mod) : init(s), trans(c), mod(mod), m(s.size()) {}
    LinearRecurrence(const vec& s, int64 mod, bool is_prime = true) : mod(mod)
    {
        vec A;
        if (is_prime)
            A = BerlekampMassey(s, mod);
        else
            A = ReedsSloane(s, mod);
        if (A.empty()) A = {0};
        m = A.size() - 1;
        trans.resize(m);
        for (int i = 0; i < m; ++i)
        {
            trans[i] = (mod - A[i + 1]) % mod;
        }
        std::reverse(trans.begin(), trans.end());
        init = {s.begin(), s.begin() + m};
    }
    int64 calc(int64 n)
    {
        if (mod == 1) return 0;
        if (n < m) return init[n];
        vec v(m), u(m << 1);
        int msk = !!n;
        for (int64 m = n; m > 1; m >>= 1) msk <<= 1;
        v[0] = 1 % mod;
        for (int x = 0; msk; msk >>= 1, x <<= 1)
        {
            std::fill_n(u.begin(), m * 2, 0);
            x |= !!(n & msk);
            if (x < m)
                u[x] = 1 % mod;
            else
            { // can be optimized by fft/ntt
                for (int i = 0; i < m; ++i)
                {
                    for (int j = 0, t = i + (x & 1); j < m; ++j, ++t)
                    {
                        u[t] = (u[t] + v[i] * v[j]) % mod;
                    }
                }
                for (int i = m * 2 - 1; i >= m; --i)
                {
                    for (int j = 0, t = i - m; j < m; ++j, ++t)
                    {
                        u[t] = (u[t] + trans[j] * u[i]) % mod;
                    }
                }
            }
            v = {u.begin(), u.begin() + m};
        }
        int64 ret = 0;
        for (int i = 0; i < m; ++i)
        {
            ret = (ret + v[i] * init[i]) % mod;
        }
        return ret;
    }
   
    vec init, trans;
    int64 mod;
    int m;
};
   
const int mod = 1e9;
   
typedef long long ll;
   
ll Pow(ll a, ll n, ll mod)
{
    ll t = 1;
    for (; n; n >>= 1, (a *= a) %= mod)
        if (n & 1) (t *= a) %= mod;
    return t;
}
   
int main()
{
    int n, m;
    cin >> n >> m;
    std::vector<long long> f = {0, 1};
    for (int i = 2; i < m * 2 + 5; i++)
        f.push_back((f[i - 1] + f[i - 2]) % mod);
   
    for (auto& t : f) t = Pow(t, m, mod);
    for (int i = 1; i < m * 2 + 5; i++)
        f[i] = (f[i - 1] + f[i]) % mod;
    LinearRecurrence solver(f, mod, false);                //f储存前若干项 false代表不为质数
    printf("%lld\n", solver.calc(n));
}