//数位DP模板

——————————————————————————————————————————————————————————————————————————————————————————————————————————————————————————
//更加模式化的版本
typedef long long ll;
int a[20];
ll dp[20][state];//不同题目状态不同
ll dfs(int pos,/*state变量*/,bool lead/*前导零*/,bool limit/*数位上界变量*/)//不是每个题都要判断前导零
{
    //递归边界，既然是按位枚举，最低位是0，那么pos==-1说明这个数我枚举完了
    if(pos==-1) return 1;/*这里一般返回1，表示你枚举的这个数是合法的，那么这里就需要你在枚举时必须每一位都要满足题目条件，也就是说当前枚举到pos位，一定要保证前面已经枚举的数位是合法的。不过具体题目不同或者写法不同的话不一定要返回1 */
    //第二个就是记忆化(在此前可能不同题目还能有一些剪枝)
    if(!limit && !lead && dp[pos][state]!=-1) return dp[pos][state];
    /*常规写法都是在没有限制的条件记忆化，这里与下面记录状态是对应，具体为什么是有条件的记忆化后面会讲*/
    int up=limit?a[pos]:9;//根据limit判断枚举的上界up;这个的例子前面用213讲过了
    ll ans=0;
    //开始计数
    for(int i=0;i<=up;i++)//枚举，然后把不同情况的个数加到ans就可以了
    {
        if() ...
        else if()...
        ans+=dfs(pos-1,/*状态转移*/,lead && i==0,limit && i==a[pos]) //最后两个变量传参都是这样写的
        /*这里还算比较灵活，不过做几个题就觉得这里也是套路了
        大概就是说，我当前数位枚举的数是i，然后根据题目的约束条件分类讨论
        去计算不同情况下的个数，还有要根据state变量来保证i的合法性，比如题目
        要求数位上不能有62连续出现,那么就是state就是要保存前一位pre,然后分类，
        前一位如果是6那么这意味就不能是2，这里一定要保存枚举的这个数是合法*/
    }
    //计算完，记录状态
    if(!limit && !lead) dp[pos][state]=ans;
    /*这里对应上面的记忆化，在一定条件下时记录，保证一致性，当然如果约束条件不需要考虑lead，这里就是lead就完全不用考虑了*/
    return ans;
}
ll solve(ll x)
{
    int pos=0;
    while(x)//把数位都分解出来
    {
        a[pos++]=x%10;//个人老是喜欢编号为[0,pos),看不惯的就按自己习惯来，反正注意数位边界就行
        x/=10;
    }
    return dfs(pos-1/*从最高位开始枚举*/,/*一系列状态 */,true,true);//刚开始最高位都是有限制并且有前导零的，显然比最高位还要高的一位视为0嘛
}
int main()
{
    ll le,ri;
    while(~scanf("%lld%lld",&le,&ri))
    {
        //初始化dp数组为-1,这里还有更加优美的优化,后面讲
        memset(dp,-1,sizeof dp);
        printf("%lld\n",solve(ri)-solve(le-1));
    }
}
_________________________________________________________________________________________________________________________



//典型的数位DP题目

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;

int arr[20];//上界数的数位拆分结果
struct Point{
	ll num,sum;
	Point(){num = -1;sum = 0;};
	Point(ll num, ll sum):num(num),sum(sum){}
}dp[20][1025];  //dp[len][x]: 当前有len位数字还不确定，在此之前0~9每个数字出现的状态为x
ll pdd[20];

ll a,b,k;
 
Point dfs(int pos,int state,bool lead,bool limit)
{
    //个位数时  满足条件的个数仅为一,而贡献已被统计过
    if(pos<=-1) return lead?Point(0,0):Point(1,0); 
    //记忆化：统计过且未达上界 直接返回
	if(!lead && !limit &&dp[pos][state].num!=-1) return dp[pos][state];
	
    //limit需要单独计算  或之前未统计过需要重新计算
	int up = limit?arr[pos]:9;
	Point ans(0,0); //初始化ans
	for(int i=0;i<=up;i++){//套路：上界约束

		Point next(0,0);
		if(!((state>>i)&1) && !( lead && i==0)){        //状态转移
			int n_state = state|1<<i;
			if(__builtin_popcountll(n_state)>k) continue;//剪枝：跳过错误状态
			next = dfs(pos-1,n_state, lead && i==0,i==up && limit);
		}else{
			next = dfs(pos-1,state, lead && i==0,i==up && limit);
        }
		ans.num = (ans.num+next.num)%mod;               //统计贡献：符合条件的个数增加
		ans.sum = (ans.sum+next.sum+pdd[pos]*i%mod*next.num%mod)%mod;//当前数位的贡献增加

	}

    //记录
	if(!lead && !limit) dp[pos][state] = ans;           //如果这一位 不含上界或前导 则作为完整的数 可以记录下来  
	return ans;
}
 
ll solve(ll x){
	int i=0;
	while(x>0){
		arr[i++] = x%10;
		x/=10;
	}
	Point ans = dfs(i-1,0,true,true);
	return ans.sum;
}
 
void init(){
	memset(pdd,0,sizeof(pdd));
    memset(dp,0,sizeof(dp));
}

int main(){
	pdd[0]=1;
	for(int i=1;i<20;++i) pdd[i]=pdd[i-1]*10%mod;
	scanf("%lld%lld%lld",&a,&b,&k);
    printf("%lld\n",(solve(b)-solve(a-1)+mod)%mod);
	return 0;	
}


______________________________________________________________________________________________________________________________



//非常简单的数位DP题目

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int arr[20]; 
ll dp[20][4];
ll dfs(int pos,int pre,int sta,bool limit)//底下这个是求没有38和49子序列的个数的 
{
	//个位数时  满足条件的个数仅为一
    if(pos==-1) return 1;					 
    //记忆化：统计过且未达上界 直接返回
    if(!limit && dp[pos][sta]!=-1) return dp[pos][sta];
    
    //limit需要单独计算  或之前未统计过需要重新计算
    int up=limit ? a[pos] : 9;	//套路：上界约束
    ll tmp=0;	//初始化ans
    for(int i=0;i<=up;i++)
    {	
        if(sta==1 && i==9)continue;						//剪枝：跳过错误状态			 
        if(sta==2 && i==8)continue;
        if(sta==3 &&(i==8||i==9)) continue;
        if(i==4&&sta==0){								//状态转移和贡献统计
        	tmp+=dfs(pos-1,i,1,limit && i==a[pos]);
		}else if(i==3&&sta==0){
			tmp+=dfs(pos-1,i,2,limit && i==a[pos]);
		}else if((i==3&&sta==1)||(i==4&&sta==2)){
			tmp+=dfs(pos-1,i,3,limit && i==a[pos]);
		}
		else{
			tmp+=dfs(pos-1,i,sta,limit && i==a[pos]);
		}
       
    }
    
    //记录
    if(!limit) dp[pos][sta]=tmp;						//如果这一位 不含上界或前导 则作为完整的数 可以记录下来
    return tmp;
}
ll solve(ll x)
{
    ll pos=0;
    while(x)
    {
        arr[pos++]=x%10;
        x/=10;
    }
    return dfs(pos-1,-1,0,true);
}
int main()
{
    int T;long long ri;
    scanf("%d",&T); 
    //memset(dp,-1,sizeof dp);可优化
    while(T--)
    {
    	scanf("%lld",&ri);
        memset(dp,-1,sizeof dp);
        printf("%lld\n",(ri-solve(ri)+1));
    }
    return 0;
}