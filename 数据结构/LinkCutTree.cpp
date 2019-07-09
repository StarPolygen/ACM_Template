#include<bits/stdc++.h>
using namespace std;

//LCT 模板   单点修改版
#define R register int
#define I inline void
#define lc c[x][0]
#define rc c[x][1]

const int N=3e5+9;//点数
int f[N],c[N][2],v[N],s[N],st[N];
//f:父节点  c[][0]:左子  v:节点的值  s:子树下的储存的权值数（包括重复权值） r:区间翻转的lazy
bool r[N];

//splay 部分
inline bool nroot(R x){//判断节点是否为一个Splay的根（与普通Splay的区别1）
    return c[f[x]][0]==x||c[f[x]][1]==x;
}//原理很简单，如果连的是轻边，他的父亲的儿子里没有它
I pushup(R x){//上传信息
    s[x]=s[lc]^s[rc]^v[x];
}
I pushr(R x){R t=lc;lc=rc;rc=t;r[x]^=1;}//翻转操作
I pushdown(R x){//判断并释放懒标记
    if(r[x]){
        if(lc)pushr(lc);
        if(rc)pushr(rc);
        r[x]=0;
    }
}
I rotate(R x){//一次旋转
    R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
    if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;//额外注意if(nroot(y))语句，此处不判断会引起致命错误（与普通Splay的区别2）
    if(w)f[w]=y;f[y]=x;f[x]=z;
    pushup(y);
}
I splay(R x){//只传了一个参数，因为所有操作的目标都是该Splay的根（与普通Splay的区别3）
    R y=x,z=0;
    st[++z]=y;//st为栈，暂存当前点到根的整条路径，pushdown时一定要从上往下放标记（与普通Splay的区别4）
    while(nroot(y))st[++z]=y=f[y];
    while(z)pushdown(st[z--]);
    while(nroot(x)){
        y=f[x];z=f[y];
        if(nroot(y))
            rotate((c[y][0]==x)^(c[z][0]==y)?x:y);
        rotate(x);
    }
    pushup(x);
}

//LCT 部分
I access(R x){//访问
    for(R y=0;x;x=f[y=x])
        splay(x),rc=y,pushup(x);
}
I makeroot(R x){//换根
    access(x);splay(x);
    pushr(x);
}
int findroot(R x){//找根（在真实的树中的）
    access(x);splay(x);
    while(lc)pushdown(x),x=lc;
    splay(x);
    return x;
}
I split(R x,R y){//提取路径
    makeroot(x);
    access(y);splay(y);
}
I link(R x,R y){//连边
    makeroot(x);
    if(findroot(y)!=x)f[x]=y;
}
I cut(R x,R y){//断边
    makeroot(x);
    if(findroot(y)==x&&f[y]==x&&!c[y][0]){
        f[y]=c[x][1]=0;
        pushup(x);
    }
}



int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(R i=1;i<=n;++i) scanf("%d",&v[i]);
    while(m--){
        int type,x,y;
        scanf("%d%d%d",&type,&x,&y);
        switch(type){
        case 0:split(x,y);printf("%d\n",s[y]);break;
        case 1:link(x,y);break;
        // 注意：cut(a,f[a]);
        //这样写是对LCT的错误应用，在调用时要以数值为准，决不能使用splay的内部关系数组，如f，因为他们随时会随着splay或LCT的操作被修改
        case 2:cut(x,y);break;
        //先把x转上去再改，不然会影响Splay信息的正确性
        case 3:splay(x); v[x]=y;
        }
    }
    return 0;
}


//LCT 模板 普适版
/*
一颗树，有很多操作：
（1）加上边a-b；
（2）将树以a为根，然后删除b和它的父节点的边；
（3）a->b的路径上的所有点权加上d（包含a，b）；
（4）查询a->b的路径上最大的点权；
不合法的操作输出-1.
*/


//相适配的·宏
#define N 300008               
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1 
#define clr(x,v) memset(x,v,sizeof(x));
#define rep(x,y,z) for (int x=y;x<=z;x++)
#define repd(x,y,z) for (int x=y;x>=z;x--)
/**************************************************************************/

