void kmp_next(char *T,int *nt)
{
    nt[0]=0;
	for(int i=1,j=0,m=strlen(T);i<m;i++)
    {
        while(j&&T[i]!=T[j])j=nt[j-1];
		if(T[i]==T[j])j++;
		nt[i]=j;
    }
}
					   
int kmp(char *S,char *T,int *nt){
	kmp_next(T,nt);
	int ans=0,sn=strlen(S),tn=strlen(T);
	for(int i=0,j=0;i<sn;i++){
		while(j&&S[i]!=T[j])  j=nt[j-1];
		if(S[i]==T[j])j++;
		if(j==tn) ans++; 
	}
    return ans;
}
