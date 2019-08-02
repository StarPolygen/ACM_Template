//BSGS + Hash(手写) 

//Hash
struct Hash {
    static const int MOD = 1999997;
    static const int N = 1e6;
    int head[MOD + 10], nx[N], top;
    int hs[N], id[N];
    void init() {
        memset(head, -1, sizeof head);
        top = 0;
    }
    void insert(int x, int y) {
        int k = x % MOD;
        hs[top] = x; id[top] = y; nx[top] = head[k]; head[k] = top++;
    }
    int find(int x) {
        int k = x % MOD;
        for(int i = head[k]; i != -1; i = nx[i]) {
            if(hs[i] == x){
                return id[i];
            }
        }
        return -1;
    }
}hs;

//BSGS模板  
struct BSGS {
    ll V, m, lim, n;
    inline ll getsqrt(ll n) {
        //适当更改块的大小和Hash的块的大小
        ll x = (ll)pow(n, 2.0 / 3);
        return x;  //预处理的a^d上界
    }
    inline void init(ll a, ll _n) {
        n = _n;
        hs.init();
        m = getsqrt(n);
        lim = n / m + 1;  //查询的 a^cm的上界
        V = get_inv(bin(a, m ,n), n); // 1/a^m
        //预处理 a^d   d∈[0, m-1];
        hs.insert(1,0);
        ll e = 1;
        for (int i = 1; i < m; ++i) {
            e = e * a % n;
            if (hs.find(e) == -1){
                hs.insert(e, i);
            }
        }
    }
    //a^x = b % n   x = cm + d 
    //需要保证gcd(a, n) = 1, 即存在逆元
    //如果有解输出的是最小的正整数解，否则输出-1
    inline ll cal(ll b) {   
        if(b == 1) return 0;   //注意这里
        for (int i = 0; i < lim; ++i) {
            int j = hs.find(b);
            if (j != -1) return 1ll * i * m + j;
            b = V * b % n;
        }
        return -1;
    }
}bsgs;


bsgs.init(a, p);
ll ans = bsgs.cal(b);