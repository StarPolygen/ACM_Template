//Miller-Rabin O(klogn^3)
//��������
//����֤��ȷ ����5������ȷ�ʼ��ɴﵽ99% 
//ǰ�ã� ���ٳˡ�������
//int ��Χ��ֻ���� 2, 7, 61
//long long ��Χ 2, 325, 9375, 28178, 450775, 9780504, 1795265022
//3E15�� 2, 2570940, 880937, 610386380, 4130785767
//4E13�� 2, 2570940, 211991001, 3749873356 
//������FFT���ٵ�O(klogn) 
bool checkQ(ll a, ll n) {
    if (n == 2 || a >= n) return 1;
    if (n == 1 || !(n & 1)) return 0;
    ll d = n - 1;
    while (!(d & 1)) d >>= 1;
    ll t = bin(a, d, n);  // ��һ����Ҫ���ٳ�
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
//�������ֽ�  
//����㷨 ����ʱ��O(n^1/4)
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
//�õ���������0-��fcnt-1��
//�����ظ������� ��������˳���޷���֤ ��Ҫ���� 
//ע���ظ�����ʱ��Ҫ��� 
void get_fac(ll n, ll cc = 19260817) {
    if (n == 4) { fac[fcnt++] = 2; fac[fcnt++] = 2; return; }
    if (primeQ(n)) { fac[fcnt++] = n; return; }
    ll p = n;
    while (p == n) p = pollard_rho(n, --cc);
    get_fac(p); get_fac(n / p);
}
