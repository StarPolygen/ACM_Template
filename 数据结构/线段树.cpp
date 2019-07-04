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
    const int maxn=1e5+10;
    int a[maxn];
    int sum[maxn<<2],lazy[maxn<<2];
    void maintain(int k)
    {
        sum[k]=sum[k<<1]+sum[k<<1|1];
    }
    void pushdown(int lenl,int lenr,int k)//标记下放，并更细节点信息
    {
        if(lazy[k]){
            lazy[k<<1]=lazy[k];
            lazy[k<<1|1]=lazy[k];
            sum[k<<1]=lazy[k]*lenl;
            sum[k<<1|1]=lazy[k]*lenr;
            lazy[k]=0;
        }
    }
    void build(int l,int r,int k)
    {
        if(l>r)
            return ;
        if(l==r){
            sum[k]=a[l];
            lazy[k]=0;
            return ;
        }
        int mid=(l+r)>>1;
        build(l,mid,k<<1);
        build(mid+1,r,k<<1|1);
        maintain(k);
    }
    
    //区间修改
    void change(int l,int r,int cl,int cr,int k,int newp)
    {
        if(l>r||cl>r||cr<l)
            return ;
        if(l>=cl&&r<=cr){
            sum[k]=newp*(r-l+1);//在发现现在区域小于需要更新区域时
            lazy[k]=newp;//更新节点的结果，并增加延迟标记lazy，用于之后的标记下放
            return ;
        }
        int mid=(l+r)>>1;
        pushdown(mid-l+1,r-mid,k);
        change(l,mid,cl,cr,k<<1,newp);
        change(mid+1,r,cl,cr,k<<1|1,newp);
        maintain(k);
    }

    //区间查询2：针对区间修改
    int query(int l,int r,int ql,int qr,int k)
    {
        if(l>r||ql>r||qr<l)
            return 0;
        if(l>=ql&&r<=qr)
            return sum[k];
        int mid=(l+r)>>1,ans=0;
        pushdown(mid-l+1,r-mid,k);//每一层询问执行到这一步，为了下一次递归更新叶节点信息
        if(mid>=l)
            ans+=query(l,mid,ql,qr,k<<1);
        if(mid<r)
            ans+=query(mid+1,r,ql,qr,k<<1|1);
        return ans;
    }