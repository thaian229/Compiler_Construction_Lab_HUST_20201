#include<stdio.h>
#include<string.h>
int main()
{  char s[100], t[100];
   int c = 0, d = 0;
   printf("Nhap xau can chuan hoa\n");
   gets(s);
	while (s[c]==' ')c++;
	while (s[c] != '\0')
   {
      if (!(s[c] == ' ' && s[c+1] == ' ')) {
        t[d] = s[c];
        d++;
      }
      c++;
   }
 
   if(t[d-1]==' ')t[d-1]='\0';else t[d] = '\0';
   strcpy(s,t);
   printf("Xau sau khi chuan hoa\n%s***\n", s);//In them dau * de dam bao cac dau cach ben phai da bi loai
 
   return 0;
}
 
