# ACM模板

___

## 一切的开始

#### Java I/O

~~~java
static class InputReader {
        public BufferedReader reader;
        public StringTokenizer tokenizer;
 
        public InputReader(InputStream stream) {
            reader = new BufferedReader(new InputStreamReader(stream), 32768);
            tokenizer = null;
        }
 
        public String next() {
            while (tokenizer == null || !tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            return tokenizer.nextToken();
        }
 
        public int nextInt() {
            return Integer.parseInt(next());
        }
 
        public long nextLong() {
            return Long.parseLong(next());
        }

 }
    public static void main(String []args) {
        InputStream inputStream = System.in;
        OutputStream outputStream = System.out;
        InputReader in = new InputReader(inputStream);
        PrintWriter out = new PrintWriter(outputStream);
        int u=121;
        slove(in,out);
        out.close();
    }
    static void slove(InputReader in, PrintWriter out){   //Slove 里的内容是真正的解题代码
    
    }
~~~

#### C++

~~~C
关闭同步：ios::sync_with_stdio(false);
自动优化：#pragma GCC optimize(1)
~~~



## 字符串

#### KMP

```c++
Java										  C++
//KMP                                            //参数为模板串和next数组
//求解next数组                                    //字符串均从下标0开始
public static int[] getNext(String s) {          int nt[10000+1];
    char[] c = s.toCharArray();                  char a[K],b[10001];
    int len = s.length();                        void kmp_next(char *T,int *nt)
    int[] next = new int[len + 1];               {
    int i = 0, j = -1;                           	nt[0]=0;
    next[i] = j;								 for(int i=1,j=0,m=strlen(T);i<m;i++)
    while (i < len) {                               {
        if (j == -1 || c[i] == c[j]) {                 while(j&&T[i]!=T[j])j=nt[j-1];
            i++;									if(T[i]==T[j])j++;
            j++;									nt[i]=j;}}
            next[i] = j;					   int kmp(char *S,char *T,int *nt){
        } else j = next[j];						   kmp_next(T,nt);
    }										     int ans=0,sn=strlen(S),tn=strlen(T);
    return next;								  for(int i=0,j=0;i<sn;i++){
}													while(j&&S[i]!=T[j])j=nt[j-1];
循环节长度：len-next[len];							 if(S[i]==T[j])j++;
循环次数：len/(len-next[len]);						  if(j==tn) ans++; 
												}return ans;
											}
```



#### AC 自动机

~~~C
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> P;
const int maxn = 1000010;
const int maxm = 50 * 10010;
int n;
char t[60], s[maxn];

struct AC {
	int ch[maxm][26];
	int val[maxm];
	int fail[maxm], last[maxm];
	int sz;
	void clear() { memset(ch[0], 0, sizeof(ch[0])); sz = 1; }
	int idx(char x) { return x - 'a'; }
	void insert(char *s) {
		int u = 0;
		int n = strlen(s);
		for (int i = 0; i<n; i++)
		{
			int c = idx(s[i]);
			if (!ch[u][c])
			{
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = 0;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
		val[u]++;
	}
	void getfail() {
		queue<int> q;
		fail[0] = 0;
		int u = 0;
		for (int i = 0; i<SIGMA_SIZE; i++){
			u = ch[0][i];
			if (u) { q.push(u); fail[u] = 0; last[u] = 0; }
		}
		while (!q.empty()){
			int r = q.front(); q.pop();
			for (int i = 0; i<SIGMA_SIZE; i++){
				u = ch[r][i];
				if (!u) { ch[r][i] = ch[fail[r]][i]; continue; }
				q.push(u);
				int v = fail[r];
				while (v && !ch[v][i])v = fail[v];
				fail[u] = ch[v][i];
				last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
			}
		}
	}
	int find(char *s){
		int u = 0, cnt = 0;
		int n = strlen(s);
		for (int i = 0; i<n; i++){
			int c = idx(s[i]);
			u = ch[u][c];
			int temp = 0;//必须赋初值为0，表示如果下面两个判断都不成立的时候while可以正常执行
			if (val[u])
				temp = u;
			else if (last[u])
				temp = last[u];
			while (temp)
			{
				cnt += val[temp];
				val[temp] = 0;
				temp = last[temp];
			}
		}
		return cnt;
	}
}tree;
int main()
{
	int T;
	scanf("%d", &T);
	while (T--)	{
		scanf("%d", &n);
		tree.clear();
		for (int i = 1; i <= n; i++){
			scanf("%s", t);
			tree.insert(t);
		}
		tree.getfail();
		scanf("%s", s);
		int ans = tree.find(s);
		printf("%d\n", ans);
	}
	return 0;
}
/*
1 5 she he say shr her yasherhs
*/
~~~

## 数学

#### 快速幂取模/逆元

```
LL bin(LL x, LL n, LL MOD) {
    LL ret = MOD != 1;
    for (x %= MOD; n; n >>= 1, x = x * x % MOD)
        if (n & 1) ret = ret * x % MOD;
    return ret;
}
inline LL get_inv(LL x, LL p) { return bin(x, p - 2, p); }
```

#### 素数筛构造

```
//朴素线性筛
int Mark[MAXSIZE];  
int prime[MAXSIZE];    //判断是否是一个素数  Mark 标记数组 index 素数个数  
int Prime(){      
	int index = 0;      memset(Mark,0,sizeof(Mark));      
	for(int i = 2; i < MAXSIZE; i++) {//如果未标记则得到一个素数     
    	if(Mark[i] == 0){              
    		prime[index++] = i;          
    	}//标记目前得到的素数的i倍为非素数          
    	for(int j = 0; j < index && prime[j] * i < MAXSIZE; j++) {              
    		Mark[i * prime[j]] = 1;              
    		if(i % prime[j] == 0)   break;         
    	}      
    }      
    return index;  即素数个数
 }  
```

#### 矩阵快速幂FWT

~~~C
//FWT C++模板
void FWT(int a[],int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++){
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=(x+y)%MOD,a[i+j+d]=(x-y+MOD)%MOD;
                //xor:a[i+j]=x+y,a[i+j+d]=(x-y+MOD)%MOD;
                //and:a[i+j]=x+y;
                //or:a[i+j+d]=x+y;
            }
}
 
void UFWT(int a[],int n){
    for(int d=1;d<n;d<<=1)
        for(int m=d<<1,i=0;i<n;i+=m)
            for(int j=0;j<d;j++)
            {
                int x=a[i+j],y=a[i+j+d];
                a[i+j]=1LL*(x+y)*inv2%MOD,a[i+j+d]=(1LL*(x-y)*inv2%MOD+MOD)%MOD;
                //xor:a[i+j]=(x+y)/2,a[i+j+d]=(x-y)/2;
                //and:a[i+j]=x-y;
                //or:a[i+j+d]=y-x;
            }
}
~~~

#### 杜教筛

例题：

![1554975241125](C:\Users\lenovo\AppData\Local\Temp\1554975241125.png)

~~~
#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define N 5001000
#define mod 1000000007
#define ll long long
using namespace std;
template<typename T>inline void read(T &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}
//杜教筛题目的关键是寻找配凑h和g 使得h=f*g 
long long f[N],sum[N];



//快速幂 求逆元 
int inv3;
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    while(b) {
        if(b&1){
            res=res*a%c;
        }
        a=a*a%c;
        b>>=1;
    }
    return res;
}

//暴力求解前根号n待求积性函数的前缀和 ，get内的代码不具有普适性 
void get(int maxn)
{
	for(int i=1;i<=maxn;++i){
        f[i]=(f[i]+(1LL*i*i-3*i+2));
        for(int j=2*i;j<=maxn;j+=i){
            f[j]=(f[j]-f[i]);
        }
    }
    for(int i=1;i<=maxn;++i) {
        f[i]=(f[i-1]+f[i])%mod;
    }

}


//乘法取模操作 
ll mul(ll a,ll b){
	return (a*b)%mod;
}
//杜教筛 
tr1::unordered_map<ll,int> mp;
long long djsf(ll n)
{
    if(n<=1e6) return f[n];
    if(mp[n]) return mp[n];
    ll ans=(((mul(n,mul(n,n))-mul(3,mul(n,n))+mod)%mod+2*n)%mod*inv3)%mod;//h的前缀和 
    for(ll l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        ans=(ans-(r-l+1)*djsf(n/l)%mod+mod)%mod;  //递归减去Σg(d)S(n/d) 
        
    }
    
    return mp[n]=ans;

}

int main()
{
    int t;
    read(t);
    inv3=fast_exp(3,mod-2,mod);
    get(1e6);
    while(t--)
    {
        static int n;
        read(n);
        printf("%lld\n",djsf(n));
    }
    return 0;
}
~~~

#### 高斯消元

~~~
#include <bits/stdc++.h>
using namespace std;

namespace Gaussian_elimination
{
    const double eps = 1e-8;
    vector<vector<double> > a;
    int n = 0;
    int augment_dimension = 1;

