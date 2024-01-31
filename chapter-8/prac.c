#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp=fopen("abc.txt","r");
    fflush(fp);
    return 0;
}
