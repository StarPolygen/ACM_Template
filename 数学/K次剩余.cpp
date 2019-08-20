#include<bits/stdc++.h>
#define ll long long
using namespace std;

//二次剩余版本1： mod数为奇素数
int Pow(int a,int b,int p){   int res=1; for(;b;a=1LL*a*a%p,b>>=1) if(b&1)res = 1LL * a * res % p;  return res;}

bool Legendre(int a,int p){   return Pow(a,p-1>>1,p)==1;}

ll modsqr(int a,int p)
{
    int x, i, k, b;
    if(p==2) x=a%p;
    else if(p%4==3) x=Pow(a,p+1>>2,p);
    else {
        for(b=1;Legendre(b,p);++b);
        i=p-1>>1; k=0;
        do {
            i>>=1;
            k>>=1;
            if(!((1LL*Pow(a,i,p)*Pow(b,k,p)+1)%p)) k+=p-1>>1;
        }while(!(i&1));
        x=1LL*Pow(a,i+1>>1,p)*Pow(b,k>>1,p)%p;
    }
    if(p-x<x) x=p-x;
    if(x==p-x) return x;
    else return p-x;
}

int main() {
    int T;  scanf("%d",&T);
    int a,n;
    while(T--) {
        scanf("%d%d",&a,&n); //x^2 ≡ a mod(n)
        a%=n;
        if(!Legendre(a,n)) {
            puts("No root");  //二次剩余 不存在
            continue;
        }
        //二次剩余的两根 注意某些情况下两者相等
        ll rt1 = modsqr(a,n);
        ll rt2 = n - rt1;
        printf("%d %d", rt1, rt2);
        //如果需要 a=0 或 n=2的情况特殊判断
    }
    return 0;
}

//二次剩余版本2 适用于所有模数
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define re register
#define gc getchar
#define pc putchar
#define puts put_s
#define cs const

namespace IO{
	namespace READONLY{
		cs int Rlen=1<<18|1;
		char buf[Rlen],*p1,*p2;
		char obuf[Rlen],*p3=obuf;
		char ch[23];
	}
	inline char get_char(){
		using namespace READONLY;
		return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,Rlen,stdin),p1==p2)?EOF:*p1++;
	}
	inline void put_char(cs char &c){
		using namespace READONLY;
		*p3++=c;
		if(p3==obuf+Rlen)fwrite(obuf,1,Rlen,stdout),p3=obuf;
	}
	inline void put_s(cs char *s){
		for(;*s;++s)pc(*s);
		pc('\n');
	}
	inline void FLUSH(){
		using namespace READONLY;
		fwrite(obuf,1,p3-obuf,stdout);
		p3=obuf;
	}
	
	inline ll getint(){
		re ll num;
		re char c;
		while(!isdigit(c=gc()));num=c^48;
		while(isdigit(c=gc()))num=(num+(num<<2)<<1)+(c^48);
		return num;
	}
	inline void outint(ll a){
		using namespace READONLY;
		if(a==0)pc('0');
		if(a<0)pc('-'),a=-a;
		while(a)ch[++ch[0]]=a-a/10*10,a/=10;
		while(ch[0])pc(ch[ch[0]--]^48);
	}
}
using namespace IO;

namespace Linear_sieves{
	cs int P=300005;
	int prime[P],pcnt;
	bool mark[P];
	
	inline void init(int len=P-5){
		mark[1]=true;
		for(int re i=2;i<=len;++i){
			if(!mark[i])prime[++pcnt]=i;
			for(int re j=1;j<=pcnt&&i*prime[j]<=len;++j){
				mark[i*prime[j]]=true;
				if(i%prime[j]==0)break;
			}
		}
	}
}

namespace Find_root{
	#define complex COMPLEX
	using namespace Linear_sieves;
	
	inline ll mul(cs ll &a,cs ll &b,cs ll &mod){
		return (a*b-(ll)((long double)a/mod*b)*mod+mod)%mod;
	}
	inline ll quickpow(ll a,ll b,cs ll &mod,ll res=1){
		for(;b;b>>=1,a=mul(a,a,mod))if(b&1)res=mul(res,a,mod);
		return res;
	}
	
	inline ll ex_gcd(cs ll &a,cs ll &b,ll &x,ll &y){
		if(!b){
			y=0;
			x=1;
			return a;
		}
		ll t=ex_gcd(b,a-a/b*b,y,x);
		y-=(a/b)*x;
		return t;
	}
	inline ll inv(cs ll a,cs ll mod){
		ll x,y;
		ll t=ex_gcd(a,mod,x,y);
		return (x%mod+mod)%mod;
	}
	