    inline void initialize() { a.assign((unsigned long)n, vector<double>(n + augment_dimension, 0)); }

    inline int sign(const double x) { return x < -eps ? -1 : x > eps; }

    bool Gaussian_elimination()
    {
        assert(n > 0);
        int r;
        double f;
        for (int i = 0; i < n; ++i)
        {
            r = i;
            for (int j = i + 1; j < n; ++j) if (sign(fabs(a[j][i]) - fabs(a[r][i])) == 1) r = j;
            if (sign(a[r][i]) == 0) return false;
            if (r != i) for (int j = 0; j < n + augment_dimension; ++j) swap(a[r][j], a[i][j]);
            for (int k = i + 1; k < n; ++k)
            {
                f = a[k][i] / a[i][i];
                for (int j = i; j < n + augment_dimension; ++j) a[k][j] -= f * a[i][j];
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
                for (int k = n; k < n + augment_dimension; ++k)
                    a[i][k] -= a[j][k] * a[i][j];
            for (int k = n; k < n + augment_dimension; ++k)
                a[i][k] /= a[i][i];
        }
        return true;
    }
}

namespace Gaussian_elimination
{
    const int MOD = 0x3b9aca07;

    inline int __sub__(int a, const int b) { a -= b; return a < 0 ? a + MOD : a; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }
    inline int __pow__(int a, long long b) { int r = 1; for (; b; b >>= 1, a = __mul__(a, a)) { if (b & 1) r = __mul__(r, a); } return r; }

