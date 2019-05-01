#define g 3//模数的原根
#define mod 998244353//通常情况下的模数

int pow(int x,int y)//快速幂
{
	ll z=1ll*x,ans=1ll;
	for (;y;y/=2,z=z*z%mod)if (y&1)ans=ans*z%mod;//注意精度
	return (int)ans%mod;
}

void ntt(int a[],int inv)
{
	int bit=0;
	while ((1<<bit)<n)bit++;
	fo(i,0,n-1)
	{
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		if (i<rev[i])swap(a[i],a[rev[i]]);
	}//前面的东西和FFT一样
	for (int mid=1;mid<n;mid*=2)
	{
		int temp=pow(g,(mod-1)/(mid*2));//用原根代替单位根
		if (inv==-1)temp=pow(temp,mod-2);//逆变换则乘上逆元
		for (int i=0;i<n;i+=mid*2)
		{
			int omega=1;
			for (int j=0;j<mid;j++,omega=1ll*omega*temp%mod)
			{
				int x=a[i+j],y=1ll*omega*a[i+j+mid]%mod;
				a[i+j]=x+y,a[i+j+mid]=x-y;
				a[i+j]=(a[i+j]%mod+mod)%mod,a[i+j+mid]=(a[i+j+mid]%mod+mod)%mod;//注意取模
			}
		}//大体流程和FFT差不多
	}
}

