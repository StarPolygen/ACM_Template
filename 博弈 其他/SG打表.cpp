//组合博弈 常常转化为子问题的SG值NIM和求解
//根据具体问题常常有两种方式求子问题SG值： SG打表(常用于 操作f相对固定且不太多 或 子问题共用SG表  的情况)         
//                                     利用DAG的一些性质获得某些结论 快速计算出SG eg.HDU1729
//SG函数值详解见文末



//SG打表模板
#pragma GCC optimize(2)

const int N = 101;
const int MAXN = 10001;

//f[N]:可改变当前状态的方式，N为方式的种类，f[N]要在getSG之前先预处理
//SG[]:0~n的SG函数值
//S[]:为x后继状态的集合
int f[N],SG[MAXN]; bool S[MAXN];
void getSG(int n,int k)   ///n求解范围 k是f的长度。
{
    int i,j;
    memset(SG,0,sizeof(SG));
    //因为SG[0]始终等于0，所以i从1开始
    for(i = 1; i <= n; i++){
        //每一次都要将上一状态 的 后继集合 重置
        memset(S,0,sizeof(S));
        for(j = 0; f[j] <= i && j < k; j++)
            S[SG[i-f[j]]] = 1;  //将后继状态的SG函数值进行标记
        for(j = 0; j < n; j++)  
            if(!S[j])   //查询当前后继状态SG值中最小的非零值
            break;
        SG[i] = j;
    } 
}

int main(){
    int n,m,k;
    f[0] = f[1] = 1;
    for(int i = 2; i <= 16; i++)
        f[i] = f[i-1] + f[i-2];
    //调用博弈SG打表
    getSG(1000,16);
    while(scanf("%d%d%d",&m,&n,&k),m||n||k){
        //查询打表结果
        if(SG[n]^SG[m]^SG[k]) printf("Fibo\n");
        else printf("Nacci\n");
    }
    return 0;
}
/*
SG即Sprague-Garundy函数，把博弈游戏抽象成有向无环图
(1) 有向无环图
(2) 玩家1先移动，起点是x0
(3) 两个玩家轮流移动
(4) 对于顶点x, 玩家能够移动到的顶点集记为F(x).
(5) 不能移动的玩家会输掉游戏
首先定义mex(minimal excludant)运算，这是施加于一个集合的运算，表示最小的不属于这个集合的非负整数。例如mex{0,1,2,4}=3、 mex{2,3,5}=0、mex{}=0。
定义: 一个图的Sprague-Grundy函数(X,F)是定义在X上的非负函数g(x)，并且满足：
       g(x) = mex{g(y) : y∈F(x)}
看到这里先好好理解一下sg值是怎么求的；
如果在取子游戏中每次只能取{1,2,3}，那么各个数的SG值是多少？
x      0 1 2 3 4 5 6 7 8 9 10 11 12 13 14. . .
g(x) 0 1 2 3 0 1 2 3 0 1  2   3   0   1   2. . .
看看这个和上面那个图的规律：
  P-点: 即令 g(x) = 0 的 x 点！
  N-点: 即令 g(x) > 0 的 x 点！
最后看下组合博弈，就是把简单的游戏组合起来，比如3堆的可以看成3个一堆的游戏。
 定理：
假设游戏 Gi的SG函数是gi, i=1,…,n, 则
G = G1 + … + Gn 的 SG函数是
g(x1,…,xn) = g1(x1)⊕…⊕gn(xn).
其中那个符合就是异或^