    vector<vector<int> > a;
    vector<int> diagonal;
    int n = 0;
    int augment_dimension = 1;

    inline void initialize()
    {
        a.assign((unsigned long)n, vector<int>(n + augment_dimension, 0));
        diagonal.assign((unsigned long)n, 0);
    }

    bool Gaussian_elimination()
    {
        assert(n > 0);
        int r;
        int f;
        for (int i = 0; i < n; ++i)
        {
            r = i;
            for (int j = i + 1; j < n; ++j) if (a[j][i] > a[r][i]) r = j;
            if (a[r][i] == 0) return false;
            if (r != i) for (int j = 0; j < n + augment_dimension; ++j) swap(a[r][j], a[i][j]);
            diagonal[i] = __pow__(a[i][i], MOD - 2);
            for (int k = i + 1; k < n; ++k)
            {
                f = __mul__(a[k][i], diagonal[i]);
                for (int j = i; j < n + augment_dimension; ++j) a[k][j] = __sub__(a[k][j], __mul__(f, a[i][j]));
            }
        }
        for (int i = n - 1; i >= 0; --i)
        {
            for (int j = i + 1; j < n; ++j)
                for (int k = n; k < n + augment_dimension; ++k)
                    a[i][k] = __sub__(a[i][k], __mul__(a[j][k], a[i][j]));
            for (int k = n; k < n + augment_dimension; ++k)
                a[i][k] = __mul__(a[i][k], diagonal[i]);
        }
        return true;
    }
}

~~~

#### 矩阵快速幂&矩阵运算&LU分解

~~~
#include <bits/stdc++.h>
using namespace std;
//矩阵快速幂 
namespace matrix
{
    const int MOD = 0x3b9aca07;
    inline int __add__(int a, const int b) { a += b; return a < MOD ? a : a - MOD; }
    inline int __mul__(long long a, const int b) { a *= b; return (int) (a < MOD ? a : a - a / MOD * MOD); }

    typedef unsigned long long ull;
    template <typename T>
    class Matrix
    {
    public:
        ull n;
        bool cyclic = false;
        vector<vector<T> > a;
        Matrix() {}
        Matrix(ull n) : n(n) { init(); }
        vector<T> &operator [] (ull i) { return a[i]; }
        Matrix<T> operator * (Matrix &b) const
        {
            Matrix<T> res(n);
            if (cyclic)
            {
                res.cyclic = true;
                for (int k = 0; k < n; k++)
                    if (a[0][k])
                        for (int j = 0; j < n; j++)
                            if (b[k][j])
                                res[0][j] = __add__(res[0][j], __mul__(a[0][k], b[k][j]));
                for (int i  = 0; i < n - 1; i++)
                {
                    res[i + 1][0] = res[i][n - 1];
                    for (int j = 0; j < n - 1; j++) res[i + 1][j + 1] = res[i][j];
                }
            }
            else
                for (int k = 0; k < n; k++)
                    for (int i = 0; i < n; i++)
                        if (a[i][k])
                            for (int j = 0; j < n; j++)
                                res[i][j] = __add__(res[i][j], __mul__(a[i][k], b[k][j]));
            return res;
        }

        Matrix<T> operator^(ull t) const
        {
            assert(n >= 0);
            Matrix<T> res(n);
            res.cyclic = cyclic;
            for (int i = 0; i < n; i++) res[i][i] = 1;
            Matrix<T> tmp = *this;
            for (; t; t >>= 1)
            {
                if (t & 1) res = res * tmp;
                tmp = tmp * tmp;
            }
            return res;
        }

        void print()
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    cout << a[i][j] << " \n"[j == n - 1];
        }

    private:
        void init() { a = vector<vector<T> >(n, vector<T>(n, 0)); }
    };
}
using matrix::Matrix;
//矩阵运算 
namespace matrix
{
    typedef unsigned long long ull;
    template <typename T>
    class Matrix
    {
    public:
        ull n;
        bool cyclic = false;
        vector<vector<T> > a;
        Matrix() {}
        Matrix(ull n) : n(n) { init(); }
        vector<T> &operator [] (ull i) { return a[i]; }
        Matrix<T> operator * (Matrix &b) const
        {
            Matrix<T> res(n);
            if (cyclic)
            {
                res.cyclic = true;
                for (int k = 0; k < n; k++)
                    if (a[0][k])
                        for (int j = 0; j < n; j++)
                            if (b[k][j])
                                res[0][j] += a[0][k] * b[k][j];
                for (int i  = 0; i < n - 1; i++)
                {
                    res[i + 1][0] = res[i][n - 1];
                    for (int j = 0; j < n - 1; j++) res[i + 1][j + 1] = res[i][j];
                }
            }
            else
                for (int k = 0; k < n; k++)
                    for (int i = 0; i < n; i++)
                        if (a[i][k])
                            for (int j = 0; j < n; j++)
                                res[i][j] += a[i][k] * b[k][j];
            return res;
        }

