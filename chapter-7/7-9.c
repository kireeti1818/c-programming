#include <stdio.h>
int isupper1(char c) {
    if (c < 'A' || c > 'Z')
        return 0;
    else
        return 1;
}
int main() 
{
    char c;
    while ((c = getchar()) != EOF && c!='\n') 
    {
        if (isupper1(c) == 1)
            printf("true\n");
        else
            printf("false\n");
    }
    return 0;
}

