'Ŀ¼�� 
'1. ŷ�����                  ����ŷ����� 
'2. EX-GCD
'3. ɸ                        ����ɸ ŷ��ɸ Ī����˹ɸ 
'4. ������ 
'5. ���ٳ�                    O(1)���ٳ�  �������ٳ� 
'6. �׳���Ԫ
'7. �����                    (��Ԫ��Lucas�� 
'8. ţ�ٷ�������� 







'1. ŷ�����    
//�и���ʱ���Ծ���ֵ�ϴ�����ķ���  ��Ϊgcd�ķ��� 
inline ll gcd(ll a,ll b)
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







'2. ��չŷ����� 
//��a �� b ���أ���ô x �� a ��ģ b �µ���Ԫ
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}






'3. ɸ 
//��������ɸ
int Mark[MAXSIZE];  
int prime[MAXSIZE];    //�ж��Ƿ���һ������  Mark ������� index ��������  

int Prime(){	
	int index=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//����������  
        prime[++index] = i;//����õ�һ������
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//���Ŀǰ�õ���������i��Ϊ������
    }
    return index;
}










'4. ������
//����˻ᱬlong long ʱ��Ҫ��Ͽ��ٳ�ʹ��  ���˷��滻Ϊ���ٳ� 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}








'5. ���ٳ� 
//���ڿ�����O(logn)   ��˱�llʱ��Ҫʹ�� 
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
//O(1)���ٳ� 
ll mul(ll u, ll v, ll p) {
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}
ll mul(ll u, ll v, ll p) { // ����
    ll t = u * v - ll((long double) u * v / p) * p;
    return t < 0 ? t + p : t;
}







'6. �׳˺���Ԫ
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








'7. �����
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









'8. ţ�ٵ��������
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



//һ�����Ҫ�� 
//���𰸻�ΪX/Y����ʽ   ��ʹ   MYͬ��X��modP�� ��M����֤M������Ψһ
//��PΪ����ʱ     MY ͬ�� X   ���ʽ�������²�����ȫ��Ӱ�������ȼ�       
//				1.ͬ��ʽ��������ͬʱ������P���ʵ�m ������ ��˿�һ��ʼ��ͨ�֣����ض�Y���Ӷ���֤X������
//     			2.��ʱ������һ�߶�Pȡģ   ������ ��˿����������оͶ�Xȡģ 
//				3. a��n���ݵ���Ԫ==a��Ԫ��n����ȡģ 