        Matrix<T> operator^(ull t) const
        {
            assert(n >= 0);
            Matrix<T> res(n);
            res.cyclic = cyclic;
            for (int i = 0; i < n; i++) res[i][i] = 1;
            Matrix<T> tmp = *this;
            for (; t; t >>= 1)
            {
                if (t & 1) res = res * tmp;
                tmp = tmp * tmp;
            }
            return res;
        }

        void print()
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    cout << a[i][j] << " \n"[j == n - 1];
        }

    private:
        void init() { a = vector<vector<T> >(n, vector<T>(n, 0)); }
    };
}
using matrix::Matrix;
//LU分解 
namespace matrix
{
    typedef double db;
    const db eps = 1e-5;
    class Matrix
    {
    public:
        unsigned col;
        unsigned row;
        vector<vector<db> > mat;
        Matrix(unsigned row=0, unsigned col=0) : row(row), col(col), mat(row, vector<db>(col, 0)){}
        inline void initialize() { mat = vector<vector<db> >(row, vector<db>(col, 0)); }

        vector<db> &operator [] (unsigned i) { return mat[i]; }

        Matrix operator + (Matrix &b) const
        {
            assert(col == b.col && row == b.row);
            Matrix res(row, col);
            for (int i = 0; i < col; ++i)
                for (int j = 0; j < row; ++j)
                    res[i][j] = mat[i][j] + b[i][j];
            return res;
        }
        Matrix &operator += (Matrix &b) { return *this = *this + b; }

        Matrix operator - (Matrix &b) const
        {
            assert(col == b.col && row == b.row);
            Matrix res(row, col);
            for (int i = 0; i < col; ++i)
                for (int j = 0; j < row; ++j)
                    res[i][j] = mat[i][j] - b[i][j];
            return res;
        }
        Matrix &operator -= (Matrix &b) { return *this = *this - b; }

        Matrix operator * (Matrix &b) const
        {
            assert(col == b.row && row == b.col);
            Matrix res(row, row);
            for (int k = 0; k < col; ++k)
                for (int i = 0; i < row; ++i)
                    if (abs(mat[i][k]) > eps)
                        for (int j = 0; j < row; ++j)
                            res[i][j] += mat[i][k] * b[k][j];
            return res;
        }
        Matrix &operator *= (Matrix &b) { return *this = *this * b; }

