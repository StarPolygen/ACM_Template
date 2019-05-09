'Ŀ¼��
'1. �׳˺���Ԫ
'2. ����� 		 �׳���Ԫ   Lucas����   
'3. ����		
'4. ��������	 
'5. ����ʽϵ�� 
'6. ˹������	 ��һ��˹������  �ڶ���˹������ 
'7. ������       ���������� ������ 
 



'1. �׳˺���Ԫ
//��Ԫ   �����ݰ� ������PΪ���� 
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }
//��Ԫ   Exgcd��  ������P��Ϊ���� 
ll get_inv2(ll a, ll M) {
    static ll x, y;
    assert(ex_gcd(a, M, x, y) == 1);
    return (x % M + M) % M;
} 
//Ԥ������Ԫ
void inv_init(ll n, ll p) {
    inv[1] = 1;
    for(int i=2;i<=n;i++)
        inv[i] = (p - p / i) * inv[p % i] % p;
} 
//�׳���Ԫ 
void fact() {
    fac[0]=1;
    for(int i=1;i<=maxn;i++) {
        fac[i]=(fac[i-1]*i) % mod;  //�׳�ȡ����
    }
    //�м�,��׳���Ԫʱmaxn���ֵΪmod-1����Ϊ����Ԫ�������˴�Ϊn!��Ҫ��mod���ʲŴ�����Ԫ��
    invf[maxn] = bin(fac[maxn], mod-2 , mod);  //���׳���Ԫ
    for(int i=maxn-1;i>=0;i--) {
        invf[i]=(invf[i+1]*(i+1))%mod;  //���ƽ׳���Ԫ
    }
}







'2. �����
/*
ǰ��ģ�壺��Ԫ-�׳���Ԫ
�������С��ģ�ϴ�ʱʹ����Ԫ*/
inline ll C(ll n, ll m) { // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * invf[m] % mod * invf[n - m] % mod;
}
/*
���ģ����С�����ֽϴ�ʹ�� Lucas ����
ǰ��ģ���ѡ1��������� �����ʹ�ý׳���Ԫ����fac_inv_init(mod, mod);��
ǰ��ģ���ѡ2��ģ�����̶���ʹ�ã��޷�����ʹ�á�*/
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

//�����Ԥ����
ll C[M][M];
void init_C(int n) {
    for(int i=0; i<n; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j=1; j<i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
}
//����ʽϵ����Ҳ������� 
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





'3. ���� 
ll derangement[MAXN];
void init_derangement() {
    derangement[1] = 0, derangement[0] = derangement[2] = 1;
    for (ll i = 3; i < MAXN; i++)
        derangement[i] = (derangement[i - 1] + derangement[i - 2]) % MOD * (i - 1) % MOD;
}





'4. ��������   1 1 2 5 14 42 132 429 1430 4862 16796 58786 ��0��ʼ�� 
//��������1
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
//��������2
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




'5. ������������    	1, 1, 3, 11, 45, 197, 903, 4279, 20793, 103049��0��ʼ��  
						F(n)*(n+1) = (6*n-3)F(n-1) - (n-2)F(n-2)
   'ʩ�޵���		 	1, 2, 6, 22, 90, 394, 1806, 8558, 41586, 206098
					'	����һ����������Ϊ������������2�� ��˿��ɳ������������� 


'6. ˹������ 
//��һ��˹������ 
ll S[MAXN][MAXN];
void init_stirling_first(){
    S[0][0] = 1;
    for (int i=1; i< MAXN;i++)
        for (int j=1; j<i + 1; j++) S[i][j] = (S[i - 1][j - 1] + (i - 1) * S[i - 1][j]) % MOD;
}
//�ڶ���˹������
ll S[MAXN][MAXN];
void init_stirling_second(){
    S[0][0] = 1;
    for (int i=1; i< MAXN;i++)
        for (int j=1; j<i + 1; j++) S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j]) % MOD;
}



'7. ������ 		  1 1 2 5 15 52 203	 
// ���������� 
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


//������ 
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
