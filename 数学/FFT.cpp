//FFT 
#include <bits/stdc++.h>
#define ll long long
#define maxn 100010
#include <complex>
//复数定义
struct Complex{
    double x, y;
    inline Complex operator+(const Complex b) const {
        return (Complex){x +b.x,y + b.y};
    }
    inline Complex operator-(const Complex b) const {
        return (Complex){x -b.x,y - b.y};
    }
    inline Complex operator*(const Complex b) const {
        return (Complex){x *b.x -y * b.y,x * b.y + y * b.x};
    }
} 

//n需补成 2 的幂 （n必须超过 a 和 b 的最高指数之和）
//卷积系数储存在a[i].real()中,作为整数使用时需要（ll）(a[i].real()+0.5) 
using namespace std;
typedef complex<double> cd;
//！！nlogn的最大长度，需要根据题意计算和修改	
const int maxl = 3600180;					
const double PI = acos(-1.0);
cd a[maxl],b[maxl];							//用于储存变换的中间结果
int rev[maxl];								//用于储存二进制反转的结果
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){			//高位决定二进制数的大小
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }										//能保证(x>>1)<x,满足递推性质
}
void fft(cd* a,int n,int dft){				//变换主要过程
    for(int i=0;i<n;i++){					//按照二进制反转
        if(i<rev[i])						//保证只把前面的数和后面的数交换,(否则数组会被翻回来)
            swap(a[i],a[rev[i]]);
    }
    for(int step=1;step<n;step<<=1){		//枚举步长的一半
        cd wn=exp(cd(0,dft*PI/step));		//计算单位复根
        for(int j=0;j<n;j+=step<<1){		//对于每一块
            cd wnk(1,0);					//!!每一块都是一个独立序列,都是以零次方位为起始的
            for(int k=j;k<j+step;k++){		//蝴蝶操作处理这一块
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;					//计算下一次的复根
            }
        }
    }
    if(dft==-1){							//如果是反变换,则要将序列除以n
        for(int i=0;i<n;i++)
            a[i]/=n;
    }
}
void ini(){
	memset(a,0,sizeof(a));
	memset(b,0,sizeof(b));
	memset(rev,0,sizeof(rev));
}
void getConv(int * arr1, ll len1, int * arr2, ll len2){  
	ini();
	int bit=1, s=2;
	for(bit=1;(1<<bit)<len1+len2-1;bit++){ 
        s<<=1;						
    }
	for(int i=0;i<len1;i++){			
        a[i]=(double)(arr1[i]); 
    }
    for(int i=0;i<len2;i++){
    	b[i]=(double)(arr2[i]);
	}
	getrev(bit); fft(a,s,1); fft(b,s,1);
    for(int i=0;i<s;i++) a[i]*=b[i];	
    fft(a,s,-1);					    
}




//以下是FFT实现高精度乘法(仅限正数)的代码，只需要将得到的系数按照十进制输出即可
int output[maxl];
char s1[maxl],s2[maxl];
int  c1[maxl],c2[maxl];
int main(){
    scanf("%s%s",s1,s2);			//读入两个数
    int l1=strlen(s1),l2=strlen(s2);//算"次数界"
    for(int i=0;i<l1;i++){			//第一个数装入a
        c1[i]=(int)(s1[l1-i-1]-'0');
    }
    for(int i=0;i<l2;i++){			//第二个数装入b
        c2[i]=(int)(s2[l2-i-1]-'0');
    }
    getConv(c1,l1,c2,l2);
      
	//若想改变进制，只要把10变成相应进制即可 
    for(int i=0;i<=l1+l2-2;i++){//还原成十进制数
        output[i]+=(int)(a[i].real()+0.5);//注意精度误差
        output[i+1]+=output[i]/10;
        output[i]%=10;
    }
    
    int i;  
    for(i=l1+l2;!output[i]&&i>=0;i--);//去掉前导零
    if(i==-1)printf("0");//特判长度为0的情况
    for(;i>=0;i--){//输出这个十进制数
        printf("%d",output[i]);
    }
    putchar('\n');
    return 0;
}


