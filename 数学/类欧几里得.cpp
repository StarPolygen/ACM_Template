//类欧几里得
//https://blog.csdn.net/VictoryCzt/article/details/86099938
//几个常用等式  ab≤c <=> a≤⌊c/b⌋    ab≥c <=> a≥⌊c/b⌋
//注意：1.一些题目可能需要按位求取，位运算优先级较低 需要加括号再取模  位运算优先级小于+-*/% 但大于+= -= /= *= %=
//      2.当位移运算达到ll数量级时，最先的1必须为1ll
//      3.当题目存在ll互乘，有可能爆ll，需要使用__int128

//仅f模板  
//注意若存在ll互乘极有可能爆ll 必要时使用define LL __int128 并将该函数内的ll替换为LL
ll f(ll a,ll b,ll c,ll n){
    if(a==0)return (n+1)*(b/c)%mod;
    if(a>=c||b>=c)return (f(a%c,b%c,c,n)+n*(n+1)%mod*inv2%mod*(a/c)%mod+(n+1)*(b/c)%mod)%mod;
    ll M=(a*n+b)/c;
    return ((n*M%mod-f(c,c-b-1,a,M-1))%mod+mod)%mod;
}

//f、g、h模板
//f(a,b,c,n): Σi ⌊ai+b/c⌋  i=[0,n]
//h(a,b,c,n): Σi ⌊ai+b/c⌋*i  i=[0,n]
//g(a,b,c,n): Σi ⌊ai+b/c⌋^2  i=[0,n]
//代码中的h,g的意义对换了一下，懒得改了

//注意若存在ll互乘极有可能爆ll 必要时使用define ll __int128 把所有ll用作__int128 时间常数会大2倍左右
#include<cstdio>
#include<cstring>
#include<algorithm>
//#define ll __int128
#define ll long long
using namespace std;
inline ll bin(ll base, ll n, ll p) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * base % p;
        base = base * base % p;
        n >>= 1;
    }
    return res;
}inline ll get_inv(ll x, ll p) {  return bin(x, p - 2, p);  }
const ll Mod=1e9+7;
const ll inv2=get_inv(2,Mod),inv6=get_inv(6,Mod);
ll S1(ll x){if(x>=Mod)x%=Mod;return (x*(x+1)%Mod)*inv2%Mod;}
ll S2(ll x){if(x>=Mod)x%=Mod;return (x*(x+1)%Mod*(x+x+1)%Mod)*inv6%Mod;}
ll Sqr(ll x){return x*x%Mod;}
struct node{
	ll f,g,h;
	void clear(){f=g=h=0;}
	node(){}
	node(ll a,ll b,ll c):f(a),g(b),h(c){}
	void out(){printf("%lld %lld %lld\n",f,g,h);}
};

node calc(ll a,ll b,ll c,ll n){
	node ans,res;ans.clear();
	ll m,t1,t2,s1,s2;
	if(!n){ans.f=b/c;ans.g=Sqr(b/c);return ans;}
	if(!a){
		t1=b/c;
		ans.f=(n+1ll)*t1%Mod;
		ans.g=(n+1ll)*Sqr(t1)%Mod;
		ans.h=S1(n)*t1%Mod;
		return ans;
	}
	if(a>=c||b>=c){
		t1=a/c;t2=b/c;
		res=calc(a%c,b%c,c,n);
		s1=S1(n);s2=S2(n);
		ans.f=(((s1*t1%Mod)+(n+1ll)*t2%Mod)%Mod+res.f)%Mod;
		ans.g=(((Sqr(t1)*s2%Mod+(n+1ll)*Sqr(t2)%Mod)%Mod)+((t1*t2%Mod)*2ll*s1%Mod+(t1*2ll*res.h%Mod))%Mod+(res.g+t2*2ll*res.f%Mod)%Mod)%Mod;
		ans.h=((s2*t1%Mod+s1*t2%Mod)+res.h)%Mod;
		return ans;
	}
	m=(n*a+b)/c-1;
	res=calc(c,c-b-1,a,m);
	ll w1=n*(m+1)%Mod,w2=n*(n+1)%Mod,w3=m+1;
	if(w3>=Mod)w3%=Mod;
	ans.f=(w1-res.f)%Mod;if(ans.f<0)ans.f+=Mod;
	ans.g=((w1*w3)%Mod-((res.h*2ll%Mod+res.f)%Mod))%Mod;if(ans.g<0)ans.g+=Mod;
	ans.h=((w2*w3)%Mod-(res.f+res.g)%Mod)%Mod*inv2%Mod;if(ans.h<0)ans.h+=Mod;
	return ans;
}
int a,b,c,n,T;
int main(){
	for(scanf("%d",&T);T--;){scanf("%d%d%d%d",&n,&a,&b,&c);calc(a,b,c,n).out();}
	return 0;
}


