//NTTģ�壬��ģ����NNTֱ�Ӷ�ԭʼ������������ԭʼ�����СΪmaxl=maxn<<2
//ע���ٴ�ʹ��ʱ�ı��ݣ���Ϊ�������NTT������ᱣ���ڵ�һ��ԭʼ����f�ڣ�����ԭʼ���ݸ��ǵ�
//�Լ����Ҫ��NTT�������ʱ��f�ڣ���Ϊ��һ��ntt��ԭʼ����ʹ�ã�ע�⽫n֮����������
//ע��ԭʼ����ĳ�ʼ��
#include<bits/stdc++.h>
#define maxn 200020
using namespace std;
typedef long long ll;
const ll mod = 998244353;  //һ��ֻ�����֣�98244353,1004535809,469762049 
const ll _g = 3;	//ģ����ԭ�� 


//ǰ��ģ��
ll mul(ll u, ll v, ll p) {
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}
ll bin(ll x, ll n,ll p) {
    ll ret = p != 1;
    for (x %= p; n; n >>= 1, x = mul(x,x,p))
        if (n & 1) ret = mul(ret,x,p);
    return ret;
}
inline ll get_inv(ll x, ll p) { return bin(x, p - 2, p); }



//NTT
const int maxl = maxn<<2; 
int rev[maxl];
void NTT(int *a,int len,int f){//�˴���len���Ѿ�����ģ����빤����mul�����
	for(int i=0;i<len;++i)if(i<rev[i])swap(a[i],a[rev[i]]);
	for(int i=1;i<len;i<<=1){
		int w1=bin(_g,((mod-1)/(i<<1)*f+mod-1)%(mod-1),mod);
		for(int j=0;j<len;j+=(i<<1)){
			int w=1;
			for(int k=0;k<i;++k,w=1ll*w*w1%mod){
				int x1=a[j+k],x2=1ll*w*a[j+i+k]%mod;
				a[j+k]=(x1+x2)%mod;
				a[j+i+k]=(x1+mod-x2)%mod;
			}
		}
	}
	if(!(~f)){
		int invlen=get_inv(len,mod);
		for(int i=0;i<len;++i)a[i]=1ll*a[i]*invlen%mod;
	}
}
void mul(int *a,int *b,int n){//�˴��Ĳ���nΪԭʼ��������ó���֮��
	int len=1,bit=0;
	while(len<=n)len<<=1,++bit;
	for(int i=0;i<len;++i)rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	NTT(a,len,1),NTT(b,len,1);
	for(int i=0;i<len;++i)a[i]=1ll*a[i]*b[i]%mod;
	NTT(a,len,-1);
}

//ԭʼ����Ҫ�󳤶�ҲΪmaxl,���ս����f�� 
int f[maxl],g[maxl];
int main(){
	return 0;
} 
