#include <ctype.h>
#include <stdio.h>
#define MAXLEN 100
#define OCTLEN 4    

int increment(int a, int n) 
{
    if (a + n < MAXLEN)
        return a + n;
    else 
    {
        putchar('\n');
        return n;
    }
}

int main()
{
    int c;
    int p = 0; 
    while ((c = getchar()) != EOF)
        if ( c == ' ' || iscntrl(c)) 
        {
            p = increment(p , OCTLEN);
            printf("\\%03o", c);
            if (c == '\n') p = 0;
            printf("\n");
        } 
        else 
        {
            p = increment(p, 1);
            printf("%c",c);
        }
    return 0;
}
