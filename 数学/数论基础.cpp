'Ŀ¼�� 
'1. ŷ�����                  ����ŷ����� 
'2. EX-GCD
'3. ɸ                        ����ɸ ŷ��ɸ Ī����˹ɸ 
'4. ������ 
'5. ���ٳ�                    O(1)���ٳ�  �������ٳ� 
'6. ţ�ٷ��������  
'7. �������ֽ� 
'8. ԭ�� 





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






'3. ����ɸ 
//����ɸ 
const int MAXSIZE; 
int Mark[MAXSIZE];     //prime[0]�� 
int prime[MAXSIZE];    //�ж��Ƿ���һ������  Mark ������� index ��������  
int Prime(){	
	int index=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//����������  
        prime[index++] = i;//����õ�һ������
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//���Ŀǰ�õ���������i��Ϊ������
    }
    return index;
}
//����ɸ+ŷ������
const LL p_max = 1E5 + 100;
LL phi[p_max];
void get_phi() {
    phi[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;
    FOR (i, 2, p_max) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            phi[i] = i - 1;
        }
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                phi[d] = phi[i] * prime[j];
                break;
            }
            else phi[d] = phi[i] * (prime[j] - 1);
        }
    }
}
//����ɸ+Ī����˹����
const LL p_max = 1E5 + 100;
LL mu[p_max];
void get_mu() {
    mu[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;
    mu[1] = 1;
    FOR (i, 2, p_max) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
        }
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                break;
            }
            else mu[d] = -mu[i];
        }
    }
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





'6. ţ�ٵ��������
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







'7. �������ֽ�
//ǰ��ģ�壺����ɸ
//��ָ�� 
ll factor[30], f_sz, factor_exp[30];
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; pr[i] <= t; ++i)
        if (x % pr[i] == 0) {
            factor_exp[f_sz] = 0;
            while (x % pr[i] == 0) {
                x /= pr[i];
                ++factor_exp[f_sz];
            }
            factor[f_sz++] = pr[i];
        }
    if (x > 1) {
        factor_exp[f_sz] = 1;
        factor[f_sz++] = x;
    }
}
//����ָ��
ll factor[30], f_sz;
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; pr[i] <= t; ++i)
        if (x % pr[i] == 0) {
            factor[f_sz++] = pr[i];
            while (x % pr[i] == 0) x /= pr[i];
        }
    if (x > 1) factor[f_sz++] = x;
} 





'8. ԭ��
//ǰ��ģ�壺����ɸ�������ݣ��ֽ�������
//Ҫ�� p Ϊ���� 
ll find_smallest_primitive_root(ll p) {
    get_factor(p - 1);
    FOR (i, 2, p) {
        bool flag = true;
        FOR (j, 0, f_sz)
            if (bin(i, (p - 1) / factor[j], p) == 1) {
                flag = false;
                break;
            }
        if (flag) return i;
    }
    assert(0); return -1;
}



//һ�����Ҫ�� 
//���𰸻�ΪX/Y����ʽ   ��ʹ   MYͬ��X��modP�� ��M����֤M������Ψһ
//��PΪ����ʱ     MY ͬ�� X   ���ʽ�������²�����ȫ��Ӱ�������ȼ�       
//				1.ͬ��ʽ��������ͬʱ������P���ʵ�m ������ ��˿�һ��ʼ��ͨ�֣����ض�Y���Ӷ���֤X������
//     			2.��ʱ������һ�߶�Pȡģ   ������ ��˿����������оͶ�Xȡģ 
//				3. a��n���ݵ���Ԫ==a��Ԫ��n����ȡģ 
