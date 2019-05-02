//ʹ��ʱ��Ҫ���ߵ� ��cmp2�� 
#include<stdio.h>	//��bits/stdc++ list��stack���������ambiguous  
#include<math.h>
#include<algorithm>
#include<iostream>
#define maxn 150010	//������� 
using namespace std;


const double eps=1e-8;
const double PI=acos(-1.0);


//��;��룺 
struct Point{
	double x;
	double y;
} list[maxn];
double cross(Point p0,Point p1,Point p2) //������ : x1y2-x2y1   p0p1 X p0p2
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}   
double dis(Point p1,Point p2){ //���� �� 
	return sqrt((long double)(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }




//͹���� 
//�������� 1
//cross > 0 ���� p0p2 �� p0p1Ϊ��ʱ��   = 0 ���� ƽ��  
bool cmp(Point p1, Point p2){		//�Ƕ���ͬ�����Сǰ
	if(sgn(cross(list[0],p1,p2))>0) return true;
	else if(sgn(cross(list[0],p1,p2))==0 && dis(list[0],p1) <= dis(list[0],p2)) return true;
	else return false;   
} 
// ����������2 ���ж��ȶ�͹��ʱʹ�� ��ȫ��ʱ�뺬�ߵ� 
bool cmp2(Point p1,Point p2){
    if(sgn(cross(list[0],p1,p2))>0) return true;
    else if(sgn(cross(list[0],p1,p2))==0){
        if(sgn(atan2(p1.y,p1.x)-PI/2)>=0) return dis(list[0],p1) > dis(list[0],p2);
        else return dis(list[0],p1) < dis(list[0],p2);
    }
    else return false;
}
//��ʼ��list[0] ���½ǵ�  O(nlogn)
void init(int n){
	Point tmp; tmp=list[0]; int k=0;
	for(int i=1;i<n;i++){
		if(list[i].y< tmp.y || (list[i].y== tmp.y && list[i].x < tmp.x)){
			tmp = list[i];
			k=i;
		}
	}
	list[k]=list[0];
	list[0]=tmp;
	//�˴�ע��ʹ��cmp����cmp2 
	sort(list+1, list+n, cmp);
} 
//���͹�� Graham-scan  O(n) 
Point stack[maxn]; int top=0;    //װ͹����ջ ջ��ָ�� 0-top
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
			while(top>0 && cross(stack[top-1],stack[top],list[i])<=0) top--;    // <0�ĳ�<=0��Ϊ��͹�����ϵĵ��߳�
			top++;
			stack[top]=list[i];			
		}		
	}
} 




//��ת���ǣ� 
//͹��ֱ�� ��Զ��� O(n)
//ע���޳�͹�����ϵĵ� 
double rotatingCalipers(){   
	double res=0;
	if(top==1) {	//����������
		return dis(stack[0],stack[1]);//disq�Ǿ���ƽ��
	}
	else{
		stack[++top]=stack[0];  //�ѵ�һ����ŵ����
		int j=2;
		for(int i=0;i<top;i++){  //ö�ٱ� 
			while(cross(stack[i],stack[i+1],stack[j])<cross(stack[i],stack[i+1],stack[j+1]))
				j= (j+1)%top;	 
			res= max(res, max(dis(stack[i],stack[j]),dis(stack[i+1],stack[j])));
		}
	}
	return res;
} 



//ADOJ EX7 
//int main(){
//	int n;
//	scanf("%d",&n);
//	for(int i=0;i<n;i++){
//		scanf("%lf%lf",&list[i].x,&list[i].y);	
//	}
//	init(n);
//	graham(n);
//	���͹�� 
//	for(int i=0;i<=top;i++){
//		printf("%lf %lf\n",stack[i].x,stack[i].y);
//	}
//	printf("%d",top+1);
//	return 0;
//} 
//POJ 2187
//int main(){
//	int n;
//	scanf("%d",&n);
//	for(int i=0;i<n;i++){
//		scanf("%lf%lf",&list[i].x,&list[i].y);	
//	}
//	init(n);  
//	graham(n);
//	double ans= rotatingCalipers();
//	printf("%.0lf",ans*ans);
//	return 0;
//} 
