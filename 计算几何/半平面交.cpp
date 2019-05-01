//POJ 3335 模板题 
//最终可能用到的  ：p[0-(pn-1)]     	轮廓点集 封闭则为凸包  逆时针序 
//                  pn              	轮廓点数量 
// 					dq[bot-(top-1)] 	轮廓线编号  极角递增  
// 					l[dq[bot-(top-1)]]  轮廓线  极角递增 
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#define ll long long
#define maxn 110
using namespace std;

const double eps = 1e-8; 

struct Point{
	double x;
	double y;
} list[maxn],p[maxn]; 	  //list 原始点集   p 半平面交轮廓点集合,逆时针 

int n, tol, pn;  	      //n 总点数  tol 总直线数  pn 半平面轮廓点数 
int dq[maxn], top, bot;   //dq 双向队列，半平面交轮廓边集合   top 队列顶   bot 队列底 

struct Line {
    Point a, b;
    double angle;
} l[maxn];

//添加边  
//使用时 addLine(l[tol++], a, b) 
//半平面取向量 ab 的左边 
void addLine(Line& l, Point a, Point b){
    l.a = a;
    l.b = b;
    l.angle = atan2(b.y - a.y, b.x - a.x);
}

//叉乘 
double cross(Point p0, Point p1, Point p2) {
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}

//消除精度影响 
int dblcmp(double k) {
    if (fabs(k) < eps) return 0;
    return k > 0 ? 1 : -1;
}

//排序：极角小的排前面，极角相同时，决定性的排在前面，以便去重
inline bool cmp(const Line& l1, const Line& l2){
    int d = dblcmp(l1.angle - l2.angle);
    return d ? d < 0 : dblcmp(cross(l1.a, l2.a, l2.b)) > 0;
}

//求两直线交点 
Point getIntersect(Line l1, Line l2) {
	Point p;   
	double dot1,dot2;    
	dot1 = cross(l2.a, l1.b, l1.a);    
	dot2 = cross(l1.b, l2.b, l1.a);    
	p.x = (l2.a.x * dot2 + l2.b.x * dot1) / (dot2 + dot1);    
	p.y = (l2.a.y * dot2 + l2.b.y * dot1) / (dot2 + dot1);
	return p;
}

//判断 l1,l2 的交点是否在 l0 的右边  
bool judge(Line l0, Line l1, Line l2){
     Point p = getIntersect(l1, l2);
     return dblcmp(cross(p, l0.a, l0.b)) < 0;
}
 
// 求解半平面交  O(nlogn) 
void HalfPlaneIntersect(){
    int i, j;
    
    sort(l, l + n, cmp); //排序 
    //去重 
    for(i = 0, j = 0; i < tol; i++) if(dblcmp(l[i].angle - l[j].angle) > 0) l[++j] = l[i];
    //模拟双端队列 
    tol = j + 1, dq[0] = 0, dq[1] = 1, top = 1, bot = 0;
    for(i = 2; i < tol; i++){
    	//判断新加入直线产生的影响
        while(top > bot && judge(l[i], l[dq[top]], l[dq[top - 1]])) top--; 
        while(top > bot && judge(l[i], l[dq[bot]], l[dq[bot + 1]])) bot++; 
        dq[++top] = i;
    }
    //最后判断最先加入的直线和最后的直线的影响
    while(top > bot && judge(l[dq[bot]], l[dq[top]], l[dq[top - 1]])) top--;
    while(top > bot && judge(l[dq[top]], l[dq[bot]], l[dq[bot + 1]])) bot++;
    dq[++top] = dq[bot];
    for(pn = 0, i = bot; i < top; i++, pn++) p[pn] = getIntersect(l[dq[i + 1]], l[dq[i]]);
}

// 利用叉乘 计算凸包面积   
double getArea(){
    if(pn < 3) return 0;
    double area = 0;
    for(int i = 1; i < pn - 1; i++) area += cross(p[0], p[i], p[i + 1]);
    if(area < 0) area = -area;
    return area / 2;
}

//判断输入点的顺序，如果面积 <0，说明输入的点为顺时针，否则为逆时针
bool judge() {
  double ans = 0;
  for (int i = 1; i < n - 1; i++) {
    ans += (cross(list[0],list[i],list[i+1]));
  }
  return ans < 0;
}


int main(){
	int T; 
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		tol = 0; 
		for(int i = 0; i < n; i++){    
			scanf("%lf %lf", &list[i].x, &list[i].y);
		}
		
		if (judge()) {//判断输入顺序，保证逆时针连边。
	      	for (int i = 0; i < n; i++) {
	        	addLine(l[tol++], list[(i + 1)%n], list[i]);
	     	}
    	}else{
		    for (int i = 0; i < n; i++) {
		        addLine(l[tol++], list[i], list[(i + 1)%n]);
		    }
    	}
		HalfPlaneIntersect();
		printf("%s\n", pn < 3 ? "NO" : "YES");	
	}
	
	
	return 0;
} 
