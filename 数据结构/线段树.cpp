//线段树
//最重要的是确定要存储什么值 可以完成题目所需要求
//注意修改时对之前改变值的更新


//单点修改 HDU1754
    const int maxn=200010;
    int n,m;
    //存储读入数据
    int st[maxn];

    //节点,其中1为根节点
    struct node{
        int l,r;
        int ms;
    }a[maxn<<2];

    //线段树三部曲：建树,修改,查询
    //建树
    void init(int l,int r,int i){//初始化线段树节点,将未被修改之前的状态计算好保存在各个节点内   
        a[i].l=l;
        a[i].r=r;
        if(l==r) {
            a[i].ms=st[l];//叶子
            return;
        }
        //设置子节点
        int mid=(l+r)>>1;
        init(l,mid,2*i);
        init(mid+1,r,2*i+1);
        //由子节点计算当前节点
        a[i].ms=max(a[2*i].ms,a[2*i+1].ms);
    }

    //单点修改
    void change(int i,int t,int x){//i:节点编号  t:被单点修改的数据下标  x：更新值
        if(a[i].l==a[i].r){//叶子
            a[i].ms=x;
            return;
        }//查询子节点直至访问到所需区间并更新
        int mid=(a[i].l+a[i].r)>>1;
        if(t<=mid) change(2*i,t,x);
        else change(2*i+1,t,x);

        //更新当前节点
        a[i].ms=max(a[2*i].ms,a[2*i+1].ms);
    }

    //单点查询
    int query(int i,int t){//i:节点编号 t:被查询的数据下标
        if(a[i].r==a[i].l) 
            return a[i].ms;
        int mid=(a[i].l+a[i].r)>>1;
        if(t<=mid) return query(2*i,t);
        else return query(2*i+1,t);
    }

    //区间查询1：针对单点修改
    int Max=0;
    void query(int i,int l,int r){
        //若[L,R]和当前节点代表区间不相交,停止继续搜素
        if(r<a[i].l||l>a[i].r) return;
        //若[L,R]完全包含当前节点代表区间,用当前节点信息更新查询结果
        if(a[i].l>=l&&a[i].r<=r) {
            Max=max(Max,a[i].ms);
            return;
        }
        //否则,递归处理当前节点左右两个子节点
        query(2*i,l,r);
        query(2*i+1,l,r);
    }







//区间修改  
    #define maxn 100010
    using namespace std;

    struct node{
        int l,r;
        ll val;
    }tree[maxn<<2];
    ll lazy[maxn<<2];
    
    //建树
    void init(int l,int r,int pos){
        tree[pos].l=l; 
        tree[pos].r=r;
        lazy[pos]=0;
        //初始化叶子节点值
        if(l==r){
            tree[pos].val=1;  //根据题目不同，赋予不同的初始值
            return;
        }
        int mid=(l+r)>>1;
        init(l,mid,pos<<1);
        init(mid+1,r,pos<<1|1);
        //由子节点推得当前节点
        tree[pos].val=tree[pos<<1].val+tree[pos<<1|1].val;
    }
    void pushdown(int pos){ //下放lazy标记,并将当前子节点的值更新
        if(lazy[pos]){
            lazy[pos<<1]=lazy[pos];
            lazy[pos<<1|1]=lazy[pos];
            //将当前节点子节点的值变为可信
            tree[pos<<1].val=lazy[pos]*(tree[pos<<1].r-tree[pos<<1].l+1);
            tree[pos<<1|1].val=lazy[pos]*(tree[pos<<1|1].r-tree[pos<<1|1].l+1);
            lazy[pos]=0;
        }
    }
    void pushup(int pos){ //向上更新节点
        tree[pos].val=tree[pos<<1].val+tree[pos<<1|1].val;
    }

    //区间修改
    void update(int l,int r,int from,int to,int pos,int k) 
    {
        if(from<=l&&r<=to){
            //若该节点在范围内，更新该节点的各项指标
            tree[pos].val=k*(r-l+1);
            lazy[pos]=k;
            return;
        }
        pushdown(pos);
        int mid=(l+r)>>1;
        if(from<=mid) update(l,mid,from,to,pos<<1,k);
        if(mid<to) update(mid+1,r,from,to,pos<<1|1,k);
        pushup(pos);
    }

    //区间查询2：针对区间修改
    ll query(int l,int r,int from,int to,int pos)
    {
        if(from<=l&&r<=to) return tree[pos].val;
        pushdown(pos);
        int mid=(l+r)>>1;
        ll res=0;
        if(from<=mid) res+=query(l,mid,from,to,pos<<1);
        if(mid<to) res+=query(mid+1,r,from,to,pos<<1|1);
        pushup(pos);
        return res;
    }