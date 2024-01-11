#include <stdio.h>

int main() {
    int blank,tab,newline;
    char c;
    for(;(c=getchar())!=EOF;){
        if(c=='\t')
        {
            tab++;
        }
        else if (c==' ')
        {
            blank++;
        }
        else if (c=='\n')
        {
            newline++;
        }
    }
    printf("\nblanks %d\ntab %d\nnewline %d ",blank,tab,newline);
    return 0;
}

