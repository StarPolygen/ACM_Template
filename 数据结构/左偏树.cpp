//��ƫ��ģ��
using namespace std;
const int N=1000000;
void swap(int &x,int &y){int t=x;x=y,y=t;}
//ch�������ӽڵ���   val���ڵ�Ȩֵ  dis���ڵ����  f���ڵ㸸��
int ch[N][2],val[N],dis[N],f[N];  
int n,m;

//�ϲ�x��yΪ���Ķѣ������¶ѵĸ�
int merge(int x,int y) 
{
    if (x==0 || y==0)
        return x+y;
    if (val[x]<val[y] || (val[x]==val[y] && x>y))
        swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    f[ch[x][1]]=x;
    if (dis[ch[x][0]]<dis[ch[x][1]])
        swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;
}

//���x���ڶѵĶѶ�
int getf(int x) {  
    while(f[x]) x=f[x];
    return x;
}

//ɾ���Ѷ�
int pop(int x) {  //ɾ��xΪ���ѵĶѶ���ά��ʣ��㱣�ֶѵ�����
	val[x]=-1;  
	f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(lc,rc);    //�����ӶѺ����ӶѺϲ�
}

//����ĳ�ڵ�Ȩֵ
int change(int x,int now)  
{
    val[x]=now;   //���ڵ�x��ֵ��Ϊnow
    f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(x,merge(lc,rc));  //�ϲ��������ٽ��µ�
}

#include <cstdio>
//��ƫ��ģ��
using namespace std;
const int N=1000000;
void swap(int &x,int &y){int t=x;x=y,y=t;}
//ch�������ӽڵ���   val���ڵ�Ȩֵ  dis���ڵ����  f���ڵ㸸��
int ch[N][2],val[N],dis[N],f[N];  
int n,m;

//�ϲ�x��yΪ���Ķѣ������¶ѵĸ�
int merge(int x,int y) 
{
    if (x==0 || y==0)
        return x+y;
    if (val[x]<val[y] || (val[x]==val[y] && x>y))
        swap(x,y);
    ch[x][1]=merge(ch[x][1],y);
    f[ch[x][1]]=x;
    if (dis[ch[x][0]]<dis[ch[x][1]])
        swap(ch[x][0],ch[x][1]);
    dis[x]=dis[ch[x][1]]+1;
    return x;
}

//���x���ڶѵĶѶ�
int getf(int x) {  
    while(f[x]) x=f[x];
    return x;
}

//ɾ���Ѷ�
int pop(int x) {  //ɾ��xΪ���ѵĶѶ���ά��ʣ��㱣�ֶѵ�����
	val[x]=-1;  
	f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(lc,rc);    //�����ӶѺ����ӶѺϲ�
}

//����ĳ�ڵ�Ȩֵ
int change(int x,int now)  
{
    val[x]=now;   //���ڵ�x��ֵ��Ϊnow
    f[ch[x][0]]=0;
	f[ch[x][1]]=0;
    int lc = ch[x][0];
    int rc = ch[x][1];
    ch[x][0]=0;
	ch[x][1]=0;
    dis[x]=0;
    return merge(x,merge(lc,rc));  //�ϲ��������ٽ��µ�
}

void init(){
    for(int i=1;i<=n;i++){
			ch[i][0]=ch[i][1]=0;
			f[i]=0;
			dis[i]=0;
	}
    memset(val,0,sizeof(val));
}