        pair<Matrix, Matrix> LU_composition() const
        {
            assert(col == row);
            assert(row > 0);
            unsigned n = row;
            Matrix L(n, n), U(n, n), tmp;
            tmp.mat = mat;
            for (int i = 0; i < n; ++i) L[i][i] = 1;
            for (int i = 0; i < n; ++i)
            {
                U[i][i] = tmp[i][i];
                for (int j = i + 1; j < n; ++j)
                {
                    L[j][i] = tmp[j][i] / U[i][i];
                    U[i][j] = tmp[i][j];
                }
                for (int j = i + 1; j < n; ++j)
                    for (int k = i + 1; k < n; ++k)
                        tmp[j][k] -= L[j][i] * U[i][k];
            }
            return make_pair(L, U);
        };
    };
}
using matrix::Matrix;
//矩阵快速幂2 java版


    static final  int N=10;                         // N在用的时候随矩阵大小变化
    static int[][] tmp=new int[N][N];
    static void multi(int[][] a,int b[][],int n)	//矩阵乘法
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            for(int k=0;k<n;k++)
            tmp[i][j]+=a[i][k]*b[k][j];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
            a[i][j]=tmp[i][j];
    }
    static int[][] res=new int[N][N];
    static void Pow(int a[][],int n){
       //n是幂，N是矩阵大小
        for(int i=0;i<N;i++) res[i][i]=1;
        while(n!=0)
        {
            if((n&1)!=0)
                multi(res,a,N);//res=res*a;复制直接在multi里面实现了；
            multi(a,a,N);//a=a*a
            n>>=1;
        }

~~~

#### 辛普森自适应积分

~~~
#include <bits/stdc++.h>
using namespace std;

namespace adaptive_Simpson_integral
{
    typedef double db;
    typedef pair<db, db> pdd;
    typedef pair<pdd, pdd> pdddd;
    const db eps = 1e-6;
    db (*f)(db);

    inline db simpson_formula(const db left, const db right)
    {
        db middle = (left + right) / 2.0;
        return (f(left) + 4.0 * f(middle) + f(right)) * (right - left) / 6.0;
    }

    inline db integral(const db left, const db right, db (*function)(double))
    {
        f = function;
        db res = 0, l, r, m, precision, S_total, S_left, S_right;
        queue<pdddd> q;
        q.push(make_pair(make_pair(left, right), make_pair(simpson_formula(left, right), eps)));
        while (!q.empty())
        {
            l = q.front().first.first;
            r = q.front().first.second;
            S_total = q.front().second.first;
            precision = q.front().second.second;
            q.pop();
            m = (l + r) / 2.0;
            S_left = simpson_formula(l, m);
            S_right = simpson_formula(m, r);
            if (fabs(S_left + S_right - S_total) <= 15.0 * precision)
                res += S_left + S_right + (S_left + S_right - S_total) / 15.0;
            else
            {
                q.push(make_pair(make_pair(l, m), make_pair(S_left, precision / 2.0)));
                q.push(make_pair(make_pair(m, r), make_pair(S_right, precision / 2.0)));
            }
        }
        return res;
    }
}
using adaptive_Simpson_integral::integral;

double a, b, c, d;
inline double f(double x) { return (c * x + d) / (a * x + b); 函数表达式}
~~~

#### 莫比乌斯反演

~~~
//整除分块  算法复杂度√n*2
	for(int l=1,r;l<=n;l=r+1) 
		{
		    r=n/(n/l);
		    count++;
		    ans+=(r-l+1)*(n/l);
		}

//打表得到μ函数
	static int[] mu=new int[100000000];		
	static void get_mu(int n)
	{	
		int cnt=0;
		int[] vis=new int[100000000];int[] prim=new int[100000000];
	    mu[1]=1;
	    for(int i=2;i<=n;i++)
	    {
	        if(vis[i]==0){prim[++cnt]=i;mu[i]=-1;}
	        for(int j=1;j<=cnt&&prim[j]*i<=n;j++)
	        {
	            vis[prim[j]*i]=1;
	            if(i%prim[j]==0)break;
	            else mu[i*prim[j]]=-mu[i];
	        }
	    }
	}

 //log(n)时间内求一个数的欧拉值
static long eular(long n) {              
        long ans = n;
        for (long i = 2; i*i <= n; i++) {
            if (n%i == 0)
            {
                ans -= ans / i;
                while (n%i == 0) n /= i;
            }
        }
        if (n > 1) ans -= ans / n;
        return ans;
    }

~~~



## 数据结构

#### 树状数组

~~~
# 1号
const int maxn=50010; //maxn代表总区间中的点数 
int D[maxn];
int lowbit(int x){return x&(-x);}
void add(int x,int k,int n){
	while(x<=n){
		D[x]+=k;
		x+=lowbit(x); 
	}
}
int querypf(int x){
	int sum=0;
	while(x>0){
		sum+=D[x];
		x-=lowbit(x);
	}
	return sum;
}
int query(int L,int R){
	return querypf(R)-querypf(L-1);
}

# 2号
const int maxn=100010; //maxn代表总区间中的点数 
LL lowbit(LL x){return x&(-x);}
void add(LL* arr,int x,int k,int n){
	while(x<=n){
		arr[x]+=k;
		x+=lowbit(x); 
	}
}
LL query(LL* arr,int x){
	LL sum=0;
	while(x>0){
		sum+=arr[x];
		x-=lowbit(x);
	}
	return sum;
}
LL C[maxn],jmC[maxn];
void addRange(int L,int R,int k,int n){
	add(C,L,k,n);
	add(C,R+1,-k,n);
	add(jmC,L,1LL*k*L,n);
	add(jmC,R+1,1LL*-k*(R+1),n);
}
LL queryRange(int L,int R){
	L--;
	LL sumL=(L+1)*query(C,L)-query(jmC,L);
	LL sumR=(R+1)*query(C,R)-query(jmC,R);
	return sumR-sumL;
}

~~~

#### 线段树

~~~
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int sum[maxn<<2],lazy[maxn<<2];
void maintain(int k)
{
    sum[k]=sum[k<<1]+sum[k<<1|1];
}
void pushdown(int lenl,int lenr,int k)//标记下放，并更细节点信息
{
    if(lazy[k]){
        lazy[k<<1]=lazy[k];
        lazy[k<<1|1]=lazy[k];
        sum[k<<1]=lazy[k]*lenl;
        sum[k<<1|1]=lazy[k]*lenr;
        lazy[k]=0;
    }
}
void build(int l,int r,int k)
{
    if(l>r)
        return ;
    if(l==r){
        sum[k]=a[l];
        lazy[k]=0;
        return ;
    }
    int mid=(l+r)>>1;
    build(l,mid,k<<1);
    build(mid+1,r,k<<1|1);
    maintain(k);
}
void change(int l,int r,int cl,int cr,int k,int newp)
{
    if(l>r||cl>r||cr<l)
        return ;
    if(l>=cl&&r<=cr){
        sum[k]=newp*(r-l+1);//在发现现在区域小于需要更新区域时
        lazy[k]=newp;//更新节点的结果，并增加延迟标记lazy，用于之后的标记下放
        return ;
    }
    int mid=(l+r)>>1;
    pushdown(mid-l+1,r-mid,k);
    change(l,mid,cl,cr,k<<1,newp);
    change(mid+1,r,cl,cr,k<<1|1,newp);
    maintain(k);
}
int query(int l,int r,int ql,int qr,int k)
{
    if(l>r||ql>r||qr<l)
        return 0;
    if(l>=ql&&r<=qr)
        return sum[k];
    int mid=(l+r)>>1,ans=0;
    pushdown(mid-l+1,r-mid,k);//每一层询问执行到这一步，为了下一次递归更新叶节点信息
    if(mid>=l)
        ans+=query(l,mid,ql,qr,k<<1);
    if(mid<r)
        ans+=query(mid+1,r,ql,qr,k<<1|1);
    return ans;
}
int main()
{
    ios::sync_with_stdio(false);
    //freopen("in.txt","r",stdin);
    int n,m,cmd,l,r,newp,x,last=-1;
    char cnm[3];
    cin>>n;
    for(int i=1;i<=n;++i)
        cin>>a[i];
    build(1,n,1);
    cin>>m;
    for(int i=0;i<m;++i){
        cin>>cnm;
        if(cnm[0]=='D'){
        	cin>>x;last=x;
        	change(1,n,x,x,0);
		}
        else if(cnm[0]=='Q'){
        	cin>>x;
        	query()
		}
        else if(cnm=='R'){
        	change(1,n,last,last,1);
		}
    }
    return 0;
}

~~~



## 图论

#### 前向星

~~~
struct EDGE{
	int next;   //下一条边的存储下标(默认0) 
	int to;     //这条边的终点 
	int w;      //权值 
}; 
EDGE edge[500010]

void Add(int u, int v, int w) {  //起点u, 终点v, 权值w 	
	//cnt为边的计数，从1开始计 	
	edge[++cnt].next = head[u];
	edge[cnt].w = w;	
	edge[cnt].to = v;	
	head[u] = cnt;    //第一条边为当前边 
} 
遍历以st为起点的边
for(int i=head[st]; i!=0; i=edge[i].next)
~~~

#### Kruskal最小生成树

~~~

struct edge{
	bool operator < ( const edge & edg ) const {
        return dis < edg.dis;
    }
    int from = 0, to = 0, dis = 0;
    edge( int from ,int to ,int dis ){
		this -> dis = dis;
		this -> from = from;
		this -> to = to;
	};
};
            
vector<edge> vecto;
int father[maxn];
int find(int x);
void unite(int x,int y);

int main()
{
    int n;
	int ans=0;
    for (int i = 0; i < maxn;i++){
        father[i] = i;
    }
    scanf("%d", &n);
    for(int p=1;p<=n;p++){
    	for(int q=p;q<=n;q++){
    		int w;
    		scanf("%d", &w);
    		vecto.push_back(edge(p-1, q, w));
        	vecto.push_back(edge(q, p-1, w));
        	
		}
        
    }
    std::sort(vecto.begin(), vecto.end());
    for (auto len : vecto)
    {	
    	int lll=find(len.from);
    	int rrr=find(len.to);
        if(lll!=rrr){
            unite(len.from, len.to);
            ans = ans+len.dis;
        }
    }
    printf("%d\n", ans);
}
int find(int x){
    if(x==father[x]) return x;
    return father[x] = find(father[x]);
}
void unite(int x,int y){
    int l=find(x);
    int r=find(y);
    father[r] = l;
}
~~~

#### 最短路

~~~
floyd：

dijstra：

SPFA：

A*：

~~~

#### 最大流/最小割

~~~
网络流最大流=最小割  除此之外还常用于解最大权闭合子图的题目  
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int N = 55003;//要注意根据题目的不同调整参数 N为图中点数 本题中为源点+汇点+maxn个基站+maxm个用户 
const int M = 320001;// M为图中边数，本题中为（3*maxm+1*maxn）*2 注意本模板中所有的加边都是加两条边，正向的容量边和逆向的容量为0的回边，所以边数要乘以2 
int cnt;
int Head[N];
int Next[M];
int W[M];
int V[M];
int Depth[N];
int cur[N];//cur就是记录当前点u循环到了哪一条边
int s, t,n,m;//s,t:源点，汇点
const int inf = 0x3f3f3f3f;
void init()
{
	cnt = -1;
	memset(Head, -1, sizeof(Head));
	memset(Next, -1, sizeof(Next));
}
void _Add(int u, int v, int w)
{
	cnt++;
	Next[cnt] = Head[u];
	Head[u] = cnt;
	V[cnt] = v;
	W[cnt] = w;
}
void Add_Edge(int u, int v, int w)
{
	_Add(u, v, w);
	_Add(v, u, 0);
}
int dfs(int u, int flow)
{
	if (u == t)
		return flow;
	for (int& i = cur[u]; i != -1; i = Next[i])//注意这里的&符号，这样i增加的同时也能改变cur[u]的值，达到记录当前弧的目的
	{
		if ((Depth[V[i]] == Depth[u] + 1) && (W[i] != 0))
		{
			int di = dfs(V[i], min(flow, W[i]));
			if (di>0)
			{
				W[i] -= di;
				W[i ^ 1] += di;
				return di;
			}
		}
	}
	return 0;
}
int bfs()
{
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	memset(Depth, 0, sizeof(Depth));
	Depth[s] = 1;
	Q.push(s);
	do
	{
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = Next[i])
			if ((Depth[V[i]] == 0) && (W[i]>0))
			{
				Depth[V[i]] = Depth[u] + 1;
				Q.push(V[i]);
			}
	} while (!Q.empty());
	if (Depth[t]>0)
		return 1;
	return 0;
}
int Dinic()
{
	int Ans = 0;
	while (bfs())
	{
		for (int i = s; i <= t; i++)//每一次建立完分层图后都要把cur置为每一个点的第一条边 感谢@青衫白叙指出这里之前的一个疏漏
			cur[i] = Head[i];
		while (int d = dfs(s, inf))
		{
			Ans += d;
		}
	}
	return Ans;
}
int main() {
	scanf("%d%d", &n, &m);
	init();
	int ans=0;
	s=0;t=n+m+1;
	for (int i = 1; i <= n; i++) {
		int pi;
		scanf("%d",&pi);getchar();
		Add_Edge(s, i ,pi);
	}
	for (int i = 1; i <= m; i++) {
		int ai,bi,ci;
		scanf("%d%d%d",&ai,&bi,&ci);
		ans+=ci;
		Add_Edge(n+i ,t, ci);
		Add_Edge(ai, n+i, inf);
		Add_Edge(bi, n+i, inf);
	}
//	scanf("%d%d", &s, &t);
	int ans1=Dinic();
	printf("%d",ans-ans1);	//当初这道题求得是最大权闭合子图，所以等于(正权和-最小割/最大流) 
}
~~~

