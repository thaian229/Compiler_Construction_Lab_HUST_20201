#include<stdio.h>
#include<math.h>
main()
{int N,i,flag=0;
float A[10],t=0,tbc;
printf("\nNhap so phan tu cua day:");
scanf("%i",&N);
for(i=0;i<N;i++)
	{printf("A[%d]=",i+1);
	scanf("%f",&A[i]);
	t+=A[i];
	}
tbc=t/N;
printf("\n%6.2f",tbc);

for(i=0;i<N;i++)
if(A[i]==tbc){flag=1;break;}
printf("\n%d",flag);
}


