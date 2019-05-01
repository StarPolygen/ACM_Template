#include <bits/stdc++.h>
这是一道线段树的题目呀，01序列那道，但是代码可能不具有模板的普适性呢 
using namespace std;
const int maxn=50000+10;
int n,m,top=0;
int st[maxn];
struct node{
	int l,r;
	int ls,ms,rs;
}a[maxn<<2];
void init(int l,int r,int i){
	a[i].l=l;
	a[i].r=r;
	a[i].ls=a[i].rs=a[i].ms=r-l+1;
	if(l!=r){
		int mid=(l+r)>>1;
		init(l,mid,2*i);
		init(mid+1,r,2*i+1);
	}
	
}
void change(int i,int t,int x){
	if(a[i].l==a[i].r){
		if(x==1) a[i].ls=a[i].ms=a[i].rs=1;
		else a[i].ls=a[i].rs=a[i].ms=0;
		return;
	}
	int mid=(a[i].l+a[i].r)>>1;
	if(t<=mid) change(2*i,t,x);
	else change(2*i+1,t,x);
	
	a[i].ls=a[2*i].ls;
	a[i].rs=a[2*i+1].rs;
	a[i].ms=max(a[2*i].ms,max(a[2*i+1].ms,a[2*i].rs+a[2*i+1].ls));
	if(a[2*i].ls==a[2*i].r-a[2*i].l+1) a[i].ls+=a[2*i+1].ls;
	if(a[2*i+1].rs==a[2*i+1].r-a[2*i+1].l+1) a[i].rs+=a[2*i].rs;

}
int query(int i,int t){
	if(a[i].r==a[i].l||a[i].r-a[i].l+1==a[i].ms||a[i].ms==0) 
		return a[i].ms;
	int mid=(a[i].l+a[i].r)>>1;
	if(t<=mid){
		if(t>=a[2*i].r-a[2*i].rs+1) return query(2*i,t)+query(2*i+1,mid+1); 
		else return query(2*i,t); 
	}else{
		if(t<=a[2*i+1].l+a[2*i+1].ls-1) return query(2*i+1,t)+query(2*i,mid);
		else return query(2*i+1,t);
	}
}
int main(){
	while(~scanf("%d%d",&n,&m)){
		char ch[2];int x;
	init(1,n,1);
	for(int i=1;i<=m;i++){
		scanf("%s",ch);
		if(ch[0]=='D'){
			scanf("%d",&x);
			st[top++]=x;
			change(1,x,0);
		}else if(ch[0]=='Q'){
			scanf("%d",&x);
			printf("%d\n",query(1,x));
		}else if(ch[0]=='R'){
			if(top>0){
				int tmp=st[--top];
				change(1,tmp,1);
			}
			
		}
	}
		
		
		
	}
	
	return 0;
}
