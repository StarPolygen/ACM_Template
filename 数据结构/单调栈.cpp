

//单调栈的作用：
//扫一遍就能得到所有a[i]前后比a[i]小的最近者及a[i]前后比a[i]小的最远者
        
int L[maxn],R[maxn],a[maxn];   

stack<int> S;
for(int i=1;i<=n;i++){
    while(!S.empty() && a[S.top()]<a[i])
        L[i]=S.top(),S.pop();               //L[i]为在a[i]之前且比a[i]小的最远者
        S.push(i);
    }
for(int i=n;i>=1;i--){
    while(!S.empty() && a[S.top()]<a[i])   //R[i]为在a[i]之后且比a[i]小的最远者
        R[i]=S.top(),S.pop();
        S.push(i);
}