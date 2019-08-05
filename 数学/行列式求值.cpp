//行列式求值
#include <bits/stdc++.h>
#define ll long long
#define maxn 205
#define inf 0x3f3f3f3f
using namespace std;

ll B[maxn][maxn];
ll n, mod;

//无须取模的话删掉mod相关操作即可
inline ll det(long long n, long long mod) {    //高斯消元实现 复杂度O(n^3)
    ll ans = 1; 	
	for (int i=0;i<n;i++){  //当前行
		for (int j=i+1;j<n;j++){ //当前之后的每一行，因为每一行的当前第一个数要转化成0（想想线性代数中行列式的计算）
			while (B[j][i]){    //利用gcd的方法，不停地进行辗转相除以实现化简为0
				ll t = B[i][i] / B[j][i];
				for (int k=i;k<n;k++){
					B[i][k] = (B[i][k] - B[j][k] * t % mod + mod) % mod;
					swap(B[i][k], B[j][k]);
				}
				ans = -ans;  //每次交换，行列式D=-D'
			}
		}
		if (B[i][i] == 0) return 0;  //斜对角中有一个0，则结果为0
		ans = (ans * B[i][i]) % mod; //行列式是消元结果中所有主对角线元素相乘
	}
	return (ans + mod) % mod;  //C++中负数取模仍为负数，为保证正数结果，还需加模取模
}


int main()
{
  while(~scanf("%lld%lld",&n,&mod)){
    for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				scanf("%lld",&B[i][j]);
				B[i][j] %= mod;
			}
		}
    ll ans = det(n, mod);
    printf("%lld\n", ans);
  }
  return 0;
}
