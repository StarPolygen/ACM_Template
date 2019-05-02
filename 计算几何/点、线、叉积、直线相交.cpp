
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>

using namespace std;
const double eps = 1e-8;
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }

//点： 加 减 乘 叉积   
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
    //点向量叉积 
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};

//线  位置关系  交点求解   
struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e)
    {
        s = _s;e = _e;
    }
    pair<Point,int> operator &(const Line &b)const
    {
        Point res = s;
        if(sgn((s-e)^(b.s-b.e)) == 0)
        {
            if(sgn((b.s-s)^(b.e-s)) == 0)
                return make_pair(res,0);//两直线重合
            else return make_pair(res,1);//两直线平行
        }
        double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
        res.x += (e.x - s.x)*t;
        res.y += (e.y - s.y)*t;
        return make_pair(res,2);//有交点
    }
};





//POJ 1269
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    scanf("%d",&T);
    double x1,y1,x2,y2,x3,y3,x4,y4;
    printf("INTERSECTING LINES OUTPUT\n");
    while(T--)
    {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        Line line1 = Line(Point(x1,y1),Point(x2,y2));
        Line line2 = Line(Point(x3,y3),Point(x4,y4));
        pair<Point,int> ans = line1 & line2;
        if( ans.second == 2)printf("POINT %.2lf %.2lf\n",ans.first.x,ans.first.y);
        else if(ans.second == 0)printf("LINE\n");
        else printf("NONE\n");
    }
    printf("END OF OUTPUT\n");
    
    return 0;
}
