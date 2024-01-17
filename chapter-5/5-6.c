#include <stdio.h>
void strindex1(char * a, char *b)
{
    char *aa=a,*a2=a,*bb=b;
    int k=0;
    while(*a!='\0')
    {
        while(*b!='\0')
        {
            if(*b!=*a)
            {
                k=1;
                break;
            }
            // printf("%c %c\n",*a,*b);
            a++;
            b++;
        }
        if(k==1)
        {
            a=++aa;
            b=bb;
            k=0;
        }
        else
        {
            printf("%ld",a-a2-(b-bb));
            break;
        }
    }
}
void reverse(char * a)
{
        char *b= a;
        while(*a++!='\0');
        a=a-2;
        // printf("%c %c\n",*(a-1),*b);
        while(b<a)
        {
            char c= *a ;
            *a=*b;
            *b=c;
            b++;a--;
        }
}

int atoi1(char * a)
{
    int val =0;
    while(*a!='\0')
    {
        val= val*10+ (*a++ - '0');
    }
    return val;
}
void itoa1(char *a,int n)
{
        char *b= a;
        while(n!=0)
        {
                *a++=n%10+'0';
                n=n/10;
        }
        *a='\0';
        reverse(b);

}
int main()
{
    int a;
    char s[30];
    char str[20]="1255";
    char str1[20]="121255";
    a=atoi1(str);
    printf("%d\n",a);
    itoa1(s,a);
    printf("%s\n",s);
    strindex1(str1,str);
    return 0;
}

