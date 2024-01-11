
#include <stdio.h>
#include <ctype.h>
#define SIZE 20
/* getint: get next integer from input into *pn */
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
int getint(int *pn)
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
    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
}
int main()
{
    int n, array[SIZE], getint(int *);
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++);
    printf("------\n");
    for(int i=0;i<n;i++)printf("%d\n",array[i]);
    return 0;
}

