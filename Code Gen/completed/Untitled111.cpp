#include<stdio.h>
main()
{
int N,i,f=-1;
int A[10];
scanf("%d",&N);
for(i=0;i<N;i++)
	scanf("%d",&A[i]);
for(i=N-1;i>=0;i--)
	if(A[i]>0 && A[i]%5==0) 
		{f=1;break;}
if (f==1) 
	printf("%d",i);
else printf("%d",f);
}


