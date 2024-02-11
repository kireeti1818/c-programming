//Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank. 

#include <stdio.h>

int main() {
    int space=0;
    char c;
    for(;(c=getchar())!=EOF;)
    {
        if(space==0)
        putchar(c);
        if (c==' ')
        {
            space=1;
        }
        else
        {
            space=0;
        }
    }
    return 0;
}

