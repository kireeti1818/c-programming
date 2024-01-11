#include<stdio.h>
int getch();
void ungetch(int c);
int buf;
int bufp = 0;    
int main() {
    int c;
    c='*';
    ungetch(c);
    while ((c = getch()) != EOF)
        putchar(c);
    return 0;
}

int getch() {
    return (bufp-- > 0) ? buf : getchar();
}

void ungetch(int c) {
    if (bufp >0)
        printf("too many characters \n");
    else{
        buf = c;
	bufp++;
    }
}