//普适模板
//f(k1,k2,a,b,c,n)=Σi i^k1*⌊ai+b/c⌋^k2   i=[0,n]
//注意若存在ll互乘极有可能爆ll 必要时使用define ll __int128 把所有ll用作__int128 时间常数会大2倍左右
//每次使用都需要memset一次F
#include<cstdio>
#include<cstring>
#include<algorithm>
//#define ll __int128
#define ll long long
using namespace std;
const int M=13;
const ll Mod=1e9+7;
ll y[M],C[M][M],F[M][M][44];
ll fpow(ll a,ll b=Mod-2){
	a%=Mod;if(a<0)a+=Mod;ll res=1;for(;b;b>>=1,a=(a*a)%Mod)if(b&1)res=(res*a)%Mod;
	return res;
}
struct Ply{
	ll x[M];
	void clear(){memset(x,0,sizeof(x));}
	Ply(){memset(x,0,sizeof(x));}
	Ply operator +(const Ply &a)const{
		Ply ans;for(int i=0;i<M;i++)ans.x[i]=(x[i]+a.x[i])%Mod;
		return ans;	
	}
	Ply operator *(const Ply &a)const{
		Ply ans;
		for(int i=0;i<M;i++)for(int j=0;i+j<M;j++)
		ans.x[i+j]=(ans.x[i+j]+x[i]*a.x[j]%Mod)%Mod;
		return ans;
	}
	ll operator ()(ll a,int b){
		ll ans=x[b+1];for(int i=b;i>=0;i--)ans=(ans*a%Mod+x[i])%Mod;
		return ans;
	}
}A[M],B[M];
void calc(Ply &a,int n){
	Ply xx,yy;
	for(int i=0;i<=n;i++){
		xx.x[0]=y[i];
		for(int j=0;j<=n;j++)if(i^j)xx.x[0]=xx.x[0]*fpow(i-j)%Mod;
		for(int j=0;j<=n;j++)if(j^i){yy.x[0]=Mod-j;yy.x[1]=1;xx=xx*yy;}
		a=a+xx;xx.clear();
	}
}
ll f(int k1,int k2,ll a,ll b,ll c,ll n,int d=0){
	if(~F[k1][k2][d]) return F[k1][k2][d];
	ll ans=0;
	if(!a) ans=B[k1](n,k1)*fpow(b/c,k2)%Mod;
	else if(!k2) ans=B[k1](n,k1);
	else if(a>=c||b>=c){
		int x=a/c,y=b/c;a%=c;b%=c;
		for(ll i=0,X=1;i<=k2;i++,X=(X*x)%Mod){
			for(ll j=0,Y=X;i+j<=k2;j++,Y=Y*y%Mod){
				ans=(ans+f(k1+i,k2-i-j,a,b,c,n,d+1)*C[k2][i]%Mod*C[k2-i][j]%Mod*Y%Mod)%Mod;
			}
		}
	}else{
		int m=(a*n+b)/c;--m;
		ans=A[k2](m,k2);
		ans=ans*B[k1](n,k1)%Mod;
		for(int j=0;j<k2;j++)for(int i=0;i<=k1+1;i++){
			ans=(ans-f(j,i,c,c-b-1,a,m,d+1)*C[k2][j]%Mod*B[k1].x[i]%Mod)%Mod;
		}
	}
	if(ans<0)(ans%=Mod)+=Mod;ans%=Mod;
	return F[k1][k2][d]=ans;
}
void init(){
	C[0][0]=1;
	for(int i=1;i<=10;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mod;
		}
	}
	for(int i=0;i<=10;i++){
		if(i)y[0]=1;
		for(int j=1;j<=i+1;j++){
			y[j]=(y[j-1]+fpow(j+1,i)-fpow(j,i))%Mod;
			if(y[j]<0)y[j]+=Mod;
		}
		calc(A[i],i+1);
		if(!i)y[0]=1;else y[0]=0;
		for(int j=1;j<=i+1;j++)y[j]=(y[j-1]+fpow(j,i))%Mod;
		calc(B[i],i+1);
	}
}
int T,a,b,c,n,k1,k2;
int main(){
	init();
	for(scanf("%d",&T);T--;){
		scanf("%d%d%d%d%d%d",&n,&a,&b,&c,&k1,&k2);
		memset(F,-1,sizeof(F));
		printf("%d\n",f(k1,k2,a,b,c,n));
	}
	return 0;
} 
