
//n �貹�� 2 ���� ��n ���볬�� a �� b �����ָ��֮�ͣ�

#include <bits/stdc++.h> 
#include <complex>
using namespace std;

typedef complex<double> cd;			//������Ķ���
const int maxl = 2094153; 			//nlogn����󳤶ȣ���Ҫ�޸� ||||||||| 
const double PI = 3.14159265358979;	//Բ����,������

cd a[maxl],b[maxl];					//���ڴ���任���м���
int rev[maxl];						//���ڴ�������Ʒ�ת�Ľ��
void getrev(int bit){
    for(int i=0;i<(1<<bit);i++){	//��λ�������������Ĵ�С
        rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
    }								//�ܱ�֤(x>>1)<x,�����������
}

void fft(cd* a,int n,int dft){		//�任��Ҫ����
    for(int i=0;i<n;i++){			//���ն����Ʒ�ת
        if(i<rev[i])				//��ֻ֤��ǰ������ͺ����������,(��������ᱻ������)
            swap(a[i],a[rev[i]]);
    }
    for(int step=1;step<n;step<<=1){//ö�ٲ�����һ��
        cd wn=exp(cd(0,dft*PI/step));//���㵥λ����
        for(int j=0;j<n;j+=step<<1){//����ÿһ��
            cd wnk(1,0);			//!!ÿһ�鶼��һ����������,��������η�λΪ��ʼ��
            for(int k=j;k<j+step;k++){//��������������һ��
                cd x=a[k];
                cd y=wnk*a[k+step];
                a[k]=x+y;
                a[k+step]=x-y;
                wnk*=wn;			//������һ�εĸ���
            }
        }
    }
    if(dft==-1){					//����Ƿ��任,��Ҫ�����г���n
        for(int i=0;i<n;i++)
            a[i]/=n;
    }
}

int output[maxl];
char s1[maxl],s2[maxl];
int main(){
    scanf("%s%s",s1,s2);			//����������
    int l1=strlen(s1),l2=strlen(s2);//��"������"
    int bit=1,s=2;					//s��ʾ�ָ�֮ǰ����ĳ���
    for(bit=1;(1<<bit)<l1+l2-1;bit++){
        s<<=1;						//�ҵ���һ��������������ʹ��������������������ĳ˻�
    }
    for(int i=0;i<l1;i++){			//��һ����װ��a
        a[i]=(double)(s1[l1-i-1]-'0');
    }
    for(int i=0;i<l2;i++){			//�ڶ�����װ��b
        b[i]=(double)(s2[l2-i-1]-'0');
    }
    getrev(bit);fft(a,s,1);fft(b,s,1);//DFT
    for(int i=0;i<s;i++)a[i]*=b[i];	//��Ӧ���
    fft(a,s,-1);					//IDFT
    
    
    
    //�õ��ľ�����  �����ϵ��������a[i].real()��; 
//  for(int i=0;i<s;i++){
//    	printf("%f\n",a[i].real());
//	}
    
    
    //������FFTʵ�ָ߾��ȳ˷�(��������)�Ĵ��룬ֻ��Ҫ���õ���ϵ������ʮ�����������  
	//����ı���ƣ�ֻҪ��10�����Ӧ���Ƽ��� 
    for(int i=0;i<s;i++){//��ԭ��ʮ������
        output[i]+=(int)(a[i].real()+0.5);//ע�⾫�����
        output[i+1]+=output[i]/2;
        output[i]%=2;
    }
    
    int i;  
    for(i=l1+l2;!output[i]&&i>=0;i--);//ȥ��ǰ����
    if(i==-1)printf("0");//���г���Ϊ0�����
    for(;i>=0;i--){//������ʮ������
        printf("%d",output[i]);
    }
    putchar('\n');
    return 0;
}


