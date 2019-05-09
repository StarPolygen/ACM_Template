//矩阵行列式求值 
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
    for(int i=0;i<N;i++)//当前行
    {
        for(int j=i+1;j<N;j++)//当前之后的每一行，因为每一行的当前第一个数要转化成0（想想线性代数中行列式的计算）
        {
            int x=i,y=j;
            while(a[y][i])//利用gcd的方法，不停地进行辗转相除
            {
                ll t=a[x][i]/a[y][i];
 
                for(int k=i;k<N;k++)
                    a[x][k]=(a[x][k]-a[y][k]*t)%MOD;
 
                swap(x,y);
            }
            if(x!=i)//奇数次交换，则D=-D'整行交换
            {
                for(int k=0;k<N;k++)
                    swap(a[i][k],a[x][k]);
                sign^=1;
            }
        }
        if(a[i][i]==0)//斜对角中有一个0，则结果为0
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