	ll W,Mod;
	class complex{
		public:
			ll x,y;
			complex(cs ll &_x=0,cs ll &_y=0):x(_x),y(_y){}
			inline friend complex operator*(cs complex &a,cs complex &b){
				return complex(
					(mul(a.x,b.x,Mod)+mul(mul(a.y,b.y,Mod),W,Mod))%Mod,
					(mul(a.x,b.y,Mod)+mul(a.y,b.x,Mod))%Mod);
			}
	};
	
	complex quickpow(complex a,ll b){
		complex res(1,0);
		for(;b;b>>=1,a=a*a)if(b&1)res=res*a;
		return res;
	}
	
	inline bool isprime(ll x){
		if(x<=P-5)return !mark[x];
		if(x%2==0||x%3==0||x%5==0||x%7==0||x%31==0||x%24251==0)return false;
		re ll t=x-1,s;
		t>>=(s=__builtin_ctzll(t));
		for(int re i=1;i<=5;++i){
			re ll p=prime[rand()%pcnt+1];
			re ll num=quickpow(p,t,x),pre=num;
			for(int re j=0;j<s;++j){
				num=mul(num,num,x);
				if(num==1&&pre!=x-1&&pre!=1)return false;
				pre=num;
				if(num==1)break;
			}
			if(num^1)return false;
		}
		return true;
	}
	
	inline ll Pollard_rho(ll x){
		if(x%2==0)return 2;
		if(x%3==0)return 3;
		if(x%5==0)return 5;
		if(x%7==0)return 7;
		if(x%31==0)return 31;
		if(x%24251==0)return 24251;
		re ll n=0,m=0,t=1,q=1,c=rand()%(x-2)+2;
		for(int re k=2;;k<<=1,m=n,q=1){
			for(int re i=1;i<=k;++i){
				n=(mul(n,n,x)+c)%x;
				q=mul(q,abs(n-m),x);
			}
			if((t=__gcd(q,x))>1)return t;
		}
	}
	
	ll fact[60],cntf;
	inline void sieves(ll x){
		if(x==1)return ;
		if(isprime(x)){fact[++cntf]=x;return;}
		re ll p=x;
		while(p==x)p=Pollard_rho(p);
		sieves(p);
		while(x%p==0)x/=p;
		sieves(x);
	}
	
	inline ll solve_2k(ll a,ll k){
		if(a%(1<<k)==0)return 0;
		a%=(1<<k);
		re ll t=0,res=1;
		a>>=(t=__builtin_ctzll(a));
		if((a&7)^1)return -1;
		if(t&1)return -1;
		k-=t;
		for(int re i=4;i<=k;++i){
			res=(res+(a%(1<<i)-res*res)/2)%(1<<k);
		}
		res%=1<<k;
		if(res<0)res+=1<<k;
		return res<<(t>>1); 
	}
	
	inline ll solve_p(ll a,ll p){
		a%=p;
		if(quickpow(a,(p-1)>>1,p)==p-1)return -1;
		re ll b;
		Mod=p;
		while(true){
			b=rand()%p;
			W=(mul(b,b,p)-a+p)%p;
			if(quickpow(W,(p-1)>>1,p)==p-1)break;
		}
		re ll ans=quickpow(complex(b,1),(p+1)>>1).x;
		return min(ans,p-ans);
	}
	
	inline ll solve_pk(ll a,ll k,ll p,ll mod){
		if(a%mod==0)return 0;
		re ll t=0,hmod=1;
		while(a%p==0)a/=p,++t,hmod*=(t&1)?p:1;
		if(t&1)return -1;
		k-=t;
		mod/=hmod*hmod;
		re ll res=solve_p(a,p);
		if(res==-1)return -1;
		complex tmp(res,1);
		W=a;
		Mod=mod;
		tmp=quickpow(tmp,k);
		res=mul(tmp.x,inv(tmp.y,Mod),Mod);
		return res*hmod;
	}
	
	ll remain[20],mod[20],p;
	inline ll CRT(){
		re ll ans=0;
		for(int re i=1;i<=cntf;++i){
			ans=(ans+mul(mul(p/mod[i],inv(p/mod[i],mod[i]),p),remain[i],p))%p;
		}
		return ans;
	}
	
