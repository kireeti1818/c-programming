#include <stdio.h>
int concat(char *a, char *b)
{
    int i=0;
    while(*a++!='\0');
    while(*b++!='\0') i++;
    a--;
    b--;
    for(;i>0;i--)
    {
        --a;--b;
        if(*a!=*b)
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    char string1[20]="helloworld";
    char string2[]="world";
    char *pointerofstring1=string1,*pointerofstring2=string2;
    int k = concat(pointerofstring1,pointerofstring2);
    printf("%d",k);
    return 0;
}
