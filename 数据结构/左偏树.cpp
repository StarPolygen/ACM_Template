//左偏树模板
using namespace std;
const int N=1000000;
void swap(int &x,int &y){int t=x;x=y,y=t;}
//ch：左右子节点编号   val：节点权值  dis：节点距离  f：节点父亲
int ch[N][2],val[N],dis[N],f[N];  
int n,m;

//合并x和y为根的堆，返回新堆的根
int merge(int x,int y) 
{
    if (x==0 || y==0)
        return x+y;
    if (val[x]<val[y] || (val[x]==val[y] && x>y))
        swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    f[ch[x][1]]=x;
    if (dis[ch[x][0]]<dis[ch[x][1]])
        swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;
}

//获得x所在堆的堆顶
int getf(int x) {  
    while(f[x]) x=f[x];
    return x;
}

//删除堆顶
int pop(int x) {  //删除x为根堆的堆顶并维护剩余点保持堆得性质
	val[x]=-1;  
	f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(lc,rc);    //将左子堆和右子堆合并
}

//更改某节点权值
int change(int x,int now)  
{
    val[x]=now;   //将节点x的值改为now
    f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(x,merge(lc,rc));  //合并子树，再将新点
}

#include <cstdio>
//左偏树模板
using namespace std;
const int N=1000000;
void swap(int &x,int &y){int t=x;x=y,y=t;}
//ch：左右子节点编号   val：节点权值  dis：节点距离  f：节点父亲
int ch[N][2],val[N],dis[N],f[N];  
int n,m;

//合并x和y为根的堆，返回新堆的根
int merge(int x,int y) 
{
    if (x==0 || y==0)
        return x+y;
    if (val[x]<val[y] || (val[x]==val[y] && x>y))
        swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    f[ch[x][1]]=x;
    if (dis[ch[x][0]]<dis[ch[x][1]])
        swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;
}

//获得x所在堆的堆顶
int getf(int x) {  
    while(f[x]) x=f[x];
    return x;
}

//删除堆顶
int pop(int x) {  //删除x为根堆的堆顶并维护剩余点保持堆得性质
	val[x]=-1;  
	f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(lc,rc);    //将左子堆和右子堆合并
}

//更改某节点权值
int change(int x,int now)  
{
    val[x]=now;   //将节点x的值改为now
    f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(x,merge(lc,rc));  //合并子树，再将新点
}

void init(){
    for(int i=1;i<=n;i++){
			ch[i][0]=ch[i][1]=0;
			f[i]=0;
			dis[i]=0;
	}
    memset(val,0,sizeof(val));
}