	inline ll solve(ll a,ll pmod){
		a%=pmod;
		cntf=0;
		p=pmod;
		sieves(pmod);
		if(cntf>1)sort(fact+1,fact+cntf+1);
		if(cntf>1)cntf=unique(fact+1,fact+cntf+1)-fact-1;
		for(int re i=1;i<=cntf;++i){
			re ll now=0,rmod=1;
			while(pmod%fact[i]==0)pmod/=fact[i],++now,rmod*=fact[i];
			mod[i]=rmod;
			if(fact[i]==2)remain[i]=solve_2k(a,now);
			else remain[i]=solve_pk(a,now,fact[i],rmod);
			if(remain[i]==-1)return -1;
		}
		return CRT();
	}
	
	#undef complex
}

int T;
signed main(){
	srand(time(0));
	Linear_sieves::init();
	T=getint();
	while(T--){
		re ll a=getint(),p=getint(),ans;
		outint(ans=Find_root::solve(a,p));pc('\n');
	}
    //解出的是其中的一个根 用mod减去此根可以得到另外的一个根
	FLUSH();
	return 0;
} 

//版本3 高次剩余求解
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <bitset>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <sstream>
#include <stack>
#include <iomanip>
using namespace std;
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
typedef long long ll;
typedef double ld;
typedef vector<int> vi;
#define fi first
#define se second
#define fe first
#define FO(x) {freopen(#x".in","r",stdin);freopen(#x".out","w",stdout);}
#define Edg int M=0,fst[SZ],vb[SZ],nxt[SZ];void ad_de(int a,int b){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;}void adde(int a,int b){ad_de(a,b);ad_de(b,a);}
#define Edgc int M=0,fst[SZ],vb[SZ],nxt[SZ],vc[SZ];void ad_de(int a,int b,int c){++M;nxt[M]=fst[a];fst[a]=M;vb[M]=b;vc[M]=c;}void adde(int a,int b,int c){ad_de(a,b,c);ad_de(b,a,c);}
#define es(x,e) (int e=fst[x];e;e=nxt[e])
#define esb(x,e,b) (int e=fst[x],b=vb[e];e;e=nxt[e],b=vb[e])
#define VIZ {printf("digraph G{\n"); for(int i=1;i<=n;i++) for es(i,e) printf("%d->%d;\n",i,vb[e]); puts("}");}
#define VIZ2 {printf("graph G{\n"); for(int i=1;i<=n;i++) for es(i,e) if(vb[e]>=i)printf("%d--%d;\n",i,vb[e]); puts("}");}
#define SZ 666666
template<class T>
inline T dw();
template<>
inline ll dw<ll>() {return 1;}
template<>
inline int dw<int>() {return 1;}
typedef pair<ll,ll> pll;
ll pll_s;
inline pll mul(pll a,pll b,ll p)
{
    pll ans;
    ans.fi=a.fi*b.fi%p+a.se*b.se%p*pll_s%p;
    ans.se=a.fi*b.se%p+a.se*b.fi%p;
    ans.fi%=p; ans.se%=p;
    return ans;
}
inline ll mul(ll a,ll b,ll c)
{return a*b%c;}
//快速幂
template<class T>
T qp(T a,ll b,ll c)
{
    T ans=dw<T>();
    while(b)
    {
        if(b&1) ans=mul(ans,a,c);
        a=mul(a,a,c); b>>=1;
    }
    return ans;
}
//随机数
inline ll ll_rnd()
{
    ll ans=0;
    for(int i=1;i<=5;i++)
        ans=ans*32768+rand();
    if(ans<0) ans=-ans;
    return ans;
}
//(x,y) -> x+sqrt(pll_s)*y
template<>
inline pll dw<pll>() {return pll(1,0);}
//find (possibly) one root of x^2 mod p=a
//correctness need to be checked
ll sqr(ll a,ll p)
{
    if(!a) return 0;
    if(p==2) return 1;
    ll w,q;
    while(1)
    {
        w=ll_rnd()%p;
        q=w*w-a;
        q=(q%p+p)%p;
        if(qp(q,(p-1)/2,p)!=1)
            break;
    }
    pll_s=q;
    pll rst=qp(pll(w,1),(p+1)/2,p);
    ll ans=rst.fi; ans=(ans%p+p)%p;
    return ans;
}
//solve x^2 mod p=a                                  二次剩余
vector<ll> all_sqr(ll a,ll p)
{
    vector<ll> vec;
    a=(a%p+p)%p;
    if(!a) {vec.pb(0); return vec;}
    ll g=sqr(a,p);
    ll g2=(p-g)%p;
    if(g>g2) swap(g,g2);
    if(g*g%p==a) vec.pb(g);
    if(g2*g2%p==a&&g!=g2) vec.pb(g2);
    return vec;
}
ll s3_a;
//f0+f1*x+f2*x^2 (for x^3=s3_a)
struct s3
{
    ll s[3];
    s3() {s[0]=s[1]=s[2]=0;}
    s3(ll* p) {s[0]=p[0]; s[1]=p[1]; s[2]=p[2];}
    s3(ll a,ll b,ll c) {s[0]=a; s[1]=b; s[2]=c;}
};
template<>
s3 dw<s3>() {return s3(1,0,0);}
s3 rs3(ll p)
{
    return s3(ll_rnd()%p,ll_rnd()%p,ll_rnd()%p);
}
s3 mul(s3 a,s3 b,ll p)
{
    ll k[3]={};
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(i+j<3) k[i+j]+=a.s[i]*b.s[j]%p;
            else k[i+j-3]+=a.s[i]*b.s[j]%p*s3_a%p;
        }
    }
    for(int i=0;i<3;i++) k[i]%=p;
    return s3(k[0],k[1],k[2]);
}
//solve x^3 mod p=a                                三次剩余
vector<ll> all_cr(ll a,ll p)
{
    vector<ll> vec;
    a=(a%p+p)%p;
    if(!a) {vec.pb(0); return vec;}
    if(p<=3)
    {
        for(int i=0;i<p;i++)
        {
            if(i*i*i%p==a) vec.pb(i);
        }
        return vec;
    }
    if(p%3==2)
    {
        vec.pb(qp(a,(p*2-1)/3,p));
        return vec;
    }
    if(qp(a,(p-1)/3,p)!=1) return vec;
    ll l=(sqr(p-3,p)-1)*qp(2LL,p-2,p)%p,x;
    s3_a=a;
    while(1)
    {
        s3 u=rs3(p);
        s3 v=qp(u,(p-1)/3,p);
        if(v.s[1]&&!v.s[0]&&!v.s[2])
        {x=qp(v.s[1],p-2,p); break;}
    }
    x=(x%p+p)%p;
    vec.pb(x); vec.pb(x*l%p); vec.pb(x*l%p*l%p);
    sort(vec.begin(),vec.end());
    return vec;
}
map<ll,ll> gg;
ll yss[2333]; int yyn=0;
//find x's primitive root
inline ll org_root(ll x)
{
    ll& pos=gg[x];
    if(pos) return pos;
    yyn=0; ll xp=x-1;
    for(ll i=2;i*i<=xp;i++)
    {
        if(xp%i) continue;
        yss[++yyn]=i;
        while(xp%i==0) xp/=i;
    }
    if(xp!=1) yss[++yyn]=xp;
    ll ans=1;
    while(1)
    {
        bool ok=1;
        for(int i=1;i<=yyn;i++)
        {
            ll y=yss[i];
            if(qp(ans,(x-1)/y,x)==1) {ok=0; break;}
        }
        if(ok) return pos=ans;
        ++ans;
    }
}
map<ll,int> bsgs_mp;
//find smallest x: a^x mod p=b
ll bsgs(ll a,ll b,ll p)
{
    if(b==0) return 1;
    map<ll,int>& ma=bsgs_mp;
    ma.clear();
    //only /2.5 for speed...
    ll hf=sqrt(p)/2.5+2,cur=b;
    for(int i=0;i<hf;i++)
        ma[cur]=i+1, cur=cur*a%p;
    ll qwq=1,qh=qp(a,hf,p);
    for(int i=0;;i++)
    {
        if(i)
        {
            if(ma.count(qwq))
                return i*hf-(ma[qwq]-1);
        }
        qwq=qwq*(ll)qh%p;
    }
    return 1e18;
}
//ax+by=1
void exgcd(ll a,ll b,ll& x,ll& y)
{
    if(b==0) {x=1; y=0; return;}
    exgcd(b,a%b,x,y);
    ll p=x-a/b*y; x=y; y=p;
}
template<class T>
T gcd(T a,T b) {if(b) return gcd(b,a%b); return a;}
//solve x^a mod p=b                                   K次剩余
vector<ll> kr(ll a,ll b,ll p)
{
    vector<ll> rst;
    if(!b) {rst.pb(0); return rst;}
    ll g=org_root(p);
    ll pb=bsgs(g,b,p);
    ll b1=a,b2=p-1,c=pb;
    ll gg=gcd(b1,b2);
    if(c%gg) return rst;
    b1/=gg, b2/=gg, c/=gg;
    ll x1,x2; exgcd(b1,b2,x1,x2);
    x1*=c; x1=(x1%b2+b2)%b2;
    ll cs=qp(g,x1,p),ec=qp(g,b2,p);
    for(ll cur=x1;cur<p-1;cur+=b2)
        rst.pb(cs), cs=cs*ec%p;
    sort(rst.begin(),rst.end());
    return rst;
}