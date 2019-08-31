目录：
1.点：   加 减 点积 向量叉积 点叉积 两点距离 
2.直线： 位置关系 交点求解 两线距离 判定点在线段 判定线段相交
3.凸包： 凸包求解 凸包相交 凸包直径(旋转卡壳)
4.半平面交
——————————————————————————————————————————————————————————————————————————
//头文件和预定义
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
——————————————————————————————————————————————————————————————————————————
//1. 点： 加 减 乘 叉积   
struct P
{
    double x,y;
    P(){}
    P(double _x,double _y)
    {
        x = _x;y = _y;
    }//向量相加
    P operator +(const P &b)const
    {
        return P(x + b.x,y + b.y);
    }//向量减
    P operator -(const P &b)const
    {
        return P(x - b.x,y - b.y);
    }
    //向量点积
    double operator *(const P &b)const
    {
        return x*b.x + y*b.y;
    }
    //向量叉积 
    double operator ^(const P &b)const
    {
        return x*b.y - y*b.x;
    }
};

// 点叉积  
//p0p1 X p0p2   <0 逆时针 >0 顺时针 =0共线
double det(P p0,P p1,P p2) {   return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);} 

// 距离
double dis(P p1,P p2) {   return sqrt((double)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
} 
——————————————————————————————————————————————————————————————————————————

//直线：  位置关系  交点求解   
struct L{
    P a,b;
    L(){}
    L(P _s,P _e)
    {
        a = _s;b = _e;
    }
    pair<P,int> operator &(const L &_b)const
    {
        P res = a;
        if(sgn((a-b)^(_b.a-_b.b)) == 0)
        {
            if(sgn((_b.a-a)^(_b.b-a)) == 0)
                return make_pair(res,0);//两直线重合
            else return make_pair(res,1);//两直线平行
        }
        double t = ((a-_b.a)^(_b.a-_b.b))/((a-b)^(_b.a-_b.b));
        res.x += (b.x - a.x)*t;
        res.y += (b.y - a.y)*t;
        return make_pair(res,2);//有交点res
    }
};

//点在线段上
bool onSeg(P p, L s) {
    return sgn(det(p, s.a, s.b)) == 0 && sgn((s.a - p) * (s.b - p)) <= 0;
}
//线段相交
bool SegmentIntersection(L l1, L l2) {
    long long c1 = det(l1.a, l1.b, l2.a), c2 = det(l1.a, l1.b, l2.b);
    long long c3 = det(l2.a, l2.b, l1.a), c4 = det(l2.a, l2.b, l1.b);
    if (sgn(c1) * sgn(c2) < 0 && sgn(c3) * sgn(c4) < 0) return true;
    if (sgn(c1) == 0 && onSeg(l2.a, l1)) return true;
    if (sgn(c2) == 0 && onSeg(l2.b, l1)) return true;
    if (sgn(c3) == 0 && onSeg(l1.a, l2)) return true;
    if (sgn(c4) == 0 && onSeg(l1.b, l2)) return true;
    return false;
}


——————————————————————————————————————————————————————————————————————————

//凸包求解
vector<P> convex(vector<P> p) {
    vector<P> ans, S;
    for (int i = 0; i < p.size(); i++) {
        while (S.size() >= 2
                && sgn(det(S[S.size() - 2], S.back(), p[i])) <= 0)
                    S.pop_back();
        S.push_back(p[i]);
    }
    ans = S;
    S.clear();
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        while (S.size() >= 2
                && sgn(det(S[S.size() - 2], S.back(), p[i])) <= 0)
                    S.pop_back();
        S.push_back(p[i]);
    }
    for (int i = 1; i + 1 < S.size(); i++)
        ans.push_back(S[i]);
    return ans;
}
//点在多边形内部    前置：onSeg
bool PointInPolygon(P p, vector<P> poly) {
    int cnt = 0;
    for (int i = 0; i < poly.size(); i++) {
        if (onSeg(p, L(poly[i], poly[(i + 1) % poly.size()]))) return true;
        int k = sgn(det(poly[i], poly[(i + 1) % poly.size()], p));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[(i + 1) % poly.size()].y - p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) cnt++;
        if (k < 0 && d2 <= 0 && d1 > 0) cnt--;
    }
    if (cnt != 0) return true;
    return false;
}

//凸包相交
bool ConvexHudoubleDivide(vector<P> p1, vector<P> p2) {
    for (int i = 0; i < p1.size(); i++)
        if (PointInPolygon(p1[i], p2))
            return false;
    for (int i = 0; i < p2.size(); i++)
        if (PointInPolygon(p2[i], p1))
            return false;
    for (int i = 0; i < p1.size(); i++)
        for (int j = 0; j < p2.size(); j++)
            if (SegmentIntersection(L(p1[i], p1[(i + 1) % p1.size()]), L(p2[j], p2[(j + 1) % p2.size()])))
                return false;
    return true;
}


——————————————————————————————————————————————————————————————————————————