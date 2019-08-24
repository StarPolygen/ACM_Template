//杜教筛
//套路式： g(1)S(n)=∑i=1-n h(i) —∑d=2-n g(d)S(n/d) 
//首先先线筛出数据范围O(n^2/3)左右的积性函数的前缀和。再递归的实现杜教筛。
//用stl中的unordered_map，而不是map
//尽量减少取模和longlong  如unordered_map 

//TLE 或 WA 必要时：
//在保证算法无误的情况下 为避免取模错误或爆ll 可以define int long long + 可取模的全部取模  
//用此代码运行大数据先获得正确答案 在依次去除冗余的ll 和 mod 并与正确答案比较保证无误

#include<bits/stdc++.h>
#include<tr1/unordered_map>
#define N 5001000
#define mod 1000000007
#define ll long long
using namespace std;

//快读 
template<typename T>inline void read(T &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}


//杜教筛题目的关键是寻找配凑h和g 使得h=f*g   1.消去  2.试凑 
long long f[N];


//快速幂 求逆元 
int inv3;
ll fast_exp(ll a,ll b,ll c){
    ll res=1;
    while(b)    {
        if(b&1){
            res=res*a%c;
        }
        a=a*a%c;
        b>>=1;
    }
    return res;
}

//暴力求解前n^2/3待求积性函数的前缀和 ，get内的代码不具有普适性 
void get(int maxn){
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

int main(){
    int t;
    read(t);
    inv3=fast_exp(3,mod-2,mod);
    get(1e6);
    while(t--)    {
        static int n;
        read(n);
        printf("%lld\n",djsf(n));
    }
    return 0;
}