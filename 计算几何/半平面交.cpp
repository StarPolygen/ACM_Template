//�����õ��� ��	p[0-(pn-1)]     �����㼯 �����Ϊ͹��  ��ʱ���� 
//            	pn              	���������� 
// 	         	dq[bot-(top-1)] 	�����߱��  ���ǵ���  
// 	      		l[dq[bot-(top-1)]]  ������  ���ǵ��� 

#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#define ll long long
using namespace std;

const double eps = 1e-8; 
const int maxn=1510; 


struct Point{
	double x;
	double y;
} list[maxn],p[maxn]; 	  //list ԭʼ�㼯   p ��ƽ�潻�����㼯��,��ʱ�� 

struct Line {
    Point a, b;
    double angle;
} l[maxn];

int n, tol, pn;  	      //n �ܵ���  tol ��ֱ����  pn ��ƽ���������� 
int dq[maxn], top, bot;   //dq ˫����У���ƽ�潻�����߼���   top ���ж�   bot ���е�



int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }
//��ӱ�  ʹ��ʱ addLine(l[tol++], a, b) ��ƽ��ȡ���� ab ����� 
void addLine(Line& l, Point a, Point b){
    l.a = a;
    l.b = b;
    l.angle = atan2(b.y - a.y, b.x - a.x);
}
double cross(Point p0, Point p1, Point p2) {

  return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}
//ֱ�����򣺼���С����ǰ�棬������ͬʱ�������Ե�����ǰ�棬�Ա�ȥ��
inline bool cmp(const Line& l1, const Line& l2){
    int d = sgn(l1.angle - l2.angle);
    return d ? d < 0 : sgn(cross(l1.a, l2.a, l2.b)) > 0;
}

//����ֱ�߽���  
Point getIntersect(Line l1, Line l2) {
	Point p;   
	double dot1,dot2;    
	dot1 = cross(l2.a, l1.b, l1.a);    
	dot2 = cross(l1.b, l2.b, l1.a);    
	p.x = (l2.a.x * dot2 + l2.b.x * dot1) / (dot2 + dot1);    
	p.y = (l2.a.y * dot2 + l2.b.y * dot1) / (dot2 + dot1);
	return p;
}

//�ж� l1,l2 �Ľ����Ƿ��� l0 ���ұ� 
bool judge(Line l0, Line l1, Line l2){
     Point p = getIntersect(l1, l2);
     return sgn(cross(p, l0.a, l0.b)) < 0;
}


// ����ƽ�潻  O(nlogn)  
void HalfPlaneIntersect(){
    int i, j;
    sort(l, l + n, cmp); //����  
    //ȥ�� 
    for(i = 0, j = 0; i < tol; i++) if(sgn(l[i].angle - l[j].angle) > 0) l[++j] = l[i];
    //ģ��˫�˶��� 
    tol = j + 1, dq[0] = 0, dq[1] = 1, top = 1, bot = 0;
    for(i = 2; i < tol; i++){
    	//�ж��¼���ֱ�߲�����Ӱ��
        while(top > bot && judge(l[i], l[dq[top]], l[dq[top - 1]])) top--; 
        while(top > bot && judge(l[i], l[dq[bot]], l[dq[bot + 1]])) bot++; 
        dq[++top] = i;
    }
   //����ж����ȼ����ֱ�ߺ�����ֱ�ߵ�Ӱ��
    while(top > bot && judge(l[dq[bot]], l[dq[top]], l[dq[top - 1]])) top--;
    while(top > bot && judge(l[dq[top]], l[dq[bot]], l[dq[bot + 1]])) bot++;
    dq[++top] = dq[bot];
    for(pn = 0, i = bot; i < top; i++, pn++) p[pn] = getIntersect(l[dq[i + 1]], l[dq[i]]);
}


// �������͹�����   
double getArea(){
    if(pn < 3) return 0;
    double area = 0;
    for(int i = 1; i < pn - 1; i++) area += cross(p[0], p[i], p[i + 1]);
    if(area < 0) area = -area;
    return area / 2;
}

//�ж�������˳�������� <0��˵������ĵ�Ϊ˳ʱ�룬����Ϊ��ʱ��
bool judge() {
  double ans = 0;
  for (int i = 1; i < n - 1; i++) {
    ans += (cross(list[0],list[i],list[i+1]));
  }
  return ans < 0;
}

//POJ 3335  POJ 1279
int main(){
	int T; 
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		tol = 0; 
		for(int i = 0; i < n; i++){    
			scanf("%lf %lf", &list[i].x, &list[i].y);
		}
		if (judge()) {//�ж�����˳�򣬱�֤��ʱ������
	      		for (int i = 0; i < n; i++) {
	        		addLine(l[tol++], list[(i + 1)%n], list[i]);
	     		}
    		}else{
		  	for (int i = 0; i < n; i++) {
		        	addLine(l[tol++], list[i], list[(i + 1)%n]);
		    	}
    		}
		HalfPlaneIntersect();
		//�����ƽ�潻������ ע����ܳ���-0.00 
		for(int i=0;i<pn;i++){
			printf("%lf %lf\n",p[i].x,p[i].y);
		}
		//POJ 3335  �ж�����κ˵Ĵ����� pn>=3�������ܿ������н����λ�� 
		printf("%s\n", pn < 3 ? "NO" : "YES");
		//POJ 1279  �����εĺ����
		printf("%.2lf\n", getArea());	
	}
	return 0;
} 

