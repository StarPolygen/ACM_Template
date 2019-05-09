//��������ʽ��ֵ 
#include<iostream>
#include<cstdio>
#include<cmath>
 
using namespace std;
 
typedef __int64 lld;

lld a[205][205];
 
int sign;
ll N,MOD;
void solved()
{
    ll ans=1;
    for(int i=0;i<N;i++)//��ǰ��
    {
        for(int j=i+1;j<N;j++)//��ǰ֮���ÿһ�У���Ϊÿһ�еĵ�ǰ��һ����Ҫת����0���������Դ���������ʽ�ļ��㣩
        {
            int x=i,y=j;
            while(a[y][i])//����gcd�ķ�������ͣ�ؽ���շת���
            {
                ll t=a[x][i]/a[y][i];
 
                for(int k=i;k<N;k++)
                    a[x][k]=(a[x][k]-a[y][k]*t)%MOD;
 
                swap(x,y);
            }
            if(x!=i)//�����ν�������D=-D'���н���
            {
                for(int k=0;k<N;k++)
                    swap(a[i][k],a[x][k]);
                sign^=1;
            }
        }
        if(a[i][i]==0)//б�Խ�����һ��0������Ϊ0
        {
            cout<<0<<endl;
            return ;
        }
 
        else
            ans=ans*a[i][i]%MOD;
 
    }
 
    if(sign!=0)
        ans*=-1;
    if(ans<0)
        ans+=MOD;
    printf("%I64d\n",ans);
}


int main()
{
    int T;
    scanf("%d",&T);
 
    while(T--)
    {
        sign=0;
        scanf("%I64d%I64d",&N,&MOD);
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                scanf("%I64d",&a[i][j]);
        solved();
    }
    return 0;
}

