#include <stdio.h>

// Function to check if a character is an upper charcter or not
int isupper1(char c) {
    if (c < 'A' || c > 'Z')   
        return 0;               // Return 0 if not an uppercase letter
    else
        return 1;               // Return 1 if an uppercase letter
}

int main() {
    char c;

    while ((c = getchar()) != EOF && c != '\n') {
        if (isupper1(c) == 1)
            printf("true\n");   
        else
            printf("false\n");  /
    }

    return 0;
}
