目录：
1. 阶乘和逆元
2. 组合数 		 阶乘逆元   Lucas定理   
3. 错排		
4. 卡特兰数	 
5. 二项式系数 
6. 斯特灵数	 第一类斯特灵数  第二类斯特灵数 
7. 贝尔数       贝尔三角形 贝尔数 
 



1. 阶乘和逆元
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







2. 组合数
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
//二项式系数，也是组合数 
vector<ll> binomial[MAXN];
void init_binomial()
{
    for (ll i = 0; i < MAXN; i++)
        binomial[i] = vector<ll>((unsigned) i + 1, 1);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef MOD
            binomial[i][j] = (binomial[i - 1][j] + binomial[i - 1][j - 1]) % MOD;
#else
            binomial[i][j] = binomial[i - 1][j] + binomial[i - 1][j - 1];
#endif
        }
    }
} 





3. 错排 
ll derangement[MAXN];
void init_derangement() {
    derangement[1] = 0, derangement[0] = derangement[2] = 1;
    for (ll i = 3; i < MAXN; i++)
        derangement[i] = (derangement[i - 1] + derangement[i - 2]) % MOD * (i - 1) % MOD;
}





4. 卡特兰数   1 1 2 5 14 42 132 429 1430 4862 16796 58786 （0开始） 
//卡特兰数1
ll catalan[MAXN];
#ifdef MOD
ll mod_inverse[MAXN];
#endif
void init_catalan()
{
    catalan[1] = 1;
#ifdef MOD
    mod_inverse[0] = 0, mod_inverse[1] = 1;
    for (ll i = 2; i < MAXN; i++)
        mod_inverse[i] = (MOD - MOD / i) * mod_inverse[MOD % i] % MOD;
    for (ll i = 2; i < MAXN; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) % MOD * mod_inverse[i + 1] % MOD;
#else
    for (ll i = 2; i < MAXN && i <= 33; i++)
        catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
    if (MAXN > 34) catalan[34] = 812944042149730764;
    if (MAXN > 35) catalan[35] = 3116285494907301262;
    // MAXIMUM 35 for long long
#endif
}
//卡特兰数2
vector<TYPE> catalan[MAXN]; // catalan[in_stack][out_stack]
void init_catalan2(){
    for (ll i = 0; i < MAXN; i++)
        catalan[i] = vector<TYPE>((unsigned) i + 1, 1);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef MOD
            catalan[i][j] = (catalan[i - 1][j] + catalan[i][j - 1]) % MOD;
#else
            catalan[i][j] = catalan[i - 1][j] + catalan[i][j - 1];
#endif
        }
        catalan[i][i] = catalan[i][i - 1];
    }
}




5.  超级卡特兰数    	1, 1, 3, 11, 45, 197, 903, 4279, 20793, 103049（0开始）  
						F(n)*(n+1) = (6*n-3)F(n-1) - (n-2)F(n-2)
    施罗德数		 	1, 2, 6, 22, 90, 394, 1806, 8558, 41586, 206098
						除第一项外其他项为超级卡特兰的2倍 因此可由超级卡特兰计算 


6. 斯特灵数 
//第一类斯特灵数 
ll S[MAXN][MAXN];
void init_stirling_first(){
    S[0][0] = 1;
    for (int i=1; i< MAXN;i++)
        for (int j=1; j<i + 1; j++) S[i][j] = (S[i - 1][j - 1] + (i - 1) * S[i - 1][j]) % MOD;
}
//第二类斯特灵数
ll S[MAXN][MAXN];
void init_stirling_second(){
    S[0][0] = 1;
    for (int i=1; i< MAXN;i++)
        for (int j=1; j<i + 1; j++) S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % MOD;
}



7. 贝尔数 		  1 1 2 5 15 52 203	 
// 贝尔三角形 
vector<TYPE> bell[MAXN]; // bell(i) = bell[i][i]
void init_bell()
{
    for (ll i = 0; i < MAXN; i++)
        bell[i] = vector<TYPE>((unsigned) i + 1, 0);
    bell[1][1] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        bell[i][1] = bell[i - 1][i - 1];
        for (ll j = 2; j <= i; j++)
        {
#ifdef MOD
            bell[i][j] = (bell[i][j - 1] + bell[i - 1][j - 1]) % MOD;
#else
           bell[i][j] = bell[i][j - 1] + bell[i - 1][j - 1];
endif
       }
  }
} 

//贝尔数 
TYPE bell[MAXN];
TYPE temp[MAXN];
void init_bell()
{
    bell[0] = bell[1] = temp[0] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        temp[i - 1] = bell[i - 1];
        for (ll j = i - 2; j >= 0; j--)
        {
#ifdef MOD
            temp[j] = (temp[j] + temp[j + 1]) % MOD;
#else
            temp[j] = temp[j] + temp[j + 1];
#endif
        }
        bell[i] = temp[0];
    }
}
