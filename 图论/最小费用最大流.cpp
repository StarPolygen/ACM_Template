#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
const int maxn = 1010; //ͬ����Ҫע����������ݹ�ͼ���������ͱ��� 
const int maxm = 30000;
bool vis[maxn]; int dist[maxn];
//����һ�¸�����ĺ��壺vis�����ô���spfa��ķ��ʱ�ǣ�����ʱ��ķ��ʱ�ǣ�dist��ÿ����ľ�����
int N, m, s, t, ans = 0;
//s����㣬t���յ㣬ans�Ƿ��ô�
int nedge = -1, p[maxm], c[maxm], cc[maxm], nex[maxm], head[maxn];
//�����Ǳ߱�����һ�¸�����ĺ��壺p[i]��ʾ��ĳһ������ı��Ϊi�ı߶�Ӧ�㣬c��ʾ���Ϊi�ıߵ�������cc��ʾ���Ϊi�ıߵķ��ã�nex��head��˵�˰ɡ�����
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
//���ߣ�����ģ��߱��ң�
inline bool spfa(int s, int t) {
	memset(vis, 0, sizeof vis);
	for (int i = s; i <= t; i++) {
		dist[i] = inf; 
		dist[t] = 0; 
		vis[t] = 1;
	}
	//����SPFA����ά�������ŵ�ʱ��Ҫ�����ܣ���������ά�������յ�����·��
	deque<int>q; q.push_back(t);
	//ʹ����SPFA��SLF�Ż���SLF�������аٶȻ�Google��
	while (!q.empty()) {
		int now = q.front(); q.pop_front();
		for (int k = head[now]; k>-1; k = nex[k])if (c[k ^ 1] && dist[p[k]]>dist[now] - cc[k]) {
			//����c[k^1]��Ϊʲô�أ���Ϊ����Ҫ��֤����������SPFA�ǵ����ܵģ�����˵����Ҫ��c[k]�Ķ�Ӧ����������ģ�������֤�ߵķ�������ȷ��
			dist[p[k]] = dist[now] - cc[k];
			//��Ϊ�Ѿ��ǵ��ŵ��ˣ�����Ҳ���Ժ�������׵�֪�����ߵ�ʱ����ߵı�Ȩ�Ǹ��ģ����Լ�һ�¾Ͷ��ˣ�����������
			if (!vis[p[k]]) {
				vis[p[k]] = 1;
				if (!q.empty() && dist[p[k]]<dist[q.front()])q.push_front(p[k]); else q.push_back(p[k]);
				//SLF�Ż�
			}
		}
		vis[now] = 0;
	}
	return dist[s]<inf;
	//�ж�����յ��Ƿ���ͨ
}
inline int dfs(int x, int low) {
	//������ǽ��Љ�����
	if (x == t) { vis[t] = 1; return low; }
	int used = 0, a; vis[x] = 1;
	//����ǲ��Ǻ�dinic����
	for (int k = head[x]; k>-1; k = nex[k])
		if (!vis[p[k]] && c[k] && dist[x] - cc[k] == dist[p[k]]) {
		//��������ͱ�ʾ�����߿��Խ��Љ���
		a = dfs(p[k], min(c[k], low - used));
		if (a) {
			ans += a*cc[k];
//			ans += cc[k];
			c[k] -= a;
			c[k ^ 1] += a;
			used += a;
		}
		//�ۼӴ𰸣������Ȳ�����������
		if (used == low)break;
	}
	return used;
}
inline int costflow() {
	int flow = 0;
	while (spfa(s, t)) {
		//�ж�����յ��Ƿ���ͨ������ͨ˵���������������˳�
		vis[t] = 1;
		while (vis[t]) {
			memset(vis, 0, sizeof vis);
			flow += dfs(s, inf);
			//һֱ����ֱ���߲���Ϊֹ������Ҳ����ʡʱ��Ŷ��
		}
	}
	return flow;//���ﷵ�ص�������������õĴ���ans��
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
