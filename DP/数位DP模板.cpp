#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int arr[20]; 
ll dp[20][4];
ll dfs(int pos,int pre,int sta,bool limit)//�����������û��38��49�����еĸ����� 
{
	//��λ��ʱ  ���������ĸ�����Ϊһ
    if(pos==-1) return 1;					 
    //���仯��ͳ�ƹ���δ���Ͻ� ֱ�ӷ���
    if(!limit && dp[pos][sta]!=-1) return dp[pos][sta];
    
    //limit��Ҫ��������  ��֮ǰδͳ�ƹ���Ҫ���¼���
    int up=limit ? a[pos] : 9;	//��·���Ͻ�Լ��
    ll tmp=0;	//��ʼ��ans
    for(int i=0;i<=up;i++)
    {	
        if(sta==1 && i==9)continue;						//��֦����������״̬			 
        if(sta==2 && i==8)continue;
        if(sta==3 &&(i==8||i==9)) continue;
        if(i==4&&sta==0){								//״̬ת�ƺ͹���ͳ��
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
    
    //��¼
    if(!limit) dp[pos][sta]=tmp;						//�����һλ �����Ͻ��ǰ�� ����Ϊ�������� ���Լ�¼����
    return tmp;
}
ll solve(ll x)
{
    ll pos=0;
    while(x)
    {
        arr[pos++]=x%10;
        x/=10;
    }
    return dfs(pos-1,-1,0,true);
}
int main()
{
    int T;long long ri;
    scanf("%d",&T); 
    //memset(dp,-1,sizeof dp);���Ż�
    while(T--)
    {
    	scanf("%lld",&ri);
        memset(dp,-1,sizeof dp);
        printf("%lld\n",(ri-solve(ri)+1));
    }
    return 0;
}