#### 最小费用最大流

~~~
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
const int maxn = 1010; //同样需要注意参数，根据构图调整点数和边数 
const int maxm = 30000;
bool vis[maxn]; int dist[maxn];
//解释一下各数组的含义：vis两个用处：spfa里的访问标记，増广时候的访问标记，dist是每个点的距离标号
int N, m, s, t, ans = 0;
//s是起点，t是终点，ans是费用答案
int nedge = -1, p[maxm], c[maxm], cc[maxm], nex[maxm], head[maxn];
//这里是边表，解释一下各数组的含义：p[i]表示以某一点出发的编号为i的边对应点，c表示编号为i的边的流量，cc表示编号为i的边的费用，nex和head不说了吧。。。
inline void init(int n) {
	N = n;
	ans = 0;
	nedge = -1;
	memset(head, -1, sizeof(head));
	memset(nex, -1, sizeof(nex));
}
const int inf = 0x3f3f3f3f;
inline void add(int x, int y, int cap, int cost) {
	p[++nedge] = y; 
	c[nedge] = cap; 
	cc[nedge] = cost; 
	nex[nedge] = head[x]; 
	head[x] = nedge;
}

inline void addedge(int x, int y, int cap, int cost) {
	add(x, y, cap, cost);
	add(y, x, 0, -cost);
}
//建边（数组模拟边表倒挂）
inline bool spfa(int s, int t) {
	memset(vis, 0, sizeof vis);
	for (int i = s; i <= t; i++) {
		dist[i] = inf; 
		dist[t] = 0; 
		vis[t] = 1;
	}
	//首先SPFA我们维护距离标号的时候要倒着跑，这样可以维护出到终点的最短路径
	deque<int>q; q.push_back(t);
	//使用了SPFA的SLF优化（SLF可以自行百度或Google）
	while (!q.empty()) {
		int now = q.front(); q.pop_front();
		for (int k = head[now]; k>-1; k = nex[k])if (c[k ^ 1] && dist[p[k]]>dist[now] - cc[k]) {
			//首先c[k^1]是为什么呢，因为我们要保证正流，但是SPFA是倒着跑的，所以说我们要求c[k]的对应反向边是正的，这样保证走的方向是正确的
			dist[p[k]] = dist[now] - cc[k];
			//因为已经是倒着的了，我们也可以很清楚明白地知道建边的时候反向边的边权是负的，所以减一下就对了（负负得正）
			if (!vis[p[k]]) {
				vis[p[k]] = 1;
				if (!q.empty() && dist[p[k]]<dist[q.front()])q.push_front(p[k]); else q.push_back(p[k]);
				//SLF优化
			}
		}
		vis[now] = 0;
	}
	return dist[s]<inf;
	//判断起点终点是否连通
}
inline int dfs(int x, int low) {
	//这里就是进行増广了
	if (x == t) { vis[t] = 1; return low; }
	int used = 0, a; vis[x] = 1;
	//这边是不是和dinic很像啊
	for (int k = head[x]; k>-1; k = nex[k])
		if (!vis[p[k]] && c[k] && dist[x] - cc[k] == dist[p[k]]) {
		//这个条件就表示这条边可以进行増广
		a = dfs(p[k], min(c[k], low - used));
		if (a) {
			ans += a*cc[k];
//			ans += cc[k];
			c[k] -= a;
			c[k ^ 1] += a;
			used += a;
		}
		//累加答案，加流等操作都在这了
		if (used == low)break;
	}
	return used;
}
inline int costflow() {
	int flow = 0;
	while (spfa(s, t)) {
		//判断起点终点是否连通，不连通说明满流，做完了退出
		vis[t] = 1;
		while (vis[t]) {
			memset(vis, 0, sizeof vis);
			flow += dfs(s, inf);
			//一直増广直到走不到为止（这样也可以省时间哦）
		}
	}
	return flow;//这里返回的是最大流，费用的答案在ans里
}

