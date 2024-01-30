#include <stdio.h>
#include <ctype.h>
#define SIZE 20
double val[SIZE];
int buf=0;
char x;
char getch()
{
    char c;
    if (buf==1)
    {
        c=x;
        buf=0;
    }
    else
    {
        c=getchar();
    }
    return c;
}
void ungetch(char c)
{
    if (buf==1) printf("buffer is full");
    else x=c;
}
int getdouble(double *pn)
{
    int c, sign;
    while (isspace(c = getch()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); 
    return 0;
    }
    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-') c = getch();
    *pn = 0;
    for (; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    if (c=='.')
    {
        int k=1;
        c=getch();
        for (; isdigit(c); c = getch()){
            *pn = 10 * *pn + (c - '0');
            k*=10;
        }
        *pn=*pn/(float)k;
    }
    
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}
int main()
{
    double array[SIZE];
    int n;
    for (n = 0; n < SIZE && getdouble(&array[n]) != EOF; n++);
    printf("------\n");
    for(int i=0;i<n;i++)printf("%g\n",array[i]);
    return 0;
}

