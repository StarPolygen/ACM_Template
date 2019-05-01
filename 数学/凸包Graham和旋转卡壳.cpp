#include<stdio.h>	//若bits/stdc++ list和stack命名会产生ambiguous 
#include<math.h>
#include<algorithm>
#include<iostream>
#define maxn 150010	//点的数量 
#define ll long long
using namespace std;

struct P{
	ll x;
	ll y;
} list[maxn];

ll cross(P p0,P p1,P p2) //计算叉积 : x1y2-x2y1   p0p1 X p0p2
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}   
double dis(P p1,P p2){ //距离 
	return sqrt((long double)(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
ll disq(P p1,P p2){ //距离平方 
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

//极角排序
//cross > 0 代表 p0p2 对 p0p1为逆时针   = 0 代表 平行 
bool cmp(P p1, P p2){		//角度相同则距离小前
	if(cross(list[0],p1,p2)>0) return true;
	else if(cross(list[0],p1,p2)==0 && dis(list[0],p1) <= dis(list[0],p2)) return true;
	else return false;   
} 

//初始化list[0] 左下角点  O(nlogn)
void init(int n){
	P tmp; tmp=list[0]; int k=0;
	for(int i=1;i<n;i++){
		if(list[i].y< tmp.y || (list[i].y== tmp.y && list[i].x < tmp.x)){
			tmp = list[i];
			k=i;
		}
	}
	list[k]=list[0];
	list[0]=tmp;
	sort(list+1, list+n, cmp);
} 

//求解凸包 Graham-scan  O(n) 
P stack[maxn]; int top=0;   //装凸集的栈 栈顶指针 
void graham(int n){
	if(n==1) {
		top=0; stack[0]=list[0];
	}if(n==2){
		top=1;
		stack[0]= list[0];
		stack[1]= list[1];
	}else{
		for(int i=0;i<=1;i++) stack[i]=list[i]; top=1;
		for(int i=2;i<n;i++){
			while(top>0 && cross(stack[top-1],stack[top],list[i])<=0) top--;    // <0改成<=0即为将凸包边上的点踢出
			top++;
			stack[top]=list[i];			
		}		
	}
} 

//旋转卡壳 凸包直径  O(n)
//注意剔除凸包边上的点 
ll rotatingCalipers(){   
	ll res=0;
	if(top==1) {	//仅有两个点
		return disq(stack[0],stack[1]);//disq是距离平方 
	}
	else{
		stack[++top]=stack[0];  //把第一个点放到最后
		int j=2;
		for(int i=0;i<top;i++){  //枚举边 
			while(cross(stack[i],stack[i+1],stack[j])<cross(stack[i],stack[i+1],stack[j+1]))
				j= (j+1)%top;	 
			res= max(res, max(disq(stack[i],stack[j]),disq(stack[i+1],stack[j])));
		}
	}
	return res;
} 



int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%lld%lld",&list[i].x,&list[i].y);	
	}
	init(n);  
	graham(n);
	ll ans= rotatingCalipers();
	printf("%lld",ans);
	return 0;
} 
