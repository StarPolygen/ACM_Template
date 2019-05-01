#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull usigned long long 
#define mod 1000000007
using namespace std; 
const int maxn=100005;
const int MOD=1005;

//ŷ�����    �и���ʱ���Ծ���ֵ�ϴ�����ķ���  ��Ϊgcd�ķ��� 
inline int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
} 

//����ŷ�����  ������Ч
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


//��չŷ�����   ��a �� b ���أ���ô x �� a ��ģ b �µ���Ԫ
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}

//������  	����˻ᱬlong long ʱ��Ҫ��Ͽ��ٳ�ʹ��  ���˷��滻Ϊ���ٳ� 
ll bin(ll x, ll n, ll MOD) {
    ll ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}

//���ٳ�	���ڿ�����O(logn)   ��˱�llʱ��Ҫʹ�� 
LL fast_multi(LL m, LL n, LL mod)//���ٳ˷� 
{
    LL ans = 0;//ע���ʼ����0������1 
    while (n)
    {
        if (n & 1)
            ans += m;
        m = (m + m) % mod;//�Ϳ�����һ����ֻ���������Ǽ� 
        m %= mod;//ȡģ����Ҫ������Χ 
        ans %= mod;
        n >>= 1;
    }
    return ans;
}
LL mul(LL a, LL b, LL m) {
    LL ret = 0;
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
 
 
//O(1) ���ٳ�  ģ���ϴ�ʱ���ܻ���� �����������ʺ�С 
inline ll ksc(ll x,ll y,ll p){
    ll z=(ld)x/p*y;
    ll res=(ull)x*y-(ull)z*p;
    return (res+p)%p;
} 
LL mul(LL u, LL v, LL p) {
    return (u * v - LL((long double) u * v / p) * p + p) % p;
}
LL mul(LL u, LL v, LL p) { // ����
    LL t = u * v - LL((long double) u * v / p) * p;
    return t < 0 ? t + p : t;
}


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
        fac[i]=(fac[i-1]*i) % MOD;  //�׳�ȡ����
    }
    //�м�,��׳���Ԫʱmaxn���ֵΪmod-1����Ϊ����Ԫ�������˴�Ϊn!��Ҫ��mod���ʲŴ�����Ԫ��
    invf[maxn] = bin(fac[maxn], MOD-2 , MOD);  //���׳���Ԫ
    for(int i=maxn-1;i>=0;i--) {
        invf[i]=(invf[i+1]*(i+1))%MOD;  //���ƽ׳���Ԫ
    }
}


/*�����
�������С��ģ�ϴ�ʱʹ����Ԫ
ǰ��ģ�壺��Ԫ-Ԥ����׳˼�����Ԫ*/

inline ll C(ll n, ll m) { // n >= m >= 0
    return n < m || m < 0 ? 0 : fac[n] * invf[m] % MOD * invf[n - m] % MOD;
}

/*
���ģ����С�����ֽϴ�ʹ�� Lucas ����
ǰ��ģ���ѡ1��������� �����ʹ�ý׳���Ԫ����fac_inv_init(MOD, MOD);��
ǰ��ģ���ѡ2��ģ�����̶���ʹ�ã��޷�����ʹ�á�*/

ll C(ll n, ll m) { // m >= n >= 0
    if (m - n < n) n = m - n;
    if (n < 0) return 0;
    ll ret = 1;
    for (int i=1; i<=n ;i++)
        ret = ret * (m - n + i) % MOD * bin(i, MOD - 2, MOD) % MOD;
    return ret;
}
ll Lucas(ll n, ll m) { // m >= n >= 0
    return m ? C(n % MOD, m % MOD) * Lucas(n / MOD, m / MOD) % MOD : 1;
}




//�����Ԥ����
ll C[M][M];
void init_C(int n) {
    for(int i=0; i<n; i++) {
        C[i][0] = C[i][i] = 1;
        for(int j=1; j<i; j++)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
    }
}




//һ�����Ҫ�� 
//���𰸻�ΪX/Y����ʽ   ��ʹ   MYͬ��X��modP�� ��M����֤M������Ψһ
//��PΪ����ʱ     MY ͬ�� X   ���ʽ�������²�����ȫ��Ӱ�������ȼ�       
//				1.ͬ��ʽ��������ͬʱ������P���ʵ�m ������ ��˿�һ��ʼ��ͨ�֣����ض�Y���Ӷ���֤X������
//     			2.��ʱ������һ�߶�Pȡģ   ������ ��˿����������оͶ�Xȡģ 
//				3. a��n���ݵ���Ԫ==a��Ԫ��n����ȡģ 
