#include <stdio.h>

int main() {
    int blank,tab,newline;
    char c;
    for(;(c=getchar())!=EOF;){
        if(c=='\t')
        {
            putchar('\\');
            putchar('t');
        }
        else if (c=='\b')
        {
            putchar('\\');
            putchar('b');
        }
        else if (c=='\\')
        {
            putchar('\\');
            putchar('\\');
        }
        else
        {
            putchar(c);
        }
    }
    return 0;
}

