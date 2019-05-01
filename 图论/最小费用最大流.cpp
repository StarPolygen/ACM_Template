#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
const int maxn = 1010; //同样需要注意参数，根据构图调整点数和边数 
const int maxm = 30000;
bool vis[maxn]; int dist[maxn];
//解释一下各数组的含义：vis两个用处：spfa里的访问标记，増广时候的访问标记，dist是每个点的距离标号
int N, m, s, t, ans = 0;
//s是起点，t是终点，ans是费用答案
int nedge = -1, p[maxm], c[maxm], cc[maxm], nex[maxm], head[maxn];
//这里是边表，解释一下各数组的含义：p[i]表示以某一点出发的编号为i的边对应点，c表示编号为i的边的流量，cc表示编号为i的边的费用，nex和head不说了吧。。。
inline void init(int n) {
	N = n;
	ans = 0;
	nedge = -1;
	memset(head, -1, sizeof(head));
	memset(nex, -1, sizeof(nex));
}
const int inf = 0x3f3f3f3f;
inline void add(int x, int y, int cap, int cost) {
	p[++nedge] = y; 
	c[nedge] = cap; 
	cc[nedge] = cost; 
	nex[nedge] = head[x]; 
	head[x] = nedge;
}

inline void addedge(int x, int y, int cap, int cost) {
	add(x, y, cap, cost);
	add(y, x, 0, -cost);
}
//建边（数组模拟边表倒挂）
inline bool spfa(int s, int t) {
	memset(vis, 0, sizeof vis);
	for (int i = s; i <= t; i++) {
		dist[i] = inf; 
		dist[t] = 0; 
		vis[t] = 1;
	}
	//首先SPFA我们维护距离标号的时候要倒着跑，这样可以维护出到终点的最短路径
	deque<int>q; q.push_back(t);
	//使用了SPFA的SLF优化（SLF可以自行百度或Google）
	while (!q.empty()) {
		int now = q.front(); q.pop_front();
		for (int k = head[now]; k>-1; k = nex[k])if (c[k ^ 1] && dist[p[k]]>dist[now] - cc[k]) {
			//首先c[k^1]是为什么呢，因为我们要保证正流，但是SPFA是倒着跑的，所以说我们要求c[k]的对应反向边是正的，这样保证走的方向是正确的
			dist[p[k]] = dist[now] - cc[k];
			//因为已经是倒着的了，我们也可以很清楚明白地知道建边的时候反向边的边权是负的，所以减一下就对了（负负得正）
			if (!vis[p[k]]) {
				vis[p[k]] = 1;
				if (!q.empty() && dist[p[k]]<dist[q.front()])q.push_front(p[k]); else q.push_back(p[k]);
				//SLF优化
			}
		}
		vis[now] = 0;
	}
	return dist[s]<inf;
	//判断起点终点是否连通
}
inline int dfs(int x, int low) {
	//这里就是进行増广了
	if (x == t) { vis[t] = 1; return low; }
	int used = 0, a; vis[x] = 1;
	//这边是不是和dinic很像啊
	for (int k = head[x]; k>-1; k = nex[k])
		if (!vis[p[k]] && c[k] && dist[x] - cc[k] == dist[p[k]]) {
		//这个条件就表示这条边可以进行増广
		a = dfs(p[k], min(c[k], low - used));
		if (a) {
			ans += a*cc[k];
//			ans += cc[k];
			c[k] -= a;
			c[k ^ 1] += a;
			used += a;
		}
		//累加答案，加流等操作都在这了
		if (used == low)break;
	}
	return used;
}
inline int costflow() {
	int flow = 0;
	while (spfa(s, t)) {
		//判断起点终点是否连通，不连通说明满流，做完了退出
		vis[t] = 1;
		while (vis[t]) {
			memset(vis, 0, sizeof vis);
			flow += dfs(s, inf);
			//一直増广直到走不到为止（这样也可以省时间哦）
		}
	}
	return flow;//这里返回的是最大流，费用的答案在ans里
}

int main()
{
	int n;
	scanf("%d%d", &n, &m);
	ans=0;
	s=0,t=n+2; 
	init(n);
	int ai[n+2]; 
	ai[0]=0;ai[n+1]=0;
	for(int i=1;i<=n;i++){
		int tepp;
		scanf("%d",&tepp);
		ai[i]=tepp;
	}
	for(int i=1;i<=m;i++){
		int si,ti,ci;
		scanf("%d%d%d",&si,&ti,&ci);
		addedge(si,ti+1,inf,ci);
	}
	for(int i=1;i<=n;i++){
		addedge(i+1,i,inf,0);
	}
	for(int i=1;i<=n+1;i++){
		int c=ai[i]-ai[i-1];
		if(c>=0) addedge(s,i,c,0);
		else addedge(i,t,-c,0);
		
	}
	costflow();
	printf("%d\n",ans);
	return 0;
}
/*
5 6 1 3
1 2 5 3
2 3 4 3
1 4 5 2
4 5 6 3
5 3 6 1
4 3 5 1
*/
