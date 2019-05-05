'目录： 
'1. 欧几里得                  卡常欧几里得 
'2. EX-GCD
'3. 筛                        线性筛 欧拉筛 莫比乌斯筛 
'4. 快速幂 
'5. 快速乘                    O(1)快速乘  卡常快速乘 
'6. 阶乘逆元
'7. 组合数                    (逆元、Lucas） 
'8. 牛顿法迭代求根 







'1. 欧几里得    
//有负数时会以绝对值较大的数的符号  作为gcd的符号 
inline ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
} 
//卡常欧几里得  负数无效
inline int ctz(ll x) { return __builtin_ctzll(x); }
ll gcd(ll a, ll b) {
    if (!a) return b; if (!b) return a;
    int t = ctz(a | b);
    a >>= ctz(a);
    do {
        b >>= ctz(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << t;
} 







'2. 扩展欧几里得 
//若a 和 b 互素，那么 x 是 a 在模 b 下的逆元
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}






'3. 筛 
//朴素线性筛
int Mark[MAXSIZE];  
int prime[MAXSIZE];    //判断是否是一个素数  Mark 标记数组 index 素数个数  

int Prime(){	
	int index=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//如标记则跳过  
        prime[++index] = i;//否则得到一个素数
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//标记目前得到的素数的i倍为非素数
    }
    return index;
}










'4. 快速幂
//当相乘会爆long long 时需要配合快速乘使用  将乘法替换为快速乘 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}








'5. 快速乘 
//基于快速幂O(logn)   相乘爆ll时需要使用 
ll mul(ll a, ll b, ll m) {
    ll ret = 0;
    while (b) {
        if (b & 1) {
            ret += a;
            if (ret >= m) ret -= m;
        }
        a += a;
        if (a >= m) a -= m;
        b >>= 1;
    }
    return ret;
}
//O(1)快速乘 
ll mul(ll u, ll v, ll p) {
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}
ll mul(ll u, ll v, ll p) { // 卡常
    ll t = u * v - ll((long double) u * v / p) * p;
    return t < 0 ? t + p : t;
}







'6. 阶乘和逆元
//逆元   快速幂版 适用于P为素数 
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }
//逆元   Exgcd版  适用于P不为素数 
ll get_inv2(ll a, ll M) {
    static ll x, y;
    assert(ex_gcd(a, M, x, y) == 1);
    return (x % M + M) % M;
} 
//预处理逆元
void inv_init(ll n, ll p) {
    inv[1] = 1;
    for(int i=2;i<=n;i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
} 
//阶乘逆元 
void fact() {
    fac[0]=1;
    for(int i=1;i<=maxn;i++) {
        fac[i]=(fac[i-1]*i) % mod;  //阶乘取余打表
    }
    //切记,求阶乘逆元时maxn最大值为mod-1，因为求逆元的数（此处为n!）要和mod互质才存在逆元。
    invf[maxn] = bin(fac[maxn], mod-2 , mod);  //最大阶乘逆元
    for(int i=maxn-1;i>=0;i--) {
        invf[i]=(invf[i+1]*(i+1))%mod;  //递推阶乘逆元
    }
}








'7. 组合数
/*
前置模板：逆元-阶乘逆元
如果数较小，模较大时使用逆元*/
inline ll C(ll n, ll m) { // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * invf[m] % mod * invf[n - m] % mod;
}
/*
如果模数较小，数字较大，使用 Lucas 定理
前置模板可选1：求组合数 （如果使用阶乘逆元，需fac_inv_init(mod, mod);）
前置模板可选2：模数不固定下使用，无法单独使用。*/
ll C(ll n, ll m) { // m >= n >= 0
    if (m - n < n) n = m - n;
    if (n < 0) return 0;
    ll ret = 1;
    for (int i=1; i<=n ;i++)
        ret = ret * (m - n + i) % mod * bin(i, mod - 2, mod) % mod;
    return ret;
}
ll Lucas(ll n, ll m) { // m >= n >= 0
    return m ? C(n % mod, m % mod) * Lucas(n / mod, m / mod) % mod : 1;
}
//组合数预处理
ll C[M][M];
void init_C(int n) {
    for(int i=0; i<n; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j=1; j<i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
}









'8. 牛顿迭代法求根
ll sqrt(ll x) {
    if (x == 0) return 0;
    double last = 0;
    double res = 1;
    while (res != last)
    {
        last = res;
        res = (res + x / res) / 2;
    }
    return ll(res);
} 



//一类输出要求： 
//将答案化为X/Y的形式   求使   MY同余X（modP） 的M，保证M存在且唯一
//在P为质数时     MY 同余 X   这个式子做以下操作完全不影响结果，等价       
//				1.同余式左右两边同时乘以与P互质的m ——》 因此可一开始就通分，给特定Y，从而保证X是整数
//     			2.随时在其中一边对P取模   ——》 因此可以在运算中就对X取模 
//				3. a的n次幂的逆元==a逆元的n次幂取模 
