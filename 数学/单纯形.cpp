#include <bits/stdc++.h>
//MΪԼ��ʽ����_+1��NΪԼ����������_+1 
//��׼ʽ Լ��Ϊ<=   Ŀ�꺯�����     �� >= ��С����Ϊ��żʽ 
#define M 5
#define N 4
#define INF 0x7f7f7f7f
using namespace std;
int m,n;
double a[M][N];
int check()
{
    for(int i=1;i<=n;i++)
        if(a[0][i]>0) return i;
    return 0;
}
void Simplex()
{
    while(int t=check())
    {
        double limit=INF;
        int choseline;
        for(int i=1;i<=m;i++)
        {
            if(a[i][t]<=0.9)continue;
            if(a[i][0]/a[i][t]<limit)limit=a[i][0]/a[i][t],choseline=i;
        }
        if(limit==INF){a[0][0]=INF;break;}
        double di=a[choseline][t];
        for(int i=0;i<=n;i++)
        {
            if(i==t)a[choseline][i]/=di;
            a[choseline][i]/=di;
        }
        for(int i=0;i<=m;i++)
        {
            if(i==choseline||!a[i][t])continue;
            if(i==0)a[i][0]+=a[choseline][0]*a[i][t];
            else a[i][0]-=a[i][t]*a[choseline][0];
            double l=a[i][t];
            for(int j=1;j<=n;j++)
            {
                if(j==t)a[i][j]=-l*a[choseline][t];
                else a[i][j]-=l*a[choseline][j];
            }
        }
    }
    return;
}
int main()
{
	int T;
	scanf("%d",&T);
	//m=Լ����n=�������� 
	//������3��Լ����4��������������Ӧ��m=3,n=4;
	//Ȼ����Ŀ�꺯����Сֵ����Լ��ʽΪ>=,���ͨ����ż����ת�ú�  ��m=4(Լ��)��n=3(��������) 
	m=4,n=3;
	while(T--){
		for(int i=0;i<5;i++){
			for(int j=0;j<4;j++){
				a[i][j]=0;
			}
		}
		// a[0][j] Ŀ�꺯�� ����jǰϵ�� 
		for(int j=1;j<=n;j++) {
	    	scanf("%lf",&a[0][j]);
		}
		// a[i][j] Լ��ʽi ����jǰϵ�� 
		a[1][1]=0,a[1][2]=2,a[1][3]=0;
		a[2][1]=0,a[2][2]=0,a[2][3]=3;
		a[3][1]=1,a[3][2]=1,a[3][3]=0;
		a[4][1]=1,a[4][2]=0,a[4][3]=2;
		// a[i][0] Լ��ʽi ����ʽ�Ҳೣ�� 
		a[1][0]=1,a[2][0]=1,a[3][0]=1,a[4][0]=1;
	    
	    Simplex();
	    
	    //�𰸣�a[0][0]   ȡ��ʱ (int)ceil(a[0][0])
	    printf("%d\n",(int)ceil(a[0][0]));
	}
    return 0;
}

