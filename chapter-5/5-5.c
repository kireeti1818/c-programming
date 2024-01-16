#include <stdio.h>
void strncatfun(char *a, char *b,int n)
{
    while(*a++!='\0');
    a--;
    int i=0;
    while(i!=n && (*a++=*b++)!='\0') i++;
}
int strncmpfun(char *a, char *b,int n)
{
    int i=0;
    for(;i<n;i++)
    {
        if (*a++!=*b++) return 0;
    }
    return 1;

}
void strncpyfun(char *a, char *b,int n)
{
    int i=0;
    for(;i<n;i++)
    {
        *a++=*b++;
    }
    *a='\0';
}
int main()
{
    char x[20]="hello";
    char y[]="hellworld";
    char z[20];
    strncatfun(x,y,4);
    printf("%s\n",x);
    printf("%d\n",strncmpfun(x,y,4));
    strncpyfun(z,y,3);
    printf("%s\n",z);
    return 0;
}