//spaly部分 
//val：点值  mx：维护最大值  tag：额外lz标记 
int val[N],c[N][2],fa[N],mx[N],tag[N],rev[N],lt[N],st[N];
int n,q,sum; 
struct line{
    int u,v,nt;
}eg[N*2];
void addedge(int u,int v){ //加边
    eg[++sum]=(line){u,v,lt[u]};
    lt[u]=sum;
}
void init(){ //初始化
    rep(i,1,n) val[i]=c[i][0]=c[i][1]=mx[i]=tag[i]=rev[i]=lt[i]=fa[i]=0;
    sum=1;
}
void dfs(int u){   //建树
    for (int i=lt[u];i;i=eg[i].nt){
        int v=eg[i].v;
        if (fa[v] || v==1) continue;
        fa[v]=u;
        dfs(v);
    }
}
bool isroot(int k){  //判断节点是否为一个Splay的根（与普通Splay的区别1）
    return c[fa[k]][0]!=k && c[fa[k]][1]!=k;
}
void pushup(int x){  //上传信息
    int l=c[x][0],r=c[x][1];
    mx[x]=max(max(mx[l],mx[r]),val[x]);
}
void pushdown(int x){  //判断并释放懒标记
    int l=c[x][0],r=c[x][1];
    if (rev[x]){ //自带的区间反转lazy标记
        if (l) rev[l]^=1;
        if (r) rev[r]^=1;
        rev[x]^=1;
        swap(c[x][0],c[x][1]);
    }
    if (tag[x]){ //额外添加的线段树区间修改lazy标记
        if (l) {tag[l]+=tag[x]; mx[l]+=tag[x], val[l]+=tag[x]; }
        if (r) {tag[r]+=tag[x]; mx[r]+=tag[x], val[r]+=tag[x]; }
        tag[x]=0;
    }
}
void rotate(int x){ //一次旋转
    int y=fa[x],z=fa[y],l,r;
    if (c[y][0]==x) l=0; else l=1; r=l^1;
    if (!isroot(y)){
        if (c[z][0]==y) c[z][0]=x; else c[z][1]=x;
    }
    fa[x]=z; fa[y]=x; fa[c[x][r]]=y;
    c[y][l]=c[x][r]; c[x][r]=y;
    pushup(y); pushup(x);
}
void splay(int x){  //splay转到根上
    int top=0; st[++top]=x;
    for (int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
    while (top) pushdown(st[top--]);
    while (!isroot(x)){
        int y=fa[x],z=fa[y];
        if (!isroot(y)){
            if (c[y][0]==x^c[z][0]==y) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

//LCT部分
void access(int x){//访问
    int t=0;
    while (x){
        splay(x);
        c[x][1]=t;
        pushup(x);            
        t=x; x=fa[x];
    }
}
int find(int u){//找根（在真实的树中的）
    access(u); splay(u);
    while (c[u][0]) u=c[u][0];
    return u;
}
bool judge(int u,int v){//判断uv是否在同一颗树内（原树）
    return find(u)==find(v);
}
void rever(int u){//区间翻转
    access(u); splay(u); rev[u]^=1;
}
void link(int u,int v){//连边
    rever(u); fa[u]=v; 
}
void cut(int u,int v){//断边
    rever(u); access(v); splay(v); fa[c[v][0]]=0; c[v][0]=0; pushup(v);
}
void add(int u,int v,int w){//区间加
    rever(u); access(v); splay(v); tag[v]+=w; mx[v]+=w; val[v]+=w;
}
void query(int u,int v){//区间查询
    rever(u); access(v); splay(v); printf("%d\n",mx[v]);
}
int main(){
    while (~scanf("%d",&n))
    {
        init();
        rep(i,1,n-1){
            int u,v;
            scanf("%d%d",&u,&v);//双向加边
            addedge(u,v); addedge(v,u);
        }
        rep(i,1,n){
            int x;
            scanf("%d",&x);//初始化节点的权值和需要维护的最大值
            val[i]=mx[i]=x;
        }
        dfs(1);
        scanf("%d",&q);
        while (q--){
            int x,u,v,w;
            scanf("%d",&x);
            if (x==1){
                scanf("%d %d",&u,&v);        
                if (!judge(u,v)) link(u,v); else puts("-1");
            }
            if (x==2){
                scanf("%d %d",&u,&v);        
                if (judge(u,v) && u!=v) cut(u,v); else puts("-1");
            }
            if (x==3){
                scanf("%d %d %d",&w,&u,&v);
                if (judge(u,v)) add(u,v,w);    else puts("-1");
            }
            if (x==4){
                scanf("%d %d",&u,&v);        
                if (judge(u,v)) query(u,v); else puts("-1");
            }
        }
        printf("\n");
    }
}