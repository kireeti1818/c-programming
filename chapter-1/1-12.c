#include <stdio.h>

int main()
{
    int count=0;
    char c;
    for(;(c=getchar())!=EOF;)
    {
        if(c==' ' || c=='\t' || c=='\n')
        {
            count++;
        }
        else
        {
            count=0;
            putchar(c);
        }
        if (count==1)
        {
            putchar('\n');
        }
    }
    return 0;
}
