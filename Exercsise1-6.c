#include <stdio.h>

int main() {
    int c = getchar();
    
    c = (c != EOF);
    printf("%d", c);
    return 0;
}

