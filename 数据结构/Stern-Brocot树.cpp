//Stern-Brocot树
用于 [从小到大] 构造 [分子分母小于等于n] 的 [最简] 分数
1.SB树是二叉排序树 
2.SB树生成N层后的前序遍历是N阶Farey序列 
3.对于每次在m1/n1,m2/n2中插入(m1+m2)/(n1+n2)构成下一排。
5.Stern-Brocot树可以构成所有有理数。
4.Stern-Brocot树构成的所有分数均为最简分数，即gcd(m,n)==1。
5.任意两个构造时相邻的两个分数都满足m1n2-m2n1==1。
6.法理序列的长度为 len(Fn) = 欧拉前n前缀和*2+1

Stern-Brocot树构造如下：
     0/1                                        1/0
                          1/1
               1/2                   2/1
         1/3         2/3       3/2         3/1



//递归构造：N阶Farey序列的构造 根据需要添加0/1 和 1/0
void build(int m1,int n1,int m2,int n2)  //m1/n2 , m1/n2
{
	if(m1+m2>n||n1+n2>n) return;
    //Stern-Brocot树 左侧总是最小的，右侧最大的，那么总是优先输入左侧，再输入中间的，最后输入右侧的数
	build(m1,n1,m1+m2,n1+n2);
	top++;
	stack[top].a=m1+m2;
	stack[top].b=n1+n2;
	//如果是指定第k小的不可约分数，可以加上这一句小小优化一下 if(top>k) return;
	build(m1+m2,n1+n2,m2,n2);
}
//递推构造：对于任意N阶Farey序列中连续的三个分数m1/n1,m2/n2,m3/n3,必有： m3=[(n1+N)/n2]m2-m1   n3=[(n1+N)/n2]n2-n1;



//前驱后继   以下为后继 前驱类似
//SB树上搜索分数L后继  SB树是二叉排序树
//从区间左端点L=a/b出发 在Stern-Brocot树上搜索答案 复杂度：O(n) 当答案为1/n时取到最劣
Frac Gen(ll a,ll b,int n,ll k) {
    Frac l{0,1},mid{1,1},r{1,0},res{-1,-1};
    ll x=a,y=b;    //在SB树上查找第一个≥L的数 （SB树中L的后继）
    //停止条件:1.x=y代表找到L  2.分子或分母即将超过n 找到的L后继为大于L的最小分数 
    while(x!=y && max(mid.first,mid.second)<=n) { 
        if(a*mid.second<b*mid.first)   //更新后继
            res=mid;
        if(x<y) {     //若x<y L在当前区间左子树 向左搜索 分数变小
            tie(l,mid,r)=make_tuple(l,make_pair(l.first+mid.first,l.second+mid.second),mid);
            y-=x;
        }
        else {  //若x>y L在当前区间右子树 向右搜索 分数变大
            tie(l,mid,r)=make_tuple(mid,make_pair(mid.first+r.first,mid.second+r.second),r);
            x-=y;
        }
    }
    return res;
}

