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

