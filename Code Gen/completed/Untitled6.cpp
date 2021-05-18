#include<stdio.h>
#include<math.h>
main()
{
	float x, y,z, F;
	scanf("%f",&x);
	scanf("%f",&y);
	scanf("%f",&z);
	F = x*x + fabs(cos(y*z));
	printf ("\n%.2f",F);
}
