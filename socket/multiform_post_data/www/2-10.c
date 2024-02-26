#include <stdio.h>

int upperToLower(int c);

int main()
{
    int c;

    while ((c=getchar())!=EOF)
    {
        putchar(upperToLower(c));
    }
}

int upperToLower(int c) 
{
       	return c>='A' && c<='Z' ? c+'a'-'A':c; 
}

