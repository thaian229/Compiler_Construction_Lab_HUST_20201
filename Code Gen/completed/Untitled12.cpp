#include<stdio.h>
#include<string.h>
#include<ctype.h>
main()
{   char s[100][50], t[50];
   int n,i,j, c, d;
   printf("Nhap so luong ho ten\n");
   scanf("%d",&n);
   for(i=0;i<n;i++)
   {
      printf("\nNhap ho ten thu %d:",i+1);
      fflush(stdin);
	  gets(s[i]);
	  c=0;d=0;
	  while (s[i][c]==' ')c++;
   	  while (s[i][c] != '\0')
   		{  
      	if (!(s[i][c] == ' ' && s[i][c+1] == ' ')) {
        t[d] = s[i][c]; 
        d++;
      }
      c++;
   }
    if(t[d-1]==' ')t[d-1]='\0';else t[d] = '\0';
	strcpy(s[i],t);
	}	
	for (i=0;i<n;i++)
	{c=0;
	while (s[i][c] != '\0')
	{if(s[i][c]==' 'and s[i][c+1]!=' ')
		s[i][c+1]=toupper(s[i][c+1]);
	else
		s[i][c+1]=tolower(s[i][c+1]);
	c++;}
	s[i][0]=toupper(s[i][0]);
	
}
   printf("\nDanh sach ten sau khi chuan hoa\n");
 	for(i=0;i<n;i++) {
	puts(s[i]); }

for(i=0;i<n;i++)
  for(j=i+1;j<n;j++)
  if(strcmp(s[i],s[j])>0)
  	{strcpy(t,s[i]);
  	strcpy(s[i],s[j]);
  	strcpy(s[j],t);}
	
 printf("\nDanh sach ten sau khi chuan hoa va sap xep\n");
 	for(i=0;i<n;i++) {
	puts(s[i]); }
}
 