int main()
{
	int n;
	scanf("%d%d", &n, &m);
	ans=0;
	s=0,t=n+2; 
	init(n);
	int ai[n+2]; 
	ai[0]=0;ai[n+1]=0;
	for(int i=1;i<=n;i++){
		int tepp;
		scanf("%d",&tepp);
		ai[i]=tepp;
	}
	for(int i=1;i<=m;i++){
		int si,ti,ci;
		scanf("%d%d%d",&si,&ti,&ci);
		addedge(si,ti+1,inf,ci);
	}
	for(int i=1;i<=n;i++){
		addedge(i+1,i,inf,0);
	}
	for(int i=1;i<=n+1;i++){
		int c=ai[i]-ai[i-1];
		if(c>=0) addedge(s,i,c,0);
		else addedge(i,t,-c,0);
		
	}
	costflow();
	printf("%d\n",ans);
	return 0;
}
/*
5 6 1 3
1 2 5 3
2 3 4 3
1 4 5 2
4 5 6 3
5 3 6 1
4 3 5 1
*/
~~~

## 其他

#### 博弈打表

```
static int[] f=new int[N];//可以取走的石子个数  
static int[] sg=new int[N];//0~n的SG函数值  
static String[] result=new String [N];
static public void getSG(int n){  
 
    for(int i = 1; i <= n; i++){  
        int[] hash=new int[N]; 
        for(int j = 1; f[j] <= i; j++)  
            hash[sg[i-f[j]]] = 1;  
        for(int j = 0; j <= n; j++){    //求mes{}中未出现的最小的非负整数  
            if(hash[j] == 0){  
                sg[i] = j;  
                break;  
            }  
        }  
    }  
}  
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		f[0] = f[1] = 1;  
	    for(int i = 2; i <= 100; i++)  
	        f[i] = f[i-1]*2;  
	    getSG(1004);  
	    Scanner in= new Scanner(System.in);
	   while(in.hasNext()) { 
	    	int n=in.nextInt();
	    	if(sg[n]==0) {
	    		System.out.println("Cici");
	    	}else {
	    		System.out.println("Kiki");
	    	}
	    	
	   }  	
```

