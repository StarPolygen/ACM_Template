//Tarjan 强连通分量 缩点 
int dfn[maxn],low[maxn],stack[maxn],vis[maxn],color[maxn],sum,deep,top;
vector<int> g[maxn];
void Tarjan(int u){
    dfn[u]=++deep;  //首先初始化dfn[u]=low[u]=第几个被dfs到 
    low[u]=deep;
    vis[u]=1;
    stack[++top]=u;  //将u存入stack[]中，并将vis[u]设为true
    int sz=g[u].size();
    for(int i=0;i<sz;i++){
        int v=g[u][i];
        if(!dfn[v]){
            Tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else{
            if(vis[v]){
                low[u]=min(low[u],low[v]);
            }
        }
    }
    if(dfn[u]==low[u]){
        color[u]=++sum;  //color[u]是u分量缩点后的点标 
        //cost[sum]=min(cost[sum],arr[u][3]); //维护缩后点的性质 
        vis[u]=0;
        while(stack[top]!=u){
        	//cost[sum]=min(cost[sum],arr[stack[top]][3]); 
            color[stack[top]]=sum;
            vis[stack[top--]]=0;
        }
        top--;
    }
}

void init();

void init(){
    sum=deep=top=0;
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(stack,0,sizeof(stack));
    memset(vis,0,sizeof(vis));
    memset(color,0,sizeof(color));
    for(int i=0;i<maxn;i++){
        g[i].clear();
    }
}
 
for(int i=1;i<=n;i++) if(!dfn[i]) Tarjan(i); //调用 
