#include <stdio.h>
void concat(char *a, char *b)
{
    while(*a++!='\0');
    a--;
    while((*a++=*b++)!='\0');
}
int main()
{
    char x[20]="hello";
    char y[]="World";
    char *a=x,*b=y;
    concat(a,b);
    printf("%s",a);
    return 0;
}
