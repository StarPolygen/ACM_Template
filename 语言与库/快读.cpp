//�����д 
//���ڶ�д�� ���ݸ��� 

//��� 
template<typename T>inline void read(T &x)
{
    x=0;
    static int p;p=1;
    static char c;c=getchar();
    while(!isdigit(c)){if(c=='-')p=-1;c=getchar();}
    while(isdigit(c)) {x=(x<<1)+(x<<3)+(c-48);c=getchar();}
    x*=p;
}

//��д  
inline void write(int x)
{
     if(x < 0) putchar('-'),x = -x;
     if(x > 9) write(x / 10);
     putchar(x % 10 + '0');
}
