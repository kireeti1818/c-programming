#include<stdio.h>
#define MAX_LINE 1000
void reverse(int i,int j,char s[])
{
    if (j<i)return;
    char c;
    c=s[i];
    s[i]=s[j];
    s[j]=c;
    return reverse(++i,--j,s);
}
int main()
{
    char s[MAX_LINE];
    int i=0;
    char c;
    while((c=getchar())!='\n')
    {
        s[i++]=c;
    }
    s[i]='\0';
    reverse(0,--i,s);
    printf("%s",s);
    return 0;
}