#### 数位DP

~~~
#include<iostream>
#include<cstdio>
#include<cstring>
#include<string>
using namespace std;
typedef long long ll;
int a[20];
ll dp[20][4];
ll dfs(int pos,int pre,int sta,bool limit)//底下这个是求没有38和49子序列的个数的 
{
    if(pos==-1) return 1;
    if(!limit && dp[pos][sta]!=-1) return dp[pos][sta];
    int up=limit ? a[pos] : 9;
    ll tmp=0;
    for(int i=0;i<=up;i++)
    {
        if(sta==1 && i==9)continue;
        if(sta==2 && i==8)continue;
        if(sta==3 &&(i==8||i==9)) continue;
        if(i==4&&sta==0){
        	tmp+=dfs(pos-1,i,1,limit && i==a[pos]);
		}else if(i==3&&sta==0){
			tmp+=dfs(pos-1,i,2,limit && i==a[pos]);
		}else if((i==3&&sta==1)||(i==4&&sta==2)){
			tmp+=dfs(pos-1,i,3,limit && i==a[pos]);
		}
		else{
			tmp+=dfs(pos-1,i,sta,limit && i==a[pos]);
		}
       
    }
    if(!limit) dp[pos][sta]=tmp;
    return tmp;
}
ll solve(ll x)
{
    ll pos=0;
    while(x)
    {
        a[pos++]=x%10;
        x/=10;
    }
    return dfs(pos-1,-1,0,true);
}
int main()
{
    int T;long long ri;
    scanf("%d",&T); 
    //memset(dp,-1,sizeof dp);可优化
    while(T--)
    {
    	scanf("%lld",&ri);
        memset(dp,-1,sizeof dp);
        printf("%lld\n",(ri-solve(ri)+1));
    }
    return 0;
}

~~~

#### 最长上升子序列（DP）

~~~
for(int i = 1; i <= n; i++){
        dp[i] = 1; //初始化
        for(int j = 1; j < i; j++){
            if(arr[j] < arr[i]) // 如果求最大下降子序列则反之
                dp[i] = max(dp[i], dp[j] + 1);

        }
        ans = max(dp[i], ans);
 }
~~~

