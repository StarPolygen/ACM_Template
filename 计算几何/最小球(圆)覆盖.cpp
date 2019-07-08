   
//模拟退火求最小球覆盖（圆覆盖）

#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<time.h>
using namespace std;



struct point3D
{
    double x,y,z;
    int    p; //距离当前球心最远点 也是限制答案减小更优的瓶颈
    double r;    //最远点对应的半径
} data[1050];
int n;
double dis(point3D a,point3D b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)+(a.z-b.z)*(a.z-b.z));
}


//模拟退火
double solve()
{   
    srand(time(0));
    double T=10000;                //T：温度            初始越高越精确  但效率越低      
    double delt=0.98;              //delt：温度降低率    越大越精确  但效率越低 一般在0.95-0.99之间                                                                        
    const double Min_T=1e-8;       //Min_T：温度下限    
    double ans=1e10;               //ans：目标函数值     由于本题求最小，因此初始设为INF
    double mt;                     //mt：当前函数值      用来更新目标函数值


    //目标解X  初始设为原点
    point3D X;
    X.x=X.y=X.z=X.p=0;
    //求出X的相关信息
    for(int i=0; i<n; i++) if(dis(X,data[X.p])<dis(X,data[i])) X.p=i,X.r=dis(X,data[X.p]);


    //外循环，标致退火完成
    while(T>Min_T) {      //当温度小于Min_T 代表解趋于稳定 可以输出目标函数值F(x)
        //由当前解X产生新解X1 
        point3D X1;
        X1.x = X.x + (data[X.p].x-X.x)/X.r*T;
        X1.y = X.y + (data[X.p].y-X.y)/X.r*T;
        X1.z = X.z + (data[X.p].z-X.z)/X.r*T;
        X1.p = 0;


        //获得X1所对应函数值F(X1)及其他相关信息
        for(int i=0; i<n; i++) if(dis(X1,data[X1.p])<dis(X1,data[i])) X1.p=i,X1.r=dis(X1,data[X1.p]);
        //目标函数差
        double def=X1.r-X.r;
        ans=min(ans,X1.r);


        //判断新解是否被接受
        if(def<0) {//移动后得到更优解，则总是接受移动
            X=X1;
        }//一定概率接受比当前更差的解
        else if(exp( def/T ) > rand()%1000/(double)1001 ){
            X=X1;
        }

        //降温退火
        T*=delt;
    }
    return ans;
}



int main()
{
    double ans;
    while(scanf("%d",&n)!=EOF)
    {
       for(int i=0; i<n; i++)
        scanf("%lf%lf%lf",&data[i].x,&data[i].y,&data[i].z);
        ans=solve();
        printf("%.7f\n",ans);
    }
    return 0;
}

/*
3 0 0 0 3 0 0 0 4 0
2.5000000
4 0 0 0 1 0 0 0 1 0 0 0 1
0.8164966
*/