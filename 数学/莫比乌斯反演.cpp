//洛谷P2257 YY的GCD

//莫比乌斯反演
//F(n)和f(n)是定义在非负整数集合上的两个函数
//并且满足条件F(n) = sum(f(d)) (d|n)
//那么f(n) = sum(u(d)*F(n/d)) (d|n)
//case 1: if d = 1, u(d) = 1
//case 2: if d = p1*p2...pk, (pi均为互异素数), u(d) = (-1)^k
//case 3: else, u(d) = 0;
//性质1: sum(u(d)) (d|n) = 1 (n == 1) or 0 (n > 1)
//性质2: sum(u(d)/d) (d|n) = phi(n)/n
//另一种形式:F(d) = sum(f(n)) (d|n) => f(d) = sum(u(n/d)*F(n)) (d|n)


//线性筛选求莫比乌斯反演函数代码
#include <bits/stdc++.h>
#define ll long long
#define maxn 10000010
using namespace std;

int T, N, M;

//求莫比乌斯函数
const ll p_max = 1E7 + 100;
ll mu[p_max];
static ll prime[p_max], p_sz, d;
void get_mu()
{
	mu[1] = 1;
	static bool vis[p_max];
	mu[1] = 1;
	for (int i = 2; i < p_max; i++)	{
		if (!vis[i])
		{
			prime[p_sz++] = i;
			mu[i] = -1;
		}
		for (ll j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j)		{
			vis[d] = 1;
			if (i % prime[j] == 0)			{
				mu[d] = 0;
				break;
			}
			else
				mu[d] = -mu[i];
		}
	}
}


//预处理 这部分因题而异不属于模板
ll mutp[maxn];
ll prefix[maxn];
void pre()
{
	memset(prefix, 0, sizeof(prefix));
	for (int i = 0; i < p_sz; i++)
	{
		int j = 1;
		while (prime[i] * j < maxn)
		{
			mutp[prime[i] * j] += mu[j];
			j++;
		}
	}
	for (int i = 1; i < maxn; i++)
	{
		prefix[i] = prefix[i - 1] + mutp[i];
	}
}



int main()
{

	scanf("%d", &T);
	get_mu();
	pre();
	while (T--)
	{
		scanf("%d%d", &N, &M);
		if (N > M)	swap(N, M);
		ll ans = 0;
		int r;
        //整除分块
		for (int l = 1; l <= N; l = r + 1)
		{
			r = min(N / (N / l),M/(M/l));
			ans += (ll)(prefix[r] - prefix[l - 1]) * (N / l) * (M / l);
		}
		printf("%lld\n", ans);
	}
	return 0;
}