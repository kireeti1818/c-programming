#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL 100
int sp = 0;
double val[MAXVAL];
double pop(void) 
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("stack empty\n");
        return 0.0;
    }
}
void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("stack full,can't push \n");
}
int getop(char s[]) {
    int c, i;
    static int lastc = 0;

    if (lastc == 0)
        c = getchar();
    else {
        c = lastc;
        lastc = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t')
        c = getchar();

    s[1] = '\0';

    if (!isdigit(c) && c != '.')
        return c;

    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getchar()));
    if (c == '.')
        while (isdigit(s[++i] = c = getchar()));
    s[i] = '\0';

    if (c != EOF)
        lastc = c;

    return NUMBER;
}

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                break;
            case '\n':
                printf("\t%.8g\n", pop());
                break;
            default:
                printf("unknown command \n");
                break;
        }
    }
    return 0;
}







