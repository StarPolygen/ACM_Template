# 1
const int maxn=50010; //maxn代表总区间中的点数 
int D[maxn];
int lowbit(int x){return x&(-x);}
void add(int x,int k,int n){
	while(x<=n){
		D[x]+=k;
		x+=lowbit(x); 
	}
}
int querypf(int x){
	int sum=0;
	while(x>0){
		sum+=D[x];
		x-=lowbit(x);
	}
	return sum;
}
int query(int L,int R){
	return querypf(R)-querypf(L-1);
}

# 2
const int maxn=100010; //maxn代表总区间中的点数 
LL lowbit(LL x){return x&(-x);}
void add(LL* arr,int x,int k,int n){
	while(x<=n){
		arr[x]+=k;
		x+=lowbit(x); 
	}
}
LL query(LL* arr,int x){
	LL sum=0;
	while(x>0){
		sum+=arr[x];
		x-=lowbit(x);
	}
	return sum;
}
LL C[maxn],jmC[maxn];
void addRange(int L,int R,int k,int n){
	add(C,L,k,n);
	add(C,R+1,-k,n);
	add(jmC,L,1LL*k*L,n);
	add(jmC,R+1,1LL*-k*(R+1),n);
}
LL queryRange(int L,int R){
	L--;
	LL sumL=(L+1)*query(C,L)-query(jmC,L);
	LL sumR=(R+1)*query(C,R)-query(jmC,R);
	return sumR-sumL;
}

