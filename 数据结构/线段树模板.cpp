#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
int a[maxn];
int sum[maxn<<2],lazy[maxn<<2];
void maintain(int k)
{
    sum[k]=sum[k<<1]+sum[k<<1|1];
}
void pushdown(int lenl,int lenr,int k)//����·ţ�����ϸ�ڵ���Ϣ
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
        sum[k]=newp*(r-l+1);//�ڷ�����������С����Ҫ��������ʱ
        lazy[k]=newp;//���½ڵ�Ľ�����������ӳٱ��lazy������֮��ı���·�
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
    pushdown(mid-l+1,r-mid,k);//ÿһ��ѯ��ִ�е���һ����Ϊ����һ�εݹ����Ҷ�ڵ���Ϣ
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

