目录： 
1. 欧几里得                  卡常欧几里得 
2. EX-GCD
3. 筛                        线性筛 欧拉筛 莫比乌斯筛 
4. 快速幂 
5. 快速乘                    O(1)快速乘  卡常快速乘 
6. 牛顿法迭代求根  
7. 质因数分解 / 全因数分解 
8. 原根 
9. 欧拉函数 




1. 欧几里得    
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







2. 扩展欧几里得 
//若a 和 b 互素，那么 x 是 a 在模 b 下的逆元
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll ret = ex_gcd(b, a % b, y, x);
    y -= a / b * x;
    return ret;
}






3. 素数筛 
//素数筛 埃氏筛 O(nloglogn)
const int MAXSIZE; 
int Mark[MAXSIZE],ind=0;     //prime[0]起 
int prime[MAXSIZE];    //判断是否是一个素数  Mark 标记数组 ind 素数个数  
void Prime(){	
	ind=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//如标记则跳过  
        prime[ind++] = i;//否则得到一个素数
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//标记目前得到的素数的i倍为非素数
    }
}
//线性筛+欧拉函数 O(n)
const LL p_max = 1E5 + 100;
LL phi[p_max];
void get_phi() {
    phi[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;	//使用时注意在函数外初始化 
    for (int i = 2; i < p_max; i++) {
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
//线性筛+莫比乌斯函数
const LL p_max = 1E5 + 100;
LL mu[p_max];
void get_mu() {
    mu[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;
    mu[1] = 1;
    for (int i = 2; i < p_max; i++) {
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









4. 快速幂
//当相乘会爆long long 时需要配合快速乘使用  将乘法替换为快速乘 
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = x * x % mod)
        if (n & 1) ret = ret * x % mod;
    return ret;
}








5. 快速乘 
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





6. 牛顿迭代法求根
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







7. 质因数分解  
//前置模板：素数筛
//带指数 
ll factor[30], f_sz, factor_exp[30];
void get_factor(ll x) {
    f_sz = 0;
    for (ll i = 0; i < ind && prime[i] * prime[i] <= t; ++i){
        if (x % prime[i] == 0) {
            factor_exp[f_sz] = 0;
            while (x % prime[i] == 0) {
                x /= prime[i];
                ++factor_exp[f_sz];
            }
            factor[f_sz++] = prime[i];
        }
	}
    if (x > 1) {
        factor_exp[f_sz] = 1;
        factor[f_sz++] = x;
    }
}
//不带指数
ll factor[30], f_sz;
void get_factor(ll x) {
    f_sz = 0;
    ll t = sqrt(x + 0.5);
    for (ll i = 0; prime[i] <= t; ++i){ 
    	if (prime[i] > x) break; 
        if (x % prime[i] == 0) {
            factor[f_sz++] = prime[i];
            while (x % prime[i] == 0) x /= prime[i];
        }
    } 
    if (x > 1) factor[f_sz++] = x;
} 

7.2 全因数分解 
//O(sqrt(n))
vector<int> v;   //v中储存因数
v.clear();
for(int j=1;j<=sqrt(x);j++){
    if(x%j==0){
        v[i].push_back(j);
        if(x!=j*j)v[i].push_back(x/j);
    }
}sort(v.begin(),v.end());  //若需要对因数排序 

//O(全因数个数)
//前置模板: 分解质因数带指数
map<long long,int> mp;   //mp中为满足条件的因数 无需记录因数时应不使用mp
map<long long,int> ::iterator it;
void dfs(int cur,int n,long long num){ //第几个数，该数第几个，总共多少个数 ,是否组合数 
	if(cur>=n)
		return;
	dfs(cur+1,n,num);
	for(int i=1;i<=factor_exp[cur];i++){
		num*=factor[cur];
        // if(num>=b) return; //求小于b的因数个数
		mp[num]=1;
		dfs(cur+1,n,num);
	}
} 
void slove(long long num){
    mp.clear();  //初始化 注意每次都对1进行装填
    mp[1]=1;
    get_factor(num);//分解质因数 
    dfs(0,f_sz,1);  //调用全因数分解 
	printf("%d\n",mp.size()); 
	for(it=mp.begin();it!=mp.end();it++)  printf("%I64d ",it->first);
	printf("\n");
	
}


 





8. 原根
//前置模板：素数筛，快速幂，分解质因数
//要求 p 为质数 
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
//有关的原根个数 ：几个重要结论 
//1.对于任意正整数m  若原根存在，个数为 φ(φ(m))
//2.对于素数p        p,p^2均存在原根，个数分别为 φ(p-1)、(p-1)φ(p-1)
//3.对于奇素数p      p^n的原根存在，个数为  p^(n-2)*(p-1)*φ(p-1)   n>=2





9. O(log)欧拉函数 
ll eular(ll n) {
	ll ret = 1, i;
	for (i = 2; i * i <= n; i++)
		if (n % i == 0){
			n /= i, ret *= i - 1;
			while (n % i == 0)	n /= i, ret *= i;
		}
	if (n > 1)	ret *= n - 1;
	return ret;
}